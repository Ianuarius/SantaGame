#include "PlayerState.h"

using namespace iae;

PlayerState::PlayerState()
{
}


PlayerState::~PlayerState()
{
}

bool PlayerState::Initialize()
{
	idle_ = false;
	running_ = false;
	jumping_ = false;
	climbing_ = false;
	dead_ = false;
	facing_right_ = true;
	return true;
}
