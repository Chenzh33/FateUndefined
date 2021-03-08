#include "server.h"
#include"qjsondocument.h"
Server::Server(QObject *parent, int port)
:QTcpServer(parent)
{
	listen(QHostAddress::Any, port);
}

void Server::incomingConnection(qintptr socketDescriptor)
{
	TcpClientSocket *tcpClientSocket = new TcpClientSocket(this);
	//进入房间后发送的初始名字
	connect(tcpClientSocket, SIGNAL(sendName(const QString&, TcpClientSocket*)), this, SLOT(sendName(const QString&, TcpClientSocket*)));
	//返回在线用户列表
	connect(tcpClientSocket, SIGNAL(nameList(TcpClientSocket*)), this, SLOT(nameList(TcpClientSocket*)));
	//用户离线后反应
	connect(tcpClientSocket, SIGNAL(disconnected(const int&)), this, SLOT(slotDisconnected(const int&)));
	//聊天消息
	connect(tcpClientSocket, SIGNAL(chat(const QVariantMap&)), this, SLOT(chat(const QVariantMap&)));
	//寻找对手
	connect(tcpClientSocket, SIGNAL(findVital(const QString &, const QString&,const int&)), this, SLOT(findVital(const QString&, const QString&,const int&)));
	//双方都同意对战
	connect(tcpClientSocket, SIGNAL(start(const QString&, TcpClientSocket*)), this, SLOT(start(const QString&, TcpClientSocket*)));
	//传递战斗数据
	connect(tcpClientSocket, SIGNAL(battle(const QVariantMap&, TcpClientSocket*)), this, SLOT(battle(const QVariantMap&, TcpClientSocket*)));
	//表示有消息过来了
	connect(tcpClientSocket, SIGNAL(messageon(const QVariantMap&)), this, SLOT(messageon(const QVariantMap&)));

	connect(tcpClientSocket, SIGNAL(lose(const QVariantMap&, TcpClientSocket*)), this, SLOT(lose(const QVariantMap&, TcpClientSocket*)));

	tcpClientSocket->setSocketDescriptor(socketDescriptor);

	tcpClientSocketList.append(tcpClientSocket);
}

void Server::messageon(const QString& msg){
	emit updateServer(msg);
}

void Server::sendName(const QString& name, TcpClientSocket*client){
	if (client->name != "0") return;
	QVariantMap answer;
	answer.insert("state", "connect");
	answer.insert("name", name);

	if (!userMap.count(name)){
		userMap.insert(name, client);
		answer.insert("from", true);
		client->name = name;
	}
	else{
		answer.insert("from", false);
	}
	/*if (!localNameList.count(name)){
		localNameList.append(name);
		userMap.insert(name, client);
		answer.insert("from", "infirmed");
	}
	else{
		answer.insert("from", "error");
	}*/
	QString json = QJsonDocument::fromVariant(answer).toJson();
	client->write(json.toLocal8Bit(), json.toLocal8Bit().length());
}

void Server::nameList(TcpClientSocket*client){
	QVariantList nameli;
	for (auto tem = userMap.begin(); tem != userMap.end(); tem++){
		if (tem.key() != client->name){
			nameli.append(tem.key());
		}
	}
	QVariantMap answer;
	answer.insert("state", "request");
	answer.insert("nameList", nameli);
	QString json = QJsonDocument::fromVariant(answer).toJson();
	client->write(json.toLocal8Bit(), json.toLocal8Bit().length());
}

void Server::chat(const QVariantMap& result){
	auto tem = userMap.find(result["to"].toString());
	QVariantMap answer;
	answer.insert("state", "chat");
	answer.insert("content", result["content"].toString());
	QString json = QJsonDocument::fromVariant(answer).toJson();
	(tem.value())->write(json.toLocal8Bit(), json.toLocal8Bit().length());
}

void Server::findVital(const QString &name, const QString& fromname,const int&map){
	auto tem = userMap.find(name);
	if (tem == userMap.end()) return;
	QVariantMap answer;
	answer.insert("state", "invite");
	answer.insert("from", fromname);
	answer.insert("map", map);
	QString json = QJsonDocument::fromVariant(answer).toJson();
	(tem.value())->write(json.toLocal8Bit(), json.toLocal8Bit().length());
}

