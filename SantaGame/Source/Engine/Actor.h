#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include "Collider.h"
#include "Component.h"
#include "Object.h"

namespace iae
{
	class Actor :
		public Object/*, 
		public EventHandler*/
	{
	public:
		Actor();
		~Actor();
		void SetImage(std::string filename);

		// TODO: Set Collider as component
		Collider collider_;
		sf::Sprite *sprite_;

	protected:
		void Initialize(sf::Clock *timeframe);
		void InitImage(std::string filename, int width, int height);
		void SetColliderBox();
		void SetPosition(sf::Vector2f new_position);
		void CenterOrigin();

		std::vector<std::shared_ptr<Component>> components_;
		sf::Vector2f position_;
		sf::Texture texture_;
		sf::Clock *timeframe_;
		int width_;
		int height_;
		int collision_offset_x_;
		int collision_offset_y_;
	};

}