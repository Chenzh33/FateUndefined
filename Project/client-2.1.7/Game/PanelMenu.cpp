#include "PanelMenu.h"

PanelMenu::PanelMenu(TcpClient*tcpclient, LocalSettings* localsettings, QWidget *parent) : QFrame(parent)
{
	_LocalSettings = localsettings;
	information = QStringLiteral( "未连接到服务器....");
	//用来播放BGM的播放列表
	playlist = new QMediaPlaylist;
	playlist->addMedia(QUrl("Resources/Music/bgm.mp3"));
	playlist->setCurrentIndex(1);
	playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
	//对应于播放列表的播放器
	player = new QMediaPlayer;
	player->setPlaylist(playlist);
	player->setVolume(_LocalSettings->BackgroundMusicVolume);
	player->play();

	//_MainWindow = parent;
	tcpPoint = tcpclient;
	this->setGeometry(0, 0, 750, 422);

	_PageSinglePlayer = nullptr;
	_PageMultiPlayer = nullptr;
	_PageOption = nullptr;
	_PageMain = new QFrame(this);
	_PageMain->setObjectName("Page_Main");
	_PageMain->setStyleSheet("QFrame#Page_Main{background-image:url(:/IconSrc/background_1)}");
	_PageMain->setGeometry(0, 0, 750, 422);

	_btSinglePlayer = new ButtonBase(_PageMain);
	_btSinglePlayer->setSizeGeometry(88, 328, 140, 36);
	_btSinglePlayer->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_Singleplayer)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_Singleplayer_2)}");

	_btMultiPlayer = new ButtonBase(_PageMain);
	_btMultiPlayer->setSizeGeometry(277, 328, 140, 36);
	_btMultiPlayer->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_Multiplayer)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_Multiplayer_2)}");

	_btOption = new ButtonBase(_PageMain);
	_btOption->setSizeGeometry(460, 328, 100, 36);
	_btOption->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_Option)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_Option_2)}");

	_btExit = new ButtonBase(_PageMain);
	_btExit->setSizeGeometry(600, 328, 80, 36);
	_btExit->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_Exit)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_Exit_2)}");

	inform = new QLabel(_PageMain);
	inform->setText(information.toUtf8());
	inform->setGeometry(20, 400, 400, 22);
	inform->setBackgroundRole(QPalette::Dark);

	QObject::connect(_btSinglePlayer, &QPushButton::clicked, this, &PanelMenu::JumpToPageSinglePlayer);
	QObject::connect(_btMultiPlayer, &QPushButton::clicked, this, &PanelMenu::JumpToPageMultiPlayer);
	QObject::connect(_btOption, &QPushButton::clicked, this, &PanelMenu::JumpToPageOption);
	QObject::connect(_btExit, &QPushButton::clicked, parent, &QWidget::close);

	//具体流程见ReadMe日志
	_PageMain->show();


}

PanelMenu::~PanelMenu()
{

}

void PanelMenu::JumpToPageSinglePlayer()
{
	_PageMain->hide();

	_PageSinglePlayer = new QFrame(this);
	_PageSinglePlayer->setGeometry(0, 0, 750, 422);
	_PageSinglePlayer->setObjectName("Page_SinglePlayer");
	_PageSinglePlayer->setStyleSheet("QFrame#Page_SinglePlayer{background-image:url(:/IconSrc/background_1_dark)}");

	_btReturn = new ButtonBase(_PageSinglePlayer);
	_btReturn->setSizeGeometry(35, 10, 50, 50);
	_btReturn->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_Return)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_Return_2)}");
	QObject::connect(_btReturn, &ButtonBase::clicked, this, &PanelMenu::ReturnToMainMenu);

	_btTutorialMode = new ButtonBase(_PageSinglePlayer);
	_btTutorialMode->setSizeGeometry(85, 328, 100, 36);
	_btTutorialMode->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_TutorialMode)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_TutorialMode_2)}");
	QObject::connect(_btTutorialMode, &ButtonBase::clicked, this, &PanelMenu::TutorialMode);

	_btEasyMode = new ButtonBase(_PageSinglePlayer);
	_btEasyMode->setSizeGeometry(208, 328, 100, 36);
	_btEasyMode->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_EasyMode)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_EasyMode_2)}");
	QObject::connect(_btEasyMode, &ButtonBase::clicked, this, &PanelMenu::EasyMode);


	_btNormalMode = new ButtonBase(_PageSinglePlayer);
	_btNormalMode->setSizeGeometry(316, 328, 100, 36);
	_btNormalMode->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_NormalMode)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_NormalMode_2)}");
	QObject::connect(_btNormalMode, &ButtonBase::clicked, this, &PanelMenu::NormalMode);

	_btHardMode = new ButtonBase(_PageSinglePlayer);
	_btHardMode->setSizeGeometry(450, 328, 100, 36);
	_btHardMode->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_HardMode)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_HardMode_2)}");
	QObject::connect(_btHardMode, &ButtonBase::clicked, this, &PanelMenu::HardMode);

	_btLunaitcMode = new ButtonBase(_PageSinglePlayer);
	_btLunaitcMode->setSizeGeometry(560, 328, 100, 36);
	_btLunaitcMode->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_LunaticMode)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_LunaticMode_2)}");
	QObject::connect(_btLunaitcMode, &ButtonBase::clicked, this, &PanelMenu::LunaticMode);

	_PageSinglePlayer->show();


}

