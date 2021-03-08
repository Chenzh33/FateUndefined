#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H
#include <QtWidgets/QMainWindow>
#include <QTcpSocket>
#include <QObject>
#include"qjsondocument.h"

class TcpClientSocket : public QTcpSocket
{
	Q_OBJECT
public:
	TcpClientSocket(QObject *parent = 0);
	QString name;
	bool _HasStartGame;
signals:
	void nameList(TcpClientSocket*);
	void chat(const QVariantMap&);
	void findVital(const QString&,const QString&,const int&);
	void start(const QString&, TcpClientSocket*);
	void battle(const QVariantMap&, TcpClientSocket*);
	void sendName(const QString&, TcpClientSocket*);
	void disconnected(const int&);
	void messageon(const QString&);
	void lose(const QVariantMap&, TcpClientSocket*);
public slots:
	void dataReceived();
	void slotDisconnected();
};

#endif // TCPCLIENTSOCKET_H