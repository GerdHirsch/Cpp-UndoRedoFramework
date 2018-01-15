/*
 * DefaultUndoRedoManagerTest.h
 *
 *  Created on: 04.11.2016
 *      Author: Gerd
 */

#ifndef INCLUDE_UNDOREDOMANAGERDELEGATIONTEST_H_
#define INCLUDE_UNDOREDOMANAGERDELEGATIONTEST_H_

#include <memory>

#include <UndoRedoFramework/ByDelegation/UndoRedoManagerImpl.h>

#include "UndoRedoTest/UndoRedoManagerTest.h"

class UndoRedoManagerByDelegationTest :
		public UndoRedoManagerTest<UndoRedoFramework::ByDelegation::UndoRedoManager> {
public:
	using this_type = UndoRedoManagerByDelegationTest;
	using base_type = UndoRedoManagerTest<UndoRedoFramework::ByDelegation::UndoRedoManager>;
	using base_type::SUT;
	using UndoRedoManagerImpl = UndoRedoFramework::ByDelegation::UndoRedoManagerImpl;


	virtual std::unique_ptr<SUT> createSUT() const override {
		return std::unique_ptr<SUT>(
				new UndoRedoManagerImpl
		);
	}
	static cute::suite make_suite(){
		return base_type::make_suite<this_type>();
	}
};

#endif /* INCLUDE_UNDOREDOMANAGERDELEGATIONTEST_H_ */
