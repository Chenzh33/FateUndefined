#include "Element.h"

Element::Element(int x, int y, int index)
{
	_character.set_Choose(abs(index));
	_character.Initial();
	_character.set_X(x - 1);
	_character.set_Y(y - 1);//new added
	_Index = index;
	surface_index = index;
	IsAttackNoted = false;

	_Effect = nullptr;
	this->setCursor(Qt::PointingHandCursor);
	this->setProperty("pos", QPointF{ static_cast<double>(MAP_INIT_SPACE_WIDTH + (x - 1)*CELL_SIZE), static_cast<double>(MAP_INIT_SPACE_HEIGHT + (y - 1)*CELL_SIZE) });
}

QRectF Element::boundingRect() const
{
	if (_Index != 15 && _Index != 16 && _Index != 17)
		return QRectF(0, 0, CELL_SIZE, CELL_SIZE);
	else
		return QRectF(0, 0, 2 * CELL_SIZE, 2 * CELL_SIZE);
}

void Element::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget*widget)
{
	int group_index;
	if (surface_index != 19 && surface_index != 20){
		group_index = (surface_index > 0) ? surface_index - 1 : 5 - surface_index;
	}
	else{
		group_index = surface_index-1;
	}

	painter->save();
	painter->fillPath(shape(), QBrush(QPixmap(ElementResoursePath[group_index])));
	painter->restore();
	painter->drawPixmap(0, 0, QPixmap(ElementResoursePath[group_index]));

}

QPainterPath Element::shape() const
{
	QPainterPath p;
	if (_Index != 15 && _Index != 16 && _Index != 17)
		p.addRect(QRect(0, 0, CELL_SIZE, CELL_SIZE));
	else
		p.addRect(QRect(0, 0, 2 * CELL_SIZE, 2 * CELL_SIZE));
	return p;
}

void Element::Move(int x, int y)
{
	//Animation here
	_character.set_X(x);
	_character.set_Y(y);
}

bool Element::checkInRange(int x, int y){ // Character class is in need
	if (abs(x - _character.get_X()) <= 5 && abs(y - _character.get_Y()) <= 5)
		return true;
	else
		return false;
}

void Element::move_note()
{
	_Effect = new QGraphicsColorizeEffect();
	_Effect->setColor(QColor(192, 192, 0));
	_Effect->setStrength(0.6);
	this->setGraphicsEffect(_Effect);

}

void Element::attack_note()
{
	_Effect = new QGraphicsColorizeEffect();
	_Effect->setColor(QColor(192, 0, 0));
	_Effect->setStrength(0.6);
	this->setGraphicsEffect(_Effect);
	IsAttackNoted = true;
}

void Element::tomb_note()
{
	_Effect = new QGraphicsColorizeEffect();
	_Effect->setColor(QColor(0, 0, 0));
	_Effect->setStrength(0.8);
	this->setGraphicsEffect(_Effect);
}

void Element::restore()
{
	if (_Effect != nullptr){
		delete(_Effect);
		_Effect = nullptr;
	}
	IsAttackNoted = false;
}

void Element::alive_note()
{
	_Effect = new QGraphicsColorizeEffect();
	_Effect->setColor(QColor(255, 255, 255));
	_Effect->setStrength(0);
	this->setGraphicsEffect(_Effect);
}