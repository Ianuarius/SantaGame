#include "Level.h"

using namespace iae;

Level::Level()
{
}

Level::~Level()
{
}

std::vector<std::vector<int>> Level::load(unsigned int width, unsigned int height, unsigned int layer_number)
{
	rapidxml::file<> xmlFile("Levels/test_level.tmx");
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	
	// map
	rapidxml::xml_node<> *Map_Node = doc.first_node();
	rapidxml::xml_attribute<> *Current_Attr = Map_Node->first_attribute("width");
	map_width_ = atoi(Current_Attr->value());
	Current_Attr = Current_Attr->next_attribute("height");
	map_height_ = atoi(Current_Attr->value());
	map_tile_count_ = map_width_ * map_height_;

	// tileset
	rapidxml::xml_node<> *Tileset_Node = Map_Node->first_node();
	Current_Attr = Tileset_Node->first_attribute("tilewidth");
	tile_width_ = atoi(Current_Attr->value());
	Current_Attr = Current_Attr->next_attribute("tileheight");
	tile_height_ = atoi(Current_Attr->value());

	// image
	rapidxml::xml_node<> *Image_Node = Tileset_Node->first_node();
	Current_Attr = Image_Node->first_attribute("source");
	tileset_source_ = Current_Attr->value();
	Current_Attr = Current_Attr->next_attribute("width");
	tileset_width_ = atoi(Current_Attr->value());
	Current_Attr = Current_Attr->next_attribute("height");
	tileset_height_ = atoi(Current_Attr->value());

	// layer
	rapidxml::xml_node<> *Layer_Node = Tileset_Node->next_sibling();
	int i = 0;

	while (i < layer_number)
	{
		Layer_Node = Layer_Node->next_sibling();
		i++;
	}

	// tiles
	rapidxml::xml_node<> *Tile_Node = Layer_Node->first_node()->first_node();

	// Load tile id numbers from xml to a double vector
	std::vector<int> tmp_row;
	int tmp_tile_count = 0;
	for (unsigned int y = 0; y < map_height_; y++)
	{
		for (unsigned int x = 0; x < map_width_; x++)
		{
			Current_Attr = Tile_Node->first_attribute("gid");
			tmp_row.push_back(atoi(Current_Attr->value()));

			if (tmp_tile_count < map_tile_count_)
			{
				Tile_Node = Tile_Node->next_sibling();
			}

			tmp_tile_count++;
		}
		level_container_.push_back(tmp_row);
		tmp_row.clear();
	}

	return level_container_;
}
