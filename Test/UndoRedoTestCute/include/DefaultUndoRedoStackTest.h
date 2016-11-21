/*
 * DefaultUndoRedoStackTest.h
 *
 *  Created on: 04.11.2016
 *      Author: Gerd
 */

#ifndef SRC_DEFAULTUNDOREDOSTACKTEST_H_
#define SRC_DEFAULTUNDOREDOSTACKTEST_H_

#include <memory>

#include <include/UndoRedoStackImpl.h>
#include "UndoRedoStackTest.h"


class DefaultUndoRedoStackTest : public UndoRedoStackTest<UndoRedoFramework::UndoRedoStack> {
public:
	using base_type = UndoRedoStackTest<UndoRedoFramework::UndoRedoStack>;
	using base_type::SUT;
	using UndoRedoStackImpl = UndoRedoFramework::ByInheritance::UndoRedoStackImpl;

	virtual std::unique_ptr<SUT> createSUT() const override {
		return std::unique_ptr<SUT>( new UndoRedoStackImpl );
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
