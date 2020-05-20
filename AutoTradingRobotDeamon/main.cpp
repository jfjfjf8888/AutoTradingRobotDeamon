
#include "PingPang.h"
#include <QtCore/QCoreApplication>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	qDebug() << "-----------------------------------------------------";
	qDebug() << "-->Server has launched.";

	PingPang pingPang;
	return a.exec();
}
