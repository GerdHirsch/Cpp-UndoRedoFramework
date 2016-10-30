#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"

#include "../include/UndoRedoStackTest.h"

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

void runAllTests(int argc, char const *argv[]){
	cute::suite s;
	//TODO add your test here
//	s.push_back(CUTE(thisIsATest));
//	s.push_back( TestClass(&TestClass::test1) );
//	s.push_back( TestClass(&TestClass::test2) );
	s.push_back( UndoRedoStackTest(&UndoRedoStackTest::testDoIt) );
	s.push_back( UndoRedoStackTest(&UndoRedoStackTest::testDoItWithException) );
	s.push_back( UndoRedoStackTest(&UndoRedoStackTest::testDoItExceptionNeutral) );

	s.push_back( UndoRedoStackTest(&UndoRedoStackTest::testUndo) );
	s.push_back( UndoRedoStackTest(&UndoRedoStackTest::testUndoWithException) );
	s.push_back( UndoRedoStackTest(&UndoRedoStackTest::testUndoExceptionNeutral) );

	s.push_back( UndoRedoStackTest(&UndoRedoStackTest::testRedo) );
	s.push_back( UndoRedoStackTest(&UndoRedoStackTest::testRedoWithException) );
	s.push_back( UndoRedoStackTest(&UndoRedoStackTest::testRedoExceptionNeutral) );
	cute::xml_file_opener xmlfile(argc,argv);
	cute::xml_listener<cute::ide_listener<> >  lis(xmlfile.out);
	cute::makeRunner(lis,argc,argv)(s, "AllTests");
}

int main(int argc, char const *argv[]){
    runAllTests(argc,argv);
    return 0;
}



