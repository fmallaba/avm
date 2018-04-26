//
// Created by Furkat MALLABAEV on 4/24/18.
//

#include <iostream>
#include "OpFactory.h"
#include "Operand.h"

OpFactory::OpFactory(void) {
	_funcs[0] = &OpFactory::createInt8;
	_funcs[1] = &OpFactory::createInt16;
	_funcs[2] = &OpFactory::createInt32;
	_funcs[3] = &OpFactory::createFloat;
	_funcs[4] = &OpFactory::createDouble;
}

OpFactory::~OpFactory(void) {}

IOperand const	*OpFactory::createOperand(eOperandType type, std::string const &value) const {
	return (dynamic_cast<const IOperand *>((this->*_funcs[type])(value)));
}

IOperand const	*OpFactory::createInt8(std::string const &value) const {
	int val;

	try {
		val = std::stoi(value);
	}
	catch (std::exception & e) {
		throw Exception("The value is not Int8");
	}
	if (val < -128 || val > 127)
		throw Exception("Overflow on value");
	return (new Operand<int8_t>(static_cast<int8_t >(val), Int8, 1));
}

IOperand const	*OpFactory::createInt16(std::string const &value) const {
	int val;

	try {
		val = std::stoi(value);
	}
	catch (std::exception & e) {
		throw Exception("The value is not Int16");
	}
	if (val < -32768 || val > 32767)
		throw Exception("Overflow on value");
	return (new Operand<int16_t>(static_cast<int16_t >(val), Int16, 2));
}

IOperand const	*OpFactory::createInt32(std::string const &value) const {
	int32_t val;

	try {
		val = std::stoi(value);
	}
	catch (std::exception & e) {
		throw Exception("The value is not Int32");
	}
	return (new Operand<int32_t>(val, Int32, 3));
}

IOperand const	*OpFactory::createFloat(std::string const &value) const {
	float val;

	try {
		val = std::stoi(value);
	}
	catch (std::exception & e) {
		throw Exception("The value is not Float");
	}
	return (new Operand<float>(val, Float, 4));
}

IOperand const	*OpFactory::createDouble(std::string const &value) const {
	double val;

	try {
		val = std::stoi(value);
	}
	catch (std::exception & e) {
		throw Exception("The value is not Double");
	}
	return (new Operand<double>(val, Double, 5));
}
