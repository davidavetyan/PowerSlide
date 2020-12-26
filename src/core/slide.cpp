#include "slide.h"

namespace Core
{

void Slide::addShape(std::shared_ptr<IShape> pShape)
{
	m_vecShapes.push_back(pShape);

	emit sigSlideChanged();
}

void Slide::removeShape(std::shared_ptr<IShape> pShape)
{
	auto it = std::find(m_vecShapes.begin(), m_vecShapes.end(), pShape);
	if (it != m_vecShapes.end())
	{
		m_vecShapes.erase(it);
		emit sigSlideChanged();
	}
}

void Slide::draw(QPainter& oPainter, QRect const& rcDraw)
{
	for (auto pShape : m_vecShapes)
		pShape->draw(oPainter, rcDraw);
}

}