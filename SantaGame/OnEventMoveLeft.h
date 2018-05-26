#pragma once
#include "Event.h"

namespace iae {
	class OnEventMoveLeft : public Event
	{
	public:
		OnEventMoveLeft(int pos) : _pos(pos), _damage(60) {};

		int getPosition()	const { return _pos; }
		int getDamage()		const { return _damage; }

	private:
		int _pos, _damage;
	};

}