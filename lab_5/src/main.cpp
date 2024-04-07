#include <QApplication>
#include "main_window.h"

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	MainWindow* main_window = new MainWindow();
	main_window->show();

	return app.exec();
}