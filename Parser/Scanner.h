#pragma once
#include <string>
#include <istream>
#include <vector>
#include "Tokens.h"

namespace dzml
{

	class Scanner final
	{
	private:
		const char * begin;
		const char * end;
		const char * ptr;
		std::string text_;

	public:
		Scanner(const std::string& text);

		bool Scan(std::vector<Token>&, const char*& error);
		bool Scan(Token& token, const char*& error);
		bool TestKeyword(unsigned int length, TokenType & keyword);
		bool TestStr(const char* target, unsigned int *, bool swallow = false);
		bool TestOp(TokenType& type);

		inline char Peek() const
		{
			return *ptr;
		}

		inline char Next()
		{
			return *ptr++;
		}

		inline bool ReachEnd() const
		{
			return ptr < end;
		}

	};

}
