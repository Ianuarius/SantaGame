#include "Collider.h"

using namespace iae;

Collider::Collider()
{
}


Collider::~Collider()
{
}

void Collider::Initialize(sf::Clock *timeframe)
{
	timeframe_ = timeframe;
}

void Collider::Update()
{
}

bool Collider::CheckCollision(int x_modifier, int y_modifier, sf::IntRect rect_target)
{
	if ((collision_box_.height + y_modifier < rect_target.top) ||
	    (collision_box_.top + y_modifier    > rect_target.height) ||
	    (collision_box_.left + x_modifier   > rect_target.width) ||
	    (collision_box_.width + x_modifier  < rect_target.left))
	{
		// std::cout << "false\n";
		return false;
	}
	else
	{
		// std::cout << "true\n";
		return true;
	}
}
