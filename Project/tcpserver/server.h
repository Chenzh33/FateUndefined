#ifndef SERVER_H
#define SERVER_H
#include <QtWidgets/QMainWindow>
#include <QTcpServer>
#include <QObject>
#include "tcpclientsocket.h"
#include"chessboard.h"
#include"qmap.h"
#include <qtimer.h>
class Server : public QTcpServer
{
	Q_OBJECT
public:
	Server(QObject *parent = 0, int port = 8010);
signals:
	void updateServer(QString);
public slots:
	void slotDisconnected(int);
	void nameList(TcpClientSocket*);
	void chat(const QVariantMap&);
	void findVital(const QString&, const QString&,const int&);
	void start(const QString&, TcpClientSocket*);
	void battle(const QVariantMap&, TcpClientSocket*);
	void sendName(const QString&, TcpClientSocket*);
	void lose(const QVariantMap&, TcpClientSocket*);
	void messageon(const QString&);
protected:
	void incomingConnection(qintptr socketDescriptor);
private:
	QList<TcpClientSocket*> tcpClientSocketList;
	QList<chessboard*> battleBoard;
	QMap<QString, TcpClientSocket*>userMap;
	bool over(int, QList<chessboard*>::iterator);
};

#endif // SERVER_H