#include "tcpclientsocket.h"

TcpClientSocket::TcpClientSocket(QObject *parent)
{
	_HasStartGame = false;
	name = "0";
	connect(this, SIGNAL(readyRead()), this, SLOT(dataReceived()));
	connect(this, SIGNAL(disconnected()), this, SLOT(slotDisconnected()));
}

void TcpClientSocket::dataReceived()
{
	while (bytesAvailable()>0)
	{
		int length = bytesAvailable();
		char buf[1024];
		read(buf, length);
		buf[length] = '\0';
		QString msg=QString::fromLocal8Bit(buf);

		QJsonParseError error;
		QJsonDocument jsonDocument = QJsonDocument::fromJson(msg.toUtf8(), &error);
		if (error.error == QJsonParseError::NoError){
			if (jsonDocument.isObject()){
				QVariantMap result = jsonDocument.toVariant().toMap();
				QString cstate = result["state"].toString();
				
				if (cstate == "connect"){
					QString temname = result["from"].toString();
					//emit messageon(name+cstate);  //这货是在server的dialog中显示的
					emit sendName(temname, this);
				}
				else if (cstate == "disconnect"){

				}
				else if (cstate == "request"){
					emit nameList(this);
				}
				else if (cstate == "find"){
					emit findVital(result["to"].toString(),result["from"].toString(),result["map"].toInt());
				}
				else if (cstate == "invite"){
					emit start(result["to"].toString(), this);
				}
				else if (cstate == "battle"){
					emit battle(result,this);
				}
				else if (cstate == "chat"){
					emit chat(result);
				}
				else if (cstate == "lose")
					emit lose(result, this);
			}
		}
	}
}

void TcpClientSocket::slotDisconnected()
{
	emit disconnected(this->socketDescriptor());
}

