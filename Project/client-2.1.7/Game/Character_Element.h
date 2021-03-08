#ifndef CHARACTER_ELEMENT_H
#define CHARACTER_ELEMENT_H

#include <random>

class Character_Element{
public:
	Character_Element(){};
	void set_HP(int temp){ HP = temp; };
	void set_Max_HP(int temp){ Max_HP = temp; };
	void set_Initiative(int temp){ Initiative = temp; };
	void set_Speed(int temp){ Speed = temp; };
	void set_Range_Inc(int temp){ Range_Inc = temp; };
	void set_AB(int temp){ AB = temp; };
	void set_AC(int temp){ AC = temp; };
	void set_X(int temp) { X = temp; };
	void set_Y(int temp) { Y = temp; };
	void set_Ability_Bonus(int temp){ Ability_Bonus = temp; };
	void set_Dice_Num(int temp){ Dice_Num = temp; };
	void set_Dice_Type(int temp){ Dice_Type = temp; };
	void set_Critical_Hit_Range(int temp){ Critical_Hit_Range = temp; };
	void set_Critical_Hit_Bonus(int temp){ Critical_Hit_Bonus = temp; };

	int get_HP(){ return HP; };
	int get_Max_HP(){ return Max_HP; };
	int get_Initiative(){ return Initiative; };
	int get_Speed(){ return Speed; };
	int get_Range_Inc(){ return Range_Inc; };
	int get_AB(){ return AB; };
	int get_AC_basic(){ return AC; };
	int get_X() { return X; };
	int get_Y() { return Y; };
	int get_Ability_Bonus(){ return Ability_Bonus; };
	int get_Dice_Num(){ return Dice_Num; };
	int get_Dice_Type(){ return Dice_Type; };
	int get_Critical_Hit_Range(){ return Critical_Hit_Range; };
	int get_Critical_Hit_Bonus(){ return Critical_Hit_Bonus; };

	virtual bool Death(int Round_temp) = 0;
	virtual void Input_Damage(int Damage) = 0;
	int get_Attack_Roll();
	int Output_Damage_basic(int AC);


private:
	int get_Damage();
	int Critical_Hit_Damage(int AC);

	int HP;						//Hit Point
	int Max_HP;					//MAX_HP
	int Initiative;				//Initiative
	int Speed;					//Speed

	int Range_Inc;				//Range Increment
	int AB;						//Attack Bonus
	int AC;						//Armor Class

	//Position
	int X;						//X_axis
	int Y;						//Y_axis

	//Damage
	int Ability_Bonus;			//Ability Bonus to the Damage 
	int Dice_Num;				//how many dices
	int Dice_Type;				//Damage = Ability_Bonus + Dice_Num * Dice_Type

	//Critical Hit
	int Critical_Hit_Range;		//Critical Hit Range
	int Critical_Hit_Bonus;		//Critical Hit Bonus

};

#endif