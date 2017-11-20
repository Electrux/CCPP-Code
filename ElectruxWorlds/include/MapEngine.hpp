#pragma once

class MapEngine : public sf::Drawable
{
	std::string tileset;
	Tileset tiles;

	int mapwidth, mapheight, tilewidth, tileheight;
	int layercount;

	std::vector<std::string> layerstr;

	std::vector<std::shared_ptr<Layer>> layers;

	void loadlayers()
	{
		for (int i = 0; i < layercount; ++i)
		{
			layers.push_back(std::make_shared<Layer>());

			layers[i]->loadlayer(layerstr[i], &tiles, mapwidth, mapheight, tilewidth, tileheight);
		}
	}
	
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		for (auto layer : layers)
		{
			target.draw(*layer);
		}
	}

public:

	bool loadmap(std::string file)
	{
		Electrux::INI_Parser corefile;

		if (!corefile.ParseFile(file)) return false;

		//Tileset file.
		corefile.GetDataString("Base", "tileset", tileset);

		//Tile width.
		corefile.GetDataInt("Base", "tilewidth", tilewidth);
		
		//Tile height.
		corefile.GetDataInt("Base", "tileheight", tileheight);

		//Total tiles width.
		corefile.GetDataInt("Base", "mapwidth", mapwidth);

		//Total tiles height.
		corefile.GetDataInt("Base", "mapheight", mapheight);

		//Number of layers.
		corefile.GetDataInt("Base", "layercount", layercount);

		//Load the tileset.
		if (!tiles.loadtileset(tileset, tilewidth, tileheight)) return false;

		//Get filenames for all layers.
		for (int i = 1; i <= layercount; ++i)
		{
			std::string str;
			corefile.GetDataString("LayerInfo", "layer" + std::to_string(i), str);
			layerstr.push_back(str);
		}

		this->loadlayers();

		return true;
	}

};