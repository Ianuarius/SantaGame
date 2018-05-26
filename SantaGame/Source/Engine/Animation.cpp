#include "Animation.h"

using namespace iae;

Animation::Animation()
{
}


Animation::~Animation()
{
}

void Animation::Initialize(sf::Clock *timeframe)
{
	timeframe_ = timeframe;
	number_of_animations = 0;
	anim_start_time_ = timeframe_->getElapsedTime().asMilliseconds();
	rect_source_sprite.width = 32;
	rect_source_sprite.height = 32;
	rect_source_sprite.left = 0;
	rect_source_sprite.top = 0;
	playing_frame_ = 1;
}

void Animation::Update()
{
	// TODO: Logic to animation or something
	int framerate = 8;
	int frame_length = 1000 / framerate;
	int time_difference = timeframe_->getElapsedTime().asMilliseconds() - anim_start_time_;
	int current_frame = time_difference / frame_length;

	if (current_frame > last_frame_)
	{
		if (active_animation_->frame_amount_ == playing_frame_)
		{
			rect_source_sprite.left = 0;
			playing_frame_ = 1;
		}
		else
		{
			rect_source_sprite.left += 32;
			playing_frame_++;
		}
		last_frame_ = current_frame;
	}

	sprite_.setTextureRect(rect_source_sprite);
}

void Animation::SetAnimation(std::string animation_name)
{
	for (int i = 0; i < animations_.size(); i++)
	{
		if (animations_.at(i)->animation_name_ == animation_name)
		{
			active_animation_ = animations_.at(i);
		}
	}
	texture_ = &active_animation_->texture_;
	sprite_.setTexture(*texture_);
	playing_frame_ = 1;
}

bool Animation::AddSequence(std::string animation_name, std::string animation_path, int frame_amount, int start_frame)
{
	animations_.push_back(std::make_shared<AnimSequence>());
	number_of_animations++;
	animations_.at(number_of_animations-1).get()->Initialize(animation_name, animation_path, frame_amount, start_frame);
	return false;
}