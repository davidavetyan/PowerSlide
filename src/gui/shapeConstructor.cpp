#include "shapeConstructor.h"

#include <QMouseEvent>
#include <QWidget>

#include "core_shapeFactory.h"

namespace GUI
{
	
bool ShapeConstructor::eventFilter(QObject* pObject, QEvent* pEvent)
{
	return false;
}

LineConstructor::LineConstructor()
	: m_bDrawingMode(false),
	m_bUniform(false)
{
	m_pLine = std::make_shared<Core::Line>(0, 0, 0, 0);
}

bool LineConstructor::eventFilter(QObject* pObject, QEvent* pEvent)
{
	switch (pEvent->type())
	{
	case QEvent::MouseMove:
		{
			QMouseEvent* pMouseEvent = dynamic_cast<QMouseEvent*>(pEvent);

			if (m_bDrawingMode)
				m_pLine->setP2(pMouseEvent->pos());

			emit sigShapeChanged();
			break;
		}
	case QEvent::MouseButtonPress:
		{
			QMouseEvent* pMouseEvent = dynamic_cast<QMouseEvent*>(pEvent);

			m_pLine->setP1(pMouseEvent->pos());
			m_pLine->setP2(pMouseEvent->pos());

			m_bDrawingMode = true;
			break;
		}
	case QEvent::MouseButtonRelease:
		{
			m_bDrawingMode = false;

			if (m_pLine->length() > 2)
				emit sigShapeReady();
			
			break;
		}
	case QEvent::KeyPress:
		{
			QKeyEvent* pKeyEvent = dynamic_cast<QKeyEvent*>(pEvent);
			if (pKeyEvent->key() == Qt::ShiftModifier)
				m_bUniform = true;
			
			break;
		}
	case QEvent::KeyRelease:
		{
			QKeyEvent* pKeyEvent = dynamic_cast<QKeyEvent*>(pEvent);
			if (pKeyEvent->key() == Qt::ShiftModifier)
				m_bUniform = false;
			break;
		}
	default:
		return false;
	}

	auto* pWidget = dynamic_cast<QWidget*>(pObject);
	if (pWidget)
		pWidget->repaint();
	
	return false;
}

std::shared_ptr<Core::IShape> LineConstructor::getShape()
{
	return m_pLine;
}

RectConstructor::RectConstructor()
	: m_bDrawingMode(false),
	m_bUniform(false)
{
	m_pRect = std::make_shared<Core::Rectangle>(0, 0, 0, 0);
}

bool RectConstructor::eventFilter(QObject* pObject, QEvent* pEvent)
{
	switch (pEvent->type())
	{
	case QEvent::MouseButtonPress:
		{
			QMouseEvent* pMouseEvent = dynamic_cast<QMouseEvent*>(pEvent);

			m_bDrawingMode = true;

			m_pRect->setWidth(0);
			m_pRect->setHeight(0);
			m_pRect->setTopLeft(pMouseEvent->pos());

			break;
		}
	case QEvent::MouseMove:
		{
			QMouseEvent* pMouseEvent = dynamic_cast<QMouseEvent*>(pEvent);

			if (!m_bDrawingMode)
				return false;

			QPoint const& oTopLeft = m_pRect->getTopLeft();

			m_pRect->setWidth(pMouseEvent->pos().x() - oTopLeft.x());
			m_pRect->setHeight(pMouseEvent->pos().y() - oTopLeft.y());

			if (m_bUniform)
			{
				int x = pMouseEvent->pos().x();
				int y = pMouseEvent->pos().y();

				int nWidth = m_pRect->getWidth();
				int nHeight = m_pRect->getHeight();

				int nAbsWidth = (nWidth > 0 ? nWidth : (-1) * nWidth);
				int nAbsHeight = (nHeight > 0 ? nHeight : (-1) * nHeight);

				if (nAbsWidth > nAbsHeight)
				{
					m_pRect->setWidth(nAbsHeight * (x - oTopLeft.x() > 0 ? 1 : -1));
				}
				else
				{
					m_pRect->setHeight(nAbsWidth * (y - oTopLeft.y() > 0 ? 1 : -1));
				}
			}

			emit sigShapeChanged();

			break;
		}
	case QEvent::MouseButtonRelease:
		{
			m_bDrawingMode = false;
			emit sigShapeReady();
			break;
		}
	case QEvent::KeyPress:
		{
			QKeyEvent* pKeyEvent = dynamic_cast<QKeyEvent*>(pEvent);
			if (pKeyEvent->modifiers() & Qt::ShiftModifier)
				m_bUniform = true;
			break;
		}
	case QEvent::KeyRelease:
		{
			QKeyEvent* pKeyEvent = dynamic_cast<QKeyEvent*>(pEvent);
			if (pKeyEvent->key() == Qt::Key_Shift)
				m_bUniform = false;
			break;
		}
	default:
		return false;
	}

	QWidget* pWidget = dynamic_cast<QWidget*>(pObject);
	if (pWidget)
		pWidget->update();
	return false;
}

std::shared_ptr<Core::IShape> RectConstructor::getShape()
{
	return m_pRect;
}

EllipseConstructor::EllipseConstructor()
	: m_bDrawingMode(false)
{
	m_pEllipse = std::make_shared<Core::Ellipse>(QPoint(0, 0), 0, 0);
}

bool EllipseConstructor::eventFilter(QObject* pObject, QEvent* pEvent)
{
	switch (pEvent->type())
	{
	case QEvent::MouseButtonPress:
	{
		QMouseEvent* pMouseEvent = dynamic_cast<QMouseEvent*>(pEvent);

		m_pEllipse->setWidth(0);
		m_pEllipse->setHeight(0);
		m_pEllipse->setBoundingTopLeft(pMouseEvent->pos());

		m_bDrawingMode = true;
		break;
	}
	case QEvent::MouseMove:
	{
		QMouseEvent* pMouseEvent = dynamic_cast<QMouseEvent*>(pEvent);

		if (m_bDrawingMode)
		{
			QPoint oTopLeft = m_pEllipse->getBoundingTopLeft();
			int nWidth = pMouseEvent->pos().x() - oTopLeft.x();
			int nHeight = pMouseEvent->pos().y() - oTopLeft.y();

			m_pEllipse->setWidth(nWidth);
			m_pEllipse->setHeight(nHeight);
		}

		emit sigShapeChanged();

		break;
	}
	case QEvent::MouseButtonRelease:
	{
		m_bDrawingMode = false;
		emit sigShapeReady();
		break;
	}
	default:
		return false;
	}

	QWidget* pWidget = dynamic_cast<QWidget*>(pObject);
	if (pWidget)
		pWidget->update();
	return false;
}

std::shared_ptr<Core::IShape> EllipseConstructor::getShape()
{
	return m_pEllipse;
}

}
