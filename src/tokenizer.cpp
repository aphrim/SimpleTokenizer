#include <iostream>

#include "chunk.hpp"
#include "token.hpp"
#include "tokenizer.hpp"

//Prints an error.
static void tokenizeError(std::string error, int line) {
	std::cout << "Error on line " << line << " : " << error << std::endl;
}

//Returns whether the character is a letter or an underscore.
static bool isAlpha(char c) {
	return (c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		(c == '_');
}

//Returns whether the character is a number.
static bool isNumber(char c) {
	return (c >= '0' && c <= '9');
}

//Gets the next character.
static char getNext(int& charIndex, std::string& code) {
	if (charIndex + 1 <= code.size()) {
		return code[charIndex++];
	} else {
		return '\0';
	}
}

//Returns the code at an index offset from the current index.
static char peek(int charIndex, std::string& code, int offset) {
	return code[charIndex + offset];
}

//Returns whether the next string after the char index matches the passed in string.
static bool matchString(int& charIndex, std::string code, std::string toMatch) {
	for (int t = 0; t < toMatch.size(); t++) {
		if (peek(charIndex, code, t - 1) != toMatch[t]) {
			return false;
		}
	}
	//If the next character in the code is a character on number then it continues on, and therefor does not match.
	if (isAlpha(peek(charIndex, code, toMatch.size() - 1)) || isNumber(peek(charIndex, code, toMatch.size() - 1))) return false;
	charIndex += toMatch.size() - 1;
	return true;
}

//Creates a token.
static Token* makeToken(int& charIndex, int& line, std::string& code, TokenType type, std::vector<uint8_t> data = {}) {
	Token* token = new Token;
	token->type = type;
	token->line = line;
	token->data = data;
	return token;
}

//Incrememts character index past whitespace.
static void skipWhitespace(int& charIndex, int& line, std::string& code) {
	char c = peek(charIndex, code, 0);
	if (!(c == ' ' || c == '\t' || c == '\n')) return;
	while(true) {
		c = getNext(charIndex, code);
		if (!(c == ' ' || c == '\t' || c == '\n')) {
			charIndex--;
			break;
		}
		if (c == '\n') line++;
	}
	return;
}

//Gets the variable name that is from the charIndex onwards.
static std::string getVariable(int& charIndex, std::string& code) {
	std::string ret;
	charIndex--;
	while(true) {
		char c = code[charIndex];
		if (c == '\0') break;
		if (isAlpha(c) || isNumber(c)) ret.push_back(c);
		else break;
		charIndex++;
	}
	return ret;
}

//Gets the integer number that is in the charIndex onwards.
//This can easily be changed to support other number types, but the code in getToken() would have to be modified slightly.
static int getNumber(int& charIndex, std::string& code) {
	std::string consumedNum;
	charIndex--;
	while(true) {
		char c = code[charIndex];
		if (c == '\0') break;
		if (isNumber(c)) consumedNum.push_back(c);
		else break;
		charIndex++;
	}
	return std::stoi(consumedNum);

}

//Gets the string stored untill the next unescaped ".
static std::string getString(int& charIndex, std::string& code, int& line) {
	std::string ret;
	bool isEscaped = false;
	while(true) {
		char c = code[charIndex];
		if(c == '\0') { tokenizeError("Unterminated String", line); break; }
		if(c == '"' && !isEscaped) break;
		if(c == '\\' && !isEscaped) { isEscaped = true; charIndex++; continue; }
		if(c == '\n') line++;
		ret.push_back(c);
		isEscaped = false;
		charIndex++;
	}
	charIndex++;
	return ret;

}

static Token* getToken(int& charIndex, int& line, std::string& code) {
	skipWhitespace(charIndex, line, code);
	char first = getNext(charIndex, code);
	switch (first) {
		case '(':
                        return makeToken(charIndex, line, code, TOKEN_LEFT_PAREN);
                case ')':
                        return makeToken(charIndex, line, code, TOKEN_RIGHT_PAREN);
                case '{':
                        return makeToken(charIndex, line, code, TOKEN_LEFT_BRACKET);
                case '}':
                        return makeToken(charIndex, line, code, TOKEN_RIGHT_BRACKET);
		case ';':
			return makeToken(charIndex, line, code, TOKEN_SEMICOLON);
		case ':':
			return makeToken(charIndex, line, code, TOKEN_COLON);
		case ',':
			return makeToken(charIndex, line, code, TOKEN_COMMA);
		case '-':
			return makeToken(charIndex, line, code, TOKEN_MINUS);
		case '+':
			return makeToken(charIndex, line, code, TOKEN_PLUS);
		case '/':
			return makeToken(charIndex, line, code, TOKEN_DIVIDE);
		case '*':
			return makeToken(charIndex, line, code, TOKEN_MULTIPLY);
		case '"': {
			std::string str = getString(charIndex, code, line);
			std::vector<uint8_t> tokenData;
			for (char c : str) tokenData.push_back((uint8_t) c);
			return makeToken(charIndex, line, code, TOKEN_STRING, tokenData);
			}
		case '\0':
			return makeToken(charIndex, line, code, TOKEN_EOF);
		case 'f':
			if (matchString(charIndex, code, "false")) return makeToken(charIndex, line, code, TOKEN_FALSE);	
			if (matchString(charIndex, code, "for")) return makeToken(charIndex, line, code, TOKEN_FOR);
			if (matchString(charIndex, code, "func")) return makeToken(charIndex, line, code, TOKEN_FUNC);
			break;
		case 'i':
			if (matchString(charIndex, code, "if")) return makeToken(charIndex, line, code, TOKEN_IF);
			break;
		case 't':
			if (matchString(charIndex, code, "true")) return makeToken(charIndex, line, code, TOKEN_TRUE);
			break;
	}
	if (isAlpha(first)) {
		std::string variableName = getVariable(charIndex, code);
		std::vector<uint8_t> tokenData;
		for (char c : variableName) tokenData.push_back((uint8_t) c);
		Token* token = makeToken(charIndex, line, code, TOKEN_VARIABLE, tokenData);
		return token;
	} else if (isNumber(first)) {
		int number = getNumber(charIndex, code);
		uint8_t tokenArr[5];
		int* loc = (int*)(&tokenArr[0]);
		*loc = number;
		std::vector<uint8_t> tokenData;
		for (uint8_t n : tokenArr) tokenData.push_back(n);
		Token* token = makeToken(charIndex, line, code, TOKEN_NUMBER, tokenData);
		return token;
	} else {
		tokenizeError("Unexpected Character", line);
		return makeToken(charIndex, line, code, TOKEN_ERROR);
	}
}

Chunk* tokenize(std::string& code) {
	Chunk* chunk = new Chunk;
	int cur = 0;
	int line = 0;
	while (true) {
		Token* token = getToken(cur, line, code);
		chunk->tokens.push_back(token);
		if (token->type == TOKEN_EOF) break;
	}
	return chunk;

}
