
#include "TcpServer.h"
#include <QtCore/QCoreApplication>

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	TcpServer server;

	if (!server.listen(QHostAddress::Any, 13888))
	{   //监听本地主机的13888端口，如果出错就输出错误信息，并关闭
		qDebug() << server.errorString();
	}
	
	qDebug() << "-----------------------------------------------------";
	qDebug() << "-->Server has launched.";
	qDebug() << "-->Server port:13888";
	return a.exec();
}
