//
// Created by Furkat MALLABAEV on 4/24/18.
//

#ifndef AVM_OPFACTORY_H
# define AVM_OPFACTORY_H

# include "IOperand.h"

class OpFactory {
public:
	typedef IOperand const *(OpFactory::*func)(std::string const &) const;
	OpFactory(void);
	~OpFactory(void);

	IOperand const	*createOperand(eOperandType type, std::string const & value) const;

private:
	IOperand const	*createInt8(std::string const & value) const;
	IOperand const	*createInt16(std::string const & value) const;
	IOperand const	*createInt32(std::string const & value) const;
	IOperand const	*createFloat(std::string const & value) const;
	IOperand const	*createDouble(std::string const & value) const;

	func	_funcs[5];
};


#endif //AVM_OPFACTORY_H
