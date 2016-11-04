/*
 * DefaultUndoRedoStackTest.h
 *
 *  Created on: 04.11.2016
 *      Author: Gerd
 */

#ifndef SRC_DEFAULTUNDOREDOSTACKTEST_H_
#define SRC_DEFAULTUNDOREDOSTACKTEST_H_

#include <include/UndoRedoManager.h>
#include "UndoRedoStackTest.h"

class DefaultUndoRedoStackTest : public UndoRedoStackTest {
public:
	virtual std::unique_ptr<UndoRedoManager> createManager() const override {
		return std::unique_ptr<UndoRedoManager>(new UndoRedoManagerImpl);
	}
	static cute::suite make_suite();

};
inline
cute::suite DefaultUndoRedoStackTest::make_suite(){
	cute::suite s { };
	UndoRedoStackTests(DefaultUndoRedoStackTest)
	return s;
}


#endif /* SRC_DEFAULTUNDOREDOSTACKTEST_H_ */
