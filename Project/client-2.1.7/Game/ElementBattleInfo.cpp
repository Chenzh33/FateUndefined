#include "ElementBattleInfo.h"

ElementBattleInfo::ElementBattleInfo(GameState *state, Element*element, QWidget *parent) : QFrame(parent)
{
	_State = state;
	_Element = element;
	IsDead = false;
	_DeathEffect = nullptr;
	_ActiveNote = nullptr;
	_ElementIcon = new QLabel(this);
	_HPNumText = new QLabel(this);
	_UltimateSkillState = new QLabel(this);

	QVector<QString> Class;
	Class.push_back("Saber");
	Class.push_back("Archer");
	Class.push_back("Rider");
	Class.push_back("Assassin");
	Class.push_back("Caster");
	Class.push_back("Berserker");
	QString String_temp_icon = { ":/IconSrc/" + Class[abs(_Element->Index()) - 1] + "_headup" };
	_ElementIcon->setPixmap(QPixmap(String_temp_icon));

	_HPNumText->setFont(QFont("Algerian", 15, QFont::Bold));
	QGraphicsColorizeEffect *ColorEffect_HPNumText = new QGraphicsColorizeEffect(_HPNumText);
	ColorEffect_HPNumText->setColor(QColor(255, 0, 0));
	_HPNumText->setGraphicsEffect(ColorEffect_HPNumText);

	_UltimateSkillState->setFont(QFont("Algerian", 15, QFont::Bold));
	QGraphicsColorizeEffect *ColorEffect_UltimateSkillState = new QGraphicsColorizeEffect(_UltimateSkillState);
	ColorEffect_UltimateSkillState->setColor(QColor(255, 0, 0));
	_UltimateSkillState->setGraphicsEffect(ColorEffect_UltimateSkillState);

	QLabel* HP_Text = new QLabel(" HP ",this);
	HP_Text->setFont(QFont("Algerian", 20, QFont::Bold));
	QGraphicsColorizeEffect *ColorEffect_HP_Text = new QGraphicsColorizeEffect(HP_Text);
	ColorEffect_HP_Text->setColor(QColor(255, 255, 65));
	HP_Text->setGraphicsEffect(ColorEffect_HP_Text);

	QLabel* UltimateSkill_Text = new QLabel(" EX ",this);
	UltimateSkill_Text->setFont(QFont("Algerian", 20, QFont::Bold));
	QGraphicsColorizeEffect *ColorEffect_UltimateSkill_Text = new QGraphicsColorizeEffect(UltimateSkill_Text);
	ColorEffect_UltimateSkill_Text->setColor(QColor(255, 255, 65));
	UltimateSkill_Text->setGraphicsEffect(ColorEffect_UltimateSkill_Text);

	if (_Element->Index() > 0){
		_ElementIcon->setGeometry(0, 0, 66, 36);
		HP_Text->setGeometry(66, 0, 50, 36);
		_HPNumText->setGeometry(116, 0, 70, 36);
		UltimateSkill_Text->setGeometry(186, 0, 60, 36);
		_UltimateSkillState->setGeometry(246, 0, 54, 36);
	}
	else{
		HP_Text->setGeometry(0, 0, 50, 36);
		_HPNumText->setGeometry(50, 0, 70, 36);
		UltimateSkill_Text->setGeometry(120, 0, 60, 36);
		_UltimateSkillState->setGeometry(180, 0, 56, 36);
		_ElementIcon->setGeometry(234, 0, 66, 36);
	}
	this->RefreshBattleInfo();
}

ElementBattleInfo::~ElementBattleInfo()
{


}


void ElementBattleInfo::paintEvent(QPaintEvent *)
{
	QPainter p(this);
	p.save();
	p.setOpacity(0.3);
	QBrush brush(QColor(0, 0, 0));
	if (_Element->Index() > 0)
		brush.setColor(QColor(255, 255, 0));
	else
		brush.setColor(QColor(0, 204, 255));

	p.setBrush(brush);
	p.drawRect(rect());
	p.restore();
}

void ElementBattleInfo::RefreshBattleInfo()
{
	int HP = _Element->_character.get_HP();
	if (HP < 0) HP = 0;
	QString String_temp_HP = std::to_string(HP).c_str();
	String_temp_HP.append('/');
	String_temp_HP.append(std::to_string(_Element->_character.get_Max_HP()).c_str());
	_HPNumText->setText(String_temp_HP);

	if ((_Element->_character.get_Choose() == 4) || (_Element->_character.get_Choose() == 6))
		_UltimateSkillState->setText("N/A");
	else if (_Element->_character.get_Choose() == 2){
		_UltimateSkillState->setText(QStringLiteral("¡Þ"));
	}
	else
		_UltimateSkillState->setText(std::to_string(_Element->_character.get_Num_Strokes()).c_str());

	if (_Element->_character.Death(_Element->_character.get_Round_Death())){
		IsDead = true;
		_DeathEffect = new QGraphicsColorizeEffect();
		_DeathEffect->setColor(QColor(0, 0, 0));
		_ElementIcon->setGraphicsEffect(_DeathEffect);
	}
	else{
		IsDead = false;
		if (_DeathEffect != nullptr){
			_DeathEffect->deleteLater();
			_DeathEffect = nullptr;
		}
	}
	this->ActiveNoteToggle();
}

void ElementBattleInfo::ActiveNoteToggle()
{
	if (_State->AttackSequence.front() == _Element->Index()){
		if (_ActiveNote == nullptr){
			_ActiveNote = new QFrame(this);
			_ActiveNote->setObjectName("ActiveNote");
			_ActiveNote->setStyleSheet("QFrame#ActiveNote{background-image:url(:/IconSrc/Active_Note)}");
			_ActiveNote->setGeometry(0, 0, 300, 36);
			_ActiveNote->show();
		}
	}
	else{
		if (_ActiveNote != nullptr){
			_ActiveNote->deleteLater();
			_ActiveNote = nullptr;
		}

	}

}