#pragma once
#include <string>
#include "lexer_t.hpp"
class xasm
{
private:
	struct syntax_error :std::exception
	{
		enum type_t
		{
			e_normal
		};

		syntax_error(type_t type= e_normal)
		{
			type_ = type;
		}
		syntax_error(char ch)
		{
			expect_ = ch;
		}
		char expect_;
		type_t type_;
	};
	struct func_t;
	struct var_t
	{
		var_t(func_t &func)
			:func_(func)
		{
		}
		int index_;
		int size_;
		int stack_index_;
		std::string name_;
		func_t &func_;
	};
	struct label_t 
	{
		int index_;
		int targIndex_;
		std::string name_;
		func_t &func_;
	};
	struct func_t 
	{
		int entry_point_;
		int param_count_;
		int local_data_size_;
		std::string name_;
		func_t()
		{
			local_data_size_ = 0;
			param_count_ = 0;
			param_count_ = 0;
		}
		std::vector<var_t> vars_;
		std::vector<label_t> labels_;
	};
	
public:
	xasm()
	{

	}
	~xasm()
	{

	}
	bool load(const std::string &filepath)
	{
		if(lexer_.init(filepath) == false)
			return false;
	}
	void gen_code()
	{

	}
	void build()
	{
		while(true)
		{

			if(next_token() == token_t::type_t::e_end)
				break;;
			try
			{
				switch(token_.type_)
				{
				case token_t::type_t::e_func:
					handle_func();
				case token_t::type_t::e_var:
					handle_var();
				case token_t::type_t::e_close_brace:
					handle_close_brace();
				}
			}
			catch(syntax_error & e)
			{

			}
			catch(std::exception& e)
			{
			}
		}
	
	}

	

private:
	token_t::type_t next_token()
	{
		token_ = lexer_.next_token();
		return token_.type_;
	}
	void init()
	{
		status_ = e_global;
		current_line_ = 0;
		instr_size_ = 0;
		global_data_size_ = 0;
		current_func_ = func_map_.end();
	}
	void handle_func()
	{
		if(status_ == e_func)
			throw syntax_error();
		status_ = e_func;

		if(next_token() != token_t::e_ident)
			throw syntax_error();

		func_t func;
		func.name_ = token_.str_;
		auto itr = func_map_.insert(std::make_pair(token_.str_, func));
		if(itr.second == false)
			throw syntax_error();
		current_func_ = itr.first;
		while(next_token() == token_t::e_new_line)
		{
			if(token_.str_ == "\n")
				++current_line_;
		}
		if(token_.type_ != token_t::type_t::e_open_brace)
			throw syntax_error();

		++instr_size_;
	}

	void handle_var()
	{
		if(next_token() != token_t::e_ident)
			throw syntax_error();
		int size = 1;
		if(lexer_.lookahead(0) == '[')
		{
			if(next_token() != token_t::e_open_bracket)
				throw syntax_error('[');
			if (next_token() != token_t::e_int)
				throw syntax_error();
			size = atoi(token_.str_.c_str());
			if(size <= 0)
				throw syntax_error();
			if(next_token() != token_t::e_close_bracket)
				throw syntax_error(']');
		}
		int stack_index = 0;
		if(status_ == e_func)
		{
			stack_index = -(current_func_->second.local_data_size_ + 2);
			current_func_->second.local_data_size_ += size;
		}
		else
		{
			stack_index = global_data_size_;
			global_data_size_ += size;
		}
		var_t var(current_func_->second);
		var.name_ = token_.str_;
		var.size_ = size;
		var.stack_index_ = stack_index;
		current_func_->second.vars_.push_back(var);
	}

	void handle_close_brace()
	{
		if(status_ != e_func)
			throw syntax_error();
		status_ = e_global;
	}



	enum 
	{
		e_global,
		e_func,
	} status_;

	std::size_t instr_size_;
	std::size_t global_data_size_;
	std::map<std::string, func_t> func_map_;
	std::map<std::string, func_t>::iterator current_func_;
	std::size_t current_line_;
	token_t token_;
	lexer_t lexer_;
};