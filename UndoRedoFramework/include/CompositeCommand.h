/*
 * CompositeCommand.h
 *
 *  Created on: 19.02.2015
 *      Author: Gerd
 */

#ifndef COMPOSITECOMMAND_H_
#define COMPOSITECOMMAND_H_

#include "Command.h"

#include<memory>

class UndoRedoStack;

class CompositeCommand: public Command {
public:
	using SmartPointer = Command::SmartPointer;

	CompositeCommand(UndoRedoStack && urMngr);
	CompositeCommand(CompositeCommand && rhs);
	virtual ~CompositeCommand();

	void doIt(Command&& c);
	void doIt(Command const& c);
	void doIt(SmartPointer && cmd);
	void doIt() override;
	void undo() override;

	virtual SmartPointer clone() && override;
	virtual SmartPointer clone() const& override;

private:
	std::unique_ptr<UndoRedoStack> urMngr;
	bool doItExceptionCatched;
	bool undoExceptionCatched;
};

#endif /* COMPOSITECOMMAND_H_ */
