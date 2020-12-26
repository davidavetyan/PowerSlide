#include "slideMainWindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QPainter>

#include "core_slideEditor.h"

namespace GUI
{

SlideMainWindow::SlideMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.horizontalLayout->setAlignment(Qt::AlignCenter);

	addMenus();
	addToolBarActions();

	m_pSlideCollectionView = std::make_unique<SlideCollectionView>(ui.centralWidget);
	m_pSlideCollectionView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
	m_pSlideCollectionView->setMinimumWidth(300);
	m_pSlideCollectionView->setWidgetResizable(true);

	ui.horizontalLayout->insertWidget(0, m_pSlideCollectionView.get());

	m_pSlideCanvas = std::make_unique<SlideCanvas>(this);
	m_pSlideCanvas->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	m_pSlideCanvas->setFixedSize(800, 600);

	ui.scrollAreaHorizontalLayout->setAlignment(Qt::AlignCenter);
	ui.scrollAreaHorizontalLayout->addWidget(m_pSlideCanvas.get());
	
	m_pCommandPane = std::make_unique<CommandPane>(this);
	ui.verticalLayout->addWidget(m_pCommandPane.get());
}

CommandPane* SlideMainWindow::getCommandPane() const
{
	return m_pCommandPane.get();
}

SlideCanvas* SlideMainWindow::getSlideCanvas() const
{
	return m_pSlideCanvas.get();
}

SlideCollectionView* SlideMainWindow::getSlideCollectionView() const
{
	return m_pSlideCollectionView.get();
}

void SlideMainWindow::setSlideEditor(std::shared_ptr<Core::SlideEditor> pSlideEditor)
{
	if (m_pSlideEditor)
		disconnect(m_pSlideEditor.get(), &Core::SlideEditor::sigActionExecuted, this, &SlideMainWindow::onActionExecuted);
	
	m_pSlideEditor = pSlideEditor;
	if (m_pSlideEditor)
		connect(m_pSlideEditor.get(), &Core::SlideEditor::sigActionExecuted, this, &SlideMainWindow::onActionExecuted);

	m_pSlideCanvas->setSlideEditor(pSlideEditor);
	updateToolBarActions();
}

void SlideMainWindow::onNewFileClicked()
{
	// TODO implement
}

void SlideMainWindow::onOpenFileClicked()
{
	// TODO implement
}

void SlideMainWindow::onNewSlideClicked()
{
	if (!m_pSlideEditor)
		return;
	
	auto pSlideCollection = m_pSlideEditor->getSlideCollection();
	if (!pSlideCollection)
		return;

	pSlideCollection->addSlide(std::make_shared<Core::Slide>(), true);
}

void SlideMainWindow::onActionExecuted()
{
	updateToolBarActions();
}

void SlideMainWindow::onSaveImageClicked()
{
	QString sImagePath = QFileDialog::getSaveFileName(this,
		tr("Save File"),
		"",
		tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" )
	);

	if (sImagePath.isEmpty())
		return;
	
	QImage imSlide(m_pSlideCanvas->size(), QImage::Format_ARGB32);
	imSlide.fill(Qt::white);
	
	QPainter oPainter(&imSlide);
	oPainter.setRenderHint(QPainter::Antialiasing);
	
	auto pSlideCollection = m_pSlideEditor->getSlideCollection();
	assert(pSlideCollection);

	auto pSlide = pSlideCollection->getActiveSlide();
	pSlide->draw(oPainter, m_pSlideCanvas->rect());

	if (!imSlide.save(sImagePath))
		QMessageBox::critical(this, "Error", "Couldn't save slide in file");
}

void SlideMainWindow::onUndoClicked()
{
	assert(m_pSlideEditor->undo());
}

void SlideMainWindow::onRedoClicked()
{
	assert(m_pSlideEditor->redo());
}

void SlideMainWindow::onLineClicked()
{
	m_pSlideCanvas->setCursor(Qt::CrossCursor);
	
	auto pLineConstructor = std::make_shared<LineConstructor>();
	m_pSlideCanvas->setShapeConstructor(pLineConstructor);
}

void SlideMainWindow::onRectClicked()
{
	m_pSlideCanvas->setCursor(Qt::CrossCursor);
	
	auto pRectConstructor = std::make_shared<RectConstructor>();
	m_pSlideCanvas->setShapeConstructor(pRectConstructor);
}

void SlideMainWindow::onEllipseClicked()
{
	m_pSlideCanvas->setCursor(Qt::CrossCursor);
	
	auto pEllipseConstructor = std::make_shared<EllipseConstructor>();
	m_pSlideCanvas->setShapeConstructor(pEllipseConstructor);
}

