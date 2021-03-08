#include "MapInfo.h"

MapInfo::MapInfo()
{


}


MapInfo::~MapInfo()
{

}

QString StringToQString(std::string s)
{
	QString ans{ s.c_str() };
	return ans;
}

void MapInfo::initMapFile(QString mapfile)
{
	std::ifstream infile{ mapfile.toStdString()};
	std::string infile_s;
	infile >> infile_s;
	CurrentMapFileInfo.MapName = StringToQString(infile_s);

	infile >> CurrentMapFileInfo.MapWidth >> CurrentMapFileInfo.MapHeight;

	int BirthPointX, BirthPointY;
	for (int i = 0; i != ELEMENTS_NUM * 2; i++){
		infile >> BirthPointX >> BirthPointY;
		CurrentMapFileInfo.BirthPoints.push_back(QPair<int, int>{BirthPointX, BirthPointY});
	}

	for (int i = 0; i < CurrentMapFileInfo.MapHeight*CurrentMapFileInfo.MapWidth; i++)
	{
		int temp;
		infile >> temp;
		CurrentMapFileInfo.MapFloorInfo.push_back((emFloor)temp);
	}
	infile.close();
}

bool MapInfo::check_MapUnit_exist(int x, int y)
{
	if (x >= 0 && x < CurrentMapFileInfo.MapWidth&&y >= 0 && y < CurrentMapFileInfo.MapHeight)
		return true;
	else
		return false;
}

MapUnit* MapInfo::get_MapUnit_around(int x, int y, int offset_x, int offset_y)
{
	if (check_MapUnit_exist(x + offset_x, y + offset_y))
		return MapUnitVector[(y + offset_y) * CurrentMapFileInfo.MapWidth + x + offset_x];
	else
		return nullptr;
}

MapUnit* MapInfo::get_MapUnit_in_MapInfo(QGraphicsItem *obj){
	for (int i = 0; i != MapUnitVector.size(); i++){
		if (MapUnitVector[i] == static_cast<MapUnit*>(obj)){
			return MapUnitVector[i];
		}
	}
	return nullptr;
}

void MapInfo::restoreAllMapUnitColor()
{
	for (int i = 0; i != MapUnitVector.size(); i++){
		if (MapUnitVector[i]->get_note_state()){
			MapUnitVector[i]->restore();
			MapUnitVector[i]->setCursor(Qt::ArrowCursor);
		}
	}
}