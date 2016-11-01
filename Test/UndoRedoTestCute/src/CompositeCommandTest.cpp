/*
 * CompositeCommandTest.cpp
 *
 *  Created on: 31.10.2016
 *      Author: Gerd
 */

#include "../include/CompositeCommandTest.h"

#include <include/CompositeCommand.h>
#include <include/CannotRollBackException.h>

#include <iostream>
using namespace std;

//CompositeCommandTest::CompositeCommandCtor() {
//	ASSERT_THROWS(CommandCompositeImpl(), std::logic_error);
//}
void CompositeCommandTest::DoItCommand() {
	Plus::throwException() = false;

	ccmd.doIt(minus);
	ccmd.doIt(plus);
	urMngr.doIt(std::move(ccmd));

	int expected { plusValue - minusValue };
	int result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	urMngr.doIt(plus);

	expected += plusValue;
	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);
}
void CompositeCommandTest::DoItCommandWithException() {
	Plus::throwException() = true;

	int expected { 0 };
	int result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	try{
		ccmd.doIt(minus);
		ccmd.doIt(minus);
		ccmd.doIt(plus);
	}catch(std::exception& e){
		cout << "catch DoItCommandWith'Exception" << endl;
	}

	result = calculator.getResult();
	cout << "result: " << result << endl;
	ASSERT_EQUAL(expected, result);

	urMngr.doIt(std::move(ccmd));

	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);
	urMngr.undo();

	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);
}
void CompositeCommandTest::UndoRedoDoIt() {
	int expected { 0 };
	int result = calculator.getResult();

	ccmd.doIt(minus);
	ccmd.doIt(plus);
	urMngr.doIt(std::move(ccmd));

	expected = plusValue - minusValue;
	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	urMngr.undo();

	expected = 0;
	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);
	urMngr.redo();

	expected = plusValue - minusValue;
	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);
}
void CompositeCommandTest::UndoWithException() {
	ccmd.doIt(minus);
	ccmd.doIt(plus); // throws in undo
	ccmd.doIt(minus);
	urMngr.doIt(std::move(ccmd));

	int expected { plusValue - (minusValue + minusValue) };
	int result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	Plus::throwException() = true;
	try{
		urMngr.undo();
	}catch(std::exception& e){}

	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	Plus::throwException() = false;

	ASSERT_EQUAL(true, urMngr.isUndoable());
	urMngr.undo();

	expected = 0;
	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	//check a second Exception
	Plus::throwException() = true;

	try{
		urMngr.redo();
	}catch(std::exception& e){}

	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);
}
void CompositeCommandTest::RedoWithException() {
	int expected { 0 };
	ccmd.doIt(minus);
	ccmd.doIt(plus);
	ccmd.doIt(minus);
	urMngr.doIt(std::move(ccmd));

	expected = plusValue - (minusValue+minusValue);
	int result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	urMngr.undo();

	expected = 0;
	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	Plus::throwException() = true;

	try{
		urMngr.redo();
	}catch(std::exception& e){}

	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	Plus::throwException() = false;

	urMngr.redo();

	expected = plusValue - (minusValue+minusValue);
	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	Plus::throwException() = true;

	try{
		urMngr.undo();
	}catch(std::exception& e){}

	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);
}
void CompositeCommandTest::DoItExceptionNeutral() {
	Plus::throwException() = true;
	ASSERT_THROWS(ccmd.doIt(plus), std::logic_error);
}
void CompositeCommandTest::UndoExceptionNeutral() {
	Plus::throwException() = false;
	ccmd.doIt(plus);
	urMngr.doIt(std::move(ccmd));

	Plus::throwException() = true;
	Plus::throwAtTimes() = 0;

	ASSERT_THROWS(urMngr.undo(), std::exception);
	ASSERT_THROWSM("should be a std::logic_error",
			urMngr.undo(), std::logic_error);
}
void CompositeCommandTest::RedoExceptionNeutral() {
	Plus::throwException() = false;
	ccmd.doIt(plus);
	urMngr.doIt(std::move(ccmd));
	urMngr.undo();
	Plus::throwException() = true;

	ASSERT_THROWS(urMngr.redo(), std::exception);
//	ASSERT_THROWS(urMngr.redo(), std::logic_error);
}

void CompositeCommandTest::DoItCommandWithExceptionInRollback(){
	Plus::throwException() = false;

	ccmd.doIt(minus);
	ccmd.doIt(plus); // throws in rollback
	ccmd.doIt(minus);

	Plus::throwException() = true;
	try{
		ccmd.doIt(plus);
	}catch(CannotRollbackException& e){

		int result = calculator.getResult();
		int expected { 2 };
		ASSERT_EQUAL(expected, result);

		Plus::throwException() = false;
		ccmd.undo();

		result = calculator.getResult();
		expected = 0;
		ASSERT_EQUAL(expected, result);
	}
}

void CompositeCommandTest::DoItThrowsCannotRollback(){
	Plus::throwException() = false;
	ccmd.doIt(minus);
	ccmd.doIt(plus); // throws in rollback
	ccmd.doIt(minus);

	Plus::throwException() = true;
	ASSERT_THROWSM("CompositeCommand cannot rollback!",
			ccmd.doIt(plus), CannotRollbackException);
}
void CompositeCommandTest::UndoThrowsCannotRollback(){
	Plus::throwException() = false;
	ccmd.doIt(minus);
	ccmd.doIt(plus); // throws in undo
	ccmd.doIt(minus);
	ccmd.doIt(plus); // throws in rollback
	urMngr.doIt(std::move(ccmd));

	Plus::throwException() = true;
	Plus::throwAtTimes() = 1;

	ASSERT_THROWS(urMngr.undo(), CannotRollbackException);
}
void CompositeCommandTest::RedoThrowsCannotRollback(){
	ccmd.doIt(minus);
	ccmd.doIt(plus); // throws in doIt
	ccmd.doIt(minus);
	ccmd.doIt(plus); // throws in rollback
	urMngr.doIt(std::move(ccmd));
	urMngr.undo();

	Plus::throwException() = true;
	Plus::throwAtTimes() = 1;

	ASSERT_THROWS(urMngr.redo(), CannotRollbackException);
}

cute::suite CompositeCommandTest::make_suite(){
	cute::suite s { };
	s.push_back(CUTE_SMEMFUN(CompositeCommandTest, DoItCommand));
	s.push_back(CUTE_SMEMFUN(CompositeCommandTest, DoItCommandWithException));
	s.push_back(CUTE_SMEMFUN(CompositeCommandTest, UndoRedoDoIt));
	s.push_back(CUTE_SMEMFUN(CompositeCommandTest, UndoWithException));
	s.push_back(CUTE_SMEMFUN(CompositeCommandTest, RedoWithException));
	s.push_back(CUTE_SMEMFUN(CompositeCommandTest, DoItCommandWithExceptionInRollback));
	s.push_back(CUTE_SMEMFUN(CompositeCommandTest, RedoThrowsCannotRollback));
	s.push_back(CUTE_SMEMFUN(CompositeCommandTest, UndoThrowsCannotRollback));
	s.push_back(CUTE_SMEMFUN(CompositeCommandTest, DoItThrowsCannotRollback));
	s.push_back(CUTE_SMEMFUN(CompositeCommandTest, DoItExceptionNeutral));
	s.push_back(CUTE_SMEMFUN(CompositeCommandTest, UndoExceptionNeutral));
	s.push_back(CUTE_SMEMFUN(CompositeCommandTest, RedoExceptionNeutral));
	return s;
}

