//
// Created by Furkat MALLABAEV on 4/26/18.
//

#include <iostream>
#include <sstream>
#include "../includes/AVM.h"
#include "../includes/Exception.h"

AVM::AVM(void) : _count(0) {
	_funcs2[0] = &AVM::push;
	_funcs2[1] = &AVM::assert;
	_funcs[0] = &AVM::pop;
	_funcs[1] = &AVM::dump;
	_funcs[2] = &AVM::add;
	_funcs[3] = &AVM::sub;
	_funcs[4] = &AVM::mul;
	_funcs[5] = &AVM::div;
	_funcs[6] = &AVM::mod;
	_funcs[7] = &AVM::print;
	_funcs[8] = &AVM::bit_and;
	_funcs[9] = &AVM::bit_or;
	_funcs[10] = &AVM::bit_xor;
	_funcs[11] = &AVM::exit_m;
	_verbose = false;
}

AVM::AVM(AVM const &rhs) : _count(0) {
	*this = rhs;
	_funcs2[0] = &AVM::push;
	_funcs2[1] = &AVM::assert;
	_funcs[0] = &AVM::pop;
	_funcs[1] = &AVM::dump;
	_funcs[2] = &AVM::add;
	_funcs[3] = &AVM::sub;
	_funcs[4] = &AVM::mul;
	_funcs[5] = &AVM::div;
	_funcs[6] = &AVM::mod;
	_funcs[7] = &AVM::print;
	_funcs[8] = &AVM::bit_and;
	_funcs[9] = &AVM::bit_or;
	_funcs[10] = &AVM::bit_xor;
	_funcs[11] = &AVM::exit_m;
	_verbose = false;
}

AVM::~AVM() {
	for (auto i = _containter.begin(); i != _containter.end(); ++i) {
		delete *i;
	}
}

AVM	&AVM::operator=(AVM const &rhs) {
	_count = rhs._count;
	_containter = rhs._containter;
	_verbose = rhs._verbose;
	return (*this);
}

void	AVM::push(eOperandType type, std::string const &val) {
	_containter.push_front(_factory.createOperand(type, val));
	_count++;
	if (_verbose == true)
		std::cout << "\033[0;33mPush value \033[0;36m" << val << "\033[0m" << std::endl;
}

void	AVM::pop() {
	if (!_count)
		throw Exception("Pop on empty stack");
	if (_verbose == true)
		std::cout << "\033[0;33mPop value \033[0;36m" << (*_containter.begin())->toString() << "\033[0m" << std::endl;
	delete *_containter.begin();
	_containter.pop_front();
	_count--;
}

void	AVM::dump() {
	if (_verbose == true)
		std::cout << "\033[0;33mDump start :\033[0m" << std::endl;
	for (std::list<IOperand const *>::iterator i = _containter.begin(); i != _containter.end(); ++i) {
		if (_verbose == true)
			std::cout << "	";
		std::cout << "\033[0;36m" << (*i)->toString() << "\033[0m" << std::endl;
	}
	if (_verbose == true)
		std::cout << "\033[0;33mDump end.\033[0m" << std::endl;
}

void	AVM::assert(eOperandType type, std::string const &val) {
	if (!_count)
		throw Exception("Assert on empty stack");
	IOperand const *top = *(_containter.begin());
	IOperand const *assert = _factory.createOperand(type, val);
	if (!(*top == *assert))
		throw Exception("Assert is not true");
	if (_verbose == true)
		std::cout << "\033[0;33mAssert value \033[0;36m" << val << " success\033[0m" << std::endl;
}

void	AVM::add() {
	IOperand const	*newOp;

	if (_count < 2)
		throw Exception("Too few elements on the stack");
	IOperand const	*tmp = *(_containter.begin());
	_containter.pop_front();
	newOp = *tmp + *(*(_containter.begin()));
	if (_verbose == true)
		std::cout << "\033[0;33mAddition : \033[0;36m"
				  << (*_containter.begin())->toString() << " + " << tmp->toString()
				  << " = " << newOp->toString() << "\033[0m" << std::endl;
	delete *_containter.begin();
	delete tmp;
	_containter.pop_front();
	_containter.push_front(newOp);
	_count--;
}

void	AVM::sub() {
	IOperand const	*newOp;

	if (_count < 2)
		throw Exception("Too few elements on the stack");
	IOperand const	*tmp = *(_containter.begin());
	_containter.pop_front();
	newOp = *tmp - *(*(_containter.begin()));
	if (_verbose == true)
		std::cout << "\033[0;33mSubtraction : \033[0;36m"
				  << (*_containter.begin())->toString() << " - " << tmp->toString()
				  << " = " << newOp->toString() << "\033[0m" << std::endl;
	delete *_containter.begin();
	delete tmp;
	_containter.pop_front();
	_containter.push_front(newOp);
	_count--;
}

void	AVM::mul() {
	IOperand const	*newOp;

	if (_count < 2)
		throw Exception("Too few elements on the stack");
	IOperand const	*tmp = *(_containter.begin());
	_containter.pop_front();
	newOp = *tmp * *(*(_containter.begin()));
	if (_verbose == true)
		std::cout << "\033[0;33mMultiplication : \033[0;36m"
				  << (*_containter.begin())->toString() << " * " << tmp->toString()
				  << " = " << newOp->toString() << "\033[0m" << std::endl;
	delete *_containter.begin();
	delete tmp;
	_containter.pop_front();
	_containter.push_front(newOp);
	_count--;
}

