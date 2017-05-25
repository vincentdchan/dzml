#include <regex>
#include <cstring>
#include <memory>
#include "Scanner.h"

#define DEF_KW(NAME, D) const char * KW_##NAME = D;
#define DEF_OP(NAME, D) const char * OP_##NAME = D;
namespace dzml
{

	std::regex white("^[ \r\n\t]");
	std::regex string("^\"[^\n\\\"]*\"");
	std::regex integer_number("^[0-9]+");
	std::regex hex_number("^0x[0-9a-fA-F]+");
	std::regex double_number("^[0-9]+.[0-9]*");
	std::regex float_number("^[0-9]+.[0-9]*f");
	std::regex literal_("[a-zA-Z_][a-zA-Z0-9_']*");

	KEYWORD_TOKENS_DEF(DEF_KW);
	OP_TOKENS_DEF(DEF_OP);

	Scanner::Scanner(const std::string& text):
		text_(text)
	{
		begin = ptr = text.c_str();
		end = begin + text.size();
	}

	bool Scanner::Scan(std::vector<Token>& result , const char*& error)
	{
		bool hr = true;
		while (!ReachEnd())
		{
			Token token;
			hr = Scan(token, error);
			if (!hr) break;
			if (token.type_ != TokenType::White)
				result.push_back(std::move(token));
		}
		return hr;
	}

	bool Scanner::Scan(Token& token, const char*& error)
	{
		std::cmatch cm;
		if (std::regex_match(ptr, cm, white))
		{
			token.type_ = TokenType::White;
			ptr += cm[0].length();
			return true;
		} 
		else if (std::regex_match(ptr, cm, integer_number))
		{
			token.type_ = TokenType::IntegerNumber;
			ptr += cm[0].length();
			token.text_ = std::make_unique<std::string>(
				cm[0].str()
				);
			return true;
		}
		else if (std::regex_match(ptr, cm, hex_number))
		{
			token.type_ = TokenType::HexNumber;
			ptr += cm[0].length();
			token.text_ = std::make_unique<std::string>(
				cm[0].str()
				);
			return true;
		}
		else if (std::regex_match(ptr, cm, float_number))
		{
			token.type_ = TokenType::FloatNumber;
			ptr += cm[0].length();
			token.text_ = std::make_unique<std::string>(
				cm[0].str()
				);
			return true;
		}
		else if (std::regex_match(ptr, cm, double_number))
		{
			token.type_ = TokenType::DoubleNumber;
			ptr += cm[0].length();
			token.text_ = std::make_unique<std::string>(
				cm[0].str()
				);
			return true;
		}
		else if (std::regex_match(ptr, cm, literal_))
		{
			std::string txt = cm[0].str();
			if (TestKeyword(txt.size(), token.type_))
				return true;
			ptr += txt.length();
			token.type_ = TokenType::Literal;
			token.text_ = std::make_unique<std::string>(txt);
			return true;
		}
		else
		{
			error = "Unexpected token.";
			return false;
		}
	}

#define TEST_KW(NAME, D) \
	else if (TestStr(KW_##NAME, &length, false) && \
		length == lit_length) \
	{ \
		type_ = TokenType::NAME; \
		ptr += length; \
		return true; \
	} 

	bool Scanner::TestKeyword(unsigned int lit_length, TokenType & type_)
	{
		unsigned int length;
		if (false);
		KEYWORD_TOKENS_DEF(TEST_KW)
		else return false;
	}

#undef TEST_STR

#define TEST_OP(NAME, D) \
	else if (TestStr(OP_##NAME, nullptr, true)) \
	{ \
		type_ = TokenType::NAME; \
		return true; \
	} 

	bool Scanner::TestOp(TokenType & type_)
	{
		if (false);
		OP_TOKENS_DEF(TEST_OP)
		else return false;
	}

	bool Scanner::TestStr(const char* target, unsigned int* length, bool swallow)
	{
		unsigned int count = 0;
		for (const char* p = target; (*p) != '\0'; ++p)
		{
			if (*p != *(ptr + count)) return false;
			++count;
		}
		if (length != nullptr)
			*length = count;
		if (swallow) ptr += count;
		return true;
	}

}
