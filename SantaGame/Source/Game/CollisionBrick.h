#pragma once
#include "Actor.h"
class CollisionBrick :
	public iae::Actor
{
public:
	CollisionBrick();
	~CollisionBrick();
	void InitBrick(sf::Vector2f new_position);
	void SetImage(std::string filepath);
};

