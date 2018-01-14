/*
 * CompositeCommandTest.cpp
 *
 *  Created on: 31.10.2016
 *      Author: Gerd
 */

#include "../include/CompositeCommandTest.h"


#include <UndoRedoFramework/UndoRedoStack.h>
#include <UndoRedoFramework/CompositeCommand.h>
#include <UndoRedoFramework/CannotRollbackException.h>

#include "cute.h"

#include <iostream>
using namespace std;

//CompositeCommandTest::CompositeCommandCtor() {
//	ASSERT_THROWS(CommandCompositeImpl(), std::logic_error);
//}
// define dtor cause unique_ptr member
CompositeCommandTest::~CompositeCommandTest(){}


void CompositeCommandTest::DoItCommand() {
	UndoRedoStack& urStack(getURStack());
	auto& ccmd(getSUT());

	Plus::throwException() = false;

	ccmd.doIt(minus);
	ccmd.doIt(plus);
	urStack.doIt(std::move(ccmd));

	int expected { plusValue - minusValue };
	int result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	urStack.doIt(plus);

	expected += plusValue;
	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);
}
void CompositeCommandTest::DoItCommandWithException() {
	UndoRedoStack& urStack(getURStack());
	auto& ccmd(getSUT());

	Plus::throwException() = true;

	int expected { 0 };
	int result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

		ccmd.doIt(minus);
		ccmd.doIt(minus);
		ASSERT_THROWSM("Command throws but SUT not!",
				ccmd.doIt(plus), std::logic_error);

	result = calculator.getResult();
	cout << "result: " << result << endl;
	ASSERT_EQUAL(expected, result);

	urStack.doIt(std::move(ccmd));

	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);
	urStack.undo();

	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);
}
void CompositeCommandTest::UndoRedoDoIt() {
	UndoRedoStack& urStack(getURStack());
	auto& ccmd(getSUT());

	int expected { 0 };
	int result = calculator.getResult();

	ccmd.doIt(minus);
	ccmd.doIt(plus);
	urStack.doIt(std::move(ccmd));

	expected = plusValue - minusValue;
	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	urStack.undo();

	expected = 0;
	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);
	urStack.redo();

	expected = plusValue - minusValue;
	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);
}
void CompositeCommandTest::UndoWithException() {
	UndoRedoStack& urStack(getURStack());
	auto& ccmd(getSUT());

	ccmd.doIt(minus);
	ccmd.doIt(plus); // throws in undo
	ccmd.doIt(minus);
	urStack.doIt(std::move(ccmd));

	int expected { plusValue - (minusValue + minusValue) };
	int result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	Plus::throwException() = true;

	ASSERT_THROWSM("Command throws but SUT not!",
			urStack.undo(), std::logic_error);

	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	Plus::throwException() = false;

	ASSERT_EQUAL(true, urStack.isUndoable());
	urStack.undo();

	expected = 0;
	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	//check a second Exception
	Plus::throwException() = true;

	ASSERT_THROWSM("Command throws but SUT not!",
			urStack.redo(), std::logic_error);

	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);
}
void CompositeCommandTest::RedoWithException() {
	UndoRedoStack& urStack(getURStack());
	auto& ccmd(getSUT());

	int expected { 0 };
	ccmd.doIt(minus);
	ccmd.doIt(plus);
	ccmd.doIt(minus);
	urStack.doIt(std::move(ccmd));

	expected = plusValue - (minusValue+minusValue);
	int result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	urStack.undo();

	expected = 0;
	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	Plus::throwException() = true;

	ASSERT_THROWSM("Command throws but SUT not!",
			urStack.redo(), std::logic_error);

	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	Plus::throwException() = false;

	urStack.redo();

	expected = plusValue - (minusValue+minusValue);
	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	Plus::throwException() = true;

	ASSERT_THROWSM("Command throws but SUT not!",
			urStack.undo(), std::logic_error);

	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);
}
void CompositeCommandTest::DoItExceptionNeutral() {
	auto& ccmd(getSUT());

	Plus::throwException() = true;
	ASSERT_THROWS(ccmd.doIt(plus), std::logic_error);
}
void CompositeCommandTest::UndoExceptionNeutral() {
	auto& urStack(getURStack());
	auto& ccmd(getSUT());

	Plus::throwException() = false;
	ccmd.doIt(plus);
	urStack.doIt(std::move(ccmd));

	Plus::throwException() = true;
	Plus::throwAtTimes() = 0;

	ASSERT_THROWS(urStack.undo(), std::exception);
	ASSERT_THROWSM("should be a std::logic_error",
			urStack.undo(), std::logic_error);
}
void CompositeCommandTest::RedoExceptionNeutral() {
	auto& urStack(getURStack());
	auto& ccmd(getSUT());

	Plus::throwException() = false;
	ccmd.doIt(plus);
	urStack.doIt(std::move(ccmd));
	urStack.undo();
	Plus::throwException() = true;

	ASSERT_THROWS(urStack.redo(), std::exception);
//	ASSERT_THROWS(urStack.redo(), std::logic_error);
}

void CompositeCommandTest::DoItCommandWithExceptionInRollback(){
	auto& ccmd(getSUT());

	Plus::throwException() = false;

	ccmd.doIt(minus);
	ccmd.doIt(plus); // throws in rollback
	ccmd.doIt(minus);

	Plus::throwException() = true;

	ASSERT_THROWSM("CannotRollbackException not thrown!",
			ccmd.doIt(plus), CannotRollbackException);

		int result = calculator.getResult();
		int expected { 2 };
		ASSERT_EQUAL(expected, result);

		Plus::throwException() = false;
		ccmd.undo();

		result = calculator.getResult();
		expected = 0;
		ASSERT_EQUAL(expected, result);
}

void CompositeCommandTest::DoItThrowsCannotRollback(){
	auto& ccmd(getSUT());

	Plus::throwException() = false;
	ccmd.doIt(minus);
	ccmd.doIt(plus); // throws in rollback
	ccmd.doIt(minus);

	Plus::throwException() = true;
	ASSERT_THROWSM("CompositeCommand cannot rollback!",
			ccmd.doIt(plus), CannotRollbackException);
}
void CompositeCommandTest::UndoThrowsCannotRollback(){
	auto& urStack(getURStack());
	auto& ccmd(getSUT());

	Plus::throwException() = false;
	ccmd.doIt(minus);
	ccmd.doIt(plus); // throws in undo
	ccmd.doIt(minus);
	ccmd.doIt(plus); // throws in rollback
	urStack.doIt(std::move(ccmd));

	Plus::throwException() = true;
	Plus::throwAtTimes() = 1;

	ASSERT_THROWS(urStack.undo(), CannotRollbackException);
}
void CompositeCommandTest::RedoThrowsCannotRollback(){
	auto& urStack(getURStack());
	auto& ccmd(getSUT());

	ccmd.doIt(minus);
	ccmd.doIt(plus); // throws in doIt
	ccmd.doIt(minus);
	ccmd.doIt(plus); // throws in rollback
	urStack.doIt(std::move(ccmd));
	urStack.undo();

	Plus::throwException() = true;
	Plus::throwAtTimes() = 1;

	ASSERT_THROWS(urStack.redo(), CannotRollbackException);
}

