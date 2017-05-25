#include <cstring>
#include <memory>
#include "Scanner.h"

#define LOAD_BUF(BUF) \
	memcpy(BUF, ptr, len); \
	buf[len] = 0; \
	ptr += len;

#define DEF_KW(NAME, D) const char * KW_##NAME = D;
#define DEF_OP(NAME, D) const char * OP_##NAME = D;
namespace dzml
{

	KEYWORD_TOKENS_DEF(DEF_KW);
	OP_TOKENS_DEF(DEF_OP);

	Scanner::Scanner(const char* text, int size):
		line_(1), offset_(0)
	{
		unsigned int _size;
		if (size > -1)
			_size = static_cast<unsigned int>(size);
		else
			_size = strlen(text);
		begin = ptr = text;
		end = begin + _size;
	}

	bool Scanner::Scan(std::vector<Token>& result , const char*& error)
	{
		bool hr = true;
		while (!ReachEnd())
		{
			Token token;
			hr = Scan(token, error);
			if (!hr)
				break;
			if (token.type_ != TokenType::White)
			{
				token.line_ = line_;
				token.offset_ = static_cast<unsigned int>(ptr - line_begin_);
				result.push_back(std::move(token));
			}
		}
		return hr;
	}

	bool Scanner::Scan(Token& token, const char*& error)
	{
		unsigned int len = 0;
		char buf[BUFFER_SIZE];
		if (TestWhite(ptr, &len))
		{
			token.type_ = TokenType::White;
			LOAD_BUF(buf);
			if (ContainsLineBreacker(buf))
				IncLine();
			return true;
		} 
		else if (TestInteger(ptr, &len))
		{
			token.type_ = TokenType::IntegerNumber;
			LOAD_BUF(buf);
			token.text_ = std::make_unique<std::string>(buf);
			return true;
		}
		else if (TestHex(ptr, &len))
		{
			token.type_ = TokenType::HexNumber;
			LOAD_BUF(buf);
			token.text_ = std::make_unique<std::string>(buf);
			return true;
		}
		else if (TestFloat(ptr, &len))
		{
			token.type_ = TokenType::FloatNumber;
			LOAD_BUF(buf);
			token.text_ = std::make_unique<std::string>(buf);
			return true;
		}
		else if (TestDouble(ptr, &len))
		{
			token.type_ = TokenType::DoubleNumber;
			LOAD_BUF(buf);
			token.text_ = std::make_unique<std::string>(buf);
			return true;
		}
		else if (TestLiteral(ptr, &len))
		{
			if (TestKeyword(len, token.type_))
				return true;
			if (len < BUFFER_SIZE)
			{
				LOAD_BUF(buf);
				token.type_ = TokenType::Literal;
				token.text_ = std::make_unique<std::string>(buf);
				return true;
			}
			else
			{
				error = "Literal too long.";
				return false;
			}
		}
		else if (TestOp(token.type_))
		{
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

	bool Scanner::ContainsLineBreacker(const std::string& str)
	{
		for (auto i = str.begin(); i != str.end(); ++i)
			if (*i == '\n') return true;
		return false;
	}

}
