/*
 * IllegalArgumentException.h
 *
 *  Created on: 01.11.2016
 *      Author: Gerd
 */

#ifndef ILLEGALARGUMENTEXCEPTION_H_
#define ILLEGALARGUMENTEXCEPTION_H_

#include <stdexcept>

class IllegalArgumentException : public std::logic_error{
public:
	IllegalArgumentException(char const* message)
	: std::logic_error(message) {}
};


#endif /* ILLEGALARGUMENTEXCEPTION_H_ */
