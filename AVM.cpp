//
// Created by Furkat MALLABAEV on 4/26/18.
//

#include <iostream>
#include "AVM.h"
#include "Exception.h"

AVM::AVM(void) : _count(0) {}

AVM::AVM(AVM const &rhs) : _count(0) {
	*this = rhs;
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
}

void	AVM::pop() {
	if (!_count)
		throw Exception("Pop on empty stack");
	_containter.pop_front();
}

void	AVM::dump() {
	for (std::list<IOperand const *>::iterator i = _containter.begin(); i != _containter.end(); ++i) {
		std::cout << (*i)->toString() << std::endl;
	}
}

void	AVM::assert(eOperandType type, std::string const &val) {
	IOperand const *top = *(_containter.begin());
	IOperand const *assert = _factory.createOperand(type, val);
	if (!(*top == *assert))
		throw Exception("Assert error");
}
