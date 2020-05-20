
#ifndef TCP_SERVER_PRIVATE_H
#define TCP_SERVER_PRIVATE_H
#include <QTcpSocket>
namespace tcp_server_private {
	class TcpSocket : public QTcpSocket {
		Q_OBJECT
	public:
		/**
		* @brief ���캯��
		* @param socketDescriptor ���Ӿ��
		* @param parent ��QObject
		*/
		TcpSocket(qintptr handle, QObject *parent = 0);
	signals:
		/*
		* �ѶϿ������ź�
		*/
		void ClientDisconnected(qintptr);
		public slots:
		/**
		* @brief �Ͽ�����
		* @param handle ���Ӿ��
		*/
		void DisconnectSocket(qintptr handle);
	private:
		qintptr handle_;
	};
	/**
	* @brief Tcp��ͻ��˷�����˽����
	*/
	class TcpServerPrivate {
	public:
		QMap<int, TcpSocket *> clients; ///�������ӵ�map
	};
}//tcp_server_private
#endif // TCP_SERVER_PRIVATE_H

