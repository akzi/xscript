#pragma once
#include <string>
#include <vector>
#include <map>
#include <string.h>
#ifdef _WIN32
#define  strupr _strupr
#endif
struct instr_t
{
	enum type_t
	{
		e_mov,

		e_add,
		e_sub,
		e_mul,
		e_div,
		e_mod,
		e_exp,
		e_neg,
		e_inc,
		e_dec,

		e_and,
		e_or,
		e_xor,
		e_not,
		e_shl,
		e_shr,

		e_str_cancat,
		e_get_chat,
		e_set_chat,

		e_jmp,
		e_je,
		e_jne,
		e_jg,
		e_jl,
		e_jge,
		e_jle,

		e_push,
		e_pop,

		e_call,
		e_ret,
		e_call_host,

		e_pause,
		e_exit,
	};
	enum op_flag_t
	{
		e_int = 1,
		e_float = 2,
		e_string = 4,
		e_mem_ref = 8,
		e_label = 16,
		e_func_name = 32,
		e_host_api_call = 64,
		e_reg = 128
	};
	typedef int opcode_flag_t;
	std::string str_;
	std::vector<opcode_flag_t> op_list_;
	type_t type_;
};

class instr_map_t
{
public:
	static instr_map_t &get_instace()
	{
		static instr_map_t inst;
		return inst;
	}
	bool find_opcode(std::string str, instr_t *opcode)
	{
		
		auto itr = opcode_map_.find(strupr((char*)str.c_str()));
		if( itr == opcode_map_.end())
			return false;
		if(opcode)
			*opcode = itr->second;
		return true;
	}
private:
	instr_map_t()
	{
		init_add();
		init_call();
		init_callhost();
		init_concat();
		init_dec();
		init_div();
		init_eq_jmp();
		init_exit();
		init_exp();
		init_get_chat();
		init_greater_eq_jmp();
		init_greater_jmp();
		init_inc();
		init_jmp();
		init_less_eq_jmp();
		init_mod();
		init_mov();
		init_mul();
		init_neg();
		init_neq_jmp();
		init_not();
		init_or();
		init_pause();
		init_pop();
		init_push();
		init_ret();
		init_set_chat();
		init_sh_left();
		init_sh_right();
		init_sub();
		init_xor();
	}

