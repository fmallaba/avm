#include <iostream>
#include <fstream>
#include <regex>
#include "AVM.h"

void	get_file_content(char *file, std::string & input)
{
	std::ifstream	ifs(file);

	if (ifs.fail())
	{
		std::cout << "File open error" << std::endl;
		exit(-1);
	}
	std::getline(ifs, input, static_cast<char>(ifs.eof()));
}

void	get_input(std::string & input)
{
	std::string	line;
	while (std::getline(std::cin, line))
	{
		if (std::regex_match(line, std::regex("^;;$")))
			return;
		input += line + "\n";
	}
	std::cout << "Unexpected terminating" << std::endl;
	exit(-1);
}

int main(int ac, char **av) {
	AVM avm;
	std::string	input;

	if (ac > 1)
		get_file_content(av[1], input);
	else
		get_input(input);
//	std::cout << input << std::endl;
	try {
		avm.start_execute(input);
	}
	catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}