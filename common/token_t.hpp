#pragma once
#include <string>
struct token_t
{
	enum type_t
	{
		e_int = 0,
		e_float,
		e_string,
		//(
		e_quote,
		//
		e_ident,
		//:
		e_colow,
		//[
		e_open_bracket,
		e_close_bracket,
		e_comma,
		//{
		e_open_brace,
		//}
		e_close_brace,
		//\n
		e_new_line,
		

		e_instr,
		e_set_stack_size,
		e_var,
		//Func
		e_func,
		e_param,
		e_reg_retval,

		e_invalid,
		e_end,
	};
	type_t type_;
	std::string str_;
};
