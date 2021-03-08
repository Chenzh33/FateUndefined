#ifndef ELEMENT_H
#define ELEMENT_H

#include <QStyleOptionGraphicsItem>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsEffect>
#include "constant.h"
#include "Set_Character.h"
#include <qstring.h>
static int Initiative[] =
{
	2, 1, 4, 3, 0, 5
};
class Element //: public QObject  , public QGraphicsItem
{
	//Q_OBJECT
public:
	Element(int x, int y, int camp,int choose);
	int Camp(){ return _Camp; };
	void Move(int x, int y);
	bool checkInRange(int x, int y);
	void destroyText();
	Character _character;
	//QRectF boundingRect() const;
	//void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
	//QPainterPath shape() const;
	//bool get_note_state(){ return IsAttackNoted; };
	//void move_note();
	//void attack_note();
	//void restore();
private:
	int _Camp;
	//bool IsAttackNoted;
	//QGraphicsColorizeEffect *_Effect;
};

#endif