
#include "TcpServer.h"
#include <QtCore/QCoreApplication>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	TcpServer server;

	if (!server.listen(QHostAddress::Any, 13888))
	{   //��������������13888�˿ڣ������������������Ϣ�����ر�
		qDebug() << server.errorString();
	}
	
	qDebug() << "-----------------------------------------------------";
	qDebug() << "-->Server has launched.";
	qDebug() << "-->Server port:13888";
	return a.exec();
}
