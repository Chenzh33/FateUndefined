#include "gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
: QMainWindow(parent) 
{
	SingleOrMulti = false;
	tcpclient = new TcpClient(this);
	manager = new QNetworkAccessManager(this);
	//设置Settings的默认值
	DefaultSettings();

	this->gameStart();
}

GameWindow::~GameWindow()
{

}

void GameWindow::initScene()
{
	_Scene = new QGraphicsScene(this);
	int scene_width{ 0 };
	int scene_height{ 0 };
	switch (_LocalSettings.BackgroundIndex)
	{
	case 1:
		scene_width = 1320;
		scene_height = 1000;
		break;
	case 2:
		scene_width = 1320;
		scene_height = 1100;
		break;
	case 3:
		scene_width = 1450;
		scene_height = 1000;
		break;
	case 4:
		scene_width = 1450;
		scene_height = 1000;
		break;
	default:
		break;
	}
	_Scene->setSceneRect(0, 0, scene_width, scene_height);
}

void GameWindow::initGameContent()
{
	_Content = new GameContent(_Scene,&_LocalSettings, this);

}

void GameWindow::initView()
{
	if (SingleOrMulti){
		_View = new PlayerViewController(_Scene, _Content, tcpclient, this);//联网实现后初始化默认参数IsHost
		_View->setFixedSize(VIEW_WIDTH, VIEW_HEIGHT);
		_View->show();
		_Single = nullptr;
		QObject::connect(_View, &PlayerViewController::ShowMenu_ViewToMainWindow_Signal, this, &GameWindow::OpenGameMainMenu);
		QObject::connect(_View, &PlayerViewController::QuitGame_Signal, this, &GameWindow::returnPanelMenu);

	}
	else{
		_Single = new SinglePlayerController(_Scene, _Content, AILevel, this);
		_Single->setFixedSize(VIEW_WIDTH, VIEW_HEIGHT);
		_Single->show();
		_View = nullptr;
		QObject::connect(_Single, &SinglePlayerController::ShowMenu_ViewToMainWindow_Signal, this, &GameWindow::OpenGameMainMenu);
		QObject::connect(_Single, &SinglePlayerController::QuitGame_Signal, this, &GameWindow::returnPanelMenu);

	}
}

void GameWindow::initSceneBackground()
{
	QString string = "Resources/IconSrc/Map/game_background_";
	string.append(_LocalSettings.BackgroundIndex + '0');
	QPixmap bg(string);
	QPainter p(&bg);
	if (SingleOrMulti){
		_View->setBackgroundBrush(QBrush(bg));
	}
	else{
		_Single->setBackgroundBrush(QBrush(bg));
	}
}

void GameWindow::gameStart()
{
	this->setFixedSize(MAINMENU_WIDTH, MAINMENU_HEIGHT);
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->move((QApplication::desktop()->width() - this->width()) / 2, (QApplication::desktop()->height() - this->height()) / 4);

	_Menu = new PanelMenu(tcpclient, &_LocalSettings, this);
	connect(manager, &QNetworkAccessManager::finished, _Menu, &PanelMenu::getHttpReply);
	manager->get(QNetworkRequest(QUrl("http://10.134.141.156/inform.txt")));
	QObject::connect(_Menu, &PanelMenu::GameStart_Signal, this, &GameWindow::initGame);
	QObject::connect(_Menu, &PanelMenu::AILevel_Signal, this, &GameWindow::setAILevel);
	//双人游戏会将SingalOrMulti置为true
	QObject::connect(_Menu, &PanelMenu::multiplay_Signal, this, &GameWindow::singleToMulti);
}

void GameWindow::singleToMulti(){
	SingleOrMulti = !SingleOrMulti;
}

void GameWindow::initGame()
{
	this->hide();

	this->setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	this->move((QApplication::desktop()->width() - this->width()) / 2, (QApplication::desktop()->height() - this->height()) / 4);


	initScene();
	initGameContent();
	//initState();
	initView();
	initSceneBackground();

	QTimer::singleShot(1000, this, &GameWindow::show);
	QTimer::singleShot(2000, this, &GameWindow::showGameStart);
}

void GameWindow::showGameStart()
{
	QLabel* textGameStart = new QLabel("GAME START", this);
	textGameStart->setGeometry(VIEW_WIDTH / 2 - 400, VIEW_HEIGHT / 2 - 100, 1000, 100);
	textGameStart->setFont(QFont("Algerian", 100, QFont::Bold));
	QGraphicsColorizeEffect *ColorEffect_Round = new QGraphicsColorizeEffect(textGameStart);
	ColorEffect_Round->setColor(QColor(255, 255, 65));
	textGameStart->setGraphicsEffect(ColorEffect_Round);
	textGameStart->show();

	QTimer::singleShot(1500, textGameStart, &QLabel::deleteLater);

	QPropertyAnimation* Upward_Anime = new QPropertyAnimation(textGameStart, "geometry");
	Upward_Anime->setDuration(1500);
	Upward_Anime->setStartValue(textGameStart->geometry());
	Upward_Anime->setEndValue(QRect(textGameStart->geometry().left(), textGameStart->geometry().top() - textGameStart->geometry().height() * 1 / 2, textGameStart->geometry().width(), textGameStart->geometry().height()));
	Upward_Anime->start();
}

void GameWindow::DefaultSettings()
{
	_LocalSettings.BackgroundMusicVolume = 50;
	_LocalSettings.EffectVolume = 50;
	_LocalSettings.MapIndex = 1;
	_LocalSettings.BackgroundIndex = 1;
}

void GameWindow::OpenGameMainMenu()
{
	if (!SingleOrMulti && _Single->isInteractive()){
		_Single->setInteractive(false); // new added
		_MainMenu = new GameMainMenu(_Content, this);
		connect(_MainMenu, &GameMainMenu::Resume_Signal, this, &GameWindow::ResumeGame);
		connect(_MainMenu, &GameMainMenu::Quit_Signal, this, &GameWindow::returnPanelMenu);
	}
	if (SingleOrMulti && _View->isInteractive()){
		_View->setInteractive(false); // new added
		_MainMenu = new GameMainMenu(_Content, this);
		connect(_MainMenu, &GameMainMenu::Resume_Signal, this, &GameWindow::ResumeGame);
		connect(_MainMenu, &GameMainMenu::Quit_Signal, this, &GameWindow::returnPanelMenu);
		connect(_MainMenu, &GameMainMenu::Quit_Signal, _View, &PlayerViewController::lose);
	}
}

void GameWindow::returnPanelMenu()
{
	//防止内存泄露开始删东西
	if (SingleOrMulti){
		_View->deleteLater();
		singleToMulti();
	}
	else{
		_Single->deleteLater();
	}
	_Scene->deleteLater();
	_Content->deleteLater();
	disconnect(manager, 0, 0, 0);
	this->gameStart();
	this->show();
}

void GameWindow::ResumeGame()
{
	if (SingleOrMulti)
		_View->setInteractive(true); // new added
	else
		_Single->setInteractive(true); // new added
	_MainMenu->hide();
	_MainMenu->deleteLater();
	_MainMenu = nullptr;

}

void GameWindow::setAILevel(int ailevel)
{
	AILevel = ailevel;
}