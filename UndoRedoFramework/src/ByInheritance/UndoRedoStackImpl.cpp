/*
 * UndoRedoStack.cpp
 *
 *  Created on: 07.11.2016
 *      Author: Gerd
 */

#include <UndoRedoFramework/ByInheritance/UndoRedoStackImpl.h>
#include <UndoRedoFramework/IllegalArgumentException.h>

#include <iostream>
using namespace std;

namespace UndoRedoFramework{
namespace ByInheritance{


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

//	if(modifications < 0)
//		modifications = undoStack.size() + 1;
//	else
//		modifications++;
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
/* ohne move nur mit shared_ptr möglich
	undoStack.top()->undo();
	modifications--;
	redoStack.push(undoStack.top());
	undoStack.pop();
*/
	undoStack.top()->undo();
	redoStack.push(std::move(undoStack.top()));
	undoStack.pop();

//	modifications--;
}

bool UndoRedoStackImpl::isRedoable() const
{
	return !redoStack.empty();
}
void UndoRedoStackImpl::redo()
{
/* ohne move nur mit shared_ptr möglich
	redoStack.top()->doIt();
	modifications++;
	undoStack.push(redoStack.top());
	redoStack.pop();
*/
	redoStack.top()->doIt();
	undoStack.push(std::move(redoStack.top()));
	redoStack.pop();

//	modifications++;

}

}} // end namespace
