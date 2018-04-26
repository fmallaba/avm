//
// Created by Furkat MALLABAEV on 4/25/18.
//

#include "Exception.h"

Exception::Exception(char const * msg) : _msg(msg) {}

Exception::Exception(void) : _msg("Error") {}

char const *Exception::what() const throw() {
	return (_msg);
}
