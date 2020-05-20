#include "TcpServer.h"
#include "tcp_server_private.h"
//���캯��
TcpServer::TcpServer(QObject *parent)
	: QTcpServer(parent),
	private_(new tcp_server_private::TcpServerPrivate) {
}

//��������
TcpServer::~TcpServer() {
	for (tcp_server_private::TcpSocket *client : private_->clients.values()) {
		client->disconnectFromHost();
		auto handle = client->socketDescriptor();
		client->deleteLater();
		//��֪���������� ��ǰsocket�Ͽ�����������Ҫ��socket��ִ�еķ���
		emit ClientDisconnected(handle);
	}
	if (private_)
		delete private_;
	this->close();
}

//��д-�����ӵ���
void TcpServer::incomingConnection(qintptr handle) {
	//����������������ر�����
	if (private_->clients.size() > maxPendingConnections()) {
		QTcpSocket tcp;
		tcp.setSocketDescriptor(handle);
		tcp.disconnectFromHost();
		return;
	}
	auto client_socket = new tcp_server_private::TcpSocket(handle);
	Q_ASSERT(client_socket->socketDescriptor() == handle);

	//socket�Ͽ����ӵ��ź���server������
	connect(client_socket,
		&tcp_server_private::TcpSocket::ClientDisconnected,
		this,
		&TcpServer::ClientDisconnectedSlot);

	//�����Ͽ����ӵĲ���
	connect(this,
		&TcpServer::InitiativeDisConnectClient,
		client_socket,
		&tcp_server_private::TcpSocket::DisconnectSocket);
	//map��¼
	private_->clients.insert(handle, client_socket);
	qDebug() << handle << "connected";
	emit ClientConnected(handle, client_socket);
}

//�ͻ����ѶϿ���
void TcpServer::ClientDisconnectedSlot(qintptr handle) {
	//map���Ƴ�
	private_->clients.remove(handle);
	qDebug() << handle << "disconnected";
	//�����ź�
	emit ClientDisconnected(handle);
}