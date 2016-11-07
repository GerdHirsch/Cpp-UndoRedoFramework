#ifndef UNDOREDOMANAGER_H
#define UNDOREDOMANAGER_H

#include "UndoRedoStack.h"
#include "Command.h"

class UndoRedoManager : public virtual UndoRedoStack
{
public:
	virtual ~UndoRedoManager() = 0;
	
	virtual bool isModified() const = 0;
	virtual void resetModified() = 0;

//	virtual std::unique_ptr<UndoRedoManager> clone() const & = 0;
	// move clone!
//	virtual std::unique_ptr<UndoRedoManager> clone() && = 0;
};

inline
UndoRedoManager::~UndoRedoManager(){}

#endif //UNDOREDOMANAGER_H
