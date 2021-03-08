#ifndef GAMESTATE_H
#define GAMESTATE_H

//#include "qqueue.h"
//#include "Element.h"

typedef struct _GameState
{
	bool IsHost;	//与联网有关，表示是否是主机
	//bool IsMyTurn;	//是否当前是自己的回合
	bool IsChoosingAttackTarget;	//是否处于点击了Attack键而准备选择攻击目标的状态
	bool IsChoosingMoveTarget;		//是否处于点击了Move键而准备选择移动目标的状态
	bool HasMoved;
	bool HasAttacked;
	bool HasUltimateSkilled;
	QVector<int> AttackSequence;
	int WhileUltimateSkilling;		//是否处于奇怪的大招状态
	int Round;
	int AILevel;	// 0:tutorial,1:easy,2:normal,3:hard,4:lunatic
}GameState;










#endif