#include "PingPang.h"

PingPang::PingPang()
{
	server.setMaxPendingConnections(SERVER_MAX_CLIENT);
	if (!server.listen(QHostAddress::Any, PORT)) {
		qDebug() << server.errorString(); // 如果出错就输出错误信息，并关闭
		return;
	}
	qDebug() << "-->Server port:" << PORT;
	qDebug() << "-->Server max client:" << SERVER_MAX_CLIENT;
}


PingPang::~PingPang()
{
}
