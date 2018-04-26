#include <iostream>
#include "Operand.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
	OpFactory factory;
	IOperand const *int8 = factory.createOperand(Int8, "97");

	std::cout << int8->toString() << std::endl;

	try {
		factory.createOperand(Int16, "349850374503");
	}
	catch (std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}