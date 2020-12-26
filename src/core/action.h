#ifndef CORE_ACTION_H
#define CORE_ACTION_H

#include <memory>

#include "slide.h"

namespace Core
{

class IAction
{
public:
	inline IAction(std::shared_ptr<Slide> pSlide = nullptr);

	virtual void setSlide(std::shared_ptr<Slide> pSlide);
	virtual void setShape(std::shared_ptr<IShape> pShape);
	
	virtual void execute() = 0;
	virtual void unexecute() = 0;

protected:
	std::weak_ptr<Slide> m_pSlide;
	std::shared_ptr<IShape> m_pShape;
};

class AddAction : public IAction
{
public:
	AddAction(std::shared_ptr<Slide> pSlide = nullptr);
	
	void execute() override;
	void unexecute() override;
};

inline IAction::IAction(std::shared_ptr<Slide> pSlide)
	: m_pSlide(pSlide)
{
	
}

inline void IAction::setSlide(std::shared_ptr<Slide> pSlide)
{
	m_pSlide = pSlide;
}

}

#endif