void SlideMainWindow::addMenus()
{
	QMenuBar* pMenuBar = ui.menuBar;

	QMenu* pFileMenu = new QMenu("File", this);

	QAction* pAction = pFileMenu->addAction("New");
	pAction->setEnabled(false);
	connect(pAction, &QAction::triggered, this, &SlideMainWindow::onNewFileClicked);
	
	pAction = pFileMenu->addAction("Open");
	pAction->setEnabled(false);
	connect(pAction, &QAction::triggered, this, &SlideMainWindow::onOpenFileClicked);

	pMenuBar->addMenu(pFileMenu);

	QMenu* pEditMenu = new QMenu("Edit", this);
	
	pAction = pEditMenu->addAction("Undo");
	connect(pAction, &QAction::triggered, this, &SlideMainWindow::onUndoClicked);

	m_mapTypeToAction.insert({ ActionType::Undo, pAction });
	
	pAction = pEditMenu->addAction("Redo");
	connect(pAction, &QAction::triggered, this, &SlideMainWindow::onRedoClicked);

	m_mapTypeToAction.insert({ ActionType::Redo, pAction });

	pMenuBar->addMenu(pEditMenu);

	QMenu* pHelpMenu = new QMenu("Help", this);

	pAction = pHelpMenu->addAction("About");
	connect(pAction, &QAction::triggered, [=]() {
		QMessageBox::about(this, "About", "PowerSlide ver 1.0");
	});
	
	pMenuBar->addMenu(pHelpMenu);
}

void SlideMainWindow::addToolBarActions()
{
	QToolBar* pToolBar = ui.mainToolBar;
	if (pToolBar == nullptr)
		return;

	QAction* pAction = new QAction(QIcon("./Resources/Icons/newSlide.png"), "New");
	pToolBar->addAction(pAction);
	pAction->setCheckable(false);
	m_mapTypeToAction.insert({ ActionType::New, pAction });

	connect(pAction, &QAction::triggered, this, &SlideMainWindow::onNewSlideClicked);

	pAction = new QAction(QIcon("./Resources/Icons/save.png"), "Save");
	pToolBar->addAction(pAction);
	pAction->setCheckable(false);
	m_mapTypeToAction.insert({ ActionType::Save, pAction });

	connect(pAction, &QAction::triggered, this, &SlideMainWindow::onSaveImageClicked);

	pToolBar->addSeparator();

	pAction = new QAction(QIcon("./Resources/Icons/undo.png"), "Undo");
	pToolBar->addAction(pAction);
	pAction->setCheckable(false);
	pAction->setEnabled(false);
	m_mapTypeToAction.insert({ ActionType::Undo, pAction });

	connect(pAction, &QAction::triggered, this, &SlideMainWindow::onUndoClicked);

	pAction = new QAction(QIcon("./Resources/Icons/redo.png"), "Redo");
	pToolBar->addAction(pAction);
	pAction->setCheckable(false);
	pAction->setEnabled(false);
	m_mapTypeToAction.insert({ ActionType::Redo, pAction });

	connect(pAction, &QAction::triggered, this, &SlideMainWindow::onRedoClicked);

	pToolBar->addSeparator();

	pToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	setStyleSheet("QToolButton { padding; 5px 40px 5px 40px}");

	QActionGroup* pShapeActionGroup = new QActionGroup(pToolBar);
	pShapeActionGroup->setExclusionPolicy(QActionGroup::ExclusionPolicy::Exclusive);

	pAction = new QAction(QIcon("./Resources/Icons/line.png"), "Line", pShapeActionGroup);
	pToolBar->addAction(pAction);
	pAction->setCheckable(false);
	pAction->setData((int) ActionType::Line);
	m_mapTypeToAction.insert({ ActionType::Line, pAction });

	connect(pAction, &QAction::triggered, this, &SlideMainWindow::onLineClicked);

	pAction = new QAction(QIcon("./Resources/Icons/ellipse.png"), "Ellipse", pShapeActionGroup);
	pToolBar->addAction(pAction);
	pAction->setCheckable(false);
	pAction->setData((int) ActionType::Ellipse);
	m_mapTypeToAction.insert({ ActionType::Ellipse, pAction });

	connect(pAction, &QAction::triggered, this, &SlideMainWindow::onEllipseClicked);

	pAction = new QAction(QIcon("./Resources/Icons/rectangle.png"), "Rectangle", pShapeActionGroup);
	pToolBar->addAction(pAction);
	pAction->setCheckable(false);
	pAction->setData((int) ActionType::Rect);
	m_mapTypeToAction.insert({ ActionType::Rect, pAction });

	connect(pAction, &QAction::triggered, this, &SlideMainWindow::onRectClicked);

	pToolBar->addSeparator();
}

void SlideMainWindow::updateToolBarActions()
{
	const auto pairUndoRange = m_mapTypeToAction.equal_range(ActionType::Undo);
	for (auto it = pairUndoRange.first; it != pairUndoRange.second; ++it)
		it->second->setEnabled(m_pSlideEditor && m_pSlideEditor->hasUndo());

	const auto pairRedoRange = m_mapTypeToAction.equal_range(ActionType::Redo);
	for (auto it = pairRedoRange.first; it != pairRedoRange.second; ++it)
		it->second->setEnabled(m_pSlideEditor && m_pSlideEditor->hasRedo());
}
	
}
