#pragma once
#include <string>
#include <fstream>
#include "..\common\token_t.hpp"
#include "..\common\instr_map_t.hpp"
class lexer_t
{
public:
	lexer_t()
	{

	}
	bool init(const std::string &filepath)
	{
		pos_ = 0;
		if(load(filepath) == false)
			return false;
		len_ = codes_.size();
		return true;
	}
	char lookahead(int index)
	{
		skip_space();
		skip_comment();
		if(pos_ + index >= len_)
			return '\0';
		return codes_[pos_ + index];
	}
	token_t next_token()
	{
		skip_space();
		if(pos_ == len_)
			return get_end_token();
		skip_comment();
		switch(codes_[pos_])
		{
		case '\r':
		case '\n':
			return get_newline_token();
		case '"':
			return get_str_token();
		case '[':
			return get_open_bracket_token();
		case ']':
			return get_close_bracket_token();
		case '{':
			return get_open_brace_token();
		case '}':
			return get_close_brace_token();
		case ',':
			return get_comma_token();
		case ':':
			return get_colon_token();
		default:
			break;
		}
		token_t token = get_token();
		if(token.type_ != token_t::e_ident)
			return token;
		if(strcasecmp(token.str_.c_str(), "SETSTACKSIZE") == 0)
			token.type_ = token_t::e_set_stack_size;
		else if(strcasecmp(token.str_.c_str(),"FUNC") == 0)
			token.type_ = token_t::e_func;
		else if(strcasecmp(token.str_.c_str(), "VAR") == 0)
			token.type_ = token_t::e_var;
		else if(strcasecmp(token.str_.c_str(), "PARAM") == 0)
			token.type_ = token_t::e_param;
		else if(strcasecmp(token.str_.c_str(), "_RETVAL") == 0)
			token.type_ = token_t::e_reg_retval;
		else if(instr_map_t::get_instace().find_opcode(token.str_, NULL))
			token.type_ = token_t::e_instr;

		return token;
	}
private:
	bool load(const std::string &filepath)
	{
		std::ifstream is(filepath, std::ifstream::binary);
		if(!is)
			return false;
		std::string str((std::istreambuf_iterator<char>(is)),
						std::istreambuf_iterator<char>());
		codes_.append(str);
		return true;
	}
	int strcasecmp(const char *s1, const char *s2)
	{
		int c1, c2;
		do
		{
			c1 = tolower(*s1++);
			c2 = tolower(*s2++);
		} while(c1 == c2 && c1 != 0);
		return c1 - c2;
	}
	void skip_comment()
	{
		if(codes_[pos_] == ';')
		{
			while(pos_ < len_)
			{
				if(codes_[pos_] == '\n')
					return;
				pos_++;
			}
		}
	}
	void skip_space()
	{
		while(pos_ < len_)
		{
			if(codes_[pos_] == ' ' || codes_[pos_] == '\t')
			{
				pos_++;
			}
			else break;
		}
	}
	token_t get_str_token()
	{
		token_t token;
		token.type_ = token_t::e_string;
		++pos_;
		while(pos_ < len_)
		{
			if(codes_[pos_] == '"')
			{
				if (token.str_.size() && token.str_.back() == '\\')
				{
					token.str_.push_back(codes_[pos_]);
					++pos_;
					continue;
				}
				++pos_;
				break;
			}
			else
			{
				token.str_.push_back(codes_[pos_]);
				++pos_;
			}
		}
		return token;
	}
	token_t get_open_bracket_token()
	{
		token_t token;
		token.type_ = token_t::e_open_bracket;
		token.str_.push_back(codes_[pos_]);
		++pos_;
		return token;
	}
	token_t get_close_bracket_token()
	{
		token_t token;
		token.type_ = token_t::e_close_bracket;
		token.str_.push_back(codes_[pos_]);
		++pos_;
		return token;
	}
	token_t get_open_brace_token()
	{
		token_t token;
		token.type_ = token_t::e_open_brace;
		token.str_.push_back(codes_[pos_]);
		++pos_;
		return token;
	}
	token_t get_close_brace_token()
	{
		token_t token;
		token.type_ = token_t::e_close_brace;
		token.str_.push_back(codes_[pos_]);
		++pos_;
		return token;
	}

	token_t get_comma_token()
	{
		token_t token;
		token.type_ = token_t::e_comma;
		token.str_.push_back(codes_[pos_]);
		++pos_;
		return token;
	}

	token_t get_end_token()
	{
		token_t token;
		token.type_ = token_t::e_end;
		++pos_;
		return token;
	}

	token_t get_newline_token()
	{
		token_t token;
		token.type_ = token_t::e_new_line;
		token.str_.push_back(codes_[pos_]);
		++pos_;
		return token;
	}

	token_t get_colon_token()
	{
		token_t token;
		token.type_ = token_t::e_colow;
		token.str_.push_back(codes_[pos_]);
		++pos_;
		return token;
	}

	token_t get_token()
	{
		token_t token;
		int i = pos_;
		token.type_ = token_t::e_int;
		bool find_minus = false;
		bool find_point = false;
		bool find_num = false;
		bool find_chat = false;
		while(pos_ < len_)
		{
			char ch = codes_[pos_];
			if(ch >= 'a' && ch <= 'z' ||
			   ch >= 'A' && ch <= 'Z' ||
			   ch == '_')
			{
				if(!!!find_chat&& (find_num || find_minus || find_point))
					token.type_ = token_t::e_invalid;
				find_chat = true;
				token.str_.push_back(codes_[pos_]);
				if(token.type_!= token_t::e_invalid)
					token.type_ = token_t::e_ident;
				++pos_;
			}
			else if('0' <= ch && '9' >= ch)
			{
				find_num = true;
				token.str_.push_back(codes_[pos_]);
				++pos_;
			}
			else if(ch == '-')
			{
				if(find_minus || token.str_.size())
					token.type_ = token_t::e_invalid;
				find_minus = true;
				token.str_.push_back(codes_[pos_]);
				++pos_;
			}
			else if (ch == '.')
			{
				if(find_point || find_chat)
					token.type_ = token_t::e_invalid;
				else if(token.type_ = token_t::e_int)
					token.type_ = token_t::e_float;
				find_point = true;
				token.str_.push_back(codes_[pos_]);
				++pos_;
			}
			else
				break;
		}
		return token;
	}

	std::size_t len_;
	std::size_t pos_;
	std::string codes_;
};