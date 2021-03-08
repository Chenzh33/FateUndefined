#include "Character_Element.h"

int Character_Element::get_Attack_Roll(){
	std::random_device rd;
	return (rd() % 20 + 1);
}

int Character_Element::get_Damage(){
	std::random_device rd;
	return (Ability_Bonus + Dice_Num * (rd() % Dice_Type + 1));
}

int Character_Element::Critical_Hit_Damage(int AC){
	int temp_Attack_Roll = get_Attack_Roll();
	if (temp_Attack_Roll == 1) return 0;
	if (temp_Attack_Roll + AB < AC) return 0;
	int Damage = 0;
	for (int i = 1; i < Critical_Hit_Bonus; i++){ Damage += get_Damage(); };
	return Damage;
}

int Character_Element::Output_Damage_basic(int AC){
	int Damage = 0;
	int temp_Attack_Roll = get_Attack_Roll();
	if (temp_Attack_Roll == 1) return 0;
	if (temp_Attack_Roll + AB < AC) return 0;
	if (20 - temp_Attack_Roll < Critical_Hit_Range) { Damage = Critical_Hit_Damage(AC); };
	Damage += get_Damage();
	return Damage;
}

