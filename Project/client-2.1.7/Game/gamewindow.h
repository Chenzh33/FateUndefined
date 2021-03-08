#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QtWidgets/QApplication>
#include <QDesktopWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGraphicsScene>
#include <QVector>
#include"qnetworkaccessmanager.h"
#include "GameContent.h"
#include "PlayerViewController.h"
#include "SinglePlayerController.h"
#include "PanelMenu.h"
#include "GameMainMenu.h"
#include "constant.h"


class GameWindow : public QMainWindow
{
	Q_OBJECT

public:
	GameWindow(QWidget *parent = 0);
	void gameStart();
	~GameWindow();
	TcpClient*tcpclient;
	public slots:
	void singleToMulti();
	void initGame();

private:

	void initScene();
	void initGameContent();
	//void initState();
	void initView();
	void initSceneBackground();


	PanelMenu* _Menu;
	QGraphicsScene* _Scene;
	PlayerViewController* _View;
	SinglePlayerController*_Single;
	GameContent* _Content;
	LocalSettings _LocalSettings;
	GameMainMenu *_MainMenu;
	QNetworkAccessManager*manager;

	int AILevel;
	bool SingleOrMulti;

	void showGameStart();
	void DefaultSettings();
	void OpenGameMainMenu();
	void returnPanelMenu();
	void ResumeGame();
	void setAILevel(int ailevel);
protected:
	//

};

#endif // GAMEWINDOW_H
