#include "PlayState.h"

using namespace iae;

void PlayState::Init()
{
	view_width_ = 1024;
	view_height_ = 576;
	map_width_ = 32;
	map_height_ = 16;
	map_resolution_ = 32;
	draw_collision_ = false;
	player_.Initialize(&timeframe_);

	//Font stuff
	/* 
	if (!font.loadFromFile("PressStart2P.ttf"))
	{
		std::cout << "Nope";
		// error...
	}

	// Set anti aliasing off for the font.
	const_cast<sf::Texture&>(font_.getTexture(8)).setSmooth(false);

	*/
	// Level itself is cheaper as a tilemap
	game_layer_container_ = game_level_.load(map_width_, map_height_, 0);

	background_texture_.loadFromFile("Graphics/Background/snow_background.png", sf::IntRect(0, 0, 378, 512));
	background_.setTexture(background_texture_);

	// Action layer needs to be loaded to a vector as actors
	action_layer_container_ = action_level_.load(map_width_, map_height_, 1);
	
	game_layer_.Load("Graphics/Tilesets/tileset_0000.png", sf::Vector2u(32, 32), game_layer_container_, 32, 16);
	action_layer_.Load("Graphics/Tilesets/tileset_0000.png", sf::Vector2u(32, 32), action_layer_container_, 32, 16);
	game_view_.reset(sf::FloatRect(0, -64, view_width_, view_height_));

	CollisionBrick brick;
	for (unsigned int i = 0; i < game_layer_container_.size(); i++)
	{
		for (unsigned int j = 0; j < game_layer_container_.at(i).size(); j++)
		{
			if (game_layer_container_.at(i).at(j) != 0)
			{
				brick.InitBrick(sf::Vector2f((float)j * 32, (float)i * 32));
				actors_.push_back(brick);
			}
		}
	}

	for (unsigned int i = 0; i < actors_.size(); i++)
	{
		actors_.at(i).SetImage("Graphics/Util/brick.png");
	}

	// GUI Stuff
	/*
	sf::FloatRect gui_view_bounds(0, 0, view_width, view_height);
	gui_view.reset(gui_view_bounds);
	
	GUIElement stat_box(gui_view_bounds,
		GUIElement::Anchor::top_right,
		sf::FloatRect(-150, 0, 150, view_height),
		sf::Color(120, 30, 20),
		"Stats Box");
	gui_elements.push_back(stat_box);
	*/
}

void PlayState::Cleanup()
{
}

void PlayState::Pause()
{
}

void PlayState::Resume()
{
}

void PlayState::HandleEvents(GameEngine* game)
{
	sf::Event event;
	std::string str;
	while (game->window_.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			game->window_.close();
		if (event.type == sf::Event::TextEntered)
			str = (char)event.text.unicode;
	}

	// SHUTDOWN
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			game->window_.close();
			game->Quit();
		}
	}

	for (unsigned int i = 0; i < player_.actions_.size(); i++)
	{
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)player_.actions_.at(i).keyboard_))
		{
			player_.ParseInput(player_.actions_.at(i).action_);
		}
	}
	/*
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::C)
		{
			toggleVisibility("Stats Box");
			toggleVisibility("Stats Text");
		}
	}
	*/
	
}

void PlayState::Update(GameEngine* game)
{
	player_.Update(&actors_);

	// GUI stuff
	/*
	for (unsigned int i = 0; i < gui_elements.size(); i++)
	{
		gui_elements.at(i).update(gui_elements.at(i)._offset_rect);
	}
	*/

	if (!game->window_.isOpen())
	{
		game->Quit();
	}
}

void PlayState::Draw(GameEngine* game)
{
	game->window_.setView(game_view_);
	game->window_.clear();
	
	// DRAW BACKGROUND
	for (int i = 0; i < view_width_; i += 378)
	{
		background_.setPosition(sf::Vector2f(i, 0));
		game->window_.draw(background_);
	}

	// GUI stuff
	/*
	// DRAW GUI
	game->window.setView(gui_view);
	
	for (unsigned int i = 0; i < gui_elements.size(); i++)
	{
		if (gui_elements.at(i).visible)
		{
			//game->window.draw(gui_elements.at(i)._gui_rectangle);
			game->window.draw(*gui_elements.at(i).getRenderTarget());
		}
	}
	/*
	for (unsigned int i = 0; i < text_elements.size(); i++)
	{
		if (text_elements.at(i).visible)
		{
			//game->window.draw(text_elements.at(i)._text);
			game->window.draw(*text_elements.at(i).getRenderTarget());
		}
	}

	for (unsigned int i = 0; i < textboxes.size(); i++)
	{
		if (textboxes.at(i).visible)
		{
			//game->window.draw(text_elements.at(i)._text);
			game->window.draw(*textboxes.at(i).getRenderBox());
			game->window.draw(*textboxes.at(i).getRenderTarget());
		}
	}
	
	*/

	// DRAW LAYERS
	game->window_.draw(game_layer_);
	game->window_.draw(action_layer_);

	// DRAW ACTORS
	if (draw_collision_)
	{
		for (unsigned int i = 0; i < actors_.size(); i++)
		{
			game->window_.draw(*actors_.at(i).sprite_);
		}
	}

	// DRAW PLAYER
	game->window_.draw(*player_.sprite_);

	game->window_.display();
}
