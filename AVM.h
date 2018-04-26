//
// Created by Furkat MALLABAEV on 4/26/18.
//

#ifndef AVM_AVM_H
#define AVM_AVM_H

#include <list>
#include "Parse.h"
#include "OpFactory.h"

class AVM {
public:
	AVM(void);
	AVM(AVM const & rhs);
	~AVM(void);

	AVM	&operator=(AVM const & rhs);

	void	start_execute(std::string const & instructions);
private:
	Parse					_parser;
	OpFactory				_factory;
	size_t					_count;
	std::list<IOperand const*>	_containter;

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
	void	exit_m(void);
};


#endif //AVM_AVM_H
