#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "../include/UndoRedoStackTest.h"

#include <iostream>
using namespace std;


void runAllTests(int argc, char const *argv[]){
	cute::suite s;

	s.push_back( DoIt() );
	s.push_back( DoItWithException() );
	s.push_back( DoItExceptionNeutral() );

	s.push_back( Undo() );
	s.push_back( UndoWithException() );
	s.push_back( UndoExceptionNeutral() );

	s.push_back( Redo() );
	s.push_back( RedoWithException() );
	s.push_back( RedoExceptionNeutral() );

	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
	cout << "main()" << endl;

//	Calculator calculator;
//	UndoRedoManagerImpl urMngr;
//	urMngr.doIt(Plus(calculator, 3));
//
//	cout << calculator.getResult() << endl;
    runAllTests(argc,argv);
    return 0;
}
/*
 *
class TestClass{
	typedef void(TestClass::*TestMethod)();
	TestMethod testMethod;
public:
	TestClass() : testMethod(&TestClass::test1){}
	TestClass(TestMethod testMethod) : testMethod(testMethod){}

	void operator()(){
		(this->*testMethod)();
	}
	void test1(){
		ASSERTM("start writing tests with Classes", false);
	}
	void test2(){
		ASSERTM("start writing tests with Classes", false);
	}
};

void thisIsATest() {
	ASSERTM("start writing tests", false);
}
 */


