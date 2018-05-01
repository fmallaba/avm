//
// Created by Furkat MALLABAEV on 4/26/18.
//

#ifndef AVM_AVM_H
#define AVM_AVM_H

# include <list>
# include "Parse.h"
# include "OpFactory.h"

class AVM {
public:
	typedef void(AVM::*func)();
	typedef void(AVM::*func2)(eOperandType, std::string const &);
	AVM(void);
	AVM(AVM const & rhs);
	~AVM(void);

	AVM	&operator=(AVM const & rhs);

	void	start_execute(std::string const & instructions);
	void	verbose(bool val);
private:
	Parse					_parser;
	OpFactory				_factory;
	size_t					_count;
	std::list<IOperand const*>	_containter;
	func					_funcs[12];
	func2					_funcs2[2];
	bool 					_verbose;

	void	push(eOperandType type, std::string const & val);
	void	pop(void);
	void	dump(void);
	void	assert(eOperandType type, std::string const & val);
	void	add(void);
	void	sub(void);
	void	mul(void);
	void	div(void);
	void	mod(void);
	void	print(void);
	void	bit_and(void);
	void	bit_or(void);
	void	bit_xor(void);
	void	exit_m(void);
};


#endif //AVM_AVM_H
