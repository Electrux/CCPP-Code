#pragma once

class Tileset
{
	sf::Texture tileset;
	
	std::vector<sf::IntRect> tiles;

	int maxwidth, maxheight, tilewidth, tileheight;

	sf::Sprite tilesprite;

	void generateblocks()
	{
		sf::IntRect rect;
		for (int h = 0; h <= maxheight - tileheight; h += tileheight - 1)
		{
			for (int w = 0; w <= maxwidth - tilewidth; w += tilewidth - 1)
			{
				rect.left = w;
				rect.top = h;
				rect.width = tilewidth - 1;
				rect.height = tileheight - 1;

				w++;

				tiles.push_back(rect);
			}

			h++;
		}
		std::cout << "Tiles: " << tiles.size() << "\n";
	}

public:

	bool loadtileset(std::string file, int tilewidth, int tileheight)
	{
		if (!tileset.loadFromFile("Assets/Tilesets/" + file)) return false;

		maxwidth = tileset.getSize().x;
		maxheight = tileset.getSize().y;
		
		this->tilewidth = tilewidth;
		this->tileheight = tileheight;

		this->generateblocks();

		tilesprite.setTexture(tileset);

		return true;
	}

	sf::Texture & gettileset()
	{
		return tileset;
	}

	sf::IntRect gettile(int id)
	{
		id--;
		return (id < 0 || id >= tiles.size()) ? tiles[0] : tiles[id];
	}

	sf::Sprite & gettilewithpos(int id, float x, float y)
	{
		tilesprite.setPosition(x, y);

		id--;

		if (id < 0 || id >= tiles.size())
			tilesprite.setTextureRect(tiles[0]);
		else
			tilesprite.setTextureRect(tiles[id]);
		
		return tilesprite;
	}

};