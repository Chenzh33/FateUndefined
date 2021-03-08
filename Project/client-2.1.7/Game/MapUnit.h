#ifndef MAPUNIT_H
#define MAPUNIT_H

#include <QStyleOptionGraphicsItem>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsEffect>
#include "constant.h"



enum class emFloor
{
	Floor_null = 0, 
	cemetery_floor = 11, tombstone = 12, broken_tombstone = 13, 
	bridge_floor = 21, sidewalk_barrier = 22, sidewalk_floor = 23, breakstone = 24,
	castle_floor = 31, carpet = 32, stairs_floor = 33, handrail = 34, fallen_rock = 35, stairs_carpet = 36,
	temple_floor = 41, temple_wall = 42, temple_tree = 43, temple_roof = 44, temple_footstep = 45, temple_floor2 = 46

};

const static QString MapUnitResoursePath[] =
{
	"",
	"", "", "", "", "", "", "", "", "", "",
	":/IconSrc/floor_tomb_1", ":/IconSrc/floor_tomb_2", ":/IconSrc/floor_tomb_3", "", "", "", "", "", "", "",
	":/IconSrc/floor_bridge_1", ":/IconSrc/floor_bridge_2", ":/IconSrc/floor_bridge_3", ":/IconSrc/floor_bridge_4", "", "", "", "", "", "",
	":/IconSrc/floor_castle_1", ":/IconSrc/floor_castle_2", ":/IconSrc/floor_castle_3", ":/IconSrc/floor_castle_4", ":/IconSrc/floor_castle_5", ":/IconSrc/floor_castle_6", "", "", "", "",
	":/IconSrc/floor_temple_1", ":/IconSrc/floor_temple_2", ":/IconSrc/floor_temple_3", ":/IconSrc/floor_temple_4", ":/IconSrc/floor_temple_5", ":/IconSrc/floor_temple_6", "", "", "", "",


};

class MapUnit : public QObject, public QGraphicsItem
{
	Q_OBJECT
public:

	MapUnit(int x, int y, emFloor eType, int index);
	MapUnit(const MapUnit& M);
	~MapUnit();


	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
	QPainterPath shape() const;

	bool get_note_state(){ return IsNoted; };

	void note();
	void restore();

	int Xcell(){ return _Xcell; };
	int Ycell(){ return _Ycell; };
	emFloor type(){ return _eType; };
	bool CanPass(){ return _IsPassable; };
private:
	int _Index;
	int _Xcell;
	int _Ycell;
	emFloor _eType;
	bool _IsPassable;
	bool IsNoted;
	QGraphicsColorizeEffect *_ColorEffect;

};

#endif