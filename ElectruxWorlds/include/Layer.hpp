#pragma once

class Layer : public sf::Drawable
{
	int mapwidth, mapheight, tilewidth, tileheight;

	Tileset *tileset;

	std::vector<std::shared_ptr<sf::Sprite>> sprites;

	std::vector<int> tilemap;

	void parseline(std::fstream &file, std::string line)
	{
		std::string temp;

		while (std::getline(file, line))
		{
			for (auto character : line)
			{
				if (character == ',')
				{
					tilemap.push_back(std::stoi(temp));
					temp.clear();
				}
				else
				{
					temp += character;
				}
			}
		}
		tilemap.push_back(std::stoi(temp));
	}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		for (auto sprite : sprites)
		{
			target.draw(*sprite);
		}
	}

public:

	bool loadlayer(std::string layerfile, Tileset *tileset, int mapwidth, int mapheight, int tilewidth, int tileheight)
	{
		std::fstream file("Assets/Maps/Level1/" + layerfile, std::ios::in);

		if (!file.is_open()) return false;

		this->tileset = tileset;

		this->mapwidth = mapwidth;
		this->mapheight = mapheight;
		this->tilewidth = tilewidth;
		this->tileheight = tileheight;

		std::string line;

		this->parseline(file, line);

		for (int i = 0; i < tilemap.size(); ++i)
		{
			sprites.push_back(std::make_shared<sf::Sprite>());

			sprites[i]->setTexture(tileset->gettileset());
		}
		
		int ctr = 0;

		for (int h = 0; h <= mapheight * tileheight - tileheight; h += tileheight - 1)
		{
			for (int w = 0; w <= mapheight * tileheight - tilewidth; w += tileheight - 1)
			{
				sprites[ctr]->setTextureRect(tileset->gettile(tilemap[ctr]));
				sprites[ctr]->setPosition(w, h);

				ctr++;
				w++;
			}

			h++;
		}

		std::cout << tilemap.size() << "\n";
		return true;
	}

};