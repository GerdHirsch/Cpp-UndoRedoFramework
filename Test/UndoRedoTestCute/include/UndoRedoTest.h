/*
 * UndoRedoTest.h
 *
 *  Created on: 30.10.2016
 *      Author: Gerd
 */

#ifndef SRC_UNDOREDOTEST_H_
#define SRC_UNDOREDOTEST_H_


#include "Calculator.h"
#include "CalculatorCommands.h"
#include "cute.h"

#include <memory>

//#include <iostream>

template<class SUTType>
class UndoRedoTest{
public:
	using SUT = SUTType;

	UndoRedoTest():
		calculator(),
		plusValue(3),
		minusValue(1),
		plus(calculator, plusValue),
		minus(calculator, minusValue),
		pSUT(nullptr)
	{
//		std::cout << "UndoRedoTest()"  << std::endl;
	}
	virtual std::unique_ptr<SUT> createSUT() const = 0;

	SUT& getSUT() {
		if(!pSUT) // one SUT for each test
			pSUT = createSUT();
		return *pSUT;
	}

protected:
	Calculator calculator;
	int plusValue;// = 3;
	int minusValue;// = 1;
	Plus plus;
	Minus minus;
	std::unique_ptr<SUT> pSUT;
};




#endif /* SRC_UNDOREDOTEST_H_ */