void PanelMenu::JumpToPageMultiPlayer()
{
	_PageMain->hide();

	_PageMultiPlayer = new QFrame(this);
	_PageMultiPlayer->setGeometry(0, 0, 750, 422);
	_PageMultiPlayer->setObjectName("Page_MultiPlayer");
	_PageMultiPlayer->setStyleSheet("QFrame#Page_MultiPlayer{background-image:url(:/IconSrc/background_1_dark)}");

	_btOnline = new ButtonBase(_PageMultiPlayer);
	_btOnline->setSizeGeometry(85, 328, 80, 36);
	_btOnline->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_Online)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_Online_2)}");
	QObject::connect(_btOnline, &QPushButton::clicked, this, &PanelMenu::JumpToPageOnline);

	_btOffline = new ButtonBase(_PageMultiPlayer);
	_btOffline->setSizeGeometry(208, 328, 80, 36);
	_btOffline->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_Offline)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_Offline_2)}");
	QObject::connect(_btOffline, &QPushButton::clicked, this, &PanelMenu::OfflineMode);

	_btReturn = new ButtonBase(_PageMultiPlayer);
	_btReturn->setSizeGeometry(35, 10, 50, 50);
	_btReturn->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_Return)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_Return_2)}");
	QObject::connect(_btReturn, &ButtonBase::clicked, this, &PanelMenu::ReturnToMainMenu);


	_PageMultiPlayer->show();

}

