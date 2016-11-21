/*
 * CompositeCommandTest.h
 *
 *  Created on: 31.10.2016
 *      Author: Gerd
 */

#ifndef COMPOSITECOMMANDTEST_H_
#define COMPOSITECOMMANDTEST_H_
#include <memory>
#include <UndoRedoFramework/CompositeCommand.h>
#include "../include/UndoRedoTest.h"

namespace UndoRedoFramework{
class UndoRedoStack;
}

class CompositeCommandTest: public UndoRedoTest<UndoRedoFramework::CompositeCommand> {
public:
	using base_type = UndoRedoTest<UndoRedoFramework::CompositeCommand>;
	using base_type::SUT;
	using UndoRedoStack = UndoRedoFramework::UndoRedoStack;

	std::unique_ptr<SUT> pCommand;
	std::unique_ptr<UndoRedoStack> pStack;



	CompositeCommandTest()
	: UndoRedoTest() {}
	virtual ~CompositeCommandTest();

	virtual std::unique_ptr<UndoRedoStack> createURStack() const = 0;

	UndoRedoStack& getURStack(){
		pStack = createURStack();
		return *pStack;
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
