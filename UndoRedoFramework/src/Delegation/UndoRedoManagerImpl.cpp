#include <stack>
#include <memory>

#include "../include/UndoRedoManagerImpl.h"
#include "../include/UndoRedoStackImpl.h"
#include "../include/Command.h"
#include "../include/IllegalArgumentException.h"

#include <iostream>
using namespace std;

UndoRedoManagerImpl::UndoRedoManagerImpl(UndoRedoManagerImpl && rhs)
	:
		//UndoRedoStackImpl(std::move(rhs)),
	urStack(std::move(rhs).urStack),
	modifications( rhs.modifications)
{
	rhs.modifications = 0;
//	cout << "UndoRedoManagerImpl(UndoRedoManagerImpl&& rhs)" << endl;

}

UndoRedoManagerImpl::UndoRedoManagerImpl()
:
	urStack(new UndoRedoStackImpl),
	modifications(0)
{
//	cout << "UndoRedoManagerImpl()" << endl;
}

std::unique_ptr<UndoRedoStack> UndoRedoManagerImpl::clone()&&{
	return std::unique_ptr<UndoRedoStack>(
			new UndoRedoManagerImpl(std::move(*this)));
}

void UndoRedoManagerImpl::undo()
{
	urStack->undo();
	modifications--;
}

void UndoRedoManagerImpl::doIt(Command && command){
	doIt(std::move(command).clone());
}

void UndoRedoManagerImpl::doIt(Command const & command){
	doIt(command.clone());
}

void UndoRedoManagerImpl::clear(){
	return urStack->clear();
}
void UndoRedoManagerImpl::doIt(SmartPointer && command)
{
	urStack->doIt(std::move(command));

	if(modifications < 0)
		modifications = urStack->undoStackSize() + 1;
	else
		modifications++;
}

void UndoRedoManagerImpl::redo()
{
	urStack->redo();
	modifications++;
}

bool UndoRedoManagerImpl::isUndoable() const {
	return urStack->isUndoable();
}
bool UndoRedoManagerImpl::isRedoable() const {
	return urStack->isRedoable();
}

std::size_t UndoRedoManagerImpl::undoStackSize() const {
	return urStack->undoStackSize();
}

bool UndoRedoManagerImpl::isModified() const
{
	return modifications != 0;
}
void UndoRedoManagerImpl::resetModified()
{
	modifications = 0;
}

