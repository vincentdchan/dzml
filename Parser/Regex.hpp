#pragma once
#include <istream>
#define SafeAssign(PTR, B) \
	if ((PTR) != nullptr) *(PTR) = B;

namespace dzml
{

	namespace Regex
	{
		typedef bool(*MatchFun)(const char * ch, unsigned int *num);
		
		static bool IsDigit(const char * ch, unsigned int * num)
		{
			if (isdigit(*ch))
			{
				SafeAssign(num, 1);
				return true;
			}
			else
			{
				SafeAssign(num, 0);
				return false;
			}
		}

		static bool IsAlpha(const char * ch, unsigned int * num)
		{
			if (isalpha(*ch))
			{
				SafeAssign(num, 1);
				return true;
			}
			else
			{
				SafeAssign(num, 0);
				return false;
			}
		}

		template<char _ch>
		bool Is(const char* txt, unsigned int * num)
		{
			if (*txt == _ch)
			{
				SafeAssign(num, 1);
				return true;
			}
			else
			{
				SafeAssign(num, 0);
				return false;
			}
		}

		template<char _ch>
		bool Not(const char* txt, unsigned int * num)
		{
			if (*txt != _ch)
			{
				SafeAssign(num, 1);
				return true;
			}
			else
			{
				SafeAssign(num, 0);
				return false;
			}
		}

		/*
		 * Test more than 1 case
		 */
		template<MatchFun Tester>
		bool TestAny(const char* txt, unsigned int * num)
		{
			unsigned int cnt = 0, tmp = 0;
			const char* tmp_ptr = txt;
			while (Tester(tmp_ptr, &tmp))
			{
				tmp_ptr += tmp;
				cnt += tmp;
			}
			SafeAssign(num, cnt);
			return true;
		}

		template<MatchFun Tester>
		bool TestMany(const char* txt, unsigned int * num)
		{
			TestAny<Tester>(txt, num);
			return *num == 0 ? false : true;
		}

		template<MatchFun A, MatchFun B>
		bool Or(const char* txt, unsigned int * num)
		{
			return A(txt, num) || B(txt, num);
		}

		template<char A, char B>
		bool Or(const char* txt, unsigned int * num)
		{
			return Is<A>(txt, num) || Is<B>(txt, num);
		}

		template<MatchFun A, char B>
		bool Or(const char* txt, unsigned int * num)
		{
			return A(txt, num) || Is<B>(txt, num);
		}

		template<char A, MatchFun B>
		bool Or(const char* txt, unsigned int * num)
		{
			return Is<A>(txt, num) || B(txt, num);
		}

		template<MatchFun A, MatchFun B>
		bool Seq(const char* txt, unsigned int * num)
		{
			unsigned int cnt = 0;
			unsigned int tmp = 0;
			if (A(txt, &tmp))
			{
				cnt += tmp;
				if (B(txt + cnt, &tmp))
				{
					cnt += tmp;
					SafeAssign(num, cnt)
						return true;
				}
			}
			return false;
		}

		template<char ch, MatchFun fun>
		bool Seq(const char* txt, unsigned int * num)
		{
			return Seq<Is<ch>, fun>(txt, num);
		}

		template<MatchFun fun, char ch>
		bool Seq(const char* txt, unsigned int * num)
		{
			return Seq<Is<ch>, fun>(txt, num);
		}

		template<char ch1, char ch2>
		bool Seq(const char* txt, unsigned int * num)
		{
			return Seq<Is<ch1>, Is<ch2>>(txt, num);
		}

	}

}
