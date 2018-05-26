#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Component.h"

namespace iae
{
	class Collider : public Component
	{
	public:
		Collider();
		~Collider();
		void Initialize(sf::Clock *timeframe);
		void Update();
		bool CheckCollision(int x_modifier, int y_modifier, sf::IntRect rect_target);

		sf::IntRect collision_box_;
	protected:
		sf::Clock *timeframe_;
	};

}