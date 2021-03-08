#ifndef SET_CHARACTER_H
#define SET_CHARACTER_H

#include "Character_Element.h"
#include <iostream>
#include <string>
#include <math.h>

class Character : public Character_Element{
public:
	Character(){};
	void Initial();
	int get_Cause_Damage() { return Cause_Damage; };
	void set_Cause_Damage(int temp){ Cause_Damage = temp; };
	void change_Cause_Damage(int Damage);
	virtual void Input_Damage(int Damage);
	virtual bool Death(int Round_temp);

	void set_Num_Strokes(int temp){ Num_Strokes = temp; };
	void change_Num_Strokes() { Num_Strokes--; };
	int get_Num_Strokes() { return Num_Strokes; };
	void set_Whether_Strokes(int temp){ Whether_Strokes = temp; };
	int get_Whether_Strokes(){ return Whether_Strokes; };
	bool if_Strokes();
	int Strokes(int Round_temp, int X_des, int Y_des, int AC, Character Example);

	void set_Round(int temp) { Round = temp; };
	void set_Round_Death(int temp) { Round_Death = temp; };
	int get_Round() { return Round; };
	int get_Round_Death() { return Round_Death; };

	int get_Distance(Character Example);
	void set_Choose(int temp) { Choose = temp; };
	int get_Choose(){ return Choose; };

	int get_AC();
	int Output_Damage(int AC);
private:
	int Choose;
	int Num_Strokes;
	int Cause_Damage;
	int Whether_Strokes;
	int Round;
	int Round_Death;
};

#endif