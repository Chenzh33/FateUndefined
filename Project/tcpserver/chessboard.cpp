#include"chessboard.h"

chessboard::chessboard(QString newplayer1,QString newplayer2){
	player1 = newplayer1;
	player2 = newplayer2;
	Round = 0;
	readyPlayer = 0;
	initElementPool();
}

void chessboard::initQueue(){
	QVector<int> ChooseSide;
	ChooseSide.push_back(rand() % 2);
	ChooseSide.push_back(1 - ChooseSide[0]);
	QVector<int> Miku, Rin;

	for (int i = 0; i < ELEMENTS_NUM; i++)
	{
		Miku.push_back((rand() % 20) * 100 + Initiative[i] * 10 + ChooseSide[0]);
		Rin.push_back((rand() % 20) * 100 + Initiative[i] * 10 + ChooseSide[1]);
	}
	for (int i = 0; i < ELEMENTS_NUM * 2; i++)
	{
		int Miku_max{ 0 }, Rin_max{ 0 };
		for (int j = 0; j < ELEMENTS_NUM; j++)
		{
			if (Miku[j] > Miku[Miku_max]) Miku_max = j;
			if (Rin[j] > Rin[Rin_max]) Rin_max = j;
		}
		int Max{ Miku[Miku_max] > Rin[Rin_max] ? Miku_max + 1 : (-1 - Rin_max) };
		if (!_Elements->get_Element(Max)->_character.Death(Round))
			AttackSequence.push_back(Max);
		if (Max > 0) Miku[Max - 1] = -1;
		else Rin[-Max - 1] = -1;
	}
}

void chessboard::initNewRound(){
	Round++;
	initQueue();
}

int chessboard::Next(){
	//_Elements->get_Element(AttackSequence.front());
	do{
		AttackSequence.pop_front();
		if (AttackSequence.empty()){
			initNewRound();
		}
	} while (_Elements->get_Element(AttackSequence.front())->_character.Death(Round));
	int nextpiece = AttackSequence.front();
	return nextpiece;
}

int chessboard::CheckVictory(){
	bool flag_Miku = true, flag_Rin = true;
	for (int i = 0; i != ELEMENTS_NUM; i++)
	if (!_Elements->get_Element(i + 1)->_character.Death(Round)) flag_Miku = false;
	if ((_Elements->get_Element(6)->_character.get_Whether_Strokes() == 1) &&
		(Round - _Elements->get_Element(6)->_character.get_Round_Death() < 2))
		flag_Miku = false;
	for (int i = 0; i != ELEMENTS_NUM; i++)
	if (!_Elements->get_Element(-(i + 1))->_character.Death(Round)) flag_Rin = false;
	if ((_Elements->get_Element(-6)->_character.get_Whether_Strokes() == 1) &&
		(Round - _Elements->get_Element(-6)->_character.get_Round_Death() < 2))
		flag_Rin = false;
	if (flag_Miku)
	{
		return 1;
	}
	if (flag_Rin)
	{
		return -1;
	}
	return 0;
}

void chessboard::initElementPool(){
	_Elements = new ElementPool();
	//各_Element都还没initial()
	for (int i = 0; i != ELEMENTS_NUM; i++){
		Element *element = new Element(0, 2 * i + 2, 0, i + 1);
		_Elements->addElement(element);
	}
	for (int i = 0; i != ELEMENTS_NUM; i++){
		//Element *element = new Element(_Map->get_map_width() - 1, 2 * i + 2, 1, i + 1);
		Element *element = new Element(8, 2 * i + 2, 1, i + 1);
		_Elements->addElement(element);
	}
}

void chessboard::Melee_Archer(Element*element){
	element->_character.set_AB(8);
	element->_character.set_AC(13);
	element->_character.set_Ability_Bonus(0);
	element->_character.set_Range_Inc(1);
	element->_character.set_Dice_Num(3);
	element->_character.set_Dice_Type(4);
	element->_character.set_Critical_Hit_Range(2);
	element->_character.set_Critical_Hit_Bonus(2);
	element->_character.set_Speed(8);
}

void chessboard::Remote_Archer(Element*element){
	element->_character.set_AB(6);
	element->_character.set_AC(13);
	element->_character.set_Ability_Bonus(0);
	element->_character.set_Range_Inc(10);
	element->_character.set_Dice_Num(1);
	element->_character.set_Dice_Type(8);
	element->_character.set_Critical_Hit_Range(1);
	element->_character.set_Critical_Hit_Bonus(3);
	element->_character.set_Speed(6);
}