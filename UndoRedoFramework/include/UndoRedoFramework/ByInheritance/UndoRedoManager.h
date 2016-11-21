#ifndef UNDOREDOMANAGERBYINHERITANCE_H
#define UNDOREDOMANAGERBYINHERITANCE_H

#include <UndoRedoFramework/UndoRedoStack.h>
#include <UndoRedoFramework/Command.h>

namespace UndoRedoFramework{
namespace ByInheritance{

class UndoRedoManager : public
virtual
UndoRedoStack
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
}} // end namespace

#endif //UNDOREDOMANAGERBYINHERITANCE_H
