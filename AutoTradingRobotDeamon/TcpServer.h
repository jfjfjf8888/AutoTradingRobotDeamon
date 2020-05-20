#ifndef TCP_SERVER_H
#define TCP_SERVER_H
#include <QTcpServer>

namespace tcp_server_private {
	class TcpServerPrivate;
}

class QTcpSocket;
/**
* @brief Tcp��ͻ��˷�����
*/
class TcpServer : public QTcpServer {
	Q_OBJECT
public:
	/**
	* @brief ���캯��
	* @param parent ��QObject
	*/
	explicit TcpServer(QObject *parent = Q_NULLPTR);
	/**
	* @brief ��������
	*    �Ƕ��߳�ģʽ��Ϊ���ر��������Ӻ�����
	*    ���߳�ģʽ��Ϊ���ر��������Ӽ��̳߳غ�����
	*/
	~TcpServer();
signals:
	/**
	* @brief �ͻ�������
	* @param ���Ӿ��
	* @param socketָ��
	*/
	void ClientConnected(qintptr, QTcpSocket*);//�������û�������Ϣ

	/**
	* @brief socket�ѶϿ�����
	*   ����Ҫ��socket����������в����Ŀ����Ӵ��ź�
	* @param ���Ӿ��
	*/
	void ClientDisconnected(qintptr);

	/**
	* @brief �����Ͽ������ź�
	*   ���������Ҫ�����Ͽ���ͻ������ӽ��ᷢ�����ź�
	*   ���źŷ�����������жϿ������������Ͽ��ɹ����ɹ���SocketDisconnected�ź�Ϊ׼
	* @param ���Ӿ��
	*/
	void InitiativeDisConnectClient(qintptr);

protected slots:
	/**
	* @brief �ͻ����ѶϿ���
	*   �˲���ͻ��˵��ѶϿ��ź�����
	* @param handle
	*/
	void ClientDisconnectedSlot(qintptr handle);
protected:
	/**
	* @brief ��д-�����ӵ���
	*    ���ӵ�����һ�����ӣ������maxPendingConnections�����Ƿ�����
	* @param handle ���Ӿ��
	*/
	virtual void incomingConnection(qintptr handle);
private:
	tcp_server_private::TcpServerPrivate *private_;
};
#endif // TCP_SERVER_H