	void init_mov()
	{
		instr_t op;
		op.str_ = "MOV";
		op.type_ = instr_t::e_mov;
		op.op_list_.push_back(instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_float |
							  instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		opcode_map_[op.str_] = op;

	}
	void init_sub()
	{
		instr_t op;
		op.str_ = "SUB";
		op.type_ = instr_t::e_sub;
		op.op_list_.push_back(instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_float |
							  instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		opcode_map_[op.str_] = op;

	}
	void init_mul()
	{
		instr_t op;
		op.str_ = "MUL";
		op.type_ = instr_t::e_mul;
		op.op_list_.push_back(instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_float |
							  instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		opcode_map_[op.str_] = op;

	}
	void init_div()
	{
		instr_t op;
		op.str_ = "DIV";
		op.type_ = instr_t::e_div;
		op.op_list_.push_back(instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_float |
							  instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		opcode_map_[op.str_] = op;

	}
	void init_mod()
	{
		instr_t op;
		op.str_ = "MOD";
		op.type_ = instr_t::e_mod;
		op.op_list_.push_back(instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_float |
							  instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		opcode_map_[op.str_] = op;

	}
	void init_exp()
	{
		instr_t op;
		op.str_ = "EXP";
		op.type_ = instr_t::e_exp;
		op.op_list_.push_back(instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_float |
							  instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		opcode_map_[op.str_] = op;

	}
	void init_neg()
	{
		instr_t op;
		op.str_ = "NEG";
		op.type_ = instr_t::e_neg;
		op.op_list_.push_back(instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		opcode_map_[op.str_] = op;

	}
	void init_inc()
	{
		instr_t inc;
		inc.str_ = "INC";
		inc.type_ = instr_t::e_inc;
		inc.op_list_.push_back(instr_t::op_flag_t::e_mem_ref |
							   instr_t::op_flag_t::e_reg);
		opcode_map_[inc.str_] = inc;

	}

	void init_dec()
	{
		instr_t op;
		op.str_ = "DEC";
		op.type_ = instr_t::e_dec;
		op.op_list_.push_back(instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);

		opcode_map_[op.str_] = op;

	}
	void init_add()
	{
		instr_t op;
		op.str_ = "AND";
		op.type_ = instr_t::e_and;
		op.op_list_.push_back(instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_float |
							  instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		opcode_map_[op.str_] = op;

	}
	void init_or()
	{
		instr_t op;
		op.str_ = "OR";
		op.type_ = instr_t::e_or;
		op.op_list_.push_back(instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_float |
							  instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		opcode_map_[op.str_] = op;

	}
	void init_xor()
	{
		instr_t op;
		op.str_ = "XOR";
		op.type_ = instr_t::e_xor;
		op.op_list_.push_back(instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_float |
							  instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		opcode_map_[op.str_] = op;

	}
	void init_not()
	{
		instr_t op;
		op.str_ = "NOT";
		op.type_ = instr_t::e_not;
		op.op_list_.push_back(instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		opcode_map_[op.str_] = op;

	}
	void init_sh_left()
	{
		instr_t op;
		op.str_ = "SHL";
		op.type_ = instr_t::e_shl;
		op.op_list_.push_back(instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_float |
							  instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		opcode_map_[op.str_] = op;

	}
	void init_sh_right()
	{
		instr_t op;
		op.str_ = "SHR";
		op.type_ = instr_t::e_shr;
		op.op_list_.push_back(instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_float |
							  instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		opcode_map_[op.str_] = op;

	}
	void init_concat()
	{
		instr_t op;
		op.str_ = "CONCAT";
		op.type_ = instr_t::e_str_cancat;
		op.op_list_.push_back(instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		op.op_list_.push_back(instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		opcode_map_[op.str_] = op;

	}
	void init_get_chat()
	{
		instr_t op;
		op.str_ = "GETCHAT";
		op.type_ = instr_t::e_get_chat;
		op.op_list_.push_back(instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		op.op_list_.push_back(instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		opcode_map_[op.str_] = op;

	}
	void init_set_chat()
	{
		instr_t op;
		op.str_ = "SETCHAT";
		op.type_ = instr_t::e_set_chat;
		op.op_list_.push_back(instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		op.op_list_.push_back(instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		opcode_map_[op.str_] = op;

	}
	void init_jmp()
	{
		instr_t op;
		op.str_ = "JMP";
		op.type_ = instr_t::e_jmp;
		op.op_list_.push_back(instr_t::op_flag_t::e_label);
		opcode_map_[op.str_] = op;

	}
	void init_eq_jmp()
	{
		instr_t op;
		op.str_ = "JE";
		op.type_ = instr_t::e_je;
		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_float |
							  instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);

		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_float |
							  instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);

		op.op_list_.push_back(instr_t::op_flag_t::e_label);

		opcode_map_[op.str_] = op;

	}
	void init_neq_jmp()
	{
		instr_t op;
		op.str_ = "JNE";
		op.type_ = instr_t::e_jne;
		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_float |
							  instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);

		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_float |
							  instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);

		op.op_list_.push_back(instr_t::op_flag_t::e_label);

	}
	void init_greater_jmp()
	{
		instr_t op;
		op.str_ = "JG";
		op.type_ = instr_t::e_jg;
		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_float |
							  instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);

		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_float |
							  instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);

		op.op_list_.push_back(instr_t::op_flag_t::e_label);
		opcode_map_[op.str_] = op;

	}
	void init_greater_eq_jmp()
	{
		instr_t op;
		op.str_ = "JGE";
		op.type_ = instr_t::e_jge;
		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_float |
							  instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);

		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_float |
							  instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);

		op.op_list_.push_back(instr_t::op_flag_t::e_label);
		opcode_map_[op.str_] = op;
	}
	void init_less_eq_jmp()
	{
		instr_t op;
		op.str_ = "JLE";
		op.type_ = instr_t::e_jle;
		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_float |
							  instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);

		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_float |
							  instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);

		op.op_list_.push_back(instr_t::op_flag_t::e_label);
		opcode_map_[op.str_] = op;

	}
	void init_push()
	{
		instr_t op;
		op.str_ = "PUSH";
		op.type_ = instr_t::e_push;
		op.op_list_.push_back(instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_float |
							  instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		opcode_map_[op.str_] = op;

	}
	void init_pop()
	{
		instr_t op;
		op.str_ = "POP";
		op.type_ = instr_t::e_pop;
		op.op_list_.push_back(instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		opcode_map_[op.str_] = op;

	}
	void init_call()
	{
		instr_t op;
		op.str_ = "CALL";
		op.type_ = instr_t::e_call;
		op.op_list_.push_back(instr_t::op_flag_t::e_func_name);
		opcode_map_[op.str_] = op;
	}

	void init_ret()
	{
		instr_t op;
		op.str_ = "RET";
		op.type_ = instr_t::e_ret;
		opcode_map_[op.str_] = op;
	}
	void init_callhost()
	{
		instr_t op;
		op.str_ = "CALLHOST";
		op.type_ = instr_t::e_call_host;
		op.op_list_.push_back(instr_t::op_flag_t::e_host_api_call);
		opcode_map_[op.str_] = op;
	}
	void init_pause()
	{
		instr_t op;
		op.str_ = "PAUSE";
		op.type_ = instr_t::e_pause;
		op.op_list_.push_back(instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		opcode_map_[op.str_] = op;
	}
	void init_exit()
	{
		instr_t op;
		op.str_ = "EXIT";
		op.type_ = instr_t::e_exit;
		op.op_list_.push_back(instr_t::op_flag_t::e_int |
							  instr_t::op_flag_t::e_float |
							  instr_t::op_flag_t::e_string |
							  instr_t::op_flag_t::e_mem_ref |
							  instr_t::op_flag_t::e_reg);
		opcode_map_[op.str_] = op;
	}

	std::map<std::string, instr_t> opcode_map_;
};