#pragma once

class Actor : public sf::Drawable
{
	int framechangecounter;

	int prevdir;

	AnimatedEntity weapon, offhand, model, head, shoulders, arms, body, legs, shoes;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		if (prevdir == DIR::UP)
		{
			target.draw(weapon);
			target.draw(offhand);
			target.draw(model);
			target.draw(head);
			target.draw(shoulders);
			target.draw(arms);
			target.draw(body);
			target.draw(legs);
			target.draw(shoes);
		}
		else if (prevdir == DIR::DOWN)
		{
			target.draw(model);
			target.draw(head);
			target.draw(shoulders);
			target.draw(arms);
			target.draw(body);
			target.draw(legs);
			target.draw(shoes);
			target.draw(weapon);
			target.draw(offhand);
		}
		else if (prevdir == DIR::LEFT)
		{
			target.draw(weapon);
			target.draw(model);
			target.draw(head);
			target.draw(shoulders);
			target.draw(arms);
			target.draw(body);
			target.draw(legs);
			target.draw(shoes);
			target.draw(offhand);
		}
		else if (prevdir == DIR::RIGHT)
		{
			target.draw(offhand);
			target.draw(model);
			target.draw(head);
			target.draw(shoulders);
			target.draw(arms);
			target.draw(body);
			target.draw(legs);
			target.draw(shoes);
			target.draw(weapon);
		}
	}

public:

	Actor()
	{
		framechangecounter = 0;
		prevdir = DIR::DOWN;
	}

	bool loadtexture(GearSet gearset)
	{
		bool ret = (weapon.loadtexture(gearset.weapon) &&
					offhand.loadtexture(gearset.offhand) &&
					model.loadtexture(gearset.model) &&
					head.loadtexture(gearset.head) &&
					shoulders.loadtexture(gearset.shoulders) &&
					arms.loadtexture(gearset.arms) &&
					body.loadtexture(gearset.body) &&
					legs.loadtexture(gearset.legs) &&
					shoes.loadtexture(gearset.shoes));

		return ret;
	}

	void setposition(sf::Vector2f pos)
	{
		this->setposition(pos.x, pos.y);
	}

	void setposition(float x, float y)
	{
		weapon.setposition(x, y);
		offhand.setposition(x, y);
		model.setposition(x, y);
		head.setposition(x, y);
		shoulders.setposition(x, y);
		arms.setposition(x, y);
		body.setposition(x, y);
		legs.setposition(x, y);
		shoes.setposition(x, y);
	}

	sf::Vector2f getposition()
	{
		return head.getposition();
	}

	void setblocksize(int size)
	{
		weapon.setblocksize(size);
		offhand.setblocksize(size);
		model.setblocksize(size);
		head.setblocksize(size);
		shoulders.setblocksize(size);
		arms.setblocksize(size);
		body.setblocksize(size);
		legs.setblocksize(size);
		shoes.setblocksize(size);
	}

	void updatedirection(int dir)
	{
		if (dir != prevdir)
		{
			weapon.updatedirection(dir);
			offhand.updatedirection(dir);
			model.updatedirection(dir);
			head.updatedirection(dir);
			shoulders.updatedirection(dir);
			arms.updatedirection(dir);
			body.updatedirection(dir);
			legs.updatedirection(dir);
			shoes.updatedirection(dir);

			prevdir = dir;
		}
	}

	void move(float x, float y)
	{
		weapon.move(x, y);
		offhand.move(x, y);
		model.move(x, y);
		head.move(x, y);
		shoulders.move(x, y);
		arms.move(x, y);
		body.move(x, y);
		legs.move(x, y);
		shoes.move(x, y);
		
		if (framechangecounter >= MAXFRAMEUPDATECTR)
		{
			weapon.nextframe();
			offhand.nextframe();

			model.nextframe();
			head.nextframe();
			shoulders.nextframe();
			arms.nextframe();
			body.nextframe();
			legs.nextframe();
			shoes.nextframe();

			framechangecounter = 0;
		}
		else
			framechangecounter++;
	}

};