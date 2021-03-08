#ifndef PANELMENU_H
#define PANELMENU_H

#include <QFrame>
#include <QDialog>
#include <QLineEdit>
#include <QListWidget>
#include <QMediaPlayer>
#include <QMediaPlayList>
#include <QPainter>
#include <QMessageBox>
#include <QSlider>
#include "constant.h"
#include "ButtonBase.h"
#include "tcpclient.h"
#include "TextLabel.h"
#include "MapInfo.h" // new added
#include "LocalSettings.h"
//http request
#include"qnetworkreply.h"
#include"qtextcodec.h"


class PanelMenu : public QFrame
{
	Q_OBJECT

public:
	PanelMenu(TcpClient*, LocalSettings*, QWidget *parent = 0);
	~PanelMenu();


signals:
	void GameStart_Signal();
	void multiplay_Signal();
	void AILevel_Signal(int ailevel);
private:
	LocalSettings *_LocalSettings;

	QMediaPlayer *player;
	QMediaPlaylist *playlist;
	TcpClient *tcpPoint;
	int temp_map;

	//Pages
	QFrame *_PageMain;
	QFrame *_PageSinglePlayer;
	QFrame *_PageMultiPlayer;
	QFrame *_PageOnline;
	QFrame *_PageOption;

	//Widgets on MainPage
	ButtonBase *_btMultiPlayer;
	ButtonBase *_btSinglePlayer;
	ButtonBase *_btOption;
	ButtonBase *_btExit;
	QString information;
	QLabel*inform;

	//Widgets on SinglePlayerPage
	ButtonBase *_btTutorialMode;
	ButtonBase *_btEasyMode;
	ButtonBase *_btNormalMode;
	ButtonBase *_btHardMode;
	ButtonBase *_btLunaitcMode;
	ButtonBase *_btReturn;

	//Widgets on MultiPlayerPage
	ButtonBase *_btOnline;
	ButtonBase *_btOffline;

	//Widgets on OnlinePage
	ButtonBase *_btOk;
	ButtonBase *_btConnect;
	ButtonBase *_btRefresh;

	QLineEdit *_NameInput;
	QListWidget *_NameList;
	QString _MyName;
	QString _Enemyname;
	QMessageBox *messagebox;
	QFrame *_Dialog;
	QLabel*_inviteMessageName;
	QGraphicsColorizeEffect*_inviteStyle;
	ButtonBase *_btConfirm;
	ButtonBase *_btCancel;

	//Widget on OptionPage
	QSlider *_slBackgroundMusicVolume;
	QSlider *_slEffectVolume;
	QListWidget *_MapChoose;
	QLabel *_CurrentMap;

	//slot
	void JumpToPageSinglePlayer();
	void JumpToPageMultiPlayer();
	void JumpToPageOnline();
	void JumpToPageOption();
	void OfflineMode();
	void TutorialMode();
	void EasyMode();
	void NormalMode();
	void HardMode();
	void LunaticMode();
	void EnterMainWindow();
	void InputName();
	void RequireConnect();
	void GetNameList();
	public slots:
	//void displayerror(QAbstractSocket::SocketError);
	void ReturnToPageMultiplayer();
	void ReturnToMainMenu();
	void nameError();
	void nameTrue();
	void nameList(QVariantList);
	void getInvite(QString,int);
	void ConfirmInvite();
	void SinglePlayerGameStart();
	void ConfirmConnect();
	void changeEnemy(QString);
	void getHttpReply(QNetworkReply*);

	void ChangeBackgroundMusicVolume(int);
	void ChangeEffectVolume(int);
	void SetCurrentMap(const QString&);
};
#endif