void Server::start(const QString& to, TcpClientSocket*client){
	//创建一盘新的棋局
	auto tem = userMap.find(to);
	if (tem == userMap.end()) return;
	if (client->_HasStartGame || tem.value()->_HasStartGame){
		return;
	}
	else{
		chessboard *newGame = new chessboard(client->name, to);
		battleBoard.append(newGame);
		client->_HasStartGame = true;
		tem.value()->_HasStartGame = true;
		QVariantMap answer;
		answer.insert("state", "start");
		answer.insert("label", true);
		QString json = QJsonDocument::fromVariant(answer).toJson();
		client->write(json.toLocal8Bit(), json.toLocal8Bit().length());
		(tem.value())->write(json.toLocal8Bit(), json.toLocal8Bit().length());
	}
}

bool Server::over(int victoryMark, QList<chessboard*>::iterator tem){
	if (victoryMark != 0){
		battleBoard.erase(tem);
		return true;
	}
	return false;
}

QVariantList que2list(QQueue<int> queue){
	QVariantList list;
	for (auto i : queue){
		list.append(i);
	}
	return list;
}

void Server::battle(const QVariantMap &result, TcpClientSocket*client){
	//移动棋子，向对手发送移动的目的地
	if (result["action"].toString() == "move"||
		(result["action"].toString() == "ult" &&
		(result["piece"].toInt() == 5 || result["piece"].toInt() == -5))){
		for (auto tem = battleBoard.begin(); tem != battleBoard.end(); tem++){
			if ((*tem)->player1 == result["from"].toString() || (*tem)->player2 == result["from"].toString()){
				(*tem)->_Elements->get_Element(result["piece"].toInt())->Move(result["x"].toInt(), result["y"].toInt());
				break;
			}
		}
		auto tem = userMap.find(result["to"].toString());
		auto indes = userMap.find(result["from"].toString());
		QVariantMap answer;
		answer.insert("state", "battle");
		if (result["action"].toString() == "move"){
			answer.insert("action", "move");
		}
		else{
			answer.insert("action", "ult");
		}
		answer.insert("piece", result["piece"].toInt());
		answer.insert("x", result["x"].toInt());
		answer.insert("y", result["y"].toInt());
		QString json = QJsonDocument::fromVariant(answer).toJson();
		tem.value()->write(json.toLocal8Bit(), json.toLocal8Bit().length());
		indes.value()->write(json.toLocal8Bit(), json.toLocal8Bit().length());
	}
	//攻击，向双方发送血量*****************************************************************************
	//这里把旧版红A的大招删去了，不过部分保留
	else if (result["action"].toString() == "attack" ||  //若有攻击过来
		(result["action"].toString() == "ult" &&       
		(result["self"].toInt() == 1 || result["self"].toInt() == -1))){  //如果有大招信号并且是单体伤害的saber
		int Damage{ 0 };
		if (result["action"].toString() == "ult" && (result["self"].toInt() == 1 || result["self"].toInt() == -1)){
			Damage = 25;
		}
		bool isDeath{ false };
		int reserveHP{ 0 };
		int shoustroke{ 0 };
		int gongstroke{ 0 };
		int AC_value{ 0 };
		Element*element;
		Element*enemy;
		int vitoryMark{ 0 };
		bool victory{ false };
		auto tem = battleBoard.begin();
		for (; tem != battleBoard.end(); tem++){
			if ((*tem)->player1 == result["from"].toString() || (*tem)->player2 == result["from"].toString()){
				element = (*tem)->_Elements->get_Element(result["self"].toInt());
				if (result["action"].toString() != "attack"){
					element->_character.change_Num_Strokes();
				}
				enemy = (*tem)->_Elements->get_Element(result["enemy"].toInt());
				break;
			}
		}

		if (result["action"].toString() == "attack"){
			    AC_value = enemy->_character.get_AC();
				Damage = element->_character.Output_Damage(AC_value);
			}
			enemy->_character.Input_Damage(Damage);


		if (enemy->_character.Death((*tem)->Round)){
			if ((enemy->_character.get_Choose() == 6) && (enemy->_character.get_Whether_Strokes() == 0))
			{
				//判定B叔用过大招了
				enemy->_character.set_Whether_Strokes(1);
			}
		}

		reserveHP = enemy->_character.get_HP();
		gongstroke = element->_character.get_Num_Strokes();
		if (enemy->_character.Death((*tem)->Round)){
			vitoryMark = (*tem)->CheckVictory();
			//有一方胜利发送胜利消息，删除这盘棋局
			isDeath = true;
		}

		QMap<QString, TcpClientSocket*>::iterator tem1 = userMap.find(result["to"].toString());
		if ( tem1!=userMap.end()){
			QVariantMap answer;
			answer.insert("state", "battle");
			if (result["action"].toString() == "attack"){
				answer.insert("action", "attack");
			}
			else{
				answer.insert("action", "ult");
			}
			answer.insert("self", result["self"].toInt());
			answer.insert("enemy", result["enemy"].toInt());
			answer.insert("my",false);
			answer.insert("damage", Damage);
			answer.insert("HP", reserveHP);
			answer.insert("death", isDeath);
			answer.insert("AC", AC_value);
			if (vitoryMark != 0){
				victory = true;
				if ((*tem)->player1 == result["to"].toString()){
					answer.insert("result", -vitoryMark);
				}
				else{
					answer.insert("result", vitoryMark);
				}
			}
			answer.insert("victory", victory);
			//加上archer的大招攻击次数
			/*if (result["action"].toString() == "ult" && result["self"].toInt() == 2){
				answer.insert("attack_num", attack_num);
			}*/
			if (result["self"].toInt() == 1 || result["self"].toInt()==-1){//|| result["self"].toInt() == 2){
				answer.insert("stroke1", gongstroke);
			}
			QString json = QJsonDocument::fromVariant(answer).toJson();
			tem1.value()->write(json.toLocal8Bit(), json.toLocal8Bit().length());
		}
		QVariantMap answer;
		answer.insert("state", "battle");
		if (result["action"].toString() == "attack"){
			answer.insert("action", "attack");
		}
		else{
			answer.insert("action", "ult");
		}
		answer.insert("self", result["self"].toInt());
		answer.insert("enemy", result["enemy"].toInt());
		answer.insert("my", true);
		answer.insert("damage", Damage);
		answer.insert("HP", reserveHP);
		answer.insert("death", isDeath);
		answer.insert("AC", AC_value);

		if (vitoryMark != 0){
			victory = true;
			if ((*tem)->player1 ==client->name){
				answer.insert("result", -vitoryMark);
			}
			else{
				answer.insert("result", vitoryMark);
			}
		}
		answer.insert("victory", victory);

		if (result["self"].toInt() == 1 || result["self"].toInt() == -1){
			answer.insert("stroke1", gongstroke);
		}
		QString json = QJsonDocument::fromVariant(answer).toJson();
		client->write(json.toLocal8Bit(), json.toLocal8Bit().length());

		if (victory){
			over(vitoryMark, tem);
		}
	}
	//大招********************************************************************************
	else if (result["action"].toString() == "ult"){
		if (result["piece"].toInt() == 3 || result["piece"].toInt() == -3){//Rider的自爆
			QVariantList elements_in_range = result["list"].toList();
			QVariantList elements_death;
			for (auto tem = battleBoard.begin(); tem != battleBoard.end(); tem++){
				if ((*tem)->player1 == result["from"].toString() || (*tem)->player2 == result["from"].toString()){
					if ((*tem)->player1 == result["from"].toString() || (*tem)->player2 == result["from"].toString()){
						Element* element = (*tem)->_Elements->get_Element(result["piece"].toInt());
						element->_character.change_Num_Strokes();
					}
					for (auto i : elements_in_range){
						Element* temp_element = (*tem)->_Elements->get_Element(i.toInt());
						int Init = temp_element->_character.get_Initiative();
						int rand_Init = Init + rand() % 20 + 1;
						if (rand_Init < 15){
							int Damage = temp_element->_character.get_HP() + 2;
							temp_element->_character.Input_Damage(Damage);
							if (temp_element->_character.Death((*tem)->Round)){
								if ((temp_element->_character.get_Choose() == 6) && (temp_element->_character.get_Whether_Strokes() == 0))
								{
									//判定B叔用过大招了
									temp_element->_character.set_Whether_Strokes(1);
								}
							}
							elements_death.append(i.toInt());
						}
					}
					int vitoryMark = (*tem)->CheckVictory();
					//有一方胜利发送胜利消息，删除这盘棋局

					auto rplayer1 = userMap.find(result["from"].toString());
					auto rplayer2 = userMap.find(result["to"].toString());
					QVariantMap answer;
					answer.insert("state", "battle");
					answer.insert("action", "ult");
					answer.insert("piece", 3);
					answer.insert("list", elements_in_range);
					answer.insert("death_list", elements_death);
					int victory{ false };
					if (vitoryMark != 0){
						victory = true;
						if ((*tem)->player1 == client->name){
							answer.insert("result", -vitoryMark);
						}
						else{
							answer.insert("result", vitoryMark);
						}
					}
					answer.insert("victory", victory);
					QString json = QJsonDocument::fromVariant(answer).toJson();
					rplayer1.value()->write(json.toLocal8Bit(), json.toLocal8Bit().length());

					QVariantMap answer1;
					answer1.insert("state", "battle");
					answer1.insert("action", "ult");
					answer1.insert("piece", 3);
					answer1.insert("list", elements_in_range);
					answer1.insert("death_list", elements_death);
					if (vitoryMark != 0){
						if ((*tem)->player1 == client->name){
							answer1.insert("result", -vitoryMark);
						}
						else{
							answer1.insert("result", vitoryMark);
						}
					}
					answer.insert("victory", victory);
					QString json1 = QJsonDocument::fromVariant(answer1).toJson();
					rplayer2.value()->write(json1.toLocal8Bit(), json1.toLocal8Bit().length());
					break;

					if (victory){
						over(vitoryMark, tem);
					}
				}
			}
		}
		else if (result["piece"].toInt() == 2 || result["piece"].toInt() == -2){//红A的状态切换
			Element*element;
			auto tem = battleBoard.begin();
			for (; tem != battleBoard.end(); tem++){
				if ((*tem)->player1 == result["from"].toString() || (*tem)->player2 == result["from"].toString()){
					element = (*tem)->_Elements->get_Element(result["piece"].toInt());
					break;
				}
			}
			if (element->_character.get_AB() == 8) (*tem)->Remote_Archer(element); else (*tem)->Melee_Archer(element);
			auto indestination = userMap.find(result["to"].toString());
			auto indes = userMap.find(result["from"].toString());
			QVariantMap answer;
			answer.insert("state", "battle");
			answer.insert("action", "ult");
			answer.insert("piece", result["piece"].toInt());
			QString json = QJsonDocument::fromVariant(answer).toJson();
			indestination.value()->write(json.toLocal8Bit(), json.toLocal8Bit().length());
			indes.value()->write(json.toLocal8Bit(), json.toLocal8Bit().length());
		}

	}
	//取消，则进行下一轮，这里是像下一个棋子的user发送棋子的标号
	else if (result["action"].toString() == "cancel"){
		bool newround{ false };
		QVariantList list;
		for (auto tem = battleBoard.begin(); tem != battleBoard.end(); tem++){
			if ((*tem)->player1 == result["from"].toString() || (*tem)->player2 == result["from"].toString()){
				int foround = (*tem)->Round;
				int nextpiece = (*tem)->Next();
				QString enemyplayer;
				if ((*tem)->Round > foround){
					newround = true;
				}
				auto indestination = userMap.begin();
				if (nextpiece > 0){
					indestination = userMap.find((*tem)->player1);
					enemyplayer = (*tem)->player2;
				}
				else{
					nextpiece = -nextpiece;
					indestination = userMap.find((*tem)->player2);
					enemyplayer = (*tem)->player1;
				}
				list = que2list((*tem)->AttackSequence);
				//向下一个棋子的enemy发送AttackSequence
				auto enemyadress = userMap.find(enemyplayer);
				QVariantMap answer1;
				answer1.insert("state", "battle");
				answer1.insert("action", "next");
				answer1.insert("my", false);
				answer1.insert("newlist", list);
				answer1.insert("host", false);
				if (newround){
					answer1.insert("newround", true);
					answer1.insert("round", (*tem)->Round);
				}
				else{
					answer1.insert("newround", false);
				}
				QString json1 = QJsonDocument::fromVariant(answer1).toJson();
				enemyadress.value()->write(json1.toLocal8Bit(), json1.toLocal8Bit().length());

				QVariantMap answer;
				answer.insert("state", "battle");
				answer.insert("action", "next");
				answer.insert("my", true);
				answer.insert("piece", nextpiece);
				answer.insert("newlist", list);
				answer.insert("host", false);
				if (newround){
					answer.insert("newround", true);
					answer.insert("round", (*tem)->Round);
				}
				else{
					answer.insert("newround", false);
				}
				
				QString json = QJsonDocument::fromVariant(answer).toJson();
				indestination.value()->write(json.toLocal8Bit(), json.toLocal8Bit().length());
				break;
			}
		}
	}
	else if (result["action"].toString() == "start"){
		for (auto tem = battleBoard.begin(); tem != battleBoard.end(); tem++){
			if ((*tem)->player1 == result["from"].toString() || (*tem)->player2 == result["from"].toString()){
				(*tem)->readyPlayer++;
				if ((*tem)->readyPlayer == 2){
					(*tem)->initNewRound();
					QVariantList list = que2list((*tem)->AttackSequence);
					int ActionPiece = (*tem)->AttackSequence.front();
					auto indestination = userMap.begin();
					auto enemyinde = userMap.begin();
						
						
					if (rand() % 2 == 0){
						indestination = userMap.find((*tem)->player1);
						enemyinde = userMap.find((*tem)->player2);
					}
					else{
						indestination = userMap.find((*tem)->player2);
						enemyinde = userMap.find((*tem)->player1);
					}
					(*tem)->player1 = indestination.key();
					(*tem)->player2 = enemyinde.key();
					QVariantMap answer;
					answer.insert("state", "battle");
					answer.insert("action", "next");
					answer.insert("newround", true);
					answer.insert("round", (*tem)->Round);
					answer.insert("newlist", list);
					answer.insert("my", (ActionPiece>0));
					answer.insert("host", true);
					answer.insert("ishost", true);
					QString json = QJsonDocument::fromVariant(answer).toJson();
					indestination.value()->write(json.toLocal8Bit(), json.toLocal8Bit().length());
					QVariantMap answer1;
					answer1.insert("state", "battle");
					answer1.insert("action", "next");
					answer1.insert("host", false);
					answer1.insert("newround", true);
					answer1.insert("round", (*tem)->Round);
					answer1.insert("newlist", list);
					answer1.insert("my", (ActionPiece<0));
					answer1.insert("host", true);
					answer1.insert("ishost", false);
					QString json1 = QJsonDocument::fromVariant(answer1).toJson();
					enemyinde.value()->write(json1.toLocal8Bit(), json1.toLocal8Bit().length());
					break;
				}
			}
		}
	}
}
//如果有一方退出游戏则通知另一方获胜
void Server::lose(const QVariantMap&result, TcpClientSocket*client){
	auto tem = battleBoard.begin();
	QString winner;
	for (; tem != battleBoard.end(); tem++){
		if ((*tem)->player1 == result["to"].toString()){
			winner = (*tem)->player1;
			break;
		}
		else if ((*tem)->player2 == result["to"].toString()){
			winner = (*tem)->player2;
			break;
		}
	}
	client->_HasStartGame = false;
	if (tem != battleBoard.end()){
		battleBoard.erase(tem);
	}
	QVariantMap answer;
	answer.insert("state", "over");
	answer.insert("win", true);
	QString json = QJsonDocument::fromVariant(answer).toJson();
	auto win = userMap.find(winner);
	if (win != userMap.end()){
		win.value()->_HasStartGame = false;
		(win.value())->write(json.toLocal8Bit(), json.toLocal8Bit().length());
	}
}
//如果断线就删掉断线的user并且如果在比赛则向对方发送胜利消息
void Server::slotDisconnected(int descriptor)
{
	for (int i = 0; i<tcpClientSocketList.count(); i++)
	{
		QTcpSocket *item = tcpClientSocketList.at(i);
		if (item->socketDescriptor() == descriptor)
		{
			QString name = tcpClientSocketList[i]->name;
			QString winner;
			bool mark{ false };
			tcpClientSocketList.removeAt(i);//删除该tcpSocket
			auto deleter = userMap.find(name);
			userMap.erase(deleter);
			auto tem = battleBoard.begin();
			for (; tem != battleBoard.end(); tem++){
				if ((*tem)->player1 == name){
					winner = (*tem)->player2;
					mark = true;
					break;
				}
				else if ((*tem)->player2 == name){
					winner = (*tem)->player1;
					mark = true;
					break;
				}
			}
			if (mark){
				QVariantMap answer;
				answer.insert("state", "over");
				answer.insert("win", true);
				QString json = QJsonDocument::fromVariant(answer).toJson();
				auto win = userMap.find(winner);
				if (win == userMap.end()) return;
				win.value()->_HasStartGame = false;
				(win.value())->write(json.toLocal8Bit(), json.toLocal8Bit().length());
				battleBoard.erase(tem);
			}
			return;
		}
	}
	return;
}