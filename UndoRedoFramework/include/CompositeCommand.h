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

class UndoRedoManager;

class CompositeCommand: public Command {
public:
	using SmartPointer = std::unique_ptr<Command>;

	CompositeCommand(UndoRedoManager && urMngr);
	CompositeCommand(CompositeCommand && rhs);
	virtual ~CompositeCommand();

	void doIt(Command&& c);
	void doIt(Command const& c);
	void doIt(SmartPointer && cmd);
	void doIt() override;
	void undo() override;
	virtual std::unique_ptr<Command> clone() && override;
	virtual std::unique_ptr<Command> clone() const& override;

private:
	std::unique_ptr<UndoRedoManager> urMngr;
};

#endif /* COMPOSITECOMMAND_H_ */
