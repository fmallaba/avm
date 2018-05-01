//
// Created by Furkat MALLABAEV on 4/25/18.
//

#ifndef AVM_EXCEPTION_H
# define AVM_EXCEPTION_H

# include <exception>

class Exception : public std::exception {
public:
	explicit Exception(char const * msg);
	Exception();
	Exception(Exception const & rhs);
	virtual ~Exception() throw();

	Exception	&operator=(Exception const & rhs);
	char const *what() const throw();

private:
	char const *_msg;
};


#endif //AVM_EXCEPTION_H
