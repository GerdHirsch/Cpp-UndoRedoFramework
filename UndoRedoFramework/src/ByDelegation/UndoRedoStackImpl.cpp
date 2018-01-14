/*
 * UndoRedoStack.cpp
 *
 *  Created on: 07.11.2016
 *      Author: Gerd
 */


#include <UndoRedoFramework/ByDelegation/UndoRedoStackImpl.h>
#include <UndoRedoFramework/IllegalArgumentException.h>
#include <UndoRedoFramework/EmptyStackException.h>

#include <iostream>
using namespace std;

namespace UndoRedoFramework{
namespace ByDelegation{


UndoRedoStackImpl::UndoRedoStackImpl(UndoRedoStackImpl&& rhs):
	undoStack(std::move(rhs.undoStack)),
	redoStack(std::move(rhs.redoStack))
{
//	cout << "UndoRedoStackImpl(UndoRedoStackImpl&& rhs)" << endl;
}
UndoRedoStackImpl::UndoRedoStackImpl(){
//	cout << "UndoRedoStackImpl()" << endl;
}

std::unique_ptr<UndoRedoStack> UndoRedoStackImpl::clone() &&
{
	return std::unique_ptr<UndoRedoStack>
		( new UndoRedoStackImpl( std::move(*this)) );
}

void UndoRedoStackImpl::doIt(Command && command)
{
	doIt(std::move(command).clone());
}
void UndoRedoStackImpl::doIt(Command const& command)
{
	doIt(command.clone());
}
void UndoRedoStackImpl::doIt(SmartPointer && command)
{
	if(command == nullptr)
		throw IllegalArgumentException("command must not be nullptr");

	command->doIt();

	undoStack.push( std::move(command) );
	clearRedoStack();

}
void UndoRedoStackImpl::clearRedoStack(){
	while(!redoStack.empty())
		redoStack.pop();
}
void UndoRedoStackImpl::clearUndoStack(){
	while(!undoStack.empty())
		undoStack.pop();
}
void UndoRedoStackImpl::clear(){
	clearRedoStack();
	clearUndoStack();
}
bool UndoRedoStackImpl::isUndoable() const
{
	return !undoStack.empty();
}
void UndoRedoStackImpl::undo()
{
	if(undoStack.empty()) throw EmptyStackException("Nothing to undo!");

	undoStack.top()->undo();
	redoStack.push(std::move(undoStack.top()));
	undoStack.pop();
}
bool UndoRedoStackImpl::isRedoable() const
{
	return !redoStack.empty();
}
void UndoRedoStackImpl::redo()
{
	if(redoStack.empty()) throw EmptyStackException("Nothing to redo!");

	redoStack.top()->doIt();
	undoStack.push(std::move(redoStack.top()));
	redoStack.pop();
}

}} // end namespace
