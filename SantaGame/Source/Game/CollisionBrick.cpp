#include "CollisionBrick.h"

CollisionBrick::CollisionBrick()
{
}

CollisionBrick::~CollisionBrick()
{
}

void CollisionBrick::InitBrick(sf::Vector2f new_position)
{
	position_ = new_position;
}

void CollisionBrick::SetImage(std::string filepath)
{
	InitImage(filepath, 32, 32);
	SetColliderBox();
}