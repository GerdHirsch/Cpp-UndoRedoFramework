/*
 * IllegalArgumentException.h
 *
 *  Created on: 01.11.2016
 *      Author: Gerd
 */

#ifndef EMPTYSTACKEXCEPTION_H_
#define EMPTYSTACKEXCEPTION_H_

#include <stdexcept>

class EmptyStackException : public std::logic_error{
public:
	EmptyStackException(char const* message)
	: std::logic_error(message) {}
};


#endif /* EMPTYSTACKEXCEPTION_H_ */
