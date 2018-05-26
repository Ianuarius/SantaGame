#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Actor.h"
#include "Action.h"
#include "Animation.h"
#include "PlayerState.h"
#include "EventHandler.h"

// TODO Is Player a part of the engine?
namespace iae
{
	class Player : 
		public Actor
	{
	public:
		Player();
		~Player();
		bool Initialize(sf::Clock *timeframe);
		void ParseInput(int action);
		void Update(std::vector<Actor> *collision_targets);

		std::vector<Action> actions_;

	protected:
		void MoveLeft();
		void MoveRight();
		void Jump();
		void Climb();

		void OnEventMoveLeft(const Player* player);

		// TODO: Only switch States in player? Leave input parsing
		// to PlayState. Or, do the input parsing separately for all
		// the States in player.

		PlayerState state_;
		EventHandler handler_;
		double jump_power_;
		double x_velocity_;
		double y_velocity_;
		double acceleration_;
		double max_velocity_;
		double slowdown_;
		double jump_force_;
		double gravity_;
		double elevation_;
	};
}
