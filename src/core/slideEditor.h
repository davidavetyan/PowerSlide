#ifndef CORE_SLIDEEDITOR_H
#define CORE_SLIDEEDITOR_H

#include <memory>

#include "slideCollection.h"
#include "action.h"

namespace Core
{

class SlideEditor : public QObject
{
	Q_OBJECT
	
public:
	SlideEditor(std::shared_ptr<SlideCollection> pSlideCollection);
	
	void setSlideCollection(std::shared_ptr<SlideCollection> pSlideCollection);
	std::shared_ptr<SlideCollection> getSlideCollection() const;

	void run(std::unique_ptr<IAction> pAction);
	bool undo();
	bool redo();

	bool hasUndo();
	bool hasRedo();
	
signals:
	void sigActionExecuted();
	
private:
	std::shared_ptr<SlideCollection> m_pSlideCollection;
	std::vector<std::unique_ptr<IAction>> m_vUndoStack;
	std::vector<std::unique_ptr<IAction>> m_vRedoStack;
};

}

#endif
