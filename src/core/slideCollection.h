#ifndef CORE_SLIDECOLLECTION_H
#define CORE_SLIDECOLLECTION_H

#include <memory>
#include <vector>

#include "slide.h"

namespace Core
{

class SlideCollection : public QObject
{
	Q_OBJECT
	
public:
	SlideCollection();

	void addSlide(std::shared_ptr<Slide> pSlide, bool bMakeActive = false);

	std::vector<std::shared_ptr<Slide>> const& getSlides() const;
	
	void setActiveSlide(int nIndex);
	void setActiveSlide(std::shared_ptr<Slide> pSlide);

	int getActiveSlideIndex() const;
	std::shared_ptr<Slide> getActiveSlide() const;

signals:
	void sigSlideAdded(int nPos);
	void sigActiveSlideChanged();
	
private:
	std::vector<std::shared_ptr<Slide>> m_vecSlides;
	int m_nActiveSlide;
};

inline SlideCollection::SlideCollection()
	: m_nActiveSlide(-1)
{
}
	
}

#endif
