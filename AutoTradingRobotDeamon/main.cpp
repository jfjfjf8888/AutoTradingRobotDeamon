
#include "TcpServer.h"
#include <QtCore/QCoreApplication>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	TcpServer server;
	// 
	return a.exec();
}
