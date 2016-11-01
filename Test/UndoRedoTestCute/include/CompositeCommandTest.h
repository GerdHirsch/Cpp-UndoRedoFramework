/*
 * CompositeCommandTest.h
 *
 *  Created on: 31.10.2016
 *      Author: Gerd
 */

#ifndef COMPOSITECOMMANDTEST_H_
#define COMPOSITECOMMANDTEST_H_

#include "../include/UndoRedoTest.h"

#include <iostream>

class CompositeCommandTest: public UndoRedoTest {
	CompositeCommand ccmd;
public:
	CompositeCommandTest()
	:
		UndoRedoTest(),
		ccmd(UndoRedoManagerImpl())
{
//		std::cout << "CompositeCommandTest()" << std::endl;
}
//	void CommandCompositeCtor();
	void DoItCommand();
	void DoItCommandWithException();

	void UndoRedoDoIt();
	void UndoWithException();
	void RedoWithException();

	void DoItExceptionNeutral();
	void UndoExceptionNeutral();
	void RedoExceptionNeutral();

	void DoItCommandWithExceptionInRollback();
	void DoItThrowsCannotRollback();
	void UndoThrowsCannotRollback();
	void RedoThrowsCannotRollback();


	static cute::suite make_suite();
};

#endif /* COMPOSITECOMMANDTEST_H_ */
