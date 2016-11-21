/*
 * DefaultUndoRedoStackTest.h
 *
 *  Created on: 04.11.2016
 *      Author: Gerd
 */

#ifndef SRC_UNDOREDOSTACKDELEGATIONTEST_H_
#define SRC_UNDOREDOSTACKDELEGATIONTEST_H_

#include <memory>

#include <UndoRedoFramework/ByDelegation/UndoRedoStackImpl.h>
#include "UndoRedoStackTest.h"


class UndoRedoStackByDelegationTest : public UndoRedoStackTest<UndoRedoFramework::UndoRedoStack> {
public:
	using base_type = UndoRedoStackTest<UndoRedoFramework::UndoRedoStack>;
	using base_type::SUT;
	using UndoRedoStackImpl = UndoRedoFramework::ByDelegation::UndoRedoStackImpl;

	virtual std::unique_ptr<SUT> createSUT() const override {
		return std::unique_ptr<SUT>( new UndoRedoStackImpl );
	}
	static cute::suite make_suite();

};
inline
cute::suite UndoRedoStackByDelegationTest::make_suite(){
	cute::suite s { };
	UndoRedoStackTests(UndoRedoStackByDelegationTest)
	return s;
}


#endif /* SRC_UNDOREDOSTACKDELEGATIONTEST_H_ */
