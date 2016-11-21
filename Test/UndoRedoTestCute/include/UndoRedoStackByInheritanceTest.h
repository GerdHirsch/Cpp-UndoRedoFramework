/*
 * DefaultUndoRedoStackTest.h
 *
 *  Created on: 04.11.2016
 *      Author: Gerd
 */

#ifndef SRC_UNDOREDOSTACKINHERITANCETEST_H_
#define SRC_UNDOREDOSTACKINHERITANCETEST_H_

#include <memory>

#include <UndoRedoFramework/ByInheritance/UndoRedoStackImpl.h>
#include "UndoRedoStackTest.h"


class UndoRedoStackByInheritanceTest : public UndoRedoStackTest<UndoRedoFramework::UndoRedoStack> {
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
cute::suite UndoRedoStackByInheritanceTest::make_suite(){
	cute::suite s { };
	UndoRedoStackTests(UndoRedoStackByInheritanceTest)
	return s;
}


#endif /* SRC_UNDOREDOSTACKINHERITANCETEST_H_ */
