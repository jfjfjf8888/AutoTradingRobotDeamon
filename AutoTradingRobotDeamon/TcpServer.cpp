#include "TcpServer.h"
#include <QDebug>

TcpServer::TcpServer()
{
	tcpServer = new QTcpServer(this);
	if (!tcpServer->listen(QHostAddress::LocalHost, 13888))
	{   //��������������13888�˿ڣ������������������Ϣ�����ر�
		qDebug() << tcpServer->errorString();
	}
	//�����źź���Ӧ�ۺ���
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
