//
// Created by Furkat MALLABAEV on 4/24/18.
//

#ifndef AVM_INT8_H
# define AVM_INT8_H

# include <sstream>
# include "IOperand.h"
# include "OpFactory.h"
# include "Exception.h"

template <typename T>
class Operand : public IOperand {

public:
	Operand(T value, eOperandType type, int prec);
	Operand(Operand<T> const & rhs);
	~Operand();

	int				getPrecision(void) const;
	eOperandType	getType(void) const;

	Operand<T>	&operator=(Operand<T> const & rhs);

	IOperand const	*operator+(IOperand const & rhs) const;
	IOperand const	*operator-(IOperand const & rhs) const;
	IOperand const	*operator*(IOperand const & rhs) const;
	IOperand const	*operator/(IOperand const & rhs) const;
	IOperand const	*operator%(IOperand const & rhs) const;
	IOperand const	*operator&(IOperand const & rhs) const;
	IOperand const	*operator|(IOperand const & rhs) const;
	IOperand const	*operator^(IOperand const & rhs) const;
	bool            operator==(IOperand const & rhs) const;

	std::string const	&toString(void) const;

private:
	Operand();
	T				_val;
	eOperandType	_type;
	int 			_prec;
	std::string		_str;
	OpFactory		_factory;
};

template <typename T>
Operand<T>::Operand() : _type(Int32), _prec(2), _val(0), _str("0") {}

template <typename T>
Operand<T>::Operand(T value, eOperandType type, int prec) : _val(value), _type(type), _prec(prec) {
	std::ostringstream	ss;

	if (type == Int8)
		ss << static_cast<int>(value);
	else
		ss << value;
	_str = ss.str();
}

template <typename T>
Operand<T>::Operand(Operand<T> const & rhs) {
	*this = rhs;
}

template <typename T>
Operand<T>::~Operand() {}

template <typename T>
int 	Operand<T>::getPrecision() const {
	return (_prec);
}

template <typename T>
eOperandType	Operand<T>::getType() const {
	return (_type);
}

template <typename T>
Operand<T>	&Operand<T>::operator=(Operand<T> const & rhs) {
	_val = rhs._val;
	_type = rhs._type;
	_prec = rhs._prec;
	_str = rhs._str;
	return (*this);
}

template <typename T>
IOperand const	*Operand<T>::operator+(IOperand const & rhs) const {
	eOperandType	newType;
	double			rval = std::stod(rhs.toString());

	if (this->getPrecision() > rhs.getPrecision())
		newType = this->getType();
	else
		newType = rhs.getType();
	return (_factory.createOperand(newType, std::to_string(_val + rval)));
}

template <typename T>
IOperand const	*Operand<T>::operator-(IOperand const & rhs) const {
	eOperandType	newType;
	double			rval = std::stod(rhs.toString());

	if (this->getPrecision() > rhs.getPrecision())
		newType = this->getType();
	else
		newType = rhs.getType();
	return (_factory.createOperand(newType, std::to_string(_val - rval)));
}

template <typename T>
IOperand const	*Operand<T>::operator*(IOperand const & rhs) const {
	eOperandType	newType;
	double			rval = std::stod(rhs.toString());

	if (this->getPrecision() > rhs.getPrecision())
		newType = this->getType();
	else
		newType = rhs.getType();
	return (_factory.createOperand(newType, std::to_string(_val * rval)));
}

template <typename T>
IOperand const	*Operand<T>::operator/(IOperand const & rhs) const {
	eOperandType	newType;
	double			rval = std::stod(rhs.toString());

	if (rval == 0)
		throw Exception("Division by zero");
	if (this->getPrecision() > rhs.getPrecision())
		newType = this->getType();
	else
		newType = rhs.getType();
	return (_factory.createOperand(newType, std::to_string(_val / rval)));
}

template <typename T>
IOperand const	*Operand<T>::operator%(IOperand const & rhs) const {
	eOperandType	newType;
	int32_t			rval = std::stoi(rhs.toString());

	if (rval == 0)
		throw Exception("Modulo by zero");
	if (this->getPrecision() > rhs.getPrecision())
		newType = this->getType();
	else
		newType = rhs.getType();
	return (this->_factory.createOperand(newType, std::to_string(static_cast<int32_t >(_val) % rval)));
}

template <typename T>
IOperand const	*Operand<T>::operator&(IOperand const &rhs) const {
	eOperandType	newType;
	double			rval = std::stod(rhs.toString());

	if (this->getPrecision() > rhs.getPrecision())
		newType = this->getType();
	else
		newType = rhs.getType();
	return (_factory.createOperand(newType, std::to_string(_val & rval)));
}

template <typename T>
IOperand const	*Operand<T>::operator|(IOperand const &rhs) const {
	eOperandType	newType;
	double			rval = std::stod(rhs.toString());

	if (this->getPrecision() > rhs.getPrecision())
		newType = this->getType();
	else
		newType = rhs.getType();
	return (_factory.createOperand(newType, std::to_string(_val | rval)));
}

template <typename T>
IOperand const	*Operand<T>::operator^(IOperand const &rhs) const {
	eOperandType	newType;
	double			rval = std::stod(rhs.toString());

	if (this->getPrecision() > rhs.getPrecision())
		newType = this->getType();
	else
		newType = rhs.getType();
	return (_factory.createOperand(newType, std::to_string(_val ^ rval)));
}

template <typename T>
bool		Operand<T>::operator==(IOperand const &rhs) const {
	if (_type == rhs.getType() && toString() == rhs.toString())
		return (true);
	return (false);
}

template <typename T>
std::string const	&Operand<T>::toString(void) const {
	return (_str);
}

#endif //AVM_INT8_H
