#pragma once
#include <SFML/Graphics.hpp>

namespace iae
{
	// A drawable vertex filled with tiles based on level data
	class TileMap : public sf::Drawable, public sf::Transformable
	{
	public:

		bool Load(const std::string& tileset, sf::Vector2u tile_size, std::vector<std::vector<int>> level_container, unsigned int width, unsigned int height)
		{
			// load the tileset texture
			if (!tileset_.loadFromFile(tileset))
				return false;

			// resize the vertex array to fit the level size
			vertices_.setPrimitiveType(sf::Quads);
			vertices_.resize(width * height * 4);

			// populate the vertex array, with one quad per tile
			for (unsigned int i = 0; i < width; ++i)
				for (unsigned int j = 0; j < height; ++j)
				{
					// get the current tile number
					int tileNumber = level_container.at(j).at(i)-1;

					// find its position in the tileset texture
					int tu = tileNumber % (tileset_.getSize().x / tile_size.x);
					int tv = tileNumber / (tileset_.getSize().x / tile_size.x);

					// get a pointer to the current tile's quad
					sf::Vertex* quad = &vertices_[(i + j * width) * 4];

					// define its 4 corners
					quad[0].position = sf::Vector2f((float)i * tile_size.x, (float)j * tile_size.y);
					quad[1].position = sf::Vector2f((float)(i + 1) * tile_size.x, (float)j * tile_size.y);
					quad[2].position = sf::Vector2f((float)(i + 1) * tile_size.x, (float)(j + 1) * tile_size.y);
					quad[3].position = sf::Vector2f((float)i * tile_size.x, (float)(j + 1) * tile_size.y);

					// define its 4 texture coordinates
					quad[0].texCoords = sf::Vector2f((float)tu * tile_size.x, (float)tv * tile_size.y);
					quad[1].texCoords = sf::Vector2f((float)(tu + 1) * tile_size.x, (float)tv * tile_size.y);
					quad[2].texCoords = sf::Vector2f((float)(tu + 1) * tile_size.x, (float)(tv + 1) * tile_size.y);
					quad[3].texCoords = sf::Vector2f((float)tu * tile_size.x, (float)(tv + 1) * tile_size.y);
				}

			return true;
		}

	private:

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			// apply the transform
			states.transform *= getTransform();

			// apply the tileset texture
			states.texture = &tileset_;

			// draw the vertex array
			target.draw(vertices_, states);
		}

		sf::VertexArray vertices_;
		sf::Texture tileset_;
	};
}