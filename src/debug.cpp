#include <iostream>
#include <vector>
#include "debug.hpp"


void printToken(TokenType type, std::vector<uint8_t> data) {
	switch (type) {
		case TOKEN_ERROR: {
			std::cout << "TOKEN_ERROR" << std::endl;
			break;
		}
		case TOKEN_NUMBER: {
			std::cout << "TOKEN_NUMER: ";
			int* loc = (int*)(&data[0]);
			std::cout << *loc << std::endl;
			break;
		}
		case TOKEN_STRING: {
			std::cout << "TOKEN_STRING: ";
			for (uint8_t c : data) {
				std::cout << (char) c;
			}
			std::cout << std::endl;
			break;
		}
		case TOKEN_VARIABLE:
			std::cout << "TOKEN_VARIABLE: ";
			for (uint8_t c : data) {
				std::cout << (char) c;
			}
			std::cout << std::endl;
			break;
		case TOKEN_FOR:
			std::cout << "TOKEN_FOR" << std::endl;
			break;
		case TOKEN_WHILE:
			std::cout << "TOKEN_WHILE" << std::endl;
			break;
		case TOKEN_FUNC:
			std::cout << "TOKEN_FUNC" << std::endl;
			break;
		case TOKEN_IF:
			std::cout << "TOKEN_IF" << std::endl;
			break;
		case TOKEN_MINUS:
			std::cout << "TOKEN_MINUS" << std::endl;
			break;
		case TOKEN_PLUS:
			std::cout << "TOKEN_PLUS" << std::endl;
			break;
		case TOKEN_DIVIDE:
			std::cout << "TOKEN_DIVIDE" << std::endl;
			break;
		case TOKEN_MULTIPLY:
			std::cout << "TOKEN_MULTIPLY" << std::endl;
			break;
		case TOKEN_INCLUDE:
			std::cout << "TOKEN_INCLUDE" << std::endl;
			break;
		case TOKEN_RIGHT_PAREN:
			std::cout << "TOKEN_RIGHT_PAREN" << std::endl;
			break;
		case TOKEN_LEFT_PAREN:
			std::cout << "TOKEN_LEFT_PAREN" << std::endl;
			break;
		case TOKEN_RIGHT_BRACKET:
			std::cout << "TOKEN_RIGHT_BRACKET" << std::endl;
			break;
		case TOKEN_LEFT_BRACKET:
			std::cout << "TOKEN_LEFT_BRACKET" << std::endl;
			break;
		case TOKEN_RIGHT_BRACE:
			std::cout << "TOKEN_RIGHT_BRACE" << std::endl;
			break;
		case TOKEN_LEFT_BRACE:
			std::cout << "TOKEN_LEFT_BRACE" << std::endl;
			break;
		case TOKEN_FALSE:
			std::cout << "TOKEN_FALSE" << std::endl;
			break;
		case TOKEN_TRUE:
			std::cout << "TOKEN_TRUE" << std::endl;
			break;
		case TOKEN_EOF:
			std::cout << "TOKEN_EOF" << std::endl;
			break;
		case TOKEN_COMMA:
			std::cout << "TOKEN_COMMA" << std::endl;
			break;
		case TOKEN_SEMICOLON:
			std::cout << "TOKEN_SEMICOLON" <<std::endl;
			break;
		case TOKEN_COLON:
			std::cout << "TOKEN_COLON" << std::endl;
			break;
		default:
			std::cout << "Unknown Token" << std::endl;
	}

}
