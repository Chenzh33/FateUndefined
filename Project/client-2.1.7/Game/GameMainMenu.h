#ifndef GAMEMAINMENU_H
#define GAMEMAINMENU_H

#include <QFrame>
#include <QLabel>
#include <QPainter>
#include <QMediaPlayer>
#include <QMediaPlayList>
#include <QSlider>
#include <QGraphicsView>
#include <QGraphicsColorizeEffect>
#include "GameContent.h"
#include "constant.h"
#include "ButtonBase.h"

class GameMainMenu : public QFrame
{
	Q_OBJECT

public:
	GameMainMenu(GameContent *content, QWidget *parent);
	~GameMainMenu();

signals:
	void Resume_Signal();
	void Quit_Signal();

private:
	ButtonBase *_btResume;
	ButtonBase *_btQuit;
	QSlider *_slBackgroundMusicVolume;
	QSlider *_slEffectVolume;
	GameContent *_Content;

	void EmitResumeSignal();
	void EmitQuitSignal();


};


#endif