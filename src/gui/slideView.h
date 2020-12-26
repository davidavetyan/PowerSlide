#ifndef GUI_SLIDEVIEW_H
#define GUI_SLIDEVIEW_H

#include <QWidget>

#include "core_slide.h"

namespace GUI
{

class SlideView : public QWidget
{
	Q_OBJECT
	
public:
    SlideView(QWidget* parent = nullptr);

	std::weak_ptr<Core::Slide> getSlide() const;
    void setSlide(std::weak_ptr<Core::Slide> pSlide);

	bool getActive() const;
	void setActive(bool bActive);

protected:
	void paintEvent(QPaintEvent* event) override;

	void mousePressEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

signals:
	void sigClicked(SlideView* pSlideView);
	
protected slots:
	void onSlideChanged();

protected:
    std::weak_ptr<Core::Slide> m_pSlide;
	bool m_bActive;
	bool m_bClickState; // used for emitting clicked signal
};

}
	
#endif
