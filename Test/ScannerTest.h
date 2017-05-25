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
"let inc = add 1";

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
	TokenType::Let,
	TokenType::Literal,
	TokenType::Equal,
	TokenType::Literal,
	TokenType::IntegerNumber,
};

class ScannerTest
{
private:
	std::vector<Token> result_;

public:

	void TestMethod1()
	{
		BOOST_TEST(true);
		Scanner scanner(TestTxt1);
		const char * err_msg;

		BOOST_TEST(scanner.Scan(result_, err_msg));
		BOOST_TEST(result_.size() == 16);
	}

	void TestMethod2()
	{
		unsigned int cnt = 0;
		for (auto i = result_.begin();
			i != result_.end(); ++i)
		{
			BOOST_TEST((i->type_ == TestType1[cnt++]));
			std::cout << static_cast<unsigned int >(i->type_) << " ";
		}
	}

};
