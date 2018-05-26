#pragma once
#include <vector>
#include "Level.h"

namespace iae
{
	/**
	 * World includes the list of levels, the game mode, the game state,
	 * list of controllers, the physics object.
	 */
	class World
	{
	public:
		World();
		~World();
	protected:
		std::vector<Level *> levels_;
	};

}