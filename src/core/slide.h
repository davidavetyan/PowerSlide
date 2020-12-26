#ifndef CORE_SLIDE_H
#define CORE_SLIDE_H

#include <QGraphicsScene>

#include "shape.h"

namespace Core
{

class Slide : public QObject
{
	Q_OBJECT
	
public:
	void addShape(std::shared_ptr<IShape> pShape);
	void removeShape(std::shared_ptr<IShape> pShape);
	
	void draw(QPainter& oPainter, QRect const& rcDraw);

signals:
	void sigSlideChanged();
	
private:
	std::vector<std::shared_ptr<IShape>> m_vecShapes;
};

}

#endif