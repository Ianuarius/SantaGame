#pragma once

namespace iae
{
	class PlayerState
	{
	public:
		PlayerState();
		~PlayerState();
		bool Initialize();
		bool idle_;
		bool running_;
		bool jumping_;
		bool climbing_;
		bool dead_;
		bool facing_right_;
	};
}
