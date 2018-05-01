//
// Created by Furkat MALLABAEV on 4/24/18.
//

#ifndef AVM_IOPERAND_H
# define AVM_IOPERAND_H

# include <string>

typedef enum {
	Int8,
	Int16,
	Int32,
	Float,
	Double
}		eOperandType;

class IOperand {
public:
	virtual int				getPrecision(void) const = 0;
	virtual eOperandType	getType(void) const = 0;

	virtual IOperand const	*operator+(IOperand const & rhs) const = 0;
	virtual IOperand const	*operator-(IOperand const & rhs) const = 0;
	virtual IOperand const	*operator*(IOperand const & rhs) const = 0;
	virtual IOperand const	*operator/(IOperand const & rhs) const = 0;
	virtual IOperand const	*operator%(IOperand const & rhs) const = 0;
	virtual IOperand const	*operator&(IOperand const & rhs) const = 0;
	virtual IOperand const	*operator|(IOperand const & rhs) const = 0;
	virtual IOperand const	*operator^(IOperand const & rhs) const = 0;
	virtual bool            operator==(IOperand const & rhs) const = 0;

	virtual std::string const	&toString(void) const = 0;

	virtual ~IOperand(void) {}
};

#endif //AVM_IOPERAND_H
