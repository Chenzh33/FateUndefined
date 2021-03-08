#include "tcpclient.h"

TcpClient::TcpClient(QWidget *parent)
{
	status = false;
	port = 8010;
	serverIP = new QHostAddress();
	HasConnected = false;
}

TcpClient::~TcpClient()
{

}

void TcpClient::Enter()
{
	if (!status)
	{
		QString ip = "127.0.0.1";
		if (!serverIP->setAddress(ip))
		{
			//这里理应发出警告
			return;
		}

		tcpSocket = new QTcpSocket(this);
		//connect(tcpSocket, SIGNAL(connected()), this, SLOT(Connected()));
		connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(disconnected()));
		connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(dataReceived()));
		//connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

		tcpSocket->connectToHost(*serverIP, port);

		status = true;
	}
	else
	{
		int length = 0;
		QVariantMap message;
		message.insert("state", "disconnect");
		message.insert("name", userName);
		QString json = QJsonDocument::fromVariant(message).toJson();

		if ((length = tcpSocket->write(json.toLocal8Bit(), json.toLocal8Bit().length())) != json.toLocal8Bit().length())
		{
			return;
		}

		tcpSocket->disconnectFromHost();
		status = false;
	}
}
/*
void TcpClient::displayError(QAbstractSocket::SocketError error){
emit(emiterror(error));
}*/
/*
void TcpClient::Connected()
{
int length = 0;
QVariantMap message;
message.insert("state", "connect");
message.insert("initname", userName);

QString json = QJsonDocument::fromVariant(message).toJson();

if ((length = tcpSocket->write(json.toLocal8Bit(), json.toLocal8Bit().length())) != json.toLocal8Bit().length())
{
return;
}
}*/

void TcpClient::disconnected(){

}


void TcpClient::dataReceived()
{
	while (tcpSocket->bytesAvailable()>0)
	{
		int length = tcpSocket->bytesAvailable();
		char buf[1024];
		tcpSocket->read(buf, length);
		buf[length] = '\0';
		QString msg = QString::fromLocal8Bit(buf);

		QJsonParseError error;
		QJsonDocument jsonDocument = QJsonDocument::fromJson(msg.toUtf8(), &error);
		if (error.error == QJsonParseError::NoError){
			if (jsonDocument.isObject()){
				QVariantMap result = jsonDocument.toVariant().toMap();
				QString cstate = result["state"].toString();
				if (cstate == "request"){
					//获得在线用户列表
					QVariantList nameli = result["nameList"].toList();
					emit(nameList(nameli));
				}
				else if (cstate == "connect"){
					if (result["from"].toBool()){
						userName = result["name"].toString();
						emit(nameTrue());
					}
					else{
						emit(nameError());
					}
				}
				else if (cstate == "invite"){
					enemyName = result["from"].toString();
					emit(getInvite(result["from"].toString(),result["map"].toInt()));
				}
				else if (cstate == "chat"){
					//获得聊天内容
					QString chatContent = result["content"].toString();
				}
				else if (cstate == "start"){
					//这里应该再加个是否同意开始游戏
					emit(startGame());
				}
				else if (cstate == "battle"){
					emit(battleData(result));
				}
				else if (cstate == "over"){
					emit(gameOver(result["win"].toBool()));
				}
			}
		}
	}
}