void	AVM::div() {
	IOperand const	*newOp;

	if (_count < 2)
		throw Exception("Too few elements on the stack");
	IOperand const	*left = *(_containter.begin());
	IOperand const	*right = *++_containter.begin();
	newOp = *right / *left;
	if (_verbose == true)
		std::cout << "\033[0;33mDivision : \033[0;36m"
				  << (*_containter.begin())->toString() << " / " << left->toString()
				  << " = " << newOp->toString() << "\033[0m" << std::endl;
	delete right;
	delete left;
	_containter.pop_front();
	_containter.pop_front();
	_containter.push_front(newOp);
	_count--;
}

void	AVM::mod() {
	IOperand const	*newOp;

	if (_count < 2)
		throw Exception("Too few elements on the stack");
	IOperand const	*left = *(_containter.begin());
	IOperand const	*right = *++_containter.begin();
	newOp = *right % *left;
	if (_verbose == true)
		std::cout << "\033[0;33mModulation : \033[0;36m"
				  << (*_containter.begin())->toString() << " % " << left->toString()
				  << " = " << newOp->toString() << "\033[0m" << std::endl;
	delete right;
	delete left;
	_containter.pop_front();
	_containter.pop_front();
	_containter.push_front(newOp);
	_count--;
}

void	AVM::print() {
	char	c;

	if (!_count)
		throw Exception("Print on empty stack");
	if ((*(_containter.begin()))->getType() != Int8)
		throw Exception("The top value type is not int8");
	c = static_cast<char>(std::stoi((*(_containter.begin()))->toString()));
	if (_verbose == true)
		std::cout << "\033[0;33mPrint : " << std::endl;
	std::cout << "\033[0;32m" << c << "\033[0m" << std::endl;
}

void	AVM::bit_and() {
	IOperand const	*newOp;

	if (_count < 2)
		throw Exception("Too few elements on the stack");
	if ((*_containter.begin())->getPrecision() > 3
		|| (*++_containter.begin())->getPrecision() > 3)
		throw Exception("Bitwise operation for float or double make no sense");
	IOperand const	*tmp = *(_containter.begin());
	_containter.pop_front();
	newOp = *(*(_containter.begin())) & *tmp;
	if (_verbose == true)
		std::cout << "\033[0;33mBitwise and : \033[0;36m"
				  << (*_containter.begin())->toString() << " & " << tmp->toString()
				  << " = " << newOp->toString() << "\033[0m" << std::endl;
	delete *_containter.begin();
	delete tmp;
	_containter.pop_front();
	_containter.push_front(newOp);
	_count--;
}

void	AVM::bit_or() {
	IOperand const	*newOp;

	if (_count < 2)
		throw Exception("Too few elements on the stack");
	if ((*_containter.begin())->getPrecision() > 3
		|| (*++_containter.begin())->getPrecision() > 3)
		throw Exception("Bitwise operation for float or double make no sense");
	IOperand const	*tmp = *(_containter.begin());
	_containter.pop_front();
	newOp = *(*(_containter.begin())) | *tmp;
	if (_verbose == true)
		std::cout << "\033[0;33mBitwise or : \033[0;36m"
				  << (*_containter.begin())->toString() << " | " << tmp->toString()
				  << " = " << newOp->toString() << "\033[0m" << std::endl;
	delete *_containter.begin();
	delete tmp;
	_containter.pop_front();
	_containter.push_front(newOp);
	_count--;
}

void	AVM::bit_xor() {
	IOperand const	*newOp;

	if (_count < 2)
		throw Exception("Too few elements on the stack");
	if ((*_containter.begin())->getPrecision() > 3
		|| (*++_containter.begin())->getPrecision() > 3)
		throw Exception("Bitwise operation for float or double make no sense");
	IOperand const	*tmp = *(_containter.begin());
	_containter.pop_front();
	newOp = *(*(_containter.begin())) ^ *tmp;
	if (_verbose == true)
		std::cout << "\033[0;33mBitwise xor : \033[0;36m"
				  << (*_containter.begin())->toString() << " ^ " << tmp->toString()
				  << " = " << newOp->toString() << "\033[0m" << std::endl;
	delete *_containter.begin();
	delete tmp;
	_containter.pop_front();
	_containter.push_front(newOp);
	_count--;
}

void	AVM::exit_m() {
	for (auto i = _containter.begin(); i != _containter.end(); ++i) {
		delete *i;
	}
	if (_verbose == true)
		std::cout << "\033[0;33mExit" << std::endl;
	exit(0);
}

void	AVM::start_execute(std::string const &instructions) {
	std::istringstream	istr(instructions);
	std::string			line;
	std::string			val;
	eInstructions		instruction;
	eOperandType		type;
	size_t				count_line = 0;


	while (std::getline(istr, line))
	{
		count_line++;
		if (line.size() > 0 && line[0] != ';')
		{
			try {
				instruction = _parser.parse_line(line, type, val);
				if (instruction == Push || instruction == Assert)
					((this->*_funcs2[instruction - 12]))(type, val);
				else
					((this->*_funcs[instruction]))();
			}
			catch (std::exception & e)
			{
				std::cout << "\033[0;31mline " << count_line << " : Error : " << e.what() << "\033[0m" << std::endl;
				if (_verbose == false)
					this->exit_m();
			}
		}
	}
	throw Exception("Exit command missing");
}

void	AVM::verbose(bool val) {
	_verbose = val;
}
