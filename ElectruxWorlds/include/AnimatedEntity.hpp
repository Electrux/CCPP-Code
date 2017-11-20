#pragma once

class AnimatedEntity : public sf::Drawable
{
	int totalx, totaly, blocksize;

	int currentframe, maxframes;

	int dir;

	sf::Texture texture;

	sf::Sprite spr;

	//The containers for blocks of individual frame for the 4 directions.
	std::map<int, std::vector<sf::IntRect>> frames;

	void generateblocks()
	{
		//starts with 0 for up, 1 for left, 2 for down, 3 for right.
		int dir = 0;

		std::vector<sf::IntRect> temp;

		sf::IntRect rect;
		for (int h = 0; h <= totaly - blocksize; h += blocksize - 1)
		{
			temp.clear();
			for (int w = 0; w <= totalx - blocksize; w += blocksize - 1)
			{
				rect.left = w;
				rect.top = h;
				rect.width = blocksize - 1;
				rect.height = blocksize - 1;

				w++;
				temp.push_back(rect);
			}

			frames[dir] = temp;

			h++;

			dir++;
		}
		std::cout << "Frames: " << frames.size() << " " << frames[0].size() << "\n";
		maxframes = frames[0].size();
	}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(spr);
	}

public:

	AnimatedEntity()
	{
		blocksize = 32;
		currentframe = 0;
		dir = DIR::DOWN;
	}

	bool loadtexture(std::string tex)
	{
		bool ret = texture.loadFromFile(tex);

		if (!ret) return false;

		totalx = texture.getSize().x;
		totaly = texture.getSize().y;

		this->generateblocks();

		spr.setTexture(texture);

		spr.setTextureRect(frames[dir][currentframe]);

		return true;
	}

	sf::Vector2f getposition()
	{
		return spr.getPosition();
	}

	void setposition(sf::Vector2f pos)
	{
		this->setposition(pos.x, pos.y);
	}

	void setposition(float x, float y)
	{
		spr.setPosition(x, y);
	}

	void setblocksize(int size)
	{
		blocksize = size;
	}

	void updatedirection(int dir)
	{
		currentframe = 0;
		
		this->dir = dir;
		
		spr.setTextureRect(frames[dir][currentframe]);
	}

	void nextframe()
	{
		spr.setTextureRect(frames[dir][currentframe]);
		
		currentframe++;
		
		if (currentframe == maxframes)
			currentframe = 0;
	}

	int getcurrentframe()
	{
		return currentframe;
	}

	void move(float x, float y)
	{
		spr.move(x, y);
	}

};
