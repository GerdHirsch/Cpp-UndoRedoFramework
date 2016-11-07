/*
 * CompositeCommand.cpp
 *
 *  Created on: 19.02.2015
 *      Author: Gerd
 */

#include "../include/CompositeCommand.h"
#include "../include/UndoRedoStack.h"
#include "../include/CannotRollbackException.h"

#include <iostream>
using namespace std;

CompositeCommand::CompositeCommand(UndoRedoStack && urMngr)
: urMngr( std::move(urMngr).clone()),
  doItExceptionCatched(false),
  undoExceptionCatched(false)
{ }

CompositeCommand::CompositeCommand(CompositeCommand && rhs)
: urMngr( std::move(rhs.urMngr) ),
  doItExceptionCatched(false),
  undoExceptionCatched(false)
{  }

std::unique_ptr<Command> CompositeCommand::clone() const&
{
	// ugly hack, but we must implement all virtual Operations
	// CompositeCommands cannot be copied
	throw std::logic_error("Operation not supported");
}
std::unique_ptr<Command> CompositeCommand::clone() &&
{
	return std::unique_ptr<Command>( new CompositeCommand( std::move(*this) ));
}
CompositeCommand::~CompositeCommand() {
	//definition wird wegen unique_ptr<..> urMngr benötigt
}

/**
 * fügt das Command c in den internen CommandManager
 * (UndoRedoHandler.doit(Command c) ein
 *
 * @param c
 */
void CompositeCommand::doIt(Command&& command) {
	doIt(std::move(command).clone());
//	urMngr->doIt( std::move(c) );
}
void CompositeCommand::doIt(Command const& command) {
	doIt(command.clone());
//	urMngr->doIt(c);
}
void CompositeCommand::doIt(SmartPointer&& c) {
	try{
		urMngr->doIt( std::move(c) );
	}catch(...){
		doItExceptionCatched = true;
		undo();
		urMngr->clear();
		throw;
	}
}
/**
 * führt die Commands wieder aus
 * nach dem sie rückgängig gemacht wurden
 * @see undo()
 *
 * @throws Exception
 */
void CompositeCommand::doIt() {
	try{
		while (urMngr->isRedoable()) {
			urMngr->redo();
	}
	}catch(std::exception& e){
		doItExceptionCatched = true;
		if(undoExceptionCatched){
			undoExceptionCatched = false;
			throw CannotRollbackException("undo not possible, cause Command.doIt() throws Exception see getCause()", e);
		}else{
			undo();
			doItExceptionCatched = false;
			throw;
		}
	}
}
/**
 * Commands müssen in der umgekehrten Reihenfolge rückgängig gemacht werden,
 * wie sie ausgeführt wurden! Dazu wird ein UndoRedoManager benutzt.
 *
 * @directed true
 * @supplierRole Command Manager
 */
void CompositeCommand::undo() {
	try{
		while (urMngr->isUndoable()) {
			urMngr->undo();
		}
	}catch(std::exception& e){
		undoExceptionCatched = true;
		if(doItExceptionCatched){
			doItExceptionCatched = false;
			throw CannotRollbackException("doIt not possible, cause Command.undo() throws Exception see getCause()", e);
		}else{
			doIt();
			undoExceptionCatched = false;
			throw; // throws original exception
		}
	}
}

