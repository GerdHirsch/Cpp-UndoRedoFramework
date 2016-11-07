/*
 * DefaultUndoRedoStackTest.h
 *
 *  Created on: 04.11.2016
 *      Author: Gerd
 */

#ifndef SRC_DEFAULTUNDOREDOSTACKTEST_H_
#define SRC_DEFAULTUNDOREDOSTACKTEST_H_

#include <include/UndoRedoStackImpl.h>
#include "UndoRedoStackTest.h"

class DefaultUndoRedoStackTest : public UndoRedoStackTest<UndoRedoStack> {
public:
	virtual std::unique_ptr<UndoRedoStack> createSUT() const override {
		return std::unique_ptr<UndoRedoStack>
		(
				new UndoRedoStackImpl
		);
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
