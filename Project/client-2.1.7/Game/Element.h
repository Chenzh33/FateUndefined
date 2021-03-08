#ifndef ELEMENT_H
#define ELEMENT_H

#include <QStyleOptionGraphicsItem>
#include <QPropertyAnimation>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsEffect>
#include "constant.h"
#include "Set_Character.h"
#include <qstring.h>

const static QString ElementResoursePath[20] =
{
	":/IconSrc/Saber_1", ":/IconSrc/Archer_1", ":/IconSrc/Rider_1",
	":/IconSrc/Assassin_1", ":/IconSrc/Caster_1", ":/IconSrc/Berserker_1",
	":/IconSrc/Saber_2", ":/IconSrc/Archer_2", ":/IconSrc/Rider_2",
	":/IconSrc/Assassin_2", ":/IconSrc/Caster_2", ":/IconSrc/Berserker_2",
	":/IconSrc/bullet_Archer", ":/IconSrc/bullet_Caster", ":/IconSrc/bullet_Saber",
	":/IconSrc/bullet_Saber_Effect_Fast", ":/IconSrc/bullet_Saber_Effect_Slow",
	":/IconSrc/Assassin_Dodge", ":/IconSrc/Archer_3",":/IconSrc/Archer_4"
};

const static int Initiative[] = 
{
	2, 1, 4, 3, 0, 5
};

class Element : public QObject, public QGraphicsItem
{
	Q_OBJECT
	Q_PROPERTY(QPointF pos READ pos WRITE setPos)
	Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
	Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)

public:
	Element(int x, int y,int index);

	int Index(){ return _Index; };

	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
	QPainterPath shape() const;

	void Move(int x, int y);
	bool checkInRange(int x, int y);
	bool get_note_state(){ return IsAttackNoted; };

	void move_note();
	void attack_note();
	void restore();
	void tomb_note();
	void alive_note();

	int surface_index;
	Character _character;
private:
	int _Index;
	bool IsAttackNoted;
	QGraphicsColorizeEffect *_Effect;
};

#endif