void PanelMenu::JumpToPageOnline()
{
	_PageMultiPlayer->hide();

	_PageOnline = new QFrame(this);
	_PageOnline->setGeometry(0, 0, 750, 422);
	_PageOnline->setObjectName("Page_Online");
	_PageOnline->setStyleSheet("QFrame#Page_Online{background-image:url(:/IconSrc/background_1_dark)}");

	_NameInput = new QLineEdit(_PageOnline);
	_NameInput->setGeometry(350, 25, 220, 30);
	_NameInput->setStyleSheet("QLineEdit{background-color: rgb(225, 225, 225)}""QLineEdit:focus{background-color: rgb(255, 255, 255)}");
	_NameList = new QListWidget(_PageOnline);
	_NameList->setGeometry(35, 70, 680, 280);
	_NameList->setStyleSheet("background-color: rgb(225, 225, 225)");
	QObject::connect(_NameList, &QListWidget::currentTextChanged, this, &PanelMenu::changeEnemy);

	_btOk = new ButtonBase(_PageOnline);
	_btOk->setSizeGeometry(600, 10, 50, 50);
	_btOk->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_Ok)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_Ok_2)}");
	QObject::connect(_btOk, &ButtonBase::clicked, this, &PanelMenu::InputName);

	//这是个刷新在线用户列表的函数，求帮忙p图把button填上去，并且把GetNameList改一下
	_btRefresh = new ButtonBase(_PageOnline);
	_btRefresh->setSizeGeometry(665, 10, 50, 50);
	_btRefresh->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_Refresh)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_Refresh_2)}");
	QObject::connect(_btRefresh, &ButtonBase::clicked, this, &PanelMenu::GetNameList);

	_btConnect = new ButtonBase(_PageOnline);
	_btConnect->setSizeGeometry(275, 360, 150, 50);
	_btConnect->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_Connect)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_Connect_2)}"\
		"QPushButton:disable{background-image:url(:/IconSrc/Button_Connect_3)}");
	_btConnect->setDisabled(true);

	_Dialog = new QFrame(_PageOnline);
	_Dialog->setObjectName("Dialog");
	_Dialog->setWindowFlags(Qt::FramelessWindowHint);
	_Dialog->setGeometry(0, 150, 750, 188);
	_Dialog->setStyleSheet("QFrame#Dialog{background-image:url(:/IconSrc/Dialog)}");

	_Dialog->setWindowOpacity(0.6);

	QLabel* _inviteMessage = new QLabel("requests a game", _Dialog);
	_inviteMessage->setGeometry(355, 30, 300, 50);
	_inviteMessage->setFont(QFont("Algerian", 15, QFont::Bold));
	QGraphicsColorizeEffect *MessageColor = new QGraphicsColorizeEffect(_inviteMessage);
	MessageColor->setColor(QColor(255, 255, 65));
	_inviteMessage->setGraphicsEffect(MessageColor);

	_inviteMessageName = new QLabel("", _Dialog);
	_inviteMessageName->setGeometry(255, 30, 100, 50);
	_inviteMessageName->setFont(QFont("Algerian", 15, QFont::Bold));
	QGraphicsColorizeEffect *NameColor = new QGraphicsColorizeEffect(_inviteMessageName);
	NameColor->setColor(QColor(87, 206, 237));
	_inviteMessageName->setGraphicsEffect(NameColor);

	_btConfirm = new ButtonBase(_Dialog);
	_btConfirm->setSizeGeometry(255, 110, 70, 50);//注意是相对于Dialog的位置
	_btConfirm->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_Confirm)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_Confirm_2)}");
	QObject::connect(_btConfirm, &ButtonBase::clicked, this, &PanelMenu::ConfirmInvite);

	_btCancel = new ButtonBase(_Dialog);
	_btCancel->setSizeGeometry(445, 110, 70, 50);//注意是相对于Dialog的位置
	_btCancel->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_Cancel)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_Cancel_2)}");
	QObject::connect(_btCancel, &ButtonBase::clicked, _Dialog, &QFrame::hide);

	_btReturn = new ButtonBase(_PageOnline);
	_btReturn->setSizeGeometry(35, 10, 50, 50);
	_btReturn->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_Return)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_Return_2)}");
	QObject::connect(_btReturn, &ButtonBase::clicked, this, &PanelMenu::ReturnToPageMultiplayer);


	//初始时没有show按钮confirm和cancel，在RequireConnect中才显示
	_PageOnline->show();
	_Dialog->hide();
	if (tcpPoint->HasConnected){
		connect(tcpPoint, &TcpClient::nameList, this, &PanelMenu::nameList);
		connect(tcpPoint, &TcpClient::getInvite, this, &PanelMenu::getInvite);
		connect(tcpPoint, &TcpClient::startGame, this, &PanelMenu::ConfirmConnect);
		connect(_btConnect, &QPushButton::clicked, this, &PanelMenu::RequireConnect);
	}
	//连接服务器
	if (!tcpPoint->HasConnected){
		tcpPoint->Enter();
		tcpPoint->HasConnected = true;
		connect(tcpPoint, &TcpClient::startGame, this, &PanelMenu::ConfirmConnect);
	}
}

