#include <iostream>
#include <fstream>
#include <regex>
#include "../includes/AVM.h"

void	get_file_content(char *file, std::string & input)
{
	std::ifstream	ifs(file);

	if (ifs.fail())
	{
		std::cout << "\033[0;31mFile open error\033[0m" << std::endl;
		exit(-1);
	}
	std::getline(ifs, input, static_cast<char>(ifs.eof()));
}

void	get_input(std::string & input)
{
	std::string	line;
	while (std::getline(std::cin, line))
	{
		if (std::regex_match(line, std::regex("(.*);;(.*)"))) {
			input += line + "\n";
			return;
		}
		input += line + "\n";
	}
	std::cout << "\033[0;31mUnexpected terminating\033[0m" << std::endl;
	exit(-1);
}

int main(int ac, char **av) {
	AVM avm;
	std::string	input;

	if (ac > 3 ||
			(ac == 3 && (strcmp(av[1], "-v") != 0 && strcmp(av[2], "-v") != 0)))
	{
		std::cout << "\033[0;31mToo many arguments\033[0m" << std::endl;
		return (-1);
	}

	if ((ac == 2 && strcmp(av[1], "-v") == 0) ||
			(ac == 3 && (strcmp(av[1], "-v") == 0 || strcmp(av[2], "-v") == 0)))
		avm.verbose(true);

	if (ac > 1 && strcmp(av[1], "-v") != 0)
		get_file_content(av[1], input);
	else if (ac == 3 && strcmp(av[2], "-v") != 0)
		get_file_content(av[2], input);
	else
		get_input(input);

	try {
		avm.start_execute(input);
	}
	catch (std::exception & e) {
		std::cout << "\033[0;31mError : " << e.what() << "\033[0m" << std::endl;
	}
	return 0;
}