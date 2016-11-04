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
{}
	virtual std::unique_ptr<CompositeCommand> createCommand() const = 0;

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


//	static cute::suite make_suite();
};
#define CompositeCommandTests(DerivedTest)									\
		s.push_back(CUTE_SMEMFUN(DerivedTest, DoItCommand));			\
		s.push_back(CUTE_SMEMFUN(DerivedTest, DoItCommandWithException));\
		s.push_back(CUTE_SMEMFUN(DerivedTest, UndoRedoDoIt));			\
		s.push_back(CUTE_SMEMFUN(DerivedTest, UndoWithException));		\
		s.push_back(CUTE_SMEMFUN(DerivedTest, RedoWithException));		\
		s.push_back(CUTE_SMEMFUN(DerivedTest, DoItExceptionNeutral));	\
		s.push_back(CUTE_SMEMFUN(DerivedTest, UndoExceptionNeutral));	\
		s.push_back(CUTE_SMEMFUN(DerivedTest, RedoExceptionNeutral));	\
		s.push_back(CUTE_SMEMFUN(DerivedTest, DoItCommandWithExceptionInRollback));\
		s.push_back(CUTE_SMEMFUN(DerivedTest, DoItThrowsCannotRollback));\
		s.push_back(CUTE_SMEMFUN(DerivedTest, UndoThrowsCannotRollback));\
		s.push_back(CUTE_SMEMFUN(DerivedTest, RedoThrowsCannotRollback));

#endif /* COMPOSITECOMMANDTEST_H_ */
