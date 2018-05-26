#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class GameState;

namespace iae
{
	class GameEngine
	{
	public:
		void Init(std::string title, int width, int height, bool fullscreen);
		void Cleanup();

		void ChangeState(GameState* state);
		void PushState(GameState* state);
		void PopState();

		void HandleEvents();
		void Update();
		void Draw();

		bool Running() { return running_; }
		void Quit() { running_ = false; }

		sf::RenderWindow window_;

	private:
		// the stack of states
		std::vector<GameState *> states_;
		bool running_;
	};

}