void PanelMenu::JumpToPageOption()
{
	_PageMain->hide();

	_PageOption = new QFrame(this);
	_PageOption->setGeometry(0, 0, 750, 422);
	_PageOption->setObjectName("Page_Option");
	_PageOption->setStyleSheet("QFrame#Page_Option{background-image:url(:/IconSrc/background_1_dark)}");

	_slBackgroundMusicVolume = new QSlider(Qt::Horizontal, _PageOption);
	_slBackgroundMusicVolume->setGeometry(200, 80, 450, 20);
	_slBackgroundMusicVolume->setRange(0, 100);
	_slBackgroundMusicVolume->setValue(_LocalSettings->BackgroundMusicVolume);
	_slBackgroundMusicVolume->setAttribute(Qt::WA_TranslucentBackground);

	_slEffectVolume = new QSlider(Qt::Horizontal, _PageOption);
	_slEffectVolume->setGeometry(200, 120, 450, 20);
	_slEffectVolume->setRange(0, 100);
	_slEffectVolume->setValue(_LocalSettings->EffectVolume);
	_slEffectVolume->setAttribute(Qt::WA_TranslucentBackground);

	QObject::connect(_slBackgroundMusicVolume, &QSlider::valueChanged, this, &PanelMenu::ChangeBackgroundMusicVolume);
	QObject::connect(_slEffectVolume, &QSlider::valueChanged, this, &PanelMenu::ChangeEffectVolume);

	//设置刚进入Option界面时Slider的位置
	_slBackgroundMusicVolume->setValue(_LocalSettings->BackgroundMusicVolume);
	_slEffectVolume->setValue(_LocalSettings->EffectVolume);


	//以下为文本显示“CHANGE VOLUME”“Background”“Effect”
	QLabel* text_volume = new QLabel("CHANGE VOLUME", _PageOption);
	text_volume->setGeometry(240, 30, 270, 30);
	text_volume->setFont(QFont("Algerian", 20, QFont::Bold));
	QGraphicsColorizeEffect *ColorEffect_Volume = new QGraphicsColorizeEffect(text_volume);
	ColorEffect_Volume->setColor(QColor(255, 255, 65));
	text_volume->setGraphicsEffect(ColorEffect_Volume);

	QLabel* text_BGM_volume = new QLabel("Background", _PageOption);
	text_BGM_volume->setGeometry(50, 80, 140, 20);
	text_BGM_volume->setFont(QFont("Algerian", 15, QFont::Bold));
	QGraphicsColorizeEffect *ColorEffect_BGM = new QGraphicsColorizeEffect(text_BGM_volume);
	ColorEffect_BGM->setColor(QColor(255, 204, 0));
	text_BGM_volume->setGraphicsEffect(ColorEffect_BGM);

	QLabel* text_Effect_volume = new QLabel("Effect", _PageOption);
	text_Effect_volume->setGeometry(50, 120, 140, 20);
	text_Effect_volume->setFont(QFont("Algerian", 15, QFont::Bold));
	QGraphicsColorizeEffect *ColorEffect_Effect = new QGraphicsColorizeEffect(text_Effect_volume);
	ColorEffect_Effect->setColor(QColor(255, 204, 0));
	text_Effect_volume->setGraphicsEffect(ColorEffect_Effect);

	//以下为文本显示“CHANGE MAP”“Current Map: ”
	QLabel* text_map = new QLabel("CHANGE MAP", _PageOption);
	text_map->setGeometry(270, 170, 270, 30);
	text_map->setFont(QFont("Algerian", 20, QFont::Bold));
	QGraphicsColorizeEffect *ColorEffect_Change_Map = new QGraphicsColorizeEffect(text_map);
	ColorEffect_Change_Map->setColor(QColor(255, 255, 65));
	text_map->setGraphicsEffect(ColorEffect_Change_Map);

	QLabel* text_current_map = new QLabel("Current Map", _PageOption);
	text_current_map->setGeometry(50, 220, 200, 20);
	text_current_map->setFont(QFont("Algerian", 15, QFont::Bold));
	QGraphicsColorizeEffect *ColorEffect_Current_Map = new QGraphicsColorizeEffect(text_current_map);
	ColorEffect_Current_Map->setColor(QColor(255, 204, 0));
	text_current_map->setGraphicsEffect(ColorEffect_Current_Map);

	_MapChoose = new QListWidget(_PageOption);
	_MapChoose->setGeometry(50, 250, 650, 150);
	_MapChoose->setViewMode(QListView::IconMode);
	_MapChoose->setFlow(QListView::LeftToRight);
	_MapChoose->setWrapping(false);
	_MapChoose->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
	_MapChoose->setMovement(QListView::Static);
	_MapChoose->setIconSize(QSize(100, 100));
	_MapChoose->setStyleSheet("background-color: rgb(225, 225, 225)");

	for (int i = 0; i != MAP_NAME_LIST_SIZE; i++){
		QListWidgetItem* Map_temp = new QListWidgetItem(QIcon(AllMapFileInfo[i].ThumbnailPath), AllMapFileInfo[i].MapName, _MapChoose);
		_MapChoose->addItem(Map_temp);
	}

	_MapChoose->setItemSelected((_MapChoose->findItems(AllMapFileInfo[_LocalSettings->MapIndex - 1].MapName, Qt::MatchExactly)).front(), true);

	_CurrentMap = new QLabel(_PageOption);
	_CurrentMap->setText(AllMapFileInfo[_LocalSettings->MapIndex - 1].MapName);
	_CurrentMap->setGeometry(250, 220, 400, 20);
	_CurrentMap->setFont(QFont("Algerian", 15, QFont::Bold));
	QGraphicsColorizeEffect *ColorEffect_Map = new QGraphicsColorizeEffect(_CurrentMap);
	ColorEffect_Map->setColor(QColor(87, 206, 237));
	_CurrentMap->setGraphicsEffect(ColorEffect_Map);

	QObject::connect(_MapChoose, &QListWidget::currentTextChanged, this, &PanelMenu::SetCurrentMap);


	_btReturn = new ButtonBase(_PageOption);
	_btReturn->setSizeGeometry(35, 10, 50, 50);
	_btReturn->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_Return)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_Return_2)}");
	QObject::connect(_btReturn, &ButtonBase::clicked, this, &PanelMenu::ReturnToMainMenu);

	_PageOption->show();
}

