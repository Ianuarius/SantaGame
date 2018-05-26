#include "GameEngine.h"
#include "GameState.h"

using namespace iae;

void GameEngine::Init(std::string title, int width, int height, bool fullscreen)
{
	// TODO: OpenGL Window
	window_.create(sf::VideoMode(width, height), title);
	window_.setKeyRepeatEnabled(false);
	window_.setFramerateLimit(60);
	running_ = true;
}

void GameEngine::Cleanup()
{
	// cleanup the all states
	while (!states_.empty()) {
		states_.back()->Cleanup();
		states_.pop_back();
	}

	// TODO: switch back to windowed mode so other 
	// programs won't get accidentally resized
}

void GameEngine::ChangeState(GameState* state)
{
	if (!states_.empty()) {
		states_.back()->Cleanup();
		states_.pop_back();
	}

	// store and init the new state
	states_.push_back(state);
	states_.back()->Init();
}

void GameEngine::PushState(GameState* state)
{
	// pause current state
	if (!states_.empty()) {
		states_.back()->Pause();
	}

	// store and init the new state
	states_.push_back(state);
	states_.back()->Init();
}

void GameEngine::PopState()
{
	// cleanup the current state
	if (!states_.empty()) {
		states_.back()->Cleanup();
		states_.pop_back();
	}

	// resume previous state
	if (!states_.empty()) {
		states_.back()->Resume();
	}
}

void GameEngine::HandleEvents()
{
	// let the state handle events
	states_.back()->HandleEvents(this);
}

void GameEngine::Update()
{
	// let the state update the game
	states_.back()->Update(this);
}

void GameEngine::Draw()
{
	// let the state draw the screen
	states_.back()->Draw(this);
}