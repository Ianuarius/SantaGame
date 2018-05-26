#pragma once
namespace iae {
	template <class T, class EventT>
	class MemberFunctionHandler
	{
	public:
		typedef void (T::*MemberFunc)(EventT*);
		
		MemberFunctionHandler(T* instance, MemberFunc mem_fn) : 
			instance_(instance), function_(mem_fn) {};
		
		void call(const Event* event)
		{
			(instance_->*function_)(static_cast<EventT*>(event));
		}

	private:
		T* instance_;
		MemberFunc function_;
	};
}