#include "slideCollection.h"

namespace Core
{
	
void SlideCollection::addSlide(std::shared_ptr<Slide> pSlide, bool bMakeActive)
{
	if (!pSlide)
		return;
	
	m_vecSlides.push_back(pSlide);

	emit sigSlideAdded(m_vecSlides.size() - 1);
	
	if (bMakeActive)
	{
		setActiveSlide(m_vecSlides.size() - 1);
		emit sigActiveSlideChanged();
	}
}

std::vector<std::shared_ptr<Slide>> const& SlideCollection::getSlides() const
{
	return m_vecSlides;
}

void SlideCollection::setActiveSlide(int nIndex)
{
	Q_ASSERT(nIndex >= 0 && nIndex < m_vecSlides.size());

	m_nActiveSlide = nIndex;

	emit sigActiveSlideChanged();
}

void SlideCollection::setActiveSlide(std::shared_ptr<Slide> pSlide)
{
	auto it = std::find(m_vecSlides.begin(), m_vecSlides.end(), pSlide);
	if (it == m_vecSlides.end())
		return;

	m_nActiveSlide = it - m_vecSlides.begin();

	emit sigActiveSlideChanged();
}

int SlideCollection::getActiveSlideIndex() const
{
	return m_nActiveSlide;
}

std::shared_ptr<Slide> SlideCollection::getActiveSlide() const
{
	return m_vecSlides[m_nActiveSlide];
}
	
}
