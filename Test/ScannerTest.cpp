#include "stdafx.h"
#define BOOST_TEST_MODULE Test
#include <boost/test/unit_test.hpp>
#include "Scanner.h"
#include "Tokens.h"
#include <vector>
#include <iostream>


using namespace boost::unit_test;

using namespace dzml;

const char* TestTxt1 = "let add a b = a + - * / b \n"
"in letrec inc = add 1 'c' \n"
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
	TokenType::Char,
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

BOOST_AUTO_TEST_CASE(Text1TokenizeTest)
{
	std::vector<Token> result;
	Scanner scanner(TestTxt1);
	std::vector<ScannerError> errors;

	BOOST_CHECK(scanner.Scan(result, errors));
	BOOST_CHECK(result.size() == 21);

	unsigned int cnt = 0;
	for (auto i = result.begin();
		i != result.end(); ++i)
	{
		BOOST_CHECK((i->type_ == TestType1[cnt++]));
		std::cout << static_cast<unsigned int >(i->type_) << " ";
	}
	std::cout << std::endl;

	BOOST_TEST((result[result.size() - 1].text_->length() == 10));
}

BOOST_AUTO_TEST_CASE(Text2TokenizeTest)
{
	std::vector<Token> result;
	Scanner scanner(TestTxt2);
	std::vector<ScannerError> errors;

	BOOST_CHECK((scanner.Scan(result, errors) == false));
	BOOST_CHECK((errors.size() > 0));

	for (auto i = errors.begin();
		i != errors.end(); ++i)
	{
		std::cout <<
			"line:" << i->line << " " <<
			"offset:" << i->offset << std::endl <<
			i->message << std::endl;
	}
}

BOOST_AUTO_TEST_CASE(Text3TokenizeTest)
{
	std::vector<Token> result;

	Scanner scanner(TestTxt3);
	std::vector<ScannerError> errors;

	BOOST_CHECK(scanner.Scan(result, errors));

	unsigned int cnt = 0;
	for (auto i = result.begin();
		i != result.end(); ++i)
	{
		BOOST_TEST((i->type_ == TestType3[cnt++]));
		std::cout << static_cast<unsigned int >(i->type_) << " ";
	}
	std::cout << std::endl;
}
