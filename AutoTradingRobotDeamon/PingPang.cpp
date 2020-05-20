#include "PingPang.h"

PingPang::PingPang()
{
	server.setMaxPendingConnections(SERVER_MAX_CLIENT);
	if (!server.listen(QHostAddress::Any, PORT)) {
		qDebug() << server.errorString(); // �����������������Ϣ�����ر�
		return;
	}
	qDebug() << "-->Server port:" << PORT;
	qDebug() << "-->Server max client:" << SERVER_MAX_CLIENT;
}


PingPang::~PingPang()
{
}
