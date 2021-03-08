#include "GameContent.h"

GameContent::GameContent(QGraphicsScene* scene, LocalSettings* localsettings, QObject *parent)
{
	_Scene = scene;
	_Settings = localsettings;

	initMapInfo();
	initElementPool();
	initMusic();
}

GameContent::~GameContent()
{

}

void GameContent::initMapInfo()
{
	_Map = new MapInfo;

	_Map->initMapFile(AllMapFileInfo[_Settings->MapIndex - 1].FileName);
	for (int i = 0; i < _Map->get_map_width() * _Map->get_map_height(); i++){
		MapUnit* MapUnitTemp = new MapUnit(
			i%_Map->get_map_width(), i / _Map->get_map_width(), _Map->get_floor_info()[i], i);
		_Map->get_MapUnit_vector().push_back(MapUnitTemp);
		_Scene->addItem(MapUnitTemp);

	}
}

void GameContent::initElementPool()
{
	_Elements = new ElementPool;

	for (int i = 0; i != ELEMENTS_NUM; i++){
		Element *element = new Element(_Map->get_BirthPoints()[i].first, _Map->get_BirthPoints()[i].second, i + 1);
		_Scene->addItem(element);
		_Elements->addElement(element);
	}
	for (int i = 0; i != ELEMENTS_NUM; i++){
		Element *element = new Element(_Map->get_BirthPoints()[i + 6].first, _Map->get_BirthPoints()[i + 6].second, -(i + 1));
		_Scene->addItem(element);
		_Elements->addElement(element);
	}

	_Scene->installEventFilter(this);
}

void GameContent::initMusic()
{
	//用来播放BGM的播放列表
	playlist = new QMediaPlaylist(this);
	playlist->addMedia(QUrl("Resources/Music/battle1.mp3"));
	playlist->addMedia(QUrl("Resources/Music/battle2.mp3"));
	playlist->addMedia(QUrl("Resources/Music/battle3.mp3"));
	playlist->addMedia(QUrl("Resources/Music/battle4.mp3"));
	playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
	
	//对应于播放列表的播放器
	player = new QMediaPlayer(this);
	player->setPlaylist(playlist);
	player->setVolume(_Settings->BackgroundMusicVolume);
	playlist->setCurrentIndex(_Settings->BackgroundIndex - 1);
	player->play();

	//以下添加攻击移动音效
	playlist_battle = new QMediaPlaylist(this);
	playlist_battle->addMedia(QUrl("Resources/Music/saber_attack.wav"));
	playlist_battle->addMedia(QUrl("Resources/Music/archer_attack.wav"));
	playlist_battle->addMedia(QUrl("Resources/Music/rider_attack.wav"));
	playlist_battle->addMedia(QUrl("Resources/Music/assassin_attack.wav"));
	playlist_battle->addMedia(QUrl("Resources/Music/caster_attack.wav"));
	playlist_battle->addMedia(QUrl("Resources/Music/berserker_attack.wav"));
	playlist_battle->addMedia(QUrl("Resources/Music/saber_move.mp3"));
	playlist_battle->addMedia(QUrl("Resources/Music/archer_move.wav"));
	playlist_battle->addMedia(QUrl("Resources/Music/rider_move.wav"));
	playlist_battle->addMedia(QUrl("Resources/Music/assassin_move.mp3"));
	playlist_battle->addMedia(QUrl("Resources/Music/caster_move.wav"));
	playlist_battle->addMedia(QUrl("Resources/Music/berserker_move.wav"));
	playlist_battle->addMedia(QUrl("Resources/Music/saber_ultimate_1.wav"));//12
	playlist_battle->addMedia(QUrl("Resources/Music/saber_ultimate_2.wav"));//13
	playlist_battle->addMedia(QUrl("Resources/Music/archer_ultimate_RemoteToMelee.wav"));//14
	playlist_battle->addMedia(QUrl("Resources/Music/rider_ultimate.wav"));//15
	playlist_battle->addMedia(QUrl("Resources/Music/caster_ultimate.wav"));//16
	playlist_battle->addMedia(QUrl("Resources/Music/archer_attack_melee.wav"));//17
	playlist_battle->addMedia(QUrl("Resources/Music/archer_ultimate_MeleeToRemote.wav"));//18
	playlist_battle->addMedia(QUrl("Resources/Music/assassin_dodge.wav"));//19

	//设置为只放一次
	playlist_battle->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
	player_battle = new QMediaPlayer(this);
	player_battle->setPlaylist(playlist_battle);
	player_battle->setVolume(_Settings->EffectVolume);
}

void GameContent::ChangeBackgroundMusicVolume(int value)
{
	_Settings->BackgroundMusicVolume = value;
	player->setVolume(_Settings->BackgroundMusicVolume);
}

void GameContent::ChangeEffectVolume(int value)
{
	_Settings->EffectVolume = value;
	player_battle->setVolume(_Settings->EffectVolume);
}