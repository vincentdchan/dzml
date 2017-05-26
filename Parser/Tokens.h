#pragma once
#include <memory>
#include <string>

#define KEYWORD_TOKENS_DEF(V) \
	V(LetRec, "letrec") \
	V(Let, "let") \
	V(In, "in") \
	V(Where, "where") \
	V(Val, "val") \
	V(And, "and") \
	V(Or, "or") \
	V(If, "if") \
	V(Then, "then") \
	V(Else, "else") \
	V(Case, "case") \
	V(Of, "of") \
	V(Fun, "fun") \
	V(End, "end") \
	V(Mut, "mut")

#define OP_TOKENS_DEF(V) \
	V(LeftParen, "(") \
	V(RightParen, ")") \
	V(LeftBracket, "[") \
	V(RightBracket, "]") \
	V(Comma, ",") \
	V(Add, "+") \
	V(Sub, "-") \
	V(Mul, "*") \
	V(Div, "/") \
	V(Equal, "=") \
	V(Greater, ">") \
	V(Less, "<") \
	V(GreaterEqual, ">=") \
	V(LessEqual, "<=") \
	V(Assign, ":=")

namespace dzml
{

#define DEF_KW(NAME, D) NAME,
#define DEF_OP(NAME, D) NAME,

	enum class TokenType
	{
		White,
		// number
		IntegerNumber,
		HexNumber,
		FloatNumber,
		DoubleNumber,
		// Keywords
		KEYWORD_TOKENS_DEF(DEF_KW)
		// operators
		OP_TOKENS_DEF(DEF_OP)
		// String
		String,
		// literial
		Literal,
		// Lazy,
	};

#undef DEF_KW
#undef DEF_OP

	class Token final
	{
	public:
		Token(TokenType token = TokenType::White) : 
			type_(token)
		{}

		Token(Token&& that);

		unsigned int line_;
		unsigned int offset_;
		TokenType type_;
		std::unique_ptr<std::string> text_;
	};

}
