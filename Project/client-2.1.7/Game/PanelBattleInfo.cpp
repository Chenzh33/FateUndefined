#include "PanelBattleInfo.h"


PanelBattleInfo::PanelBattleInfo(GameContent *content,GameState *state, QWidget *parent) : QFrame(parent)
{
	_Content = content;
	_State = state;

	this->setObjectName("PanelBattleInfo");
	this->setGeometry(VIEW_WIDTH / 2 - 140, 45, 300, 600);
	this->setFixedSize(300, 600);
	this->setWindowFlags(Qt::FramelessWindowHint);


	QLabel* text_round = new QLabel("ROUND:", this);
	text_round->setGeometry(90, 55, 120, 20);
	text_round->setFont(QFont("Algerian", 20, QFont::Bold));
	QGraphicsColorizeEffect *ColorEffect_Round = new QGraphicsColorizeEffect(text_round);
	ColorEffect_Round->setColor(QColor(255, 255, 65));
	text_round->setGraphicsEffect(ColorEffect_Round);

	_RoundNumText = new QLabel(QString{ std::to_string(_State->Round).c_str() }, this);
	_RoundNumText->setGeometry(210, 45, 120, 30);
	_RoundNumText->setFont(QFont("Algerian", 30, QFont::Bold));
	QGraphicsColorizeEffect *ColorEffect_RoundNum = new QGraphicsColorizeEffect(_RoundNumText);
	ColorEffect_RoundNum->setColor(QColor(87, 206, 237));
	_RoundNumText->setGraphicsEffect(ColorEffect_RoundNum);
}

PanelBattleInfo::~PanelBattleInfo()
{

}

void PanelBattleInfo::RefreshNewRoundInfo()
{
	_RoundNumText->setText(std::to_string(_State->Round).c_str());
	for (int i = 0; i != AllElementInfo.size(); i++){
		AllElementInfo[i]->deleteLater();
	}
	AllElementInfo.clear();
	for (int i = 0; i != _State->AttackSequence.size(); i++){
		ElementBattleInfo* elementInfo_tmp = new ElementBattleInfo(_State,_Content->Elements()->get_Element(_State->AttackSequence[i]), this);
		elementInfo_tmp->setGeometry(0, 100 + 36 * i, 300, 36);
		AllElementInfo.push_back(elementInfo_tmp);
		elementInfo_tmp->show();
	}
}

void PanelBattleInfo::RefreshAllBattleInfo()
{
	for (int i = 0; i != AllElementInfo.size(); i++){
		AllElementInfo[i]->RefreshBattleInfo();
	}
}

void PanelBattleInfo::paintEvent(QPaintEvent *)
{
	QPainter p(this);
	p.save();
	QBrush brush(QColor(0, 0, 0));
	p.setBrush(brush);
	p.setOpacity(0.5);
	p.drawRoundedRect(rect(), 20, 20);
	p.restore();
}