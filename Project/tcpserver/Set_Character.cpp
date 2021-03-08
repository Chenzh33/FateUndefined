#include "Set_Character.h"
#include <iostream>
#include <string>
#include <math.h>
#define min(x,y) (x>y?y:x)
#define max(x,y) (x>y?x:y)

int Character::get_Distance(Character Example)
{
	int X_diff = abs(get_X() - Example.get_X());
	int Y_diff = abs(get_Y() - Example.get_Y());
	int small = min(X_diff, Y_diff);
	int large = max(X_diff, Y_diff);
	int Distance = floor(1.5*small) + (large - small);
	return Distance;
}

bool Character::Death(int Round_temp)
{
	if (get_HP() > 0) return false;
	if (Choose != 6) return true;
	if (Whether_Strokes == 0)
	{
		Round_Death = Round_temp;
		return true;
	}
	if ((Whether_Strokes == 1) && (Round_temp - Round_Death == 2))
	{
		set_HP(15);
		return false;
	}
	return true;
}

bool Character::if_Strokes()
{
	if (Num_Strokes > 0) return true;
	return false;
}

void Character::Input_Damage(int Damage)
{
	switch (Choose)
	{
	case 1: case 2: case 4: case 6:
	{
				set_HP(get_HP() - Damage);
				break;
	}
	case 3:
	{
			  set_HP(get_HP() - Damage);
			  if ((get_HP() <= 13) && (Whether_Strokes == 0))
			  {
				  Whether_Strokes++;
				  Num_Strokes = 1;
			  }
			  break;
	}
	case 5:
	{
			  set_HP(get_HP() - Damage + min(Damage, 2));
			  break;
	}
	}

}

void Character::Initial()
{
	switch (Choose)
	{
	case 1: {
				set_HP(38);
				set_Max_HP(38);
				set_Initiative(2);
				set_Speed(4);
				set_Range_Inc(1);
				set_AB(8);
				set_AC(18);
				set_Ability_Bonus(6);
				set_Dice_Num(1);
				set_Dice_Type(10);
				set_Critical_Hit_Range(2);
				set_Critical_Hit_Bonus(2);
				set_Whether_Strokes(0);
				set_Num_Strokes(0);
				set_Cause_Damage(0);
				break;
	}
	case 2:{
			   set_HP(34);
			   set_Max_HP(34);
			   set_Initiative(1);
			   set_Speed(6);
			   set_Range_Inc(10);
			   set_AB(6);
			   set_AC(13);
			   set_Ability_Bonus(0);
			   set_Dice_Num(1);
			   set_Dice_Type(8);
			   set_Critical_Hit_Range(1);
			   set_Critical_Hit_Bonus(3);
			   set_Whether_Strokes(0);
			   set_Num_Strokes(1);
			   set_Cause_Damage(0);
			   break;
	}
	case 3:{
			   set_HP(26);
			   set_Max_HP(26);
			   set_Initiative(4);
			   set_Speed(6);
			   set_Range_Inc(1);
			   set_AB(7);
			   set_AC(15);
			   set_Ability_Bonus(3);
			   set_Dice_Num(2);
			   set_Dice_Type(4);
			   set_Critical_Hit_Range(1);
			   set_Critical_Hit_Bonus(3);
			   set_Whether_Strokes(0);
			   set_Num_Strokes(0);
			   set_Cause_Damage(0);
			   break;
	}
	case 4:{
			   set_HP(16);
			   set_Max_HP(16);
			   set_Initiative(3);
			   set_Speed(6);
			   set_Range_Inc(1);
			   set_AB(6);
			   set_AC(15);
			   set_Ability_Bonus(2);
			   set_Dice_Num(1);
			   set_Dice_Type(8);
			   set_Critical_Hit_Range(1);
			   set_Critical_Hit_Bonus(3);
			   set_Whether_Strokes(0);
			   set_Num_Strokes(0);
			   break;
	}
	case 5:{
			   set_HP(11);
			   set_Max_HP(11);
			   set_Initiative(0);
			   set_Speed(4);
			   set_Range_Inc(100);
			   set_AB(40);
			   set_AC(10);
			   set_Ability_Bonus(0);
			   set_Dice_Num(1);
			   set_Dice_Type(4);
			   set_Critical_Hit_Range(0);
			   set_Critical_Hit_Bonus(1);
			   set_Whether_Strokes(1);
			   set_Num_Strokes(3);
			   break;
	}
	case 6:{
			   set_HP(47);
			   set_Max_HP(47);
			   set_Initiative(5);
			   set_Speed(8);
			   set_Range_Inc(1);
			   set_AB(9);
			   set_AC(8);
			   set_Ability_Bonus(7);
			   set_Dice_Num(1);
			   set_Dice_Type(12);
			   set_Critical_Hit_Range(1);
			   set_Critical_Hit_Bonus(3);
			   set_Whether_Strokes(0);
			   set_Num_Strokes(0);
			   break;
	}
	}
}

void Character::change_Cause_Damage(int Damage)
{
	Cause_Damage += Damage;
	if ((Choose == 1) && (Cause_Damage > 30) && (Whether_Strokes == 0))
	{
		Whether_Strokes = 1;
		Num_Strokes = 1;
	}
	if ((Choose == 2) && (Cause_Damage > 10) && (Whether_Strokes == 0))
	{
		Whether_Strokes = 1;
		Num_Strokes = 1;
	}
}

int Character::get_AC()
{
	int temp = get_AC_basic();
	if (Choose != 4) return temp;
	std::random_device rd;
	if (rd() % 2) return 30;
	return temp;
}

int Character::Output_Damage(int AC)
{
	int temp = Output_Damage_basic(AC);
	change_Cause_Damage(temp);
	return temp;
}