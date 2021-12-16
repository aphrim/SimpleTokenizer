#include <string>
#include <iostream>

#include "tokenizer.hpp"
#include "chunk.hpp"
#include "debug.hpp"

void repl() {
	std::string input;
	std::cout << std::endl << ">";
	getline(std::cin, input);
	Chunk* tokenizedInput = tokenize(input);
	for (int i = 0; i < tokenizedInput->tokens.size(); i++) {
		printToken(tokenizedInput->tokens[i]->type, tokenizedInput->tokens[i]->data);
	}
	repl();
}

int main() {
	repl();
}
