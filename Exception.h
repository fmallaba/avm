//
// Created by Furkat MALLABAEV on 4/25/18.
//

#ifndef AVM_EXCEPTION_H
# define AVM_EXCEPTION_H

# include <exception>

class Exception : public std::exception {
public:
	Exception(char const * msg);
	Exception(void);
	virtual ~Exception() throw(){}
	char const *what() const throw();

private:
	char const *_msg;
};


#endif //AVM_EXCEPTION_H
