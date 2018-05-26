#pragma once
#include <string>
#include <memory>
#include <vector>
#include "AnimSequence.h"
#include "Component.h"

namespace iae
{
	/**
	 * Controls which animation is played.
	 */
	class Animation : public Component
	{
	public:
		Animation();
		~Animation();
		void SetAnimation(std::string animation_name);
		void Initialize(sf::Clock *timeframe);
		void Update();
		bool AddSequence(std::string animation_name, std::string animation_path, int frame_amount, int start_frame);
		std::shared_ptr<AnimSequence> active_animation_;
		sf::Sprite sprite_;
	protected:
		sf::Texture *texture_;
		sf::Clock *timeframe_;
		std::vector<std::shared_ptr<AnimSequence>> animations_;
		unsigned int number_of_animations;

		sf::IntRect rect_source_sprite;
		int last_frame_;
		int anim_start_time_;
		int playing_frame_;
	};
}