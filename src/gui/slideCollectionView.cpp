#include "slideCollectionView.h"

#include <QVBoxLayout>

#include "core_slideCollection.h"
#include "slideView.h"

namespace GUI
{
	
SlideCollectionView::SlideCollectionView(QWidget* parent)
	: QScrollArea(parent),
	m_pSlideCollection(std::make_shared<Core::SlideCollection>())
{
	QWidget* pSlideCollectionViewWidget = new QWidget();
	
	QVBoxLayout* pCollectionViewWidgetLayout = new QVBoxLayout(pSlideCollectionViewWidget);
	pCollectionViewWidgetLayout->setAlignment(Qt::AlignTop);

	setWidget(pSlideCollectionViewWidget);
}

void SlideCollectionView::setSlideCollection(std::shared_ptr<Core::SlideCollection> pSlideCollection)
{
	if (pSlideCollection)
	{
		disconnect(pSlideCollection.get(), &Core::SlideCollection::sigSlideAdded, this, &SlideCollectionView::onSlideAdded);
		disconnect(pSlideCollection.get(), &Core::SlideCollection::sigActiveSlideChanged, this, &SlideCollectionView::onActiveSlideChanged);
	}
	
	m_pSlideCollection = pSlideCollection;
	
	m_vecSlideViews.clear();

	if (!m_pSlideCollection)
		return;

	connect(m_pSlideCollection.get(), &Core::SlideCollection::sigSlideAdded, this, &SlideCollectionView::onSlideAdded);
	connect(m_pSlideCollection.get(), &Core::SlideCollection::sigActiveSlideChanged, this, &SlideCollectionView::onActiveSlideChanged);
	
	auto const& pSlides = m_pSlideCollection->getSlides();
	for (auto pSlide : pSlides)
	{
		std::shared_ptr<SlideView> pSlideView = std::make_shared<SlideView>();

		widget()->layout()->addWidget(pSlideView.get());

		pSlideView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
		pSlideView->setFixedHeight(150);

		pSlideView->setSlide(pSlide);
		
		connect(pSlideView.get(), &SlideView::sigClicked, this, &SlideCollectionView::onSlideViewClicked);
		
		m_vecSlideViews.push_back(pSlideView);
	}

	int nActiveIndex = m_pSlideCollection->getActiveSlideIndex();
	if (nActiveIndex != -1)
	{
		Q_ASSERT(nActiveIndex < m_vecSlideViews.size());
		m_vecSlideViews[nActiveIndex]->setActive(true);
	}

	repaint();
}

std::shared_ptr<Core::SlideCollection> SlideCollectionView::getSlideCollection() const
{
	return m_pSlideCollection;
}

void SlideCollectionView::mousePressEvent(QMouseEvent* event)
{
	QScrollArea::mousePressEvent(event);
}

void SlideCollectionView::onSlideAdded(int nPos)
{
	Q_ASSERT(m_pSlideCollection);
	
	auto const& pSlides = m_pSlideCollection->getSlides();
	Q_ASSERT(nPos > 0 && nPos < pSlides.size() && nPos <= m_vecSlideViews.size());

	std::shared_ptr<SlideView> pSlideView = std::make_shared<SlideView>();

	widget()->layout()->addWidget(pSlideView.get());

	pSlideView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	pSlideView->setFixedHeight(150);

	m_vecSlideViews.insert(m_vecSlideViews.begin() + nPos, pSlideView);

	Q_ASSERT(pSlides.size() == m_vecSlideViews.size());

	pSlideView->setSlide(pSlides.at(nPos));

	connect(pSlideView.get(), &SlideView::sigClicked, this, &SlideCollectionView::onSlideViewClicked);

	repaint();
}

void SlideCollectionView::onActiveSlideChanged()
{
	auto const& pSlides = m_pSlideCollection->getSlides();
	Q_ASSERT(pSlides.size() == m_vecSlideViews.size());

	for (size_t i = 0; i < m_vecSlideViews.size(); ++i)
	{
		auto const& pSlide = pSlides.at(i);
		auto pSlideView = m_vecSlideViews.at(i);

		pSlideView->setSlide(pSlide);
		pSlideView->setActive(false);
	}

	int nActiveIndex = m_pSlideCollection->getActiveSlideIndex();
	if (nActiveIndex != -1)
	{
		Q_ASSERT(nActiveIndex < m_vecSlideViews.size());
		m_vecSlideViews[nActiveIndex]->setActive(true);
	}

	repaint();
}

void SlideCollectionView::onSlideViewClicked(SlideView* pSlideView)
{
	if (!pSlideView)
		return;
	
	auto pSlide = pSlideView->getSlide().lock();
	if (pSlide)
		m_pSlideCollection->setActiveSlide(pSlide);
}

}
