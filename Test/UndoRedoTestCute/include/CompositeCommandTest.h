/*
 * CompositeCommandTest.h
 *
 *  Created on: 31.10.2016
 *      Author: Gerd
 */

#ifndef COMPOSITECOMMANDTEST_H_
#define COMPOSITECOMMANDTEST_H_

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

#endif /* COMPOSITECOMMANDTEST_H_ */
