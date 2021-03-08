#include "Element.h"

Element::Element(int x, int y, int camp,int choose)
{
	_character.set_Choose(choose);
	_character.Initial();
	_character.set_X(x);
	_character.set_Y(y);

	_Camp = camp;
}


void Element::Move(int x, int y){
	//Animation here
	_character.set_X(x);
	_character.set_Y(y);
	//setPos(MAP_INIT_SPACE_WIDTH + x*CELL_SIZE, MAP_INIT_SPACE_HEIGHT + y*CELL_SIZE);
}

bool Element::checkInRange(int x, int y){ // Character class is in need
	if (abs(x - _character.get_X()) <= 5 && abs(y - _character.get_Y()) <= 5)
		return true;
	else
		return false;
}
