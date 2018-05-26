#include "AnimSequence.h"

using namespace iae;

AnimSequence::AnimSequence()
{
}


AnimSequence::~AnimSequence()
{
}

bool AnimSequence::Initialize(std::string animation_name, std::string animation_path, int frame_amount, int start_frame)
{
	animation_name_ = animation_name;
	animation_filepath_ = animation_path;
	frame_amount_ = frame_amount;
	starting_frame_ = start_frame;
	frame_width_ = 0;
	frame_height_ = 0;
	frame_rate_ = 8;

	texture_.loadFromFile(animation_path, sf::IntRect(0, 0, frame_width_, frame_height_));

	return true;
}
