#ifndef TCPCLIENT_H
#define TCPCLIENT_H


#include <QHostAddress>
#include <QTcpSocket>
#include"qjsondocument.h"
#include"qjsondocument.h"

class TcpClient : public QObject
{
	Q_OBJECT

public:
	TcpClient(QWidget *parent = 0);
	~TcpClient();

	bool HasConnected;
	QString ip;
	QString userName;
	QString enemyName;
	QTcpSocket *tcpSocket;
	void Enter();
	//void Connected();
public slots:
	void disconnected();
	void dataReceived();
	//void displayError(QAbstractSocket::SocketError);
signals:
	//void emiterror(QAbstractSocket::SocketError);
	void nameError();
	void nameTrue();
	void nameList(QVariantList);
	void getInvite(QString,int);
	void startGame();
	void battleData(QVariantMap);
	void gameOver(bool);
private:
	bool status;
	int port;
	QHostAddress *serverIP;
	

};

#endif // TCPCLIENT_H

