/*
 * CannotRollbackException.h
 *
 *  Created on: 01.11.2016
 *      Author: Gerd
 */

#ifndef CANNOTROLLBACKEXCEPTION_H_
#define CANNOTROLLBACKEXCEPTION_H_

#include <stdexcept>

class CannotRollbackException : public std::logic_error{
	std::exception& cause;
public:
	CannotRollbackException(char const* message, std::exception& cause)
	: std::logic_error(message),
	  cause(cause){}

	virtual char const* what() const noexcept override {
		std::string retVal(std::logic_error::what());
		retVal += " ";
		retVal += cause.what();
		return retVal.c_str();
	}
};



#endif /* CANNOTROLLBACKEXCEPTION_H_ */
