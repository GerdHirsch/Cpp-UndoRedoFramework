/*
 * UndoRedoStackImpl.h
 *
 *  Created on: 14.01.2018
 *      Author: Gerd
 */

#ifndef UNDOREDOCUSTIMIZED_UNDOREDOSTACKIMPL_H_
#define UNDOREDOCUSTIMIZED_UNDOREDOSTACKIMPL_H_

#include <UndoRedoFramework/UndoRedoStack.h>
#include <UndoRedoFramework/Command.h>

namespace UndoRedoCustomized{

class UndoRedoStackImpl : public UndoRedoFramework::UndoRedoStack{

	using Command = UndoRedoFramework::Command;

	virtual ~UndoRedoStackImpl();
	//for non copyable commands
	virtual void doIt(Command && command){}
	//for copyable commands
	virtual void doIt(Command const& command){}
	//for SmartPointers
	virtual void doIt(SmartPointer&& command){}

	virtual bool isUndoable() const { return false;}
	virtual void undo() {}

	virtual bool isRedoable() const { return false; }
	virtual void redo() {};

	virtual void clear() {}
	virtual std::size_t undoStackSize() const { return 0;}
	virtual std::size_t redoStackSize() const { return 0;}
//	virtual std::unique_ptr<UndoRedoManager> clone() const & = 0;
	// move clone!
	virtual std::unique_ptr<UndoRedoStack> clone() && { return std::unique_ptr<UndoRedoStack>(); }
};

} // end namespace Custom


#endif /* UNDOREDOCUSTIMIZED_UNDOREDOSTACKIMPL_H_ */
