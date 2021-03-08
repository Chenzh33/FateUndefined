#include"MapUnit.h"

MapUnit::MapUnit(int x, int y, emFloor eType, int index)
{
	setPos(MAP_INIT_SPACE_WIDTH + CELL_SIZE * x, MAP_INIT_SPACE_HEIGHT + CELL_SIZE * y);
	_eType = eType;
	_ColorEffect = nullptr;
	_Index = index;
	_Xcell = x;
	_Ycell = y;
	IsNoted = false;
	if (_eType == emFloor::Floor_null)
		_IsPassable = false;

	if (_eType == emFloor::cemetery_floor)
		_IsPassable = true;
	if (_eType == emFloor::tombstone || _eType == emFloor::broken_tombstone)
		_IsPassable = false;

	if (_eType == emFloor::bridge_floor || _eType == emFloor::sidewalk_floor)
		_IsPassable = true;
	if (_eType == emFloor::sidewalk_barrier || _eType == emFloor::breakstone)
		_IsPassable = false;

	if (_eType == emFloor::castle_floor || _eType == emFloor::carpet || _eType == emFloor::stairs_floor || _eType == emFloor::stairs_carpet)
		_IsPassable = true;
	if (_eType == emFloor::handrail || _eType == emFloor::fallen_rock)
		_IsPassable = false;

	if (_eType == emFloor::temple_floor || _eType == emFloor::temple_floor2 || _eType == emFloor::temple_footstep)
		_IsPassable = true;
	if (_eType == emFloor::temple_roof || _eType == emFloor::temple_tree || _eType == emFloor::temple_wall)
		_IsPassable = false;

}


MapUnit::~MapUnit()
{

}

QRectF MapUnit::boundingRect() const
{
	return QRectF(0, 0, CELL_SIZE, CELL_SIZE);
}

void MapUnit::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget*widget)
{
	painter->save();
	painter->setOpacity(0.6);//新增，调节透明度
	painter->fillPath(shape(), QBrush(QPixmap(MapUnitResoursePath[static_cast<int>(_eType)])));
	painter->drawPixmap(0, 0, QPixmap(MapUnitResoursePath[static_cast<int>(_eType)]));
	painter->restore();

}

QPainterPath MapUnit::shape() const
{
	QPainterPath p;
	p.addRect(QRectF(0, 0, CELL_SIZE, CELL_SIZE));
	return p;
}

void MapUnit::note()
{
	this->setCursor(Qt::PointingHandCursor);
	_ColorEffect = new QGraphicsColorizeEffect();
	_ColorEffect->setColor(QColor(0, 192, 0));
	_ColorEffect->setStrength(0.3);
	this->setGraphicsEffect(_ColorEffect);
	IsNoted = true;
}

void MapUnit::restore()
{
	this->setCursor(Qt::ArrowCursor);
	if (_ColorEffect != nullptr){
		delete(_ColorEffect);
		_ColorEffect = nullptr;
	}
	IsNoted = false;
}


