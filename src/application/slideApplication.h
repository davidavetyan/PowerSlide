#ifndef SLIDEAPPLICATION_H
#define SLIDEAPPLICATION_H

#include <QApplication>

namespace Core
{
	class SlideCollection;
	class SlideEditor;
}

namespace GUI
{
	class SlideMainWindow;
}

namespace CMD
{
	class CommandHandler;
}

class SlideApplication : public QApplication
{
public:
	SlideApplication(int& argc, char** argv, int i = QCoreApplication::ApplicationFlags)
		: QApplication(argc, argv, i),
		m_pSlideMainWindow(nullptr)
	{
	}

	void init(GUI::SlideMainWindow* pMainWindow);
	
private:
	GUI::SlideMainWindow* m_pSlideMainWindow;
	std::shared_ptr<CMD::CommandHandler> m_pCommandHandler;
	std::shared_ptr<Core::SlideCollection> m_pSlideCollection;
	std::shared_ptr<Core::SlideEditor> m_pSlideEditor;
};

#endif