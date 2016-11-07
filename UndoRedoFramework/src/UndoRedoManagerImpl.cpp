#include <stack>
#include <memory>

#include "../include/UndoRedoManagerImpl.h"
#include "../include/Command.h"
#include "../include/IllegalArgumentException.h"

#include <iostream>
using namespace std;

UndoRedoManagerImpl::UndoRedoManagerImpl(UndoRedoManagerImpl && rhs)
	: UndoRedoStackImpl(std::move(rhs)),
	modifications( rhs.modifications)
{
	rhs.modifications = 0;
}


UndoRedoManagerImpl::UndoRedoManagerImpl() : modifications(0)
{
}

void UndoRedoManagerImpl::undo()
{
	UndoRedoStackImpl::undo();
	modifications--;
}

void UndoRedoManagerImpl::doIt(SmartPointer && command)
{
	UndoRedoStackImpl::doIt(std::move(command));

	if(modifications < 0)
		modifications = UndoRedoStackImpl::undoStackSize() + 1;
	else
		modifications++;
}

void UndoRedoManagerImpl::redo()
{
	UndoRedoStackImpl::redo();
	modifications++;
}


bool UndoRedoManagerImpl::isModified() const
{
	return modifications != 0;
}
void UndoRedoManagerImpl::resetModified()
{
	modifications = 0;
}

