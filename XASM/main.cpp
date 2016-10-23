#include <string.h>
#include <stdio.h>
#include "lexer_t.hpp"
#include <iostream>

int main()
{
	lexer_t lexer;
	lexer.init("test/test_1.xasm");
	while(true)
	{
		token_t token = lexer.next_token();
		if (token.type_ == token_t::type_t::e_end)
			break;
		std::cout << token.str_ << ";" << token.type_ << "; ";
	}
	getchar();
	return 0;
}