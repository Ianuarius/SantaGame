#pragma once
#include <SFML/Graphics.hpp>
#include "GUIObject.h"
/*
- Position things on screen based on anchor points.
- Position things on a container based on anchor points.
*/

namespace iae
{
	class GUIElement :
		public GUIObject
	{
	public:
		GUIElement(sf::FloatRect parent, int anchor, 
			sf::FloatRect offset_rect, sf::Color color, std::string id);
		~GUIElement();
		void Update(sf::FloatRect rect);
		sf::Drawable* getRenderTarget();

		// TODO: Make this general for element and text in the parent class.
		void setAnchor();

		sf::RectangleShape gui_rectangle_;
		sf::FloatRect offset_rect_; // human readable
		sf::FloatRect bounds_rect_; // absolute
		sf::FloatRect parent_rect_;
		int anchor_;
		bool visible_ = true;
		sf::Color color_;
		std::string id_;
	};
}