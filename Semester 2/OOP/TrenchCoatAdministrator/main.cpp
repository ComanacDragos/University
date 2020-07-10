#include "GUI.h"
#include "tests.h"
#include <QtWidgets/QApplication>
#include <qlabel.h>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	GUI gui{};
	gui.show();
	
	return a.exec();
}
