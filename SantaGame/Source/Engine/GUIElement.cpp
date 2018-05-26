#include "GUIElement.h"

using namespace iae;

GUIElement::GUIElement(sf::FloatRect parent, int anchor, 
	sf::FloatRect offset_rect, sf::Color color, std::string id) :
	anchor_(anchor),
	parent_rect_(parent),
	offset_rect_(offset_rect),
	color_(color),
	id_(id)
{
	gui_rectangle_.setFillColor(color_);
	Update(offset_rect_);
}

GUIElement::~GUIElement()
{
}

void GUIElement::Update(sf::FloatRect rect)
{
	// _gui_rectangle.setFillColor(_color);
	offset_rect_ = rect;
	gui_rectangle_.setSize(sf::Vector2f(offset_rect_.width, offset_rect_.height));
	setAnchor();
}

sf::Drawable* GUIElement::getRenderTarget()
{
	return &gui_rectangle_;
}

void GUIElement::setAnchor()
{
	sf::Vector2f tmp_position;
	switch (anchor_)
	{
		// TOP
	case Anchor::top_left:
		tmp_position.x = offset_rect_.left + parent_rect_.left;
		tmp_position.y = offset_rect_.top + parent_rect_.top;
		gui_rectangle_.setPosition(tmp_position);
		break;

	case Anchor::top_center:
		tmp_position.x = offset_rect_.left + parent_rect_.width / 2;
		tmp_position.y = offset_rect_.top + parent_rect_.top;
		gui_rectangle_.setPosition(tmp_position);
		break;

	case Anchor::top_right:
		tmp_position.x = offset_rect_.left + parent_rect_.width;
		tmp_position.y = offset_rect_.top + parent_rect_.top;
		gui_rectangle_.setPosition(tmp_position);
		break;

		// MIDDLE
	case Anchor::middle_left:
		tmp_position.x = offset_rect_.left + parent_rect_.left;
		tmp_position.y = offset_rect_.top + parent_rect_.height / 2;
		gui_rectangle_.setPosition(tmp_position);
		break;

	case Anchor::middle_center:
		tmp_position.x = offset_rect_.left + parent_rect_.width / 2;
		tmp_position.y = offset_rect_.top + parent_rect_.height / 2;
		gui_rectangle_.setPosition(tmp_position);
		break;

	case Anchor::middle_right:
		tmp_position.x = offset_rect_.left + parent_rect_.width;
		tmp_position.y = offset_rect_.top + parent_rect_.height / 2;
		gui_rectangle_.setPosition(tmp_position);
		break;

		// BOTTOM
	case Anchor::bottom_left:
		tmp_position.x = offset_rect_.left + parent_rect_.left;
		tmp_position.y = offset_rect_.top + parent_rect_.height;
		gui_rectangle_.setPosition(tmp_position);
		break;

	case Anchor::bottom_center:
		tmp_position.x = offset_rect_.left + parent_rect_.width / 2;
		tmp_position.y = offset_rect_.top + parent_rect_.height;
		gui_rectangle_.setPosition(tmp_position);
		break;

	case Anchor::bottom_right:
		tmp_position.x = offset_rect_.left + parent_rect_.width;
		tmp_position.y = offset_rect_.top + parent_rect_.height;
		gui_rectangle_.setPosition(tmp_position);
		break;
	default:
		break;
	}

	bounds_rect_.left = tmp_position.x;
	bounds_rect_.top = tmp_position.y;
}
