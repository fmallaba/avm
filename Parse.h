//
// Created by Furkat MALLABAEV on 4/25/18.
//

#ifndef AVM_PARSE_H
# define AVM_PARSE_H

#include <string>
#include "IOperand.h"

typedef enum {
	Push,
	Pop,
	Dump,
	Assert,
	Add,
	Sub,
	Mul,
	Div,
	Mod,
	Print,
	Exit
}		eInstructions;

class Parse    {
public:
	Parse(void);
	~Parse(void);

	eInstructions	parse_line(std::string const & line, eOperandType & type, std::string & val);

private:
	eInstructions	get_instruction(std::string const &line, std::string::size_type &pos);
	eOperandType parse_value(std::string const &line, std::string::size_type pos, std::string &val);
	void		get_val(std::string const & line, std::string & val);
};


#endif //AVM_PARSE_H
