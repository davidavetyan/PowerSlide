#ifndef GUI_SLIDECANVAS_H
#define GUI_SLIDECANVAS_H

#include "slideView.h"
#include "shapeConstructor.h"

namespace Core
{
	class SlideEditor;
}

namespace GUI
{

class SlideCanvas : public SlideView
{
public:
	SlideCanvas(QWidget* pParent = nullptr);

	void setSlideEditor(std::shared_ptr<Core::SlideEditor> pSlideEditor);
	void setShapeConstructor(std::shared_ptr<ShapeConstructor> pShapeConstructor);

protected:
	void paintEvent(QPaintEvent* event) override;

protected slots:
	void onShapeChanged();
	void onShapeReady();

	void onActiveSlideChanged();

private:
	std::shared_ptr<Core::SlideEditor> m_pSlideEditor;
	std::shared_ptr<ShapeConstructor> m_pShapeConstructor;
	std::shared_ptr<Core::IShape> m_pTempShape;
};

}

#endif