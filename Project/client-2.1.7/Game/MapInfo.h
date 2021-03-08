#ifndef MAPINFO_H
#define MAPINFO_H

#include "MapUnit.h"
#include "LocalSettings.h"
#include <fstream>
#include<QVector>

typedef struct STMapInfo
{
	QString MapName;
	int MapWidth;
	int MapHeight;
	QVector<QPair<int, int> > BirthPoints;
	QVector<emFloor> MapFloorInfo;
}stMapInfo;

typedef struct STMapFile
{
	QString MapName;
	QString ThumbnailPath;
	QString FileName;
}MapFile;

const static MapFile AllMapFileInfo[] = 
{
	MapFile{ "Church yard", ":/IconSrc/Map_Churchyard", "Resources/MapFile/Churchyard.txt" },
	MapFile{ "Einzbern Castle", ":/IconSrc/Map_EinzbernCastle", "Resources/MapFile/EinzbernCastle.txt" },
	MapFile{ "Fuyuki Bridge", ":/IconSrc/Map_FuyukiBridge", "Resources/MapFile/FuyukiBridge.txt" },
	MapFile{ "Liyudou Temple", ":/IconSrc/Map_LiyudouTemple", "Resources/MapFile/LiyudouTemple.txt" }
};

class MapInfo{

public:

	MapInfo();
	~MapInfo();

	bool check_MapUnit_exist(int x, int y);
	MapUnit* get_MapUnit_around(int x, int y, int offset_x, int offset_y);

	int get_map_width(){ return CurrentMapFileInfo.MapWidth; };
	int get_map_height(){ return CurrentMapFileInfo.MapHeight; };
	QVector<emFloor>& get_floor_info(){ return CurrentMapFileInfo.MapFloorInfo; };
	QVector<MapUnit*>& get_MapUnit_vector(){ return MapUnitVector; };
	QVector<QPair<int, int> >& get_BirthPoints(){ return CurrentMapFileInfo.BirthPoints; };
	MapUnit* MapInfo::get_MapUnit_in_MapInfo(QGraphicsItem *obj);
	void restoreAllMapUnitColor();

	void initMapFile(QString mapfile);
private:
	stMapInfo CurrentMapFileInfo;
	QVector<MapUnit*> MapUnitVector;

};



#endif