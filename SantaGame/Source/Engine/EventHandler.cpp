#include "EventHandler.h"

using namespace iae;

void EventHandler::HandleEvent(const Event *event)
{
	Handlers::iterator it = handlers_.find(TypeInfo(typeid(*event)));

	if (it != handlers_.end())
	{
		it->second->exec(event);
	}
}

template <class T, class EventT>
void EventHandler::RegisterEventFunc(T* obj, void (T::*mem_fn)(EventT*))
{
	handlers_[TypeInfo(typeid(EventT))] = new MemberFunctionHandler<T, EventT>(obj, mem_fn);
}