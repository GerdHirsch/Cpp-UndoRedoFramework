#ifndef UNDOREDOMANAGER_H
#define UNDOREDOMANAGER_H

#include "Command.h"

class UndoRedoManager
{
public:
	using SmartPointer = Command::SmartPointer;

	virtual ~UndoRedoManager() = 0;
	//for non copyable commands
	virtual void doIt(Command && command) = 0;
	//for copyable commands
	virtual void doIt(Command const& command) = 0;
	//for SmartPointers
	virtual void doIt(SmartPointer&& command) = 0;

	virtual bool canUndo() const = 0;
	virtual void undo() = 0;

	virtual bool canRedo() const = 0;
	virtual void redo() = 0;
	
	virtual bool isModified() const = 0;
	virtual void resetModified() = 0;

//	virtual std::unique_ptr<UndoRedoManager> clone() const & = 0;
	// move clone!
	virtual std::unique_ptr<UndoRedoManager> clone() && = 0;
};

inline
UndoRedoManager::~UndoRedoManager(){}

#endif //UNDOREDOMANAGER_H
