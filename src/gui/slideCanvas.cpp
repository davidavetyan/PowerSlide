#include "slideCanvas.h"

#include <QPainter>

#include "core_slideEditor.h"

namespace GUI
{

SlideCanvas::SlideCanvas(QWidget* pParent)
	: SlideView(pParent)
{
	
}

void SlideCanvas::setSlideEditor(std::shared_ptr<Core::SlideEditor> pSlideEditor)
{
	std::shared_ptr<Core::SlideCollection> pOldCollection;
	if (m_pSlideEditor)
		pOldCollection = m_pSlideEditor->getSlideCollection();
	
	m_pSlideEditor = pSlideEditor;
	
	std::shared_ptr<Core::SlideCollection> pNewCollection;
	if (m_pSlideEditor)
		pNewCollection = m_pSlideEditor->getSlideCollection();

	if (pOldCollection != pNewCollection)
	{
		if (pOldCollection)
			disconnect(pOldCollection.get(), &Core::SlideCollection::sigActiveSlideChanged, this, &SlideCanvas::onActiveSlideChanged);
		if (pNewCollection)
			connect(pNewCollection.get(), &Core::SlideCollection::sigActiveSlideChanged, this, &SlideCanvas::onActiveSlideChanged);
	}
}

void SlideCanvas::setShapeConstructor(std::shared_ptr<ShapeConstructor> pShapeConstructor)
{
	if (m_pShapeConstructor)
	{
		removeEventFilter(m_pShapeConstructor.get());
		disconnect(m_pShapeConstructor.get(), &ShapeConstructor::sigShapeReady, this, &SlideCanvas::onShapeReady);
		disconnect(m_pShapeConstructor.get(), &ShapeConstructor::sigShapeChanged, this, &SlideCanvas::onShapeChanged);
	}

	m_pShapeConstructor = std::move(pShapeConstructor);
	
	if (m_pShapeConstructor)
	{
		installEventFilter(m_pShapeConstructor.get());
		connect(m_pShapeConstructor.get(), &ShapeConstructor::sigShapeReady, this, &SlideCanvas::onShapeReady);
		connect(m_pShapeConstructor.get(), &ShapeConstructor::sigShapeChanged, this, &SlideCanvas::onShapeChanged);
	}
}

void SlideCanvas::paintEvent(QPaintEvent* event)
{
	SlideView::paintEvent(event);

	QPainter oPainter(this);
	if (m_pTempShape)
		m_pTempShape->draw(oPainter, rect());
}

void SlideCanvas::onShapeChanged()
{
	if (!m_pShapeConstructor)
		return;

	m_pTempShape = m_pShapeConstructor->getShape();
}

void SlideCanvas::onShapeReady()
{
	auto pSlide = m_pSlide.lock();
	if (!pSlide)
		return;

	if (!m_pShapeConstructor)
		return;

	m_pTempShape = m_pShapeConstructor->getShape();
	if (!m_pTempShape)
		return;
	
	std::unique_ptr<Core::IAction> pAction = std::make_unique<Core::AddAction>(pSlide);
	pAction->setShape(m_pTempShape);

	m_pSlideEditor->run(std::move(pAction));

	setCursor(Qt::ArrowCursor);
	
	m_pTempShape.reset();

	removeEventFilter(m_pShapeConstructor.get());
}

void SlideCanvas::onActiveSlideChanged()
{
	if (!m_pSlideEditor)
		return;

	auto pSlideCollection = m_pSlideEditor->getSlideCollection();
	if (!pSlideCollection)
		return;

	setSlide(pSlideCollection->getActiveSlide());
}

}
