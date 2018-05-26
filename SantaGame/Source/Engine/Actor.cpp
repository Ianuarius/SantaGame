#include "Actor.h"

using namespace iae;

Actor::Actor()
{
}


Actor::~Actor()
{
}

void Actor::SetImage(std::string filename)
{
	InitImage(filename, 32, 32);
	SetColliderBox();
}

void Actor::Initialize(sf::Clock *timeframe)
{
	timeframe_ = timeframe;
}

void Actor::InitImage(std::string filename, int width, int height)
{
	width_ = width;
	height_ = height;
	collision_offset_x_ = 0;
	collision_offset_y_ = 0;
	texture_.loadFromFile(filename, sf::IntRect(0, 0, width, height));
	//sprite_.setTexture(texture_);
	//sprite_.setPosition(position_);
}

void Actor::SetColliderBox()
{
	collider_.collision_box_.left =   (int)(position_.x - collision_offset_x_);
	collider_.collision_box_.top =    (int)(position_.y - collision_offset_y_);
	collider_.collision_box_.width =  (int)(position_.x + 32 - collision_offset_x_);
	collider_.collision_box_.height = (int)(position_.y + 32 - collision_offset_y_);
}

void Actor::SetPosition(sf::Vector2f new_position)
{
	position_ = new_position;
}

void Actor::CenterOrigin()
{
	collision_offset_x_ = (int)sprite_->getLocalBounds().width / 2;
	collision_offset_y_ = (int)sprite_->getLocalBounds().height / 2;
	
	sprite_->setOrigin(sf::Vector2f((float)collision_offset_x_, (float)collision_offset_y_));
}
