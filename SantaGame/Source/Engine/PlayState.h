#pragma once
#include "Actor.h"
#include "CollisionBrick.h"
#include "GameState.h"
#include "GUIElement.h"
#include "Level.h"
#include "Player.h"
#include "TileMap.h"

namespace iae
{
	class PlayState :
		public GameState
	{
	public:
		void Init();
		void HandleEvents(GameEngine* game);
		void Cleanup();

		void Pause();
		void Resume();

		// void setHistory();

		// void toggleVisibility(std::string id);

		void Update(GameEngine* game);
		void Draw(GameEngine* game);

		PlayState() { }

	private:
		std::vector<GUIElement> gui_elements_;

		Level game_level_;
		Level action_level_;

		std::vector<std::vector<int>> game_layer_container_;
		std::vector<std::vector<int>> action_layer_container_;
		std::vector<Actor> actors_;

		int map_width_;
		int map_height_;
		int map_resolution_;
		float view_width_;
		float view_height_; 
		bool draw_collision_;

		Player player_;
		sf::Clock timeframe_;
		TileMap game_layer_;
		TileMap action_layer_;
		sf::Font font_;
		sf::Texture brick_texture_;
		sf::Sprite sprite_;
		sf::Texture background_texture_;
		sf::Sprite background_;

		sf::View game_view_;
		sf::View gui_view_;
	};

}