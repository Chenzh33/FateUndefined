#ifndef GAMECONTENT_H
#define GAMECONTENT_H

#include <QGraphicsScene>
#include "ElementPool.h"
#include "MapInfo.h"
#include"qmediaplayer.h"
#include"qmediaplaylist.h"
#include "LocalSettings.h"


class GameContent : public QObject
{
	Q_OBJECT

public:
	GameContent(QGraphicsScene* scene, LocalSettings* localsettings, QObject *parent);
	~GameContent();
	MapInfo* Map(){ return _Map; };
	ElementPool* Elements(){ return _Elements; };
	LocalSettings* Settings(){ return _Settings; };
	//�������ǲ���BGM�õģ�playlist������Ų����б�
	QMediaPlayer *player;
	QMediaPlaylist *playlist;
	QMediaPlayer *player_battle;
	QMediaPlaylist *playlist_battle;
	void ChangeBackgroundMusicVolume(int value);
	void ChangeEffectVolume(int value);
private:
	MapInfo* _Map;
	ElementPool* _Elements;
	QGraphicsScene* _Scene;
	LocalSettings *_Settings;

	void initMapInfo();
	void initElementPool();
	void initMusic();

};
#endif