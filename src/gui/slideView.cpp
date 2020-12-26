#include "slideView.h"

#include <QPainter>
#include <QStyleOption>

namespace GUI
{
	
SlideView::SlideView(QWidget* parent)
	: QWidget(parent),
	m_bActive(false),
	m_bClickState(false)
{
	setAttribute(Qt::WA_StyledBackground, true);
	setStyleSheet("border: 1px solid gray; background-color: white");
}

std::weak_ptr<Core::Slide> SlideView::getSlide() const
{
	return m_pSlide;
}

void SlideView::setSlide(std::weak_ptr<Core::Slide> pSlide)
{
	if (m_pSlide.lock() == pSlide.lock())
		return;
	
	auto pPrevSlide = m_pSlide.lock();
	if (pPrevSlide)
		disconnect(pPrevSlide.get(), &Core::Slide::sigSlideChanged, this, &SlideView::onSlideChanged);
	
	m_pSlide = pSlide;
	auto pCurrentSlide = m_pSlide.lock();
	if (pCurrentSlide)
		connect(pCurrentSlide.get(), &Core::Slide::sigSlideChanged, this, &SlideView::onSlideChanged);
	
	repaint();
}

bool SlideView::getActive() const
{
	return m_bActive;
}

void SlideView::setActive(bool bActive)
{
	if (m_bActive == bActive)
		return;

	m_bActive = bActive;
	if (m_bActive)
		setStyleSheet("border: 2px solid orange; background-color: white");
	else
		setStyleSheet("border: 1px solid gray; background-color: white");
}

void SlideView::paintEvent(QPaintEvent* event)
{
	QPainter oPainter(this);
	oPainter.setRenderHint(QPainter::Antialiasing);
	
	auto pSlide = m_pSlide.lock();
	if (pSlide)
		pSlide->draw(oPainter, rect());
}

void SlideView::mousePressEvent(QMouseEvent* event)
{
	QWidget::mousePressEvent(event);

	m_bClickState = true;
}

void SlideView::mouseReleaseEvent(QMouseEvent* event)
{
	QWidget::mousePressEvent(event);

	if (m_bClickState)
		emit sigClicked(this);
}

void SlideView::onSlideChanged()
{
	repaint();
}

}
