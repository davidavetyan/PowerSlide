#include "shape.h"

#include <QPainter>

namespace Core
{

SShapeProperties& BasicShape::properties()
{
	return m_oProperties;
}

SShapeProperties BasicShape::getProperties() const
{
	return m_oProperties;
}

void BasicShape::setProperties(SShapeProperties const& oProperties)
{
	m_oProperties = oProperties;
}

void Line::draw(QPainter& painter, QRect const& rcDraw)
{
	painter.save();

	painter.setPen(m_oProperties.m_oPen);

	QTransform oTransform;
	oTransform.scale(rcDraw.width() / 800.0, rcDraw.height() / 600.0);
	painter.setTransform(oTransform);
	
	painter.drawLine(m_lnLine);

	painter.restore();
}

std::unique_ptr<IShape> Line::clone()
{
	IShape* pNewShape = new Line(*this);
	return std::unique_ptr<IShape>(pNewShape);
}

double Line::length()
{
	return ((QLineF)m_lnLine).length();
}

void Line::setP1(QPoint const& oPoint)
{
	m_lnLine.setP1(oPoint);
}

void Line::setP2(QPoint const& oPoint)
{
	m_lnLine.setP2(oPoint);
}

void Rectangle::draw(QPainter& painter, QRect const& rcDraw)
{
	painter.save();

	painter.setPen(m_oProperties.m_oPen);

	QTransform oTransform;
	oTransform.scale(rcDraw.width() / 800.0, rcDraw.height() / 600.0);
	painter.setTransform(oTransform);

	if (m_oProperties.m_clrFill.isValid())
		painter.fillRect(m_rcRect, m_oProperties.m_clrFill);
	
	painter.drawRect(m_rcRect);

	painter.restore();
}

std::unique_ptr<IShape> Rectangle::clone()
{
	IShape* pNewShape = new Rectangle(*this);
	return std::unique_ptr<IShape>(pNewShape);
}

int Rectangle::getWidth() const
{
	return m_rcRect.width();
}

void Rectangle::setWidth(int nWidth)
{
	m_rcRect.setWidth(nWidth);
}

int Rectangle::getHeight() const
{
	return m_rcRect.height();
}

void Rectangle::setHeight(int nHeight)
{
	m_rcRect.setHeight(nHeight);
}

QPoint Rectangle::getTopLeft() const
{
	return m_rcRect.topLeft();
}

void Rectangle::setTopLeft(QPoint const& oPoint)
{
	m_rcRect.setTopLeft(oPoint);
}

void Ellipse::draw(QPainter& painter, QRect const& rcDraw)
{
	painter.save();

	painter.setPen(m_oProperties.m_oPen);

	if (m_oProperties.m_clrFill.isValid())
		painter.setBrush(m_oProperties.m_clrFill);

	QTransform oTransform;
	oTransform.scale(rcDraw.width() / 800.0, rcDraw.height() / 600.0);
	painter.setTransform(oTransform);

	painter.drawEllipse(m_rcBoundingRect);

	painter.restore();
}

std::unique_ptr<IShape> Ellipse::clone()
{
	IShape* pNewShape = new Ellipse(*this);
	return std::unique_ptr<IShape>(pNewShape);
}

int Ellipse::getWidth() const
{
	return m_rcBoundingRect.width();
}

void Ellipse::setWidth(int nWidth)
{
	m_rcBoundingRect.setWidth(nWidth);
}

int Ellipse::getHeight() const
{
	return m_rcBoundingRect.height();
}

void Ellipse::setHeight(int nHeight)
{
	m_rcBoundingRect.setHeight(nHeight);
}

QPoint Ellipse::getBoundingTopLeft() const
{
	return m_rcBoundingRect.topLeft();
}

void Ellipse::setBoundingTopLeft(QPoint const& oPoint)
{
	m_rcBoundingRect.setTopLeft(oPoint);
}
	
}
