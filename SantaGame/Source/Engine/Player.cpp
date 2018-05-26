#include "Player.h"

using namespace iae;

Player::Player()
{
}

Player::~Player()
{
}

bool Player::Initialize(sf::Clock *timeframe)
{
	timeframe_ = timeframe;
	x_velocity_ = 0;
	y_velocity_ = 0;
	jump_power_ = 7;
	acceleration_ = 1;
	slowdown_ = acceleration_ - 0.8;
	max_velocity_ = 4;
	gravity_ = 0.27;
	state_.Initialize();

	components_.push_back(std::make_shared<Animation>());
	std::dynamic_pointer_cast<Animation>(components_.at(0))->Initialize(timeframe);
	std::dynamic_pointer_cast<Animation>(components_.at(0))->AddSequence("idle", "Graphics/Player/santa_0000.png", 1, 0);
	std::dynamic_pointer_cast<Animation>(components_.at(0))->AddSequence("run", "Graphics/Player/santa_0000.png", 4, 0);
	std::dynamic_pointer_cast<Animation>(components_.at(0))->AddSequence("climb", "Graphics/Player/santa_0000.png", 2, 4);
	std::dynamic_pointer_cast<Animation>(components_.at(0))->SetAnimation("idle");
	sprite_ = &std::dynamic_pointer_cast<Animation>(components_.at(0))->sprite_;
	std::dynamic_pointer_cast<Animation>(components_.at(0))->Update();

	CenterOrigin();
	SetColliderBox();

	position_.x = 330;
	position_.y = 200;
	//InitImage("Graphics/Player/santa_0000.png", 128, 32);
	//sprite_->setTextureRect(rect_source_sprite);

	Action move_left;
	move_left.action_ = Action::ActionList::move_left;
	move_left.keyboard_ = (int)sf::Keyboard::Left;
	actions_.push_back(move_left);

	Action move_right;
	move_right.action_ = Action::ActionList::move_right;
	move_right.keyboard_ = (int)sf::Keyboard::Right;
	actions_.push_back(move_right);

	Action jump;
	jump.action_ = Action::ActionList::jump;
	jump.keyboard_ = (int)sf::Keyboard::Space;
	actions_.push_back(jump);

	Action climb_up;
	climb_up.action_ = Action::ActionList::climb_up;
	climb_up.keyboard_ = (int)sf::Keyboard::Up;
	actions_.push_back(climb_up);

	Action climb_down;
	climb_down.action_ = Action::ActionList::climb_down;
	climb_down.keyboard_ = (int)sf::Keyboard::Down;
	actions_.push_back(climb_down);

	// RegisterEventFunc(this, &Player::OnEventMoveLeft);

	return true;
}

// TODO: running_ doesn't always set correctly -> frames go over the amount

void Player::MoveLeft()
{
	if (x_velocity_ > -max_velocity_)
	{
		x_velocity_ -= acceleration_;
	}
	else
	{
		x_velocity_ = -max_velocity_;
	}
	state_.facing_right_ = false;

	if (!state_.running_)
	{
		// Set animation to run
		std::dynamic_pointer_cast<Animation>(components_.at(0))->SetAnimation("run");
		sprite_ = &std::dynamic_pointer_cast<Animation>(components_.at(0))->sprite_;
		state_.running_ = true;
	}

	// OnEventMoveLeft
	// Jump();
}

void Player::MoveRight()
{
	if (x_velocity_ < max_velocity_)
	{
		x_velocity_ += acceleration_;
	}
	else
	{
		x_velocity_ = max_velocity_;
	}
	state_.facing_right_ = true;

	if (!state_.running_)
	{
		// Set animation to run
		std::dynamic_pointer_cast<Animation>(components_.at(0))->SetAnimation("run");
		sprite_ = &std::dynamic_pointer_cast<Animation>(components_.at(0))->sprite_;
		state_.running_ = true;
	}
}

// TODO: Jump height varies

void Player::Jump()
{
	if (!state_.jumping_)
	{
		y_velocity_ -= jump_power_;
		state_.jumping_ = true;
	}
}

