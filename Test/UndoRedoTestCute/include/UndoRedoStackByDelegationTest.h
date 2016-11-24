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
	using this_type = UndoRedoStackByDelegationTest;
	using base_type = UndoRedoStackTest<UndoRedoFramework::UndoRedoStack>;
	using base_type::SUT;
	using UndoRedoStackImpl = UndoRedoFramework::ByDelegation::UndoRedoStackImpl;

	virtual std::unique_ptr<SUT> createSUT() const override {
		return std::unique_ptr<SUT>( new UndoRedoStackImpl );
	}
	static cute::suite make_suite(){
		return base_type::make_suite<this_type>();
	}

};


#endif /* SRC_UNDOREDOSTACKDELEGATIONTEST_H_ */
