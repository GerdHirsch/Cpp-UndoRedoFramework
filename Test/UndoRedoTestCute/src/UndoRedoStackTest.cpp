/*
 * UndoRedoStackTest.cpp
 *
 *  Created on: 30.10.2016
 *      Author: Gerd
 */

#include "../include/UndoRedoStackTest.h"


<<<<<<< HEAD
//#include <iostream>
//#include <exception>
//using namespace std;


void UndoRedoStackTest::DoIt(){
	int result = calculator.getResult();
	int expected = 0;
	ASSERT_EQUAL(expected, result);
	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());

	urMngr.doIt(Plus(calculator, 3));

	expected = plusValue;
	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(true, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}
void UndoRedoStackTest::DoItWithException(){
	Plus::throwException() = true;
	int result = calculator.getResult();
	int expected = 0;
	ASSERT_EQUAL(expected, result);

	try{
		urMngr.doIt(plus);
	}catch(std::exception& e){}

	ASSERT_EQUAL(expected, result);
	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}

//==========
void UndoRedoStackTest::Undo(){
	Plus::throwException() = false;
	urMngr.doIt(plus);
	urMngr.undo();

	int result = calculator.getResult();
	int expected { 0 };

	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(true, urMngr.isRedoable());
}
void UndoRedoStackTest::UndoWithException(){
	urMngr.doIt(plus);
	Plus::throwException() = true;
	try{
		urMngr.undo();
	}catch(std::exception& e){
//		cout << "catch UndoWithException" << endl;
	}

	int expected = plusValue;
	int result = calculator.getResult();

	ASSERT_EQUAL(expected, result);
	ASSERT_EQUAL(true, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}

//==========
void UndoRedoStackTest::Redo(){
	Plus::throwException() = false;
	urMngr.doIt(plus);
	urMngr.undo();

	int result = calculator.getResult();
	int expected { plusValue };

	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(true, urMngr.isRedoable());

	ASSERT_EQUAL(expected, result);

	urMngr.redo();

	result = calculator.getResult();
	expected = 0;

	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(true, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}
void UndoRedoStackTest::RedoWithException(){
	Plus::throwException() = false;
	urMngr.doIt(plus);
	urMngr.undo();
	Plus::throwException() = true;
	try{
		urMngr.redo();
	}catch(std::exception& e){
//		cout << "catch UndoWithException" << endl;
	}

	int result = calculator.getResult();
	int expected { 0 };

	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(true, urMngr.isRedoable());
}

void UndoRedoStackTest::DoItExceptionNeutral(){
	Plus::throwException() = true;

	ASSERT_THROWS(urMngr.doIt(plus), std::logic_error);
}
void UndoRedoStackTest::UndoExceptionNeutral(){
	Plus::throwException() = false;
	urMngr.doIt(plus);
	Plus::throwException() = true;

	ASSERT_THROWS(urMngr.undo(), std::logic_error);
}
void UndoRedoStackTest::RedoExceptionNeutral(){
	Plus::throwException() = false;
	urMngr.doIt(plus);
	urMngr.undo();
	Plus::throwException() = true;

	ASSERT_THROWS(urMngr.redo(), std::logic_error);
}

cute::suite UndoRedoStackTest::make_suite(){
	cute::suite s { };
	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, DoIt));
	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, DoItWithException));

	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, Undo));
	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, UndoWithException));

	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, Redo));
	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, RedoWithException));

	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, DoItExceptionNeutral));
	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, UndoExceptionNeutral));
=======
#include <iostream>
#include <exception>
using namespace std;


void UndoRedoStackTest::DoIt(){
	Plus::throwException() = false;
	int result = calculator.getResult();
	int expected = 0;
	ASSERT_EQUAL(expected, result);
	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());

	urMngr.doIt(Plus(calculator, 3));

	expected = plusValue;
	result = calculator.getResult();
	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(true, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}
void UndoRedoStackTest::DoItWithException(){
	cout << "UndoRedoStackTest::DoItWithException()" << endl;

	Plus::throwException() = true;
	int result = calculator.getResult();
	int expected = 0;
	ASSERT_EQUAL(expected, result);

	try{
		urMngr.doIt(plus);
	}catch(std::exception& e){}

	ASSERT_EQUAL(expected, result);
	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}

void UndoRedoStackTest::DoItExceptionNeutral(){
	Plus::throwException() = true;

	ASSERT_THROWS(urMngr.doIt(plus), std::logic_error);
}
//==========
void UndoRedoStackTest::Undo(){
	Plus::throwException() = false;
	urMngr.doIt(plus);
	urMngr.undo();

	int result = calculator.getResult();
	int expected { 0 };

	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}
void UndoRedoStackTest::UndoWithException(){
	urMngr.doIt(plus);
	Plus::throwException() = true;
	try{
		urMngr.undo();
	}catch(std::exception& e){
		cout << "catch UndoWithException" << endl;
	}

	int result = calculator.getResult();
	int expected = plusValue;

	ASSERT_EQUAL(expected, result);
	ASSERT_EQUAL(true, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}

void UndoRedoStackTest::UndoExceptionNeutral(){
	Plus::throwException() = false;
	urMngr.doIt(plus);
	Plus::throwException() = true;

	ASSERT_THROWS(urMngr.undo(), std::logic_error);
}
//==========
void UndoRedoStackTest::Redo(){
	Plus::throwException() = false;
	urMngr.doIt(plus);
	urMngr.undo();

	int result = calculator.getResult();
	int expected { plusValue };

	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(true, urMngr.isRedoable());

	ASSERT_EQUAL(expected, result);

	urMngr.redo();

	result = calculator.getResult();
	expected = 0;

	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(true, urMngr.isUndoable());
	ASSERT_EQUAL(false, urMngr.isRedoable());
}
void UndoRedoStackTest::RedoWithException(){
	Plus::throwException() = false;
	urMngr.doIt(plus);
	urMngr.undo();
	Plus::throwException() = true;
	try{
		urMngr.redo();
	}catch(std::exception& e){
		cout << "catch UndoWithException" << endl;
	}

	int result = calculator.getResult();
	int expected { 0 };

	ASSERT_EQUAL(expected, result);

	ASSERT_EQUAL(false, urMngr.isUndoable());
	ASSERT_EQUAL(true, urMngr.isRedoable());
}

void UndoRedoStackTest::RedoExceptionNeutral(){
	Plus::throwException() = false;
	urMngr.doIt(plus);
	urMngr.undo();
	Plus::throwException() = true;

	ASSERT_THROWS(urMngr.redo(), std::logic_error);
}


cute::suite UndoRedoStackTest::make_suite(){
	cute::suite s { };
	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, DoIt));
	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, DoItWithException));
	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, DoItExceptionNeutral));
	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, Undo));
	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, UndoWithException));
	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, UndoExceptionNeutral));
	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, Redo));
	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, RedoWithException));
>>>>>>> branch 'add-tests' of https://github.com/GerdHirsch/Cpp-UndoRedoFramework.git
	s.push_back(CUTE_SMEMFUN(UndoRedoStackTest, RedoExceptionNeutral));
	return s;
}
