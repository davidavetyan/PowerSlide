#include "slideEditor.h"

namespace Core
{
SlideEditor::SlideEditor(std::shared_ptr<Core::SlideCollection> pSlideCollection)
	: m_pSlideCollection(pSlideCollection)
{
}

void SlideEditor::setSlideCollection(std::shared_ptr<Core::SlideCollection> pSlideCollection)
{
	m_pSlideCollection = pSlideCollection;
}

std::shared_ptr<SlideCollection> SlideEditor::getSlideCollection() const
{
	return m_pSlideCollection;
}

void SlideEditor::run(std::unique_ptr<IAction> pAction)
{
	pAction->execute();
	
	m_vUndoStack.push_back(std::move(pAction));
	m_vRedoStack.clear();

	emit sigActionExecuted();
}

bool SlideEditor::undo()
{
	if (m_vUndoStack.empty())
		return false;
	
	auto pAction = std::move(m_vUndoStack.back());
	m_vUndoStack.pop_back();
	
	pAction->unexecute();

	m_vRedoStack.push_back(std::move(pAction));

	emit sigActionExecuted();
	
	return true;
}

bool SlideEditor::redo()
{
	if (m_vRedoStack.empty())
		return false;

	auto pAction = std::move(m_vRedoStack.back());
	m_vRedoStack.pop_back();
	
	pAction->execute();

	m_vUndoStack.push_back(std::move(pAction));

	emit sigActionExecuted();
	
	return true;
}

bool SlideEditor::hasUndo()
{
	return !m_vUndoStack.empty();
}

bool SlideEditor::hasRedo()
{
	return !m_vRedoStack.empty();
}

}
