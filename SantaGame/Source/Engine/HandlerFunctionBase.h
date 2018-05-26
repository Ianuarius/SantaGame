#pragma once
#include "Event.h"

namespace iae {

	class HandlerFunctionBase
	{
	public:
		virtual ~HandlerFunctionBase() {};
		void exec(const Event* event) { call(event); }

	private:
		virtual void call(const Event*) = 0;
	};

}