void PanelMenu::OfflineMode()
{
	emit AILevel_Signal(-1);
	SinglePlayerGameStart();
}

void PanelMenu::TutorialMode()
{
	emit AILevel_Signal(0);
	SinglePlayerGameStart();
}

void PanelMenu::EasyMode()
{
	emit AILevel_Signal(1);
	SinglePlayerGameStart();
}

void PanelMenu::NormalMode()
{
	emit AILevel_Signal(2);
	SinglePlayerGameStart();
}

void PanelMenu::HardMode()
{
	emit AILevel_Signal(3);
	SinglePlayerGameStart();
}

void PanelMenu::LunaticMode(){
	emit AILevel_Signal(4);
	SinglePlayerGameStart();
}

void PanelMenu::changeEnemy(QString enemy)
{
	_Enemyname = enemy;
	_btConnect->setEnabled(true);
}

void PanelMenu::EnterMainWindow()
{
	emit GameStart_Signal();
	this->hide();
	this->deleteLater();
}

void PanelMenu::ReturnToPageMultiplayer()
{
	if (_PageOnline != nullptr){
		disconnect(tcpPoint, 0, 0, 0);
		_PageOnline->hide();
		_PageOnline->deleteLater();
		_PageOnline = nullptr;
	}
	_PageMultiPlayer->show();
}

void PanelMenu::ReturnToMainMenu()
{
	if (_PageSinglePlayer != nullptr){
		_PageSinglePlayer->hide();
		_PageSinglePlayer->deleteLater();
		_PageSinglePlayer = nullptr;
	}
	if (_PageMultiPlayer != nullptr){
		_PageMultiPlayer->hide();
		_PageMultiPlayer->deleteLater();
		_PageMultiPlayer = nullptr;
	}
	if (_PageOption != nullptr){
		_PageOption->hide();
		_PageOption->deleteLater();
		_PageOption = nullptr;
	}

	_PageMain->show();
}

void PanelMenu::ChangeBackgroundMusicVolume(int value)
{
	_LocalSettings->BackgroundMusicVolume = value;
	player->setVolume(value);
}

void PanelMenu::ChangeEffectVolume(int value)
{
	_LocalSettings->EffectVolume = value;

}

void PanelMenu::SetCurrentMap(const QString& string)
{
	_CurrentMap->setText(string);
	int index = 0;
	while (AllMapFileInfo[index].MapName != string)
		++index;

	_LocalSettings->MapIndex = index + 1;
	_LocalSettings->BackgroundIndex = index + 1;
}

void PanelMenu::SinglePlayerGameStart()
{
	//确认连接，开始游戏
	EnterMainWindow();
	player->deleteLater();
	playlist->deleteLater();
}


/********下为网络相关********/

void PanelMenu::nameError()
{
	QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("您的名字重复！"),
		QMessageBox::Yes, QMessageBox::Yes);
	disconnect(_btConnect, &QPushButton::clicked, this, &PanelMenu::RequireConnect);
}

void PanelMenu::nameTrue()
{
	QMessageBox::information(this, QStringLiteral("通知"), QStringLiteral("您的名字有效！"),
		QMessageBox::Yes, QMessageBox::Yes);
	connect(tcpPoint, &TcpClient::nameList, this, &PanelMenu::nameList);
	connect(tcpPoint, &TcpClient::getInvite, this, &PanelMenu::getInvite);
	GetNameList();
	connect(_btConnect, &QPushButton::clicked, this, &PanelMenu::RequireConnect);
}

void PanelMenu::getInvite(QString name,int map)
{
	_inviteMessageName->setText(name);
	temp_map = map;
	tcpPoint->enemyName = name;
	_Dialog->show();
	_btConfirm->show();//此处应让【对方】的按钮显示，而不是这里的【自己】的
	_btCancel->show();

}

void PanelMenu::ConfirmInvite()
{
	_LocalSettings->MapIndex = temp_map;
	_LocalSettings->BackgroundIndex = temp_map;
	QVariantMap answer;
	answer.insert("state", "invite");
	answer.insert("to", tcpPoint->enemyName);
	QString json = QJsonDocument::fromVariant(answer).toJson();
	tcpPoint->tcpSocket->write(json.toLocal8Bit(), json.toLocal8Bit().length());
}

void PanelMenu::nameList(QVariantList namelist)
{
	//把NameList之前的东西都删掉以后再填上去
	_NameList->clear();
	for (auto tem = namelist.begin(); tem != namelist.end(); tem++){
		_NameList->addItem(new QListWidgetItem(QIcon(QObject::tr(":/IconSrc/Player")), (*tem).toString()));
	}
}

void PanelMenu::GetNameList()
{
	QVariantMap answer;
	answer.insert("state", "request");
	QString json = QJsonDocument::fromVariant(answer).toJson();
	tcpPoint->tcpSocket->write(json.toLocal8Bit(), json.toLocal8Bit().length());
}

void PanelMenu::InputName()
{
	/*此函数由于没有网络部分参考没有完全实现，仅仅实现了添加新项的功能*/

	//应该在服务器端建一个NameItemPool，类似于ElementPool，用于索引
	_MyName = _NameInput->text();//返回QTextEdit中的内容
	_NameInput->clear();//点击OK后会清空QTextEdit的内容
	//_NameList->removeItemWidget(find.....);//每次点击OK都会把在NameItemPool中的原先的名字删除

	if (_MyName == "") return;//判断是否为空，若为空直接跳出，不执行下面的connect等程序
	//if (CanFindInList(_MyName)) return;//检查这个名字是否已经存在，CanFindInList只是一个示意性的函数，应该要用到网络
	QVariantMap answer;
	answer.insert("state", "connect");
	answer.insert("from", _MyName);
	QString json = QJsonDocument::fromVariant(answer).toJson();
	tcpPoint->tcpSocket->write(json.toLocal8Bit(), json.toLocal8Bit().length());
	/*********************************/
	connect(tcpPoint, &TcpClient::nameTrue, this, &PanelMenu::nameTrue);
	connect(tcpPoint, &TcpClient::nameError, this, &PanelMenu::nameError);
	//图标素材未导入，路径无效
}

void PanelMenu::RequireConnect()
{
	tcpPoint->enemyName = _Enemyname;
	//这里向对方发送请求信息,对方名字需要某种手段添加进去
	QVariantMap answer;
	answer.insert("state", "find");
	answer.insert("from", tcpPoint->userName);
	answer.insert("to", tcpPoint->enemyName);
	answer.insert("map", _LocalSettings->MapIndex);
	//answer.insert("map",)
	QString json = QJsonDocument::fromVariant(answer).toJson();
	tcpPoint->tcpSocket->write(json.toLocal8Bit(), json.toLocal8Bit().length());

	//在点击过item之后点击connect键即可请求连接
	//显示【对方】的confirm和cancel按钮，显示信息尚未加入（"等待XXX确认"/"XXX想与你连接，是否同意？"）

}

void PanelMenu::ConfirmConnect()
{
	emit multiplay_Signal();
	player->deleteLater();
	playlist->deleteLater();
	//确认连接，开始游戏
	EnterMainWindow();
}

void PanelMenu::getHttpReply(QNetworkReply*reply){
	QTextCodec *codec = QTextCodec::codecForName("utf8");
	QString all = codec->toUnicode(reply->readAll());
	all = all.toUtf8();
	if (all.size() != 0){
		information = all;
	}
	inform->setText(information);
	reply->deleteLater();
}
