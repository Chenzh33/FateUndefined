#include "PanelMenu.h"

PanelMenu::PanelMenu(TcpClient*tcpclient, LocalSettings* localsettings, QWidget *parent) : QFrame(parent)
{
	_LocalSettings = localsettings;
	information = QStringLiteral( "δ���ӵ�������....");
	//��������BGM�Ĳ����б�
	playlist = new QMediaPlaylist;
	playlist->addMedia(QUrl("Resources/Music/bgm.mp3"));
	playlist->setCurrentIndex(1);
	playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
	//��Ӧ�ڲ����б�Ĳ�����
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

	//�������̼�ReadMe��־
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

	//���Ǹ�ˢ�������û��б�ĺ��������æpͼ��button����ȥ�����Ұ�GetNameList��һ��
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
	_btConfirm->setSizeGeometry(255, 110, 70, 50);//ע���������Dialog��λ��
	_btConfirm->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_Confirm)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_Confirm_2)}");
	QObject::connect(_btConfirm, &ButtonBase::clicked, this, &PanelMenu::ConfirmInvite);

	_btCancel = new ButtonBase(_Dialog);
	_btCancel->setSizeGeometry(445, 110, 70, 50);//ע���������Dialog��λ��
	_btCancel->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_Cancel)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_Cancel_2)}");
	QObject::connect(_btCancel, &ButtonBase::clicked, _Dialog, &QFrame::hide);

	_btReturn = new ButtonBase(_PageOnline);
	_btReturn->setSizeGeometry(35, 10, 50, 50);
	_btReturn->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_Return)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_Return_2)}");
	QObject::connect(_btReturn, &ButtonBase::clicked, this, &PanelMenu::ReturnToPageMultiplayer);


	//��ʼʱû��show��ťconfirm��cancel����RequireConnect�в���ʾ
	_PageOnline->show();
	_Dialog->hide();
	if (tcpPoint->HasConnected){
		connect(tcpPoint, &TcpClient::nameList, this, &PanelMenu::nameList);
		connect(tcpPoint, &TcpClient::getInvite, this, &PanelMenu::getInvite);
		connect(tcpPoint, &TcpClient::startGame, this, &PanelMenu::ConfirmConnect);
		connect(_btConnect, &QPushButton::clicked, this, &PanelMenu::RequireConnect);
	}
	//���ӷ�����
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

	//���øս���Option����ʱSlider��λ��
	_slBackgroundMusicVolume->setValue(_LocalSettings->BackgroundMusicVolume);
	_slEffectVolume->setValue(_LocalSettings->EffectVolume);


	//����Ϊ�ı���ʾ��CHANGE VOLUME����Background����Effect��
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

	//����Ϊ�ı���ʾ��CHANGE MAP����Current Map: ��
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
	//ȷ�����ӣ���ʼ��Ϸ
	EnterMainWindow();
	player->deleteLater();
	playlist->deleteLater();
}


/********��Ϊ�������********/

void PanelMenu::nameError()
{
	QMessageBox::warning(this, QStringLiteral("����"), QStringLiteral("���������ظ���"),
		QMessageBox::Yes, QMessageBox::Yes);
	disconnect(_btConnect, &QPushButton::clicked, this, &PanelMenu::RequireConnect);
}

void PanelMenu::nameTrue()
{
	QMessageBox::information(this, QStringLiteral("֪ͨ"), QStringLiteral("����������Ч��"),
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
	_btConfirm->show();//�˴�Ӧ�á��Է����İ�ť��ʾ������������ġ��Լ�����
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
	//��NameList֮ǰ�Ķ�����ɾ���Ժ�������ȥ
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
	/*�˺�������û�����粿�ֲο�û����ȫʵ�֣�����ʵ�����������Ĺ���*/

	//Ӧ���ڷ������˽�һ��NameItemPool��������ElementPool����������
	_MyName = _NameInput->text();//����QTextEdit�е�����
	_NameInput->clear();//���OK������QTextEdit������
	//_NameList->removeItemWidget(find.....);//ÿ�ε��OK�������NameItemPool�е�ԭ�ȵ�����ɾ��

	if (_MyName == "") return;//�ж��Ƿ�Ϊ�գ���Ϊ��ֱ����������ִ�������connect�ȳ���
	//if (CanFindInList(_MyName)) return;//�����������Ƿ��Ѿ����ڣ�CanFindInListֻ��һ��ʾ���Եĺ�����Ӧ��Ҫ�õ�����
	QVariantMap answer;
	answer.insert("state", "connect");
	answer.insert("from", _MyName);
	QString json = QJsonDocument::fromVariant(answer).toJson();
	tcpPoint->tcpSocket->write(json.toLocal8Bit(), json.toLocal8Bit().length());
	/*********************************/
	connect(tcpPoint, &TcpClient::nameTrue, this, &PanelMenu::nameTrue);
	connect(tcpPoint, &TcpClient::nameError, this, &PanelMenu::nameError);
	//ͼ���ز�δ���룬·����Ч
}

void PanelMenu::RequireConnect()
{
	tcpPoint->enemyName = _Enemyname;
	//������Է�����������Ϣ,�Է�������Ҫĳ���ֶ���ӽ�ȥ
	QVariantMap answer;
	answer.insert("state", "find");
	answer.insert("from", tcpPoint->userName);
	answer.insert("to", tcpPoint->enemyName);
	answer.insert("map", _LocalSettings->MapIndex);
	//answer.insert("map",)
	QString json = QJsonDocument::fromVariant(answer).toJson();
	tcpPoint->tcpSocket->write(json.toLocal8Bit(), json.toLocal8Bit().length());

	//�ڵ����item֮����connect��������������
	//��ʾ���Է�����confirm��cancel��ť����ʾ��Ϣ��δ���루"�ȴ�XXXȷ��"/"XXX���������ӣ��Ƿ�ͬ�⣿"��

}

void PanelMenu::ConfirmConnect()
{
	emit multiplay_Signal();
	player->deleteLater();
	playlist->deleteLater();
	//ȷ�����ӣ���ʼ��Ϸ
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
