#include "MainWindow.h"
#include <QApplication>

#define APPLICATION_NAME "Lcd 2020"
#define AUTHOR_NAME "Ruilx"
#define ORGANIZATION_NAME "GT-Soft"
#define ORGANIZATION_DOMAIN "www.ruilx.top"
#define APPLICATION_VERSION "0.1"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setApplicationName(APPLICATION_NAME);
	a.setOrganizationName(ORGANIZATION_NAME);
	a.setOrganizationDomain(ORGANIZATION_DOMAIN);
	a.setApplicationVersion(APPLICATION_VERSION);
	a.setApplicationDisplayName(APPLICATION_NAME);
	MainWindow w;
	w.show();

	return a.exec();
}
