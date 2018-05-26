#pragma once
#include <SFML/System.hpp>

/*
 * Top level class for actor components.
 */

namespace iae
{
	class Component
	{
	public:
		virtual void Initialize(sf::Clock *timeframe) = 0;
		virtual void Update() = 0;
	};
}