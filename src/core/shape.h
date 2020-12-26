#ifndef CORE_SHAPE_H
#define CORE_SHAPE_H 

#include <QColor>
#include <QPen>

namespace Core
{

extern constexpr int g_nPenLengthDefault = 3;

struct SShapeProperties
{
	SShapeProperties()
	{
		m_oPen.setWidth(g_nPenLengthDefault);
	}

	SShapeProperties(QColor oColor, QPen oPen)
		: m_clrFill(oColor),
		m_oPen(oPen)
	{

	}

	QColor m_clrFill;
	QPen m_oPen;
};

class IShape
{
public:
	virtual void draw(QPainter& painter, QRect const& rcDraw) = 0;
	virtual std::unique_ptr<IShape> clone() = 0;

	virtual SShapeProperties& properties() = 0;
	virtual SShapeProperties getProperties() const = 0;
	virtual void setProperties(SShapeProperties const& oProperties) = 0;
};

class BasicShape : public IShape
{
public:
	BasicShape() = default;
	BasicShape(BasicShape const&) = default;
	BasicShape& operator=(BasicShape const&) = default;
	virtual ~BasicShape() = default;

	SShapeProperties& properties() override;
	SShapeProperties getProperties() const override;
	void setProperties(SShapeProperties const& oProperties) override;

protected:
	SShapeProperties m_oProperties;
};

class Line : public BasicShape
{
public:
	Line(int x1, int y1, int x2, int y2)
		: m_lnLine(x1, y1, x2, y2)
	{}

	Line(QPoint const& first, QPoint const& second)
		: m_lnLine(first, second)
	{}

	Line(Line const&) = default;
	Line& operator=(Line const&) = default;

	void draw(QPainter& painter, QRect const& rcDraw) override;

	std::unique_ptr<IShape> clone() override;

	double length();
	void setP1(QPoint const& oPoint);
	void setP2(QPoint const& oPoint);

private:
	QLine m_lnLine;
};
	
class Rectangle : public BasicShape
{
public:
	Rectangle(int x, int y, int width, int height)
		: m_rcRect(x, y, width, height)
	{
		m_rcRect = m_rcRect.normalized();
	}

	Rectangle(QPoint const& topLeft, QSize const& size)
		: m_rcRect(topLeft, size)
	{
		m_rcRect = m_rcRect.normalized();
	}

	Rectangle(Rectangle const&) = default;
	Rectangle& operator=(Rectangle const&) = default;

	void draw(QPainter& painter, QRect const& rcDraw) override;

	std::unique_ptr<IShape> clone() override;

	int getWidth() const;
	void setWidth(int nWidth);
	int getHeight() const;
	void setHeight(int nHeight);

	QPoint getTopLeft() const; 
	void setTopLeft(QPoint const& oPoint);
	
private:
	QRect m_rcRect;
};

class Ellipse : public BasicShape
{
public:
	Ellipse(QPoint ptCenter, int width, int height)
		: m_rcBoundingRect(ptCenter.x() - width / 2, ptCenter.y() - height / 2, width, height)
	{
		m_rcBoundingRect = m_rcBoundingRect.normalized();
	}

	Ellipse(QRect const& rcBounding)
		: m_rcBoundingRect(rcBounding)
	{
		m_rcBoundingRect = m_rcBoundingRect.normalized();
	}

	void draw(QPainter& painter, QRect const& rcDraw) override;

	std::unique_ptr<IShape> clone() override;

	int getWidth() const;
	void setWidth(int nWidth);
	int getHeight() const;
	void setHeight(int nHeight);

	QPoint getBoundingTopLeft() const; 
	void setBoundingTopLeft(QPoint const& oPoint);
	
private:
	QRect m_rcBoundingRect;
};

}

#endif