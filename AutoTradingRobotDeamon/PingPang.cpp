#include "PingPang.h"
#include <QTcpSocket>
#include <QJsonParseError>
#include <QTimer>
#include <QProcess>

PingPang::PingPang()
{
	m_server.setMaxPendingConnections(SERVER_MAX_CLIENT);
	if (!m_server.listen(QHostAddress::Any, PORT)) {
		qDebug() << m_server.errorString(); // �����������������Ϣ�����ر�
		return;
	}

	connect(&m_server, &TcpServer::ClientConnected, this, &PingPang::ClientConnected);
	connect(&m_server, &TcpServer::ClientDisconnected, this, &PingPang::ClientDisconnected);
	connect(&m_server, &TcpServer::InitiativeDisConnectClient, this, &PingPang::InitiativeDisConnectClient);

	qDebug() << "--> Server port:" << PORT;
	qDebug() << "--> Server max client:" << SERVER_MAX_CLIENT;
}


PingPang::~PingPang()
{
}

void PingPang::ClientConnected(qintptr handle, QTcpSocket * socket)
{
	QTimer * timer = new QTimer;

	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeout()));
	connect(socket, &QTcpSocket::readyRead, this, &PingPang::readyRead);

	m_timerClientHandleMap.insert(handle, timer);
	m_timerClientSocketMap.insert(handle, socket);

	QString seyhi = "{\"msg\": \"welcome\"}";
	socket->write(seyhi.toUtf8());

	timer->start(5000);
}

void PingPang::ClientDisconnected(qintptr handle)
{
	//QTimer * timer = m_timerClientHandleMap.value(handle, nullptr);
	//if (timer) {
	//	timer->stop();
	//	delete timer;
	//}
	//m_timerClientHandleMap.remove(handle);
	//m_timerClientSocketMap.remove(handle);
}

void PingPang::InitiativeDisConnectClient(qintptr handle)
{
	QTimer * timer = m_timerClientHandleMap.value(handle, nullptr);
	if (timer) {
		timer->stop();
		delete timer;
	}
	m_timerClientHandleMap.remove(handle);
	m_timerClientSocketMap.remove(handle);
}

void PingPang::readyRead()
{
	QTcpSocket * socket = (QTcpSocket * )sender();
	if (socket) {
		qintptr handle = m_timerClientSocketMap.key(socket);
		QTimer * timer = m_timerClientHandleMap.value(handle);
		timer->stop();
		QByteArray data = socket->readAll();
		//qDebug() << "--> " << data;
		QJsonParseError jsonError;//Qt5���� 
		QJsonDocument document = QJsonDocument::fromJson(data, &jsonError);//Qt5����
		if (jsonError.error == QJsonParseError::NoError) {
			QVariantMap map = document.toVariant().toMap();
			QString name = map["name"].toString();
			QString msg = map["msg"].toString();
			m_timerClientNameMap.insert(handle, name);
			QString replyMsg = "{\"msg\": \"pang\"}";
			socket->write(replyMsg.toUtf8());
		}
		timer->start();
	}
}

void PingPang::timeout()
{
	QTimer * timer = (QTimer * )sender();
	if (timer) {
		// ���ػ��Ľ�������������
		qintptr handle = m_timerClientHandleMap.key(timer);
		QString name = m_timerClientNameMap.value(handle);
		if (!name.isEmpty()) {
			qDebug() << "launch robot.";
			QProcess* process = new QProcess;
			process->start(name, QStringList() << "");

			// �����ɾ���Լ����ȴ�����Ľ������ӽ���
			QTimer * timer = m_timerClientHandleMap.value(handle, nullptr);
			if (timer) {
				timer->stop();
				delete timer;
			}
			m_timerClientHandleMap.remove(handle);
			m_timerClientSocketMap.remove(handle);
			m_timerClientNameMap.remove(handle);
		}
	}
}
