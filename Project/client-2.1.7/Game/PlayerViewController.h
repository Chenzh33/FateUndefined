#ifndef PLAYERVIEWCONTROLLER_H
#define PLAYERVIEWCONTROLLER_H

#include <QGraphicsView>
#include <QtWidgets/QGraphicsScene>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <qparallelanimationgroup.h>
#include "PanelOperate.h"
#include "PanelHeadUp.h"
#include "PanelBattleInfo.h"
#include "GameContent.h"
#include <qevent.h>
#include "constant.h"
#include "GameState.h"
#include <qlabel.h>
#include <qmath.h>
#include <qtimer.h>
#include "tcpclient.h"

class M_Element_Animation;

class PlayerViewController : public QGraphicsView
{
	Q_OBJECT

public:
	PlayerViewController(QGraphicsScene* scene, GameContent* content, TcpClient*tcpclient, QWidget *parent, bool IsHost = true);
	~PlayerViewController();
	GameState _State;
	void lose();
signals:
	void ShowMenu_ViewToMainWindow_Signal();
	void QuitGame_Signal();
private:
	//init
	void initHeadUp();
	void initBattleInfo();

	//game control
	void newRound(QVariantList);
	void Next();

	//animation and move
	void attackAnimation(Element*, Element*, int, bool,int);
	void saberAnimation(Element*, Element*, int, bool);
	void archerAnimation(bool);
	void casterAnimation(Element*, int, int);
	void riderAnimation(QVariantList, QVariantList);
	void MoveElement(int,int, int);
	void MoveAnimate(Element*, int, int);
	void newRoundAnimation();

	//assistant
	void resetOperate();
	void show_damage(int);
	void Melee_Archer();
	void Remote_Archer();
	void UltimateSkill_Saber_Effect_Fast();
	void UltimateSkill_Saber_Effect_Slow();
	void UltimateSkill_Saber_Sound_Effect();
	void UltimateSkill_Assassin_Sound_Effect();

	//note
	void notePossibleMoveTargetMapUnit();
	bool notePossibleAttackTargetElement();
	bool noteUltimateSkillTarget_Saber();
	bool noteUltimateSkillTarget_Archer();//to be deleted
	void noteUltimateSkillTarget_Caster();

	//operate
	void undo();
	void Move(MapUnit* target);
	void Attack(int);
	void UltimateSkill_Saber(int);
	void UltimateSkill_Archer();
	void UltimateSkill_Caster(MapUnit*);
	void UltimateSkill_Rider();
	void Cancel();

	//slot
	void battleData(QVariantMap);
	void gameOver(int);
	void ShowMenu();
	void TogglePanelBattleInfo();
	void btMovePressed();
	void btAttackPressed();
	void btUltimateSkillPressed();
	void btCancelPressed();

	//event
	void wheelEvent(QWheelEvent* e);
	void mousePressEvent(QMouseEvent *e);
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void viewMoveTimer(int type);
	void moveView_Left();
	void moveView_Right();
	void moveView_Up();
	void moveView_Down();
	QTimer *_timer;


	GameContent* _Content;
	PanelOperate* _Operate;
	PanelHeadUp* _HeadUp;
	QGraphicsScene *_Scene;
	PanelBattleInfo *_BattleInfo;
	TcpClient *tcpPoint;
	int ActionPiece;//存正在活动的棋子标号
	bool gamestart;//表示游戏是否开始运行

	//这个是connect函数本身逗比所以才需要的一个参数M_Element_Animation
	M_Element_Animation* _EAnime;
	M_Element_Animation* _HealthAnime;
	//弹道变量
	Element* _BulletPicture_Archer;
	Element* _BulletPicture_Caster;
	Element* _BulletPicture_Saber;
	//Rider专用
	M_Element_Animation* _EAnime_Rider[12];

};

//因为connect本身函数的问题才需要这个类，本身没什么用，记得搬过去就好
class M_Element_Animation :public QObject
{
	Q_OBJECT
public:
	M_Element_Animation(Element* ActionElement);
	M_Element_Animation(Element* ActionElement, int Damage);
	M_Element_Animation(Element* ActionElement, int Round, PanelHeadUp* HeadUp);
	void Emit_Hide_Signal();
	void Emit_Damage_Signal();
	void Emit_Set_Health_Signal();
	void Emit_Tomb_Note_Signal();

signals:
	void Damage_signal(const int& Damage);
private:
	Element* _ActionElement;
	int _Damage;
	int _Round;
	PanelHeadUp* _HeadUp;
};

#endif