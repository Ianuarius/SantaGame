#pragma once
#include <SFML/Graphics.hpp>

namespace iae
{
	class GUIObject
	{
	public:
	
		enum Anchor
		{
			top_left, top_center, top_right,
			middle_left, middle_center, middle_right,
			bottom_left, bottom_center, bottom_right
		};
	
		virtual sf::Drawable* getRenderTarget() = 0;
	
		bool visible_;
	};

}