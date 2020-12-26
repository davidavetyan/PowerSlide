#include "action.h"

namespace Core
{
	
void IAction::setShape(std::shared_ptr<IShape> pShape)
{
	m_pShape = pShape;
}

AddAction::AddAction(std::shared_ptr<Slide> pSlide)
	: IAction(pSlide)
{
}

void AddAction::execute()
{
	auto pSlide = m_pSlide.lock();
	if (pSlide)
		pSlide->addShape(m_pShape);
}

void AddAction::unexecute()
{
	auto pSlide = m_pSlide.lock();
	if (pSlide)
		pSlide->removeShape(m_pShape);
}

}
