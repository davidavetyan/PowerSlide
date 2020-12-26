#ifndef GUI_SLIDEMAINWINDOW_H
#define GUI_SLIDEMAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_PowerSlide.h"

#include <memory>

#include "commandPane.h"
#include "slideCanvas.h"
#include "slideCollectionView.h"

namespace GUI
{
	
class SlideMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	SlideMainWindow(QWidget* parent = Q_NULLPTR);

	CommandPane* getCommandPane() const;
	SlideCanvas* getSlideCanvas() const;
	SlideCollectionView* getSlideCollectionView() const;

	void setSlideEditor(std::shared_ptr<Core::SlideEditor> pSlideEditor);

protected slots:
	void onNewFileClicked();
	void onOpenFileClicked();
	void onNewSlideClicked();
	void onSaveImageClicked();
	void onUndoClicked();
	void onRedoClicked();
	void onLineClicked();
	void onRectClicked();
	void onEllipseClicked();
	
	void onActionExecuted();

protected:
	void addMenus();
	void addToolBarActions();
	void updateToolBarActions();

	enum class ActionType
	{
		Line,
		Rect,
		Ellipse,
		New,
		Save,
		Undo,
		Redo
	};

private:
	Ui::PowerSlideClass ui;
	std::unique_ptr<CommandPane> m_pCommandPane;
	std::unique_ptr<SlideCanvas> m_pSlideCanvas;
	std::unique_ptr<SlideCollectionView> m_pSlideCollectionView;
	
	std::shared_ptr<Core::SlideEditor> m_pSlideEditor;
	std::multimap<ActionType, QAction*> m_mapTypeToAction;
};
	
}

#endif