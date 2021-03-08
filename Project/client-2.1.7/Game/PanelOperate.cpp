#include "PanelOperate.h"

PanelOperate::PanelOperate(qreal x, qreal y, const GameState& state, Operate_type type, bool EX_state, QWidget *parent) : QLabel(parent)
{
	this->setGeometry(QRect(x, y, 126, 126));

	this->setObjectName("Operate");
	switch (type){
	case Operate_type::Left_Bottom:
		this->setStyleSheet("QFrame#Operate{background-image:url(:/IconSrc/Panel_Operate_LB)}");
		_Offset = new QPoint(8, 12);
		break;
	case Operate_type::Left_Top:
		this->setStyleSheet("QFrame#Operate{background-image:url(:/IconSrc/Panel_Operate_LT)}");
		_Offset = new QPoint(8, 6);
		break;
	case Operate_type::Right_Bottom:
		this->setStyleSheet("QFrame#Operate{background-image:url(:/IconSrc/Panel_Operate_RB)}");
		_Offset = new QPoint(16, 12);
		break;
	case Operate_type::Right_Top:
		_Offset = new QPoint(16, 6);
		this->setStyleSheet("QFrame#Operate{background-image:url(:/IconSrc/Panel_Operate_RT)}");
		break;
	}

	_btAttack = new ButtonBase(this);
	_btAttack->setSizeGeometry(_Offset->x(), _Offset->y(), 50, 50);
	_btAttack->setStyleSheet("QPushButton:enabled{background-image:url(:/IconSrc/Button_Attack)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_Attack_2)}"\
		"QPushButton:!enabled{background-image:url(:/IconSrc/Button_Attack_disable)}");

	_btMove = new ButtonBase(this);
	_btMove->setSizeGeometry(_Offset->x() + 50, _Offset->y(), 50, 50);
	_btMove->setStyleSheet("QPushButton:enabled{background-image:url(:/IconSrc/Button_Move)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_Move_2)}"\
		"QPushButton:!enabled{background-image:url(:/IconSrc/Button_Move_disable)}");

	//因人而异，见下面的switch
	_btUltimateSkill = new ButtonBase(this);
	_btUltimateSkill->setSizeGeometry(_Offset->x(), _Offset->y() + 50, 50, 50);

	_btCancel = new ButtonBase(this);
	_btCancel->setSizeGeometry(_Offset->x() + 50, _Offset->y() + 50, 50, 50);
	_btCancel->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_Defend)}"\
		"QPushButton:hover{background-image:url(:/IconSrc/Button_Defend_2)}");


	//注意暂时没有导入不同的大招按钮素材，故只是用了一种单一的素材
	//hover是鼠标【悬浮】在上面时的状态，enabled是【普通可用】的状态，!enable是灰色【不可用】的状态
	//assassin只有永久的【普通可用】状态，berserker只有【普通可用】状态和【不可用】状态，其余的人三种状态都有
	switch (abs(state.AttackSequence.front())){
	case 1:		//saber
		_btUltimateSkill->setStyleSheet("QPushButton:enabled{background-image:url(:/IconSrc/Button_UltimateSkill1)}"\
			"QPushButton:hover{background-image:url(:/IconSrc/Button_UltimateSkill1_2)}"\
			"QPushButton:!enabled{background-image:url(:/IconSrc/Button_UltimateSkill1_disable)}");
		if (state.HasMoved || state.HasUltimateSkilled) 
			_btMove->setDisabled(true);
		if (state.HasAttacked || state.HasUltimateSkilled) 
			_btAttack->setDisabled(true);
		if (state.HasMoved || state.HasAttacked || state.HasUltimateSkilled || !EX_state) 
			_btUltimateSkill->setDisabled(true);
		break;
	case 2:		//archer
		_btUltimateSkill->setStyleSheet("QPushButton:enabled{background-image:url(:/IconSrc/Button_UltimateSkill2)}"\
			"QPushButton:hover{background-image:url(:/IconSrc/Button_UltimateSkill2_2)}"\
			"QPushButton:!enabled{background-image:url(:/IconSrc/Button_UltimateSkill2_disable)}");
		if (state.HasMoved)
			_btMove->setDisabled(true);
		if (state.HasAttacked)
			_btAttack->setDisabled(true);
		if (state.HasMoved || state.HasAttacked || state.HasUltimateSkilled)
			_btUltimateSkill->setDisabled(true);
		break;
	case 3:		//rider
		_btUltimateSkill->setStyleSheet("QPushButton:enabled{background-image:url(:/IconSrc/Button_UltimateSkill3)}"\
			"QPushButton:hover{background-image:url(:/IconSrc/Button_UltimateSkill3_2)}"\
			"QPushButton:!enabled{background-image:url(:/IconSrc/Button_UltimateSkill3_disable)}");
		if (state.HasMoved)
			_btMove->setDisabled(true);
		if (state.HasAttacked || state.HasUltimateSkilled)
			_btAttack->setDisabled(true);		
		if (state.HasAttacked || state.HasUltimateSkilled || !EX_state)
			_btUltimateSkill->setDisabled(true);
		break;
	case 4:		//assassin
		_btUltimateSkill->setStyleSheet("QPushButton{background-image:url(:/IconSrc/Button_UltimateSkill4)}");
		if (state.HasMoved)
			_btMove->setDisabled(true);
		if (state.HasAttacked)
			_btAttack->setDisabled(true);
		break;
	case 5:		//caster
		_btUltimateSkill->setStyleSheet("QPushButton:enabled{background-image:url(:/IconSrc/Button_UltimateSkill5)}"\
			"QPushButton:hover{background-image:url(:/IconSrc/Button_UltimateSkill5_2)}"\
			"QPushButton:!enabled{background-image:url(:/IconSrc/Button_UltimateSkill5_disable)}");
		if (state.HasMoved || state.HasUltimateSkilled)
			_btMove->setDisabled(true);
		if (state.HasAttacked || state.HasUltimateSkilled)
			_btAttack->setDisabled(true);
		if (state.HasMoved || state.HasAttacked || state.HasUltimateSkilled || !EX_state)
			_btUltimateSkill->setDisabled(true);
		break;
	case 6:		//berserker
		_btUltimateSkill->setStyleSheet("QPushButton:enabled{background-image:url(:/IconSrc/Button_UltimateSkill6)}"\
			"QPushButton:!enabled{background-image:url(:/IconSrc/Button_UltimateSkill6_disable)}");
		if (state.HasMoved)
			_btMove->setDisabled(true);
		if (state.HasAttacked)
			_btAttack->setDisabled(true);
		if (!EX_state)
			_btUltimateSkill->setDisabled(true);
		break;
	}

	QObject::connect(_btMove, &QPushButton::clicked, this, &PanelOperate::EmitMovePressedSignal);
	QObject::connect(_btAttack, &QPushButton::clicked, this, &PanelOperate::EmitAttackPressedSignal);
	QObject::connect(_btUltimateSkill, &QPushButton::clicked, this, &PanelOperate::EmitUltimateSkillPressedSignal);
	QObject::connect(_btCancel, &QPushButton::clicked, this, &PanelOperate::EmitCancelPressedSignal);

	this->show();
}

PanelOperate::~PanelOperate()
{

}

void PanelOperate::EmitMovePressedSignal(){
	emit btMovePressed_Signal();
}

void PanelOperate::EmitAttackPressedSignal(){
	emit btAttackPressed_Signal();
}

void PanelOperate::EmitUltimateSkillPressedSignal(){
	emit btUltimateSkillPressed_Signal();
}

void PanelOperate::EmitCancelPressedSignal(){
	emit btCancelPressed_Signal();
}
