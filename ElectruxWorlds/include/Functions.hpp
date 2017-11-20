#pragma once

bool initdefaults()
{
	if (!corefont.loadFromFile("Assets/Fonts/" + corefontname)) return false;

	//Weaponry.
	defaultgearset.weapon = "Assets/Actors/thrust/WEAPON_spear.png";
	defaultgearset.offhand = "Assets/Actors/thrust/WEAPON_shield_cutout_body.png";

	//Armor + Model.
	defaultgearset.model = "Assets/Actors/walkcycle/BODY_male.png";
	defaultgearset.head = "Assets/Actors/walkcycle/HEAD_plate_armor_helmet.png";
	defaultgearset.shoulders = "Assets/Actors/walkcycle/TORSO_plate_armor_arms_shoulders.png";
	defaultgearset.arms = "Assets/Actors/walkcycle/HANDS_plate_armor_gloves.png";
	defaultgearset.body = "Assets/Actors/walkcycle/TORSO_plate_armor_torso.png";
	defaultgearset.legs = "Assets/Actors/walkcycle/LEGS_plate_armor_pants.png";
	defaultgearset.shoes = "Assets/Actors/walkcycle/FEET_plate_armor_shoes.png";

	return true;
}
