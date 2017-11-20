#pragma once


//Login to the game.
void login(tgui::EditBox::Ptr user, tgui::EditBox::Ptr pass)
{
	if (!user->getText().isEmpty() && !pass->getText().isEmpty())
	{
		std::cout << "Username: " << user->getText().toAnsiString() << "\n";
		std::cout << "Password: " << pass->getText().toAnsiString() << "\n";

		uname = user->getText().toAnsiString();
		pword = pass->getText().toAnsiString();

		loggedin = true;
		mainmenu = false;
		settingsmenu = false;
	}

}

//Logout back to the main menu.
void logout()
{
	loggedin = false;
	mainmenu = true;
	settingsmenu = false;
}

//Load settings from main menu.
void settings()
{
	loggedin = false;
	mainmenu = false;
	settingsmenu = true;
}

//Load settings when ingame.
void ingamesettings()
{
	loggedin = true;
	mainmenu = false;
	settingsmenu = true;
}

//Save the settings while being ingame.
void ingamesavesettings(tgui::Slider::Ptr res)
{
	loggedin = true;
	mainmenu = false;
	settingsmenu = false;

	loadedloggedin = false;
}

//Updates the resolution label when slider changes.
void updatereslabel(tgui::Slider::Ptr slider, tgui::Label::Ptr res)
{
	int resol = slider->getValue();

	res->setText(std::to_string(RESOLUTIONS[resol].width) + " x " + std::to_string(RESOLUTIONS[resol].height));
}

//Go back to main menu.
void savesettings(tgui::Slider::Ptr res)
{
	loggedin = false;
	mainmenu = true;
	settingsmenu = false;
}

namespace Menus
{
	//Load the main menu interface widgets.
	void loadmainui(tgui::Gui &gui)
	{
		//Load the Baby Blue theme.
		auto theme = tgui::Theme::create("Assets/Menu/BabyBlue.txt");

		auto windowwidth = tgui::bindWidth(gui);
		auto windowheight = tgui::bindHeight(gui);

		//Background image.
		auto pic = tgui::Picture::create("Assets/Menu/DarkAngel.jpg");
		pic->setSize(tgui::bindMax(width, windowwidth), tgui::bindMax(height, windowheight));
		gui.add(pic);

		//Username label.
		tgui::Label::Ptr user = theme->load("Label");
		user->setTextColor(sf::Color::Cyan);
		user->setText("Username: ");
		user->setPosition(windowwidth / 4, windowheight / 2 - 97);
		gui.add(user, "User");

		//Username edit box.
		tgui::EditBox::Ptr editboxuser = theme->load("EditBox");
		editboxuser->setSize(windowwidth / 2, windowheight / 20);
		editboxuser->setPosition(windowwidth / 4, windowheight / 2 - 70);
		editboxuser->setDefaultText("Username");
		gui.add(editboxuser, "Username");

		//Password label.
		tgui::Label::Ptr pass = theme->load("Label");
		pass->setTextColor(sf::Color::Cyan);
		pass->setText("Password: ");
		pass->setPosition(windowwidth / 4, windowheight / 2 - 25);
		gui.add(pass, "Pass");

		//Password edit box.
		tgui::EditBox::Ptr editboxpass = theme->load("EditBox");
		editboxpass->setSize(windowwidth / 2, windowheight / 20);
		editboxpass->setPosition(windowwidth / 4, windowheight / 2);
		editboxpass->setDefaultText("Password");
		gui.add(editboxpass, "Password");

		//Login button.
		tgui::Button::Ptr loginbutton = theme->load("Button");
		loginbutton->setSize(windowwidth / 2, windowheight / 20);
		loginbutton->setPosition(windowwidth / 4, windowheight / 2 + 70);
		loginbutton->setText("Login");
		loginbutton->connect("pressed", login, editboxuser, editboxpass);
		gui.add(loginbutton);

		//Settings button.
		tgui::Button::Ptr settingsbutton = theme->load("Button");
		settingsbutton->setSize(windowwidth / 4, windowheight / 20);
		settingsbutton->setPosition(windowwidth - 350, windowheight - 70);
		settingsbutton->setText("Settings");
		settingsbutton->connect("pressed", settings);
		gui.add(settingsbutton);

	}
	
	//Load the ingame interface widgets.
	void loadgameui(tgui::Gui &gui)
	{
		//Load the Baby Blue theme.
		auto theme = tgui::Theme::create("Assets/Menu/BabyBlue.txt");

		auto windowwidth = tgui::bindWidth(gui);
		auto windowheight = tgui::bindHeight(gui);

		//Logout button.
		tgui::Button::Ptr logoutbutton = theme->load("Button");
		logoutbutton->setSize(windowwidth / 2, windowheight / 20);
		logoutbutton->setPosition(0, windowheight - windowheight / 20);
		logoutbutton->setText("Logout");
		logoutbutton->connect("pressed", logout);
		gui.add(logoutbutton);

		//Settings button.
		tgui::Button::Ptr settingsbutton = theme->load("Button");
		settingsbutton->setSize(windowwidth / 2, windowheight / 20);
		settingsbutton->setPosition(windowwidth / 2, windowheight - windowheight / 20);
		settingsbutton->setText("Settings");
		settingsbutton->connect("pressed", ingamesettings);
		gui.add(settingsbutton);
	}

	//Load the settings menu interface widgets.
	void loadsettingsui(tgui::Gui &gui)
	{
		//Load the Baby Blue theme.
		auto theme = tgui::Theme::create("Assets/Menu/BabyBlue.txt");

		auto windowwidth = tgui::bindWidth(gui);
		auto windowheight = tgui::bindHeight(gui);

		//Background image.
		auto pic = tgui::Picture::create("Assets/Menu/DarkAngel.jpg");
		pic->setSize(tgui::bindMax(width, windowwidth), tgui::bindMax(height, windowheight));
		gui.add(pic);

		//Resolution label.
		tgui::Label::Ptr res = theme->load("Label");
		res->setTextColor(sf::Color::Cyan);
		res->setText("Resolution: ");
		res->setPosition(windowwidth / 4 - 320, windowheight / 2);
		gui.add(res, "Resolution");

		//Current Resolution label.
		tgui::Label::Ptr curres = theme->load("Label");
		curres->setTextColor(sf::Color::Cyan);
		curres->setText(std::to_string(RESOLUTIONS[0].width) + " x " + std::to_string(RESOLUTIONS[0].height));
		curres->setPosition(windowwidth - 400, windowheight / 2 - 35);
		gui.add(curres);

		//Resolution slider.
		tgui::Slider::Ptr slider = theme->load("Slider");
		slider->setMinimum(0);
		slider->setMaximum(4);
		slider->setValue(0);
		slider->setSize(windowwidth / 6, windowheight / 20);
		slider->setPosition(windowwidth - 400, windowheight / 2);
		slider->connect("valuechanged", updatereslabel, slider, curres);
		gui.add(slider, "ResolutionVal");

		//Save the settings.
		tgui::Button::Ptr button = theme->load("Button");
		button->setSize(windowwidth / 2, windowheight / 20);
		button->setPosition(windowwidth / 4, windowheight / 2 + 140);
		button->setText("Save");
		if(loggedin && settingsmenu)
			button->connect("pressed", ingamesavesettings, slider);
		else
			button->connect("pressed", savesettings, slider);
		gui.add(button);
	}

}