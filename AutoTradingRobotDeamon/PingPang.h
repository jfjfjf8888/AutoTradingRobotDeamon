#pragma once
#include "TcpServer.h"
#include <QObject>
#include <QMap>

#define SERVER_MAX_CLIENT 10
#define PORT 13888

class QTcpSocket;
class QTimer;

class PingPang : public QObject
{
	Q_OBJECT
public:
	PingPang();
	~PingPang();


public slots:
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

	void readyRead();
	void timeout();
private:
	TcpServer m_server;
	QMap<qintptr, QTimer *> m_timerClientHandleMap;
	QMap<qintptr, QTcpSocket *> m_timerClientSocketMap;
	QMap<qintptr, QString> m_timerClientNameMap;
};

