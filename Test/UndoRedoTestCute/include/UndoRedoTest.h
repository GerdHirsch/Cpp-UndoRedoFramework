/*
 * UndoRedoTest.h
 *
 *  Created on: 30.10.2016
 *      Author: Gerd
 */

#ifndef SRC_UNDOREDOTEST_H_
#define SRC_UNDOREDOTEST_H_

#include "../include/Test.h"

#include <memory>

class UndoRedoTest{
public:
	UndoRedoTest():
		calculator(),
		plusValue(3),
		minusValue(1),
		plus(calculator, plusValue),
		minus(calculator, minusValue),
		pManager(new UndoRedoManagerImpl()),
		urMngr(*pManager)
{ }


protected:
	Calculator calculator;
	int plusValue;
	int minusValue;
	Plus plus;
	Minus minus;
	std::shared_ptr<UndoRedoManager> pManager;
	UndoRedoManager& urMngr;
};




#endif /* SRC_UNDOREDOTEST_H_ */
