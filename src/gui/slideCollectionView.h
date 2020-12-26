#ifndef GUI_SLIDECOLLECTIONVIEW_H
#define GUI_SLIDECOLLECTIONVIEW_H

#include <QScrollArea>

namespace Core
{
	class SlideCollection;
}

namespace GUI
{

	class SlideView;
	
class SlideCollectionView : public QScrollArea
{
public:
	explicit SlideCollectionView(QWidget* parent = nullptr);

	void setSlideCollection(std::shared_ptr<Core::SlideCollection> pSlideCollection);
	std::shared_ptr<Core::SlideCollection> getSlideCollection() const;

protected:
	void mousePressEvent(QMouseEvent* event) override;

protected slots:
	void onSlideAdded(int nPos);
	void onActiveSlideChanged();

	void onSlideViewClicked(SlideView* pSlideView);

private:
	std::shared_ptr<Core::SlideCollection> m_pSlideCollection;
	std::vector<std::shared_ptr<SlideView>> m_vecSlideViews;
};

}

#endif