#pragma once
#include <boost/test/included/unit_test.hpp>
#include "ScannerTest.h"
#include "Scanner.h"
#include "Tokens.h"
#include <vector>
#include <iostream>

using namespace boost::unit_test;

using namespace dzml;

const char* TestTxt1 = "let add a b = a + - * / b \n"
"in letrec inc = add 1 \n"
"where := \"abc\\\"cde\"";

const char* TestTxt2 = "323abc";
const char* TestTxt3 = "let ¹þ¹þ = 1";

dzml::TokenType TestType1 [] = {
	TokenType::Let,
	TokenType::Literal,
	TokenType::Literal,
	TokenType::Literal,
	TokenType::Equal,
	TokenType::Literal,
	TokenType::Add,
	TokenType::Sub,
	TokenType::Mul,
	TokenType::Div,
	TokenType::Literal,
	// second line
	TokenType::In,
	TokenType::LetRec,
	TokenType::Literal,
	TokenType::Equal,
	TokenType::Literal,
	TokenType::IntegerNumber,
	TokenType::Where,
	TokenType::Assign,
	TokenType::String,
};

dzml::TokenType TestType3[] = {
	TokenType::Let,
	TokenType::Literal,
	TokenType::Equal,
	TokenType::IntegerNumber,
};

class ScannerTest
{
private:
	std::vector<Token> result1;
	std::vector<Token> result2;
	std::vector<Token> result3;

public:

	void TestMethod1()
	{
		Scanner scanner(TestTxt1);
		std::vector<ScannerError> errors;

		BOOST_TEST(scanner.Scan(result1, errors));
		BOOST_TEST(result1.size() == 20);
	}

	void TestMethod2()
	{
		unsigned int cnt = 0;
		for (auto i = result1.begin();
			i != result1.end(); ++i)
		{
			BOOST_TEST((i->type_ == TestType1[cnt++]));
			std::cout << static_cast<unsigned int >(i->type_) << " ";
		}
		std::cout << std::endl;
	}

	void TestMethod3()
	{
		BOOST_TEST((result1[result1.size() - 1].text_->length() == 10));
	}

	void TestMethod4()
	{
		Scanner scanner(TestTxt2);
		std::vector<ScannerError> errors;

		BOOST_TEST((scanner.Scan(result2, errors) == false));
		BOOST_TEST((errors.size() > 0));

		for (auto i = errors.begin();
			i != errors.end(); ++i)
		{
			std::cout <<
				"line:" << i->line << " " <<
				"offset:" << i->offset << std::endl <<
				i->message << std::endl;
		}
	}

	void TestMethod5()
	{
		Scanner scanner(TestTxt3);
		std::vector<ScannerError> errors;

		BOOST_TEST(scanner.Scan(result3, errors));
	}

	void TestMethod6()
	{
		unsigned int cnt = 0;
		for (auto i = result3.begin();
			i != result3.end(); ++i)
		{
			BOOST_TEST((i->type_ == TestType3[cnt++]));
			std::cout << static_cast<unsigned int >(i->type_) << " ";
		}
		std::cout << std::endl;
	}

};
