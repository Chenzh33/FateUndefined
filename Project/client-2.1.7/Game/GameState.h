#ifndef GAMESTATE_H
#define GAMESTATE_H

//#include "qqueue.h"
//#include "Element.h"

typedef struct _GameState
{
	bool IsHost;	//�������йأ���ʾ�Ƿ�������
	//bool IsMyTurn;	//�Ƿ�ǰ���Լ��Ļغ�
	bool IsChoosingAttackTarget;	//�Ƿ��ڵ����Attack����׼��ѡ�񹥻�Ŀ���״̬
	bool IsChoosingMoveTarget;		//�Ƿ��ڵ����Move����׼��ѡ���ƶ�Ŀ���״̬
	bool HasMoved;
	bool HasAttacked;
	bool HasUltimateSkilled;
	QVector<int> AttackSequence;
	int WhileUltimateSkilling;		//�Ƿ�����ֵĴ���״̬
	int Round;
	int AILevel;	// 0:tutorial,1:easy,2:normal,3:hard,4:lunatic
}GameState;










#endif