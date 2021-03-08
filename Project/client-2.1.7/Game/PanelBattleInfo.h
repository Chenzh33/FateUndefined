#ifndef PANELBATTLEINFO_H
#define PANELBATTLEINFO_H

#include <QFrame>
#include "constant.h"
#include "GameContent.h"
#include "ElementBattleInfo.h"
#include <QLabel>
#include <QGraphicsColorizeEffect>

class PanelBattleInfo : public QFrame
{
	Q_OBJECT

public:
	PanelBattleInfo(GameContent *_Content,GameState *state, QWidget *parent = 0);
	~PanelBattleInfo();
	void RefreshNewRoundInfo();
	void RefreshAllBattleInfo();
private:
	GameContent *_Content;
	GameState *_State;
	QLabel *_RoundNumText;
	QVector<ElementBattleInfo*> AllElementInfo;
	void paintEvent(QPaintEvent *);
};
#endif