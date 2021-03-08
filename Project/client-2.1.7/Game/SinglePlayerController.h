#ifndef SINGLEPLAYERCONTROLLER_H
#define SINGLEPLAYERCONTROLLER_H

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
#include<time.h>

//这里是类的声明（一定要有！）
class Element_Animation;
class AI_Animation;

class SinglePlayerController : public QGraphicsView
{
	Q_OBJECT

public:
	SinglePlayerController(QGraphicsScene* scene, GameContent* content, int ailevel, QWidget *parent, bool IsHost = true);
	~SinglePlayerController();
	GameState _State;
signals:
	void ShowMenu_ViewToMainWindow_Signal();
	void QuitGame_Signal();
private:
	//init
	void initHeadUp();
	void initBattleInfo();
	void initQueue();
	void initNewRound();

	//game control
	bool CheckIsNextAttacker(int index);
	void Next();
	void CheckVictory();
	

	//note
	void notePossibleMoveTargetMapUnit();
	bool notePossibleAttackTargetElement();
	bool noteUltimateSkillTarget_Saber();
	void noteUltimateSkillTarget_Caster();

	//assistant	
	void resetOperate();
	void show_damage(int damage);
	void Melee_Archer();
	void Remote_Archer();
	void UltimateSkill_Saber_Effect_Fast();
	void UltimateSkill_Saber_Effect_Slow();
	void UltimateSkill_Saber_Sound_Effect();
	void UltimateSkill_Assassin_Sound_Effect();

	//operate
	void undo();
	void Move(MapUnit* target);
	void Attack(Element* enemy);
	void UltimateSkill_Saber(Element* enemy);
	void UltimateSkill_Archer();
	void UltimateSkill_Rider();
	void UltimateSkill_Caster(MapUnit* target);
	void Cancel();

	//slot
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


	//AI
	void SinglePlayerAI();
	void AI_Action_TutorialMode();
	void AI_Action_EasyMode();
	void AI_Action_NormalMode();
	void AI_Action_HardMode();
	void AI_Action_LunaticMode();
	void AI_Action_HardMode_UltimateSkill_Saber();
	void AI_Action_LunaticMode_UltimateSkill_Saber();
	void AI_Action_HardMode_UltimateSkill_Caster();
	void AI_Action_LunaticMode_UltimateSkill_Caster();

	QTimer *_timer;
	GameContent *_Content;
	PanelOperate *_Operate;
	PanelHeadUp *_HeadUp;
	QGraphicsScene *_Scene;
	PanelBattleInfo *_BattleInfo;

	//这个是connect函数本身逗比所以才需要的一个参数
	Element_Animation* _EAnime;
	Element_Animation* _HealthAnime;
	//弹道变量
	Element* _BulletPicture_Archer;
	Element* _BulletPicture_Caster;
	Element* _BulletPicture_Saber;
	//Rider专用
	Element_Animation* _EAnime_Rider[12];

	//AI
	AI_Animation* AI_Anime_Move;
	AI_Animation* AI_Anime_Attack;
};


//因为connect本身函数的问题才需要这个类，本身没什么用，记得搬过去就好
class Element_Animation :public QObject
{
	Q_OBJECT
public:
	Element_Animation(Element* ActionElement);
	Element_Animation(Element* ActionElement, int Damage);
	Element_Animation(Element* ActionElement, int Round, PanelHeadUp* HeadUp);
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


class AI_Animation :public QObject
{
	Q_OBJECT
public:
	AI_Animation(MapUnit* target);
	AI_Animation(Element* enemy);
	void Emit_Move_Signal();
	void Emit_Attack_Signal();

signals:
	void Move_Signal(MapUnit* target);
	void Attack_Signal(Element* enemy);

private:
	MapUnit* _target;
	Element* _enemy;
};

#endif