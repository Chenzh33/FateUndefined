#ifndef PANELOPERATE_H
#define PANELOPERATE_H

#include <QLabel>
#include <QPainter>
#include "constant.h"
#include "ButtonBase.h"
#include "GameState.h"


enum class Operate_type{
	Right_Bottom, Left_Bottom, Right_Top, Left_Top
};

class PanelOperate : public QLabel
{
	Q_OBJECT

public:
	PanelOperate(qreal x, qreal y, const GameState& state, Operate_type type, bool EX_state,QWidget *parent = 0);
	~PanelOperate();
signals:
	void btAttackPressed_Signal();
	void btMovePressed_Signal();
	void btUltimateSkillPressed_Signal();
	void btCancelPressed_Signal();

private:
	ButtonBase *_btAttack;
	ButtonBase *_btMove;
	ButtonBase *_btUltimateSkill;
	ButtonBase *_btCancel;
	QPoint *_Offset;
	void EmitAttackPressedSignal();
	void EmitMovePressedSignal();
	void EmitUltimateSkillPressedSignal();
	void EmitCancelPressedSignal();
};
#endif