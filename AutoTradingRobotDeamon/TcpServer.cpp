#include "TcpServer.h"
#include <QDebug>

TcpServer::TcpServer()
{
	tcpServer = new QTcpServer(this);
	if (!tcpServer->listen(QHostAddress::LocalHost, 13888))
	{   //监听本地主机的13888端口，如果出错就输出错误信息，并关闭
		qDebug() << tcpServer->errorString();
	}
	//连接信号和相应槽函数
	connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
	qDebug() << "------------------------------------------------------";
	qDebug() << "--> AutoTradingRobotDeamon v1.0 started.";
}


TcpServer::~TcpServer()
{
}

void TcpServer::newConnection()
{
	qDebug() << "new connection.";
}
