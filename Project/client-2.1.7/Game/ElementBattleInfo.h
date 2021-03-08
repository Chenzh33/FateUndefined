#ifndef ELEMENTBATTLEINFO_H
#define ELEMENTBATTLEINFO_H

#include <QFrame>
#include "constant.h"
#include "GameState.h"
#include <QLabel>
#include <QGraphicsColorizeEffect>
#include "Element.h"

class ElementBattleInfo : public QFrame
{
	Q_OBJECT

public:
	ElementBattleInfo(GameState *state, Element*element, QWidget *parent = 0);
	~ElementBattleInfo();

	void RefreshBattleInfo();
	void ActiveNoteToggle();
private:
	GameState *_State;
	Element* _Element;
	QLabel* _ElementIcon;
	QLabel *_HPNumText;
	QLabel *_UltimateSkillState;
	QGraphicsColorizeEffect *_DeathEffect;
	QFrame *_ActiveNote;
	bool IsDead;
	void paintEvent(QPaintEvent *);
};




#endif