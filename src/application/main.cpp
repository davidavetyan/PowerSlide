#include "slideApplication.h"
#include "gui_slideMainWindow.h"

int main(int argc, char *argv[])
{
	SlideApplication a(argc, argv);
	
	GUI::SlideMainWindow w;
	w.show();

	a.init(&w);
	return a.exec();
}
