#pragma once
#include <string>
#include <istream>
#include <vector>
#include "Tokens.h"
#include "Regex.hpp"

#define BUFFER_SIZE 256

#define SafeAssign(PTR, B) \
	if ((PTR) != nullptr) *(PTR) = B;

namespace dzml
{

	class Scanner final
	{
	private:
		const char * begin;
		const char * end;
		const char * ptr;

		const char * line_begin_;
		unsigned int line_;
		unsigned int offset_;

		bool TestLiteral(const char* txt, unsigned int *num)
		{
			using namespace Regex;
			return 
				Seq<
					Or<'_', IsAlpha>, 
					TestAny<
						Or<
							Or<'_', '\''>,
							Or<IsAlpha, IsDigit>
						>
				>>
				(txt, num);
		}

		bool TestWhite(const char* txt, unsigned int * num)
		{
			using namespace Regex;
			return Or<' ',
				Or<'\r',
				Or<'\n', '\t'>>>(txt, num);
		}

		bool TestInteger(const char* txt, unsigned int * num)
		{
			using namespace Regex;
			return TestMany<IsDigit>(txt, num);
		}

		static bool IsHexPostFixChar(const char* txt, unsigned int *num)
		{
			char ch = *txt;
			if ((ch >= '0' && ch <= '9') ||
				(ch >= 'a' && ch <= 'f') ||
				(ch >= 'A' && ch <= 'F'))
			{
				*num = 1;
				return true;
			}
			else
			{
				*num = 0;
				return false;
			}
		}

		bool TestHex(const char* txt, unsigned int* len)
		{
			using namespace Regex;
			return Seq<'0',
				Seq<'x',
				TestMany<IsHexPostFixChar>>>(txt, len);
		}

		static bool TestDouble(const char* txt, unsigned int* len)
		{
			using namespace Regex;
			return Seq<TestMany<IsDigit>,
				Seq<'.',
				TestAny<IsDigit>>>(txt, len);
		}

		bool TestFloat(const char* txt, unsigned int* len)
		{
			using namespace Regex;
			return Seq<TestDouble, 'f'>(txt, len);
		}

	public:
		Scanner(const char* str, int size = -1);

		bool Scan(std::vector<Token>&, const char*& error);
		bool Scan(Token& token, const char*& error);

	private:
		bool TestKeyword(unsigned int length, TokenType & keyword);
		bool TestStr(const char* target, unsigned int *, bool swallow = false);
		bool TestOp(TokenType& type);

		bool ContainsLineBreacker(const std::string&);

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
			return ptr >= end;
		}

		inline void IncLine()
		{
			++line_;
			line_begin_ = ptr;
			offset_ = 0;
		}

	};

}
