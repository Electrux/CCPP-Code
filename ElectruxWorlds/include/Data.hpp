#pragma once

std::string uname, pword;

const std::string corefontname = "Painter.ttf";

bool loggedin = false;
bool mainmenu = true;
bool settingsmenu = false;

bool loadedloggedin = false;
bool loadedmainmenu = false;
bool loadedsettingsmenu = false;

const uint32_t	width = 1280,
				height = 720;

sf::Font corefont;

const float SKIP = 2.0f;

const float PI = 3.141592653589f;

const int MAXFRAMERATE = 60,
		  MAXFRAMEUPDATECTR = 5;

struct Resolutions
{
	int width;
	int height;
};

const std::vector<Resolutions> RESOLUTIONS = {
	{800, 600},
	{1280, 720},
	{1920, 1080},
	{2560, 1440},
	{3840, 2160}
};

struct GearSet {

	std::string weapon,
				offhand,
				model,
				head,
				shoulders,
				arms,
				body,
				legs,
				shoes;

} defaultgearset;

enum DIR
{
	UP,
	LEFT,
	DOWN,
	RIGHT
};