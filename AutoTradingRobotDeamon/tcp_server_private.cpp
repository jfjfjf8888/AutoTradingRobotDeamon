//cpp
#include "tcp_server_private.h"
namespace tcp_server_private {
	//���캯��
	TcpSocket::TcpSocket(qintptr handle, QObject *parent)
		: QTcpSocket(parent), handle_(handle) {
		this->setSocketDescriptor(handle_);
		//�Ͽ�������Ϣ
		connect(this, &TcpSocket::disconnected,
			[&]() {
			this->deleteLater();
			emit this->ClientDisconnected(handle_);
		});
	}
	//�����Ͽ����Ӳ�
	void TcpSocket::DisconnectSocket(qintptr handle) {
		if (handle == handle_)
			disconnectFromHost();
	}
}