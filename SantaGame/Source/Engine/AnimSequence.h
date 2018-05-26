#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace iae
{
	class AnimSequence
	{
	public:
		AnimSequence();
		~AnimSequence();
		bool Initialize(std::string animation_name, std::string animation_path, int frame_amount, int start_frame);
		std::string animation_name_;
		std::string animation_filepath_;
		unsigned int frame_amount_;
		unsigned int frame_width_;
		unsigned int frame_height_;
		unsigned int starting_frame_;
		unsigned int frame_rate_;
		sf::Texture texture_;
	};
}