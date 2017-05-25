#include "Tokens.h"

namespace dzml
{

	Token::Token(Token&& that):
		line_(that.line_), offset_(that.offset_),
		type_(that.type_), text_(std::move(that.text_))
	{ }

}