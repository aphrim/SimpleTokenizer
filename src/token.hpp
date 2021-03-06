#include <vector>
#ifndef tokenh
#define tokenh

enum TokenType {
	TOKEN_NUMBER, TOKEN_STRING, TOKEN_TRUE, TOKEN_FALSE, TOKEN_VARIABLE,

	TOKEN_FOR, TOKEN_WHILE, TOKEN_FUNC, TOKEN_IF, TOKEN_INCLUDE,

	TOKEN_RIGHT_PAREN, TOKEN_LEFT_PAREN,
	TOKEN_RIGHT_BRACKET, TOKEN_LEFT_BRACKET,
	TOKEN_RIGHT_BRACE, TOKEN_LEFT_BRACE,

	TOKEN_MINUS, TOKEN_PLUS, TOKEN_DIVIDE, TOKEN_MULTIPLY,

	TOKEN_COMMA, TOKEN_COLON, TOKEN_SEMICOLON,	

	TOKEN_ERROR,
	TOKEN_EOF,
};

struct Token {
	TokenType type;
	int line;
	std::vector<uint8_t> data;
};
#endif
