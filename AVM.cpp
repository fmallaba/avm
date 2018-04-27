//
// Created by Furkat MALLABAEV on 4/26/18.
//

#include <iostream>
#include <sstream>
#include "AVM.h"
#include "Exception.h"

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
}

AVM::~AVM() {
	std::list<IOperand const *>::iterator	it = _containter.begin();
	for (int i = 0; i < _count; ++i) {
		delete *it++;
	}
}

AVM	&AVM::operator=(AVM const &rhs) {
	_count = rhs._count;
	_containter = rhs._containter;
	return (*this);
}

void	AVM::push(eOperandType type, std::string const &val) {
	_containter.push_front(_factory.createOperand(type, val));
	_count++;
}

void	AVM::pop() {
	if (!_count)
		throw Exception("Pop on empty stack");
	_containter.pop_front();
	_count--;
}

void	AVM::dump() {
	for (std::list<IOperand const *>::iterator i = _containter.begin(); i != _containter.end(); ++i) {
		std::cout << (*i)->toString() << std::endl;
	}
}

void	AVM::assert(eOperandType type, std::string const &val) {
	if (!_count)
		throw Exception("Assert on empty stack");
	IOperand const *top = *(_containter.begin());
	IOperand const *assert = _factory.createOperand(type, val);
	if (!(*top == *assert))
		throw Exception("Values are not equal");
}

void	AVM::add() {
	IOperand const	*newOp;

	if (_count < 2)
		throw Exception("Too few elements");
	IOperand const	*tmp = *(_containter.begin());
	_containter.pop_front();
	newOp = *tmp + *(*(_containter.begin()));
	_containter.pop_front();
	_containter.push_front(newOp);
	_count--;
}

void	AVM::sub() {
	IOperand const	*newOp;

	if (_count < 2)
		throw Exception("Too few elements");
	IOperand const	*tmp = *(_containter.begin());
	_containter.pop_front();
	newOp = *tmp - *(*(_containter.begin()));
	_containter.pop_front();
	_containter.push_front(newOp);
	_count--;
}

void	AVM::mul() {
	IOperand const	*newOp;

	if (_count < 2)
		throw Exception("Too few elements");
	IOperand const	*tmp = *(_containter.begin());
	_containter.pop_front();
	newOp = *tmp * *(*(_containter.begin()));
	_containter.pop_front();
	_containter.push_front(newOp);
	_count--;
}

void	AVM::div() {
	IOperand const	*newOp;

	if (_count < 2)
		throw Exception("Too few elements");
	IOperand const	*tmp = *(_containter.begin());
	_containter.pop_front();
	newOp = *(*(_containter.begin())) / *tmp;
	_containter.pop_front();
	_containter.push_front(newOp);
	_count--;
}

void	AVM::mod() {
	IOperand const	*newOp;

	if (_count < 2)
		throw Exception("Too few elements");
	IOperand const	*tmp = *(_containter.begin());
	_containter.pop_front();
	newOp = *(*(_containter.begin())) % *tmp;
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
	std::cout << c << std::endl;
}

void	AVM::bit_and() {
	IOperand const	*newOp;

	if (_count < 2)
		throw Exception("Too few elements");
	IOperand const	*tmp = *(_containter.begin());
	_containter.pop_front();
	newOp = *(*(_containter.begin())) & *tmp;
	_containter.pop_front();
	_containter.push_front(newOp);
	_count--;
}

void	AVM::bit_or() {
	IOperand const	*newOp;

	if (_count < 2)
		throw Exception("Too few elements");
	IOperand const	*tmp = *(_containter.begin());
	_containter.pop_front();
	newOp = *(*(_containter.begin())) | *tmp;
	_containter.pop_front();
	_containter.push_front(newOp);
	_count--;
}

void	AVM::bit_xor() {
	IOperand const	*newOp;

	if (_count < 2)
		throw Exception("Too few elements");
	IOperand const	*tmp = *(_containter.begin());
	_containter.pop_front();
	newOp = *(*(_containter.begin())) ^ *tmp;
	_containter.pop_front();
	_containter.push_front(newOp);
	_count--;
}

void	AVM::exit_m() {
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
					((this->*_funcs2[instruction % 10]))(type, val);
				else
					((this->*_funcs[instruction]))();
			}
			catch (std::exception & e)
			{
				std::cout << "line " << count_line << " : Error : " << e.what() << std::endl;
			}
		}
	}
	throw Exception("Exit command missing");
}
