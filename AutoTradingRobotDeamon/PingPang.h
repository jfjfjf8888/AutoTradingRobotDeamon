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
	* @brief 客户端连入
	* @param 连接句柄
	* @param socket指针
	*/
	void ClientConnected(qintptr, QTcpSocket*);//发送新用户连接信息

	/**
	* @brief socket已断开连接
	*   若需要在socket后析构后进行操作的可连接此信号
	* @param 连接句柄
	*/
	void ClientDisconnected(qintptr);

	/**
	* @brief 主动断开连接信号
	*   若服务端想要主动断开与客户端连接将会发出此信号
	*   此信号发出这表明进行断开操作不表明断开成功，成功以SocketDisconnected信号为准
	* @param 连接句柄
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