void Player::Climb()
{
	std::dynamic_pointer_cast<Animation>(components_.at(0))->SetAnimation("climb");
	sprite_ = &std::dynamic_pointer_cast<Animation>(components_.at(0))->sprite_;
}
/*
void Player::OnEventMoveLeft(const Actor * actor)
{
}
*/
void Player::ParseInput(int action)
{
	switch (action)
	{
	case (int)Action::ActionList::move_left:
		MoveLeft();
		break;
	case (int)Action::ActionList::move_right:
		MoveRight();
		break;
	case (int)Action::ActionList::jump:
		Jump();
		break;
	case (int)Action::ActionList::climb_up:
		Climb();
		break;
	case (int)Action::ActionList::climb_down:
		Climb();
		break;
	default:
		break;
	}
}

void Player::Update(std::vector<Actor> *collision_targets)
{
	int animation_velocity_cutoff = 2;
	if (x_velocity_ < animation_velocity_cutoff && x_velocity_ > -animation_velocity_cutoff)
	{
		// Set animation to idle
		std::dynamic_pointer_cast<Animation>(components_.at(0))->SetAnimation("idle");
		sprite_ = &std::dynamic_pointer_cast<Animation>(components_.at(0))->sprite_;
		state_.running_ = false;
		/*
		sprite_->setOrigin({ sprite_->getLocalBounds().width, 0 });
		*/
	}

	if (state_.facing_right_)
	{
		sprite_->setScale({ 1, 1 });
	}
	else
	{
		sprite_->setScale({ -1, 1 });
	}
	// sprite_->setTextureRect(rect_source_sprite);
	std::dynamic_pointer_cast<Animation>(components_.at(0))->Update();

	// HORIZONTAL MOVEMENT
	if (x_velocity_ > slowdown_)
	{
		x_velocity_ -= slowdown_;
	}

	if (x_velocity_ < -slowdown_)
	{
		x_velocity_ += slowdown_;
	}

	if (x_velocity_ < slowdown_ && x_velocity_ > -slowdown_)
	{
		x_velocity_ = 0;
	}

	// VERTICAL MOVEMENT

	y_velocity_ += gravity_;

	int x_velocity_int = (int)x_velocity_;
	int y_velocity_int = (int)y_velocity_;


	for (unsigned int i = 0; i < collision_targets->size(); i++)
	{
		Collider *tmp_collider = &collision_targets->at(i).collider_;

		// Y_COLLISION
		if (collider_.CheckCollision(0, y_velocity_int, tmp_collider->collision_box_))
		{
			while (!collider_.CheckCollision(0, (y_velocity_int > 0) - (y_velocity_int < 0), tmp_collider->collision_box_))
			{
				position_.y += (y_velocity_int > 0) - (y_velocity_int < 0);
				SetColliderBox();
			}

			if ((y_velocity_int > 0) - (y_velocity_int < 0) == 1)
			{
				state_.jumping_ = false;
			}

			y_velocity_ = 0;
			y_velocity_int = 0;
		}

		// X_COLLISION
		if (collider_.CheckCollision(x_velocity_int, 0, tmp_collider->collision_box_))
		{
			while (!collider_.CheckCollision((x_velocity_int > 0) - (x_velocity_int < 0), 0, tmp_collider->collision_box_))
			{
				position_.x += (x_velocity_int > 0) - (x_velocity_int < 0);
				SetColliderBox();
			}

			x_velocity_ = 0;
			x_velocity_int = 0;
		}

		// DOUBLE CHECK FOR 45-DEG ANGLES
		// If checking in 45-deg angle, neither x or y individually will detect a collision.
		if (collider_.CheckCollision(x_velocity_int, y_velocity_int, tmp_collider->collision_box_))
		{
			y_velocity_ = 0;
			y_velocity_int = 0;
		}
		sprite_->setPosition(position_);
	}
	
	position_.x += x_velocity_int;
	position_.y += y_velocity_int;
	// BUG: The player sprite is one px above ground for some reason.
	sprite_->setPosition(sf::Vector2f(position_.x, position_.y + 1));
	SetColliderBox();
}