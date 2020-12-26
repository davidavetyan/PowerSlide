#ifndef GUI_SHAPECONSTRUCTOR_H
#define GUI_SHAPECONSTRUCTOR_H

#include <QObject>

#include "core_shape.h"

namespace GUI
{
	
class ShapeConstructor : public QObject
{
	Q_OBJECT

public:
	virtual std::shared_ptr<Core::IShape> getShape() = 0;

protected:
	bool eventFilter(QObject* pObject, QEvent* pEvent) override;
	
signals:
	void sigShapeChanged();
	void sigShapeReady();
};

class LineConstructor : public ShapeConstructor
{
public:
	LineConstructor();

	std::shared_ptr<Core::IShape> getShape() override;

protected:
	bool eventFilter(QObject* pObject, QEvent* pEvent) override;
	
private:
	bool m_bDrawingMode;
	bool m_bUniform;
	std::shared_ptr<Core::Line> m_pLine;
};

class RectConstructor : public ShapeConstructor
{
public:
	RectConstructor();

	std::shared_ptr<Core::IShape> getShape() override;

protected:
	bool eventFilter(QObject* pObject, QEvent* pEvent) override;
	
private:
	bool m_bDrawingMode;
	bool m_bUniform;
	std::shared_ptr<Core::Rectangle> m_pRect;
};

class EllipseConstructor : public ShapeConstructor
{
public:
	EllipseConstructor();

	std::shared_ptr<Core::IShape> getShape() override;

protected:
	bool eventFilter(QObject* pObject, QEvent* pEvent) override;
	
private:
	bool m_bDrawingMode;
	std::shared_ptr<Core::Ellipse> m_pEllipse;
};

}

#endif