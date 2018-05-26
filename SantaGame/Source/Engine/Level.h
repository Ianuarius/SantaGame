#pragma once
#include <vector>
#include <string>
#include "rapidxml\rapidxml.hpp"
#include "rapidxml\rapidxml_utils.hpp"

namespace iae
{
	class Level
	{
	public:
		Level();
		~Level();

		std::vector<std::vector<int>> load(unsigned int width, unsigned int height, unsigned int layer_number);

		std::vector<std::vector<int>> level_container_;
		int map_width_ = 0;
		int map_height_ = 0;
		int map_tile_count_ = 0;
		int tile_width_ = 0;
		int tile_height_ = 0;
		std::string tileset_source_;
		int tileset_width_ = 0;
		int tileset_height_ = 0;
	};

}