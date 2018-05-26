#pragma once

namespace iae
{
	class Action
	{
	public:
		enum ActionList
		{
			move_left,
			move_right,
			jump,
			climb_up,
			climb_down
		};

		int action_;
		int keyboard_;
	};
}