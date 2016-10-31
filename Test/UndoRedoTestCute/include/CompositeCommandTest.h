/*
 * CompositeCommandTest.h
 *
 *  Created on: 31.10.2016
 *      Author: Gerd
 */

#ifndef COMPSITECOMMANDTEST_H_
#define COMPSITECOMMANDTEST_H_

#include "../include/UndoRedoTest.h"

class CompositeCommandTest: public UndoRedoTest {
	CompositeCommand ccmd;
public:
	CompositeCommandTest()
	:
		UndoRedoTest(),
		ccmd(UndoRedoManagerImpl())
{

}
	void DoItCommand();
	void DoItCommandWithException();

	void testUndoRedoDoIt();
	void UndoWithException();
	void RedoWithException();

	void DoItExceptionNeutral();
	void UndoExceptionNeutral();
	void RedoExceptionNeutral();

	static cute::suite make_suite();
};

#endif /* COMPSITECOMMANDTEST_H_ */
