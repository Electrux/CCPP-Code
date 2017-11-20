#pragma once

class Player : public sf::Drawable
{
	std::string name;
	sf::Text nametext;

	int direction;
	
	Actor model;
	
	float prevangle, newangle;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(model);
		target.draw(nametext);
	}

	float getangle(sf::Vector2f pos, sf::Vector2f newpos)
	{
		//Fetch the angle between player and mouse using atan2 function.
		return (float)atan2(newpos.y - pos.y, newpos.x - pos.x) * 180 / PI;
	}

public:

	Player()
	{
		model.setblocksize(64);
		model.loadtexture(defaultgearset);
		model.setposition(width / 2, height / 2);

		name = "Unnamed";
		nametext.setString(name);
		nametext.setFont(corefont);
		nametext.setCharacterSize(20);
		nametext.setFillColor(sf::Color::Cyan);
		nametext.setPosition(model.getposition().x, model.getposition().y - 32);

		prevangle = newangle = 90;

		direction = DIR::DOWN;
	}

	void setname(std::string name)
	{
		this->name = name;
		nametext.setString(name);
	}

	std::string getname()
	{
		return this->name;
	}

	void setpos(sf::Vector2f pos)
	{
		model.setposition(pos);
		nametext.setPosition(pos.x, pos.y - 32);
	}
	
	void move(float x, float y)
	{
		model.move(x, y);
		nametext.move(x, y);
	}

	void setpos(float x, float y)
	{
		model.setposition(x, y);
		nametext.setPosition(x, y - 32);
	}

	void setlookingangle(sf::Vector2f pos)
	{
		newangle = getangle(model.getposition(), pos);

		if (newangle != prevangle)
		{
			prevangle = newangle;

			if (newangle >= -45 && newangle <= 45)
				direction = DIR::RIGHT;
			if ((newangle <= -135 && newangle >= -180) || (newangle >= 135 && newangle <= 180))
				direction = DIR::LEFT;
			if (newangle <= -45 && newangle >= -135)
				direction = DIR::UP;
			if (newangle >= 45 && newangle <= 135)
				direction = DIR::DOWN;

			model.updatedirection(direction);
		}
	}

	sf::Vector2f getpos()
	{
		return model.getposition();
	}

};