/*
 * UndoRedoStack.h
 *
 *  Created on: 07.11.2016
 *      Author: Gerd
 */

#ifndef UNDOREDOSTACK_H_
#define UNDOREDOSTACK_H_

#include "Command.h"

class UndoRedoStack
{
public:
	using SmartPointer = Command::SmartPointer;

	virtual ~UndoRedoStack() = 0;
	//for non copyable commands
	virtual void doIt(Command && command) = 0;
	//for copyable commands
	virtual void doIt(Command const& command) = 0;
	//for SmartPointers
	virtual void doIt(SmartPointer&& command) = 0;

	virtual bool isUndoable() const = 0;
	virtual void undo() = 0;

	virtual bool isRedoable() const = 0;
	virtual void redo() = 0;

	virtual void clear() = 0;
	virtual std::size_t undoStackSize() const = 0;
//	virtual std::unique_ptr<UndoRedoManager> clone() const & = 0;
	// move clone!
	virtual std::unique_ptr<UndoRedoStack> clone() && = 0;
};

inline
UndoRedoStack::~UndoRedoStack(){}



#endif /* UNDOREDOSTACK_H_ */
