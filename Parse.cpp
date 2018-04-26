//
// Created by Furkat MALLABAEV on 4/25/18.
//

#include <regex>
#include "Parse.h"
#include "Exception.h"

Parse::Parse(void) {}

Parse::~Parse(void) {}

eInstructions	Parse::parse_line(std::string const &line, eOperandType &type, std::string &val) {
	eInstructions			intstruction;
	std::string::size_type	pos;

	intstruction = get_instruction(line, pos);
	if (intstruction == Push || intstruction == Assert)
		parse_value(line, pos, val);
	return (intstruction);
}

eInstructions	Parse::get_instruction(std::string const &line, std::string::size_type &pos) {
	if ((pos = line.find("push ", 0)) == 0)
		return (Push);
	else if (std::regex_match(line, std::regex("^(pop)(;.*)?$")))
		return (Pop);
	else if (std::regex_match(line, std::regex("^(dump)(;.*)?$")))
		return (Dump);
	else if ((pos = line.find("assert ", 0)) == 0)
		return (Assert);
	else if (std::regex_match(line, std::regex("^(add)(;.*)?$")))
		return (Add);
	else if (std::regex_match(line, std::regex("^(sub)(;.*)?$")))
		return (Sub);
	else if (std::regex_match(line, std::regex("^(mul)(;.*)?$")))
		return (Mul);
	else if (std::regex_match(line, std::regex("^(div)(;.*)?$")))
		return (Div);
	else if (std::regex_match(line, std::regex("^(mod)(;.*)?$")))
		return (Mod);
	else if (std::regex_match(line, std::regex("^(print)(;.*)?$")))
		return (Print);
	else if (std::regex_match(line, std::regex("^(exit)(;.*)?$")))
		return (Exit);
	throw Exception("Unknown instruction");
}

eOperandType Parse::parse_value(std::string const &line, std::string::size_type pos, std::string &val) {
	if (std::regex_match(line.begin() + pos, line.end(), std::regex("^(int8\\([-]?[0-9]*\\))(;.*)?$"))) {
		get_val(line, val);
		return (Int8);
	}
	else if (std::regex_match(line.begin() + pos, line.end(), std::regex("^(int16\\([-]?[0-9]*\\))(;.*)?$"))) {
		get_val(line, val);
		return (Int16);
	}
	else if (std::regex_match(line.begin() + pos, line.end(), std::regex("^(int32\\([-]?[0-9]*\\))(;.*)?$"))) {
		get_val(line, val);
		return (Int32);
	}
	else if (std::regex_match(line.begin() + pos, line.end(), std::regex("^(float\\([-]?([0-9]*[.])?[0-9]+\\))(;.*)?$"))) {
		get_val(line, val);
		return (Float);
	}
	else if (std::regex_match(line.begin() + pos, line.end(), std::regex("^(double\\([-]?([0-9]*[.])?[0-9]+\\))(;.*)?$"))) {
		get_val(line, val);
		return (Double);
	}
	throw Exception("Syntax error");
}

void	Parse::get_val(std::string const &line, std::string &val) {
	std::string::size_type start = line.find("(") + 1;
	std::string::size_type end = line.find(")");

	val = line.substr(start, end - start);
}
