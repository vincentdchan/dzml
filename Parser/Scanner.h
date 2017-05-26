#pragma once
#include <string>
#include <istream>
#include <vector>
#include "Tokens.h"
#include "Regex.hpp"

#define BUFFER_SIZE 512

#define SafeAssign(PTR, B) \
	if ((PTR) != nullptr) *(PTR) = B;

namespace dzml
{

	struct ScannerError
	{
		unsigned int line;
		unsigned int offset;
		const char* message;
	};

	class Scanner final
	{
	private:
		const char * begin;
		const char * end;
		const char * ptr;

		const char * line_begin_;
		unsigned int line_;
		unsigned int offset_;

		static bool TestString(const char* txt, unsigned int *num, const char*& error)
		{
			const char* tmp = txt;
			if (*tmp++ != '"')
				return false;

			char ch;
			while ((ch = *tmp++) != '"')
			{
				if (ch == '\n')
				{
					error = "Line breaker in a string";
					return false;
				}
				else if (ch == '\\')
				{
					tmp++;
				}
			}

			*num = tmp - txt;
			return true;
		}

		inline bool TestChar(const char* txt, unsigned int *num, const char*& error)
		{
			auto tmp = txt;
			if (*tmp++ != '\'') return false;

			if (*tmp == '\\')
				tmp += 2;
			else if (*tmp == '\n')
			{
				error = "A line breaker in a char, try to use escape char \\n.";
				return false;
			}
			else
				tmp++;

			if (*tmp++ != '\'')
			{
				error = "A char must end with \'";
				return false;
			}

			*num = tmp - txt;
			return true;
		}

		static bool TestDigitStart(const char* txt, unsigned *num)
		{
			using namespace Regex;
			return Seq <IsDigit,
				TestAny<
					Or<
						Or<'_', '\''>,
						Or<IsAlpha,
							Or<IsDigit, IsAnotherByte>>>>>(txt, num);
		}

		static bool TestLiteral(const char* txt, unsigned int *num)
		{
			using namespace Regex;
			return 
				Seq<
					Or<'_', Or<IsAlpha, IsAnotherByte>>, 
					TestAny<
						Or<
							Or<'_', '\''>,
							Or<IsAlpha, 
								Or<IsDigit, IsAnotherByte>>
						>
				>>
				(txt, num);
		}

		static bool TestWhite(const char* txt, unsigned int * num)
		{
			using namespace Regex;
			return Or<' ',
				Or<'\r',
				Or<'\n', '\t'>>>(txt, num);
		}

		static bool TestInteger(const char* txt, unsigned int * num)
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

		static bool TestHex(const char* txt, unsigned int* len)
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

		bool Scan(std::vector<Token>&, std::vector<ScannerError>& errors);

	private:
		bool Scan(Token& token, const char*& error);

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

		/**
		 * if reach the end of file, return false
		 */
		inline bool NextLine()
		{
			while (!ReachEnd())
			{
				if (*ptr++ == '\n')
					return true;
			}
			return false;
		}

	};

}
