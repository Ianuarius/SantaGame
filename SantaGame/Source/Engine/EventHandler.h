#pragma once
#include <map>
#include <typeinfo>
#include "Event.h"
#include "HandlerFunctionBase.h"

namespace iae
{
	class TypeInfo {
	public:
		explicit TypeInfo(const type_info& info) : _typeInfo(info) {};
		bool operator < (const TypeInfo& rhs) const {
			return _typeInfo.before(rhs._typeInfo) != 0;
		}
	private:
		const type_info& _typeInfo;
	};

	class EventHandler
	{
	public:
		void HandleEvent(const Event*);

		template <class T, class EventT>
		void RegisterEventFunc(T*, void (T::*mem_fn)(EventT*));

	private:
		typedef std::map<TypeInfo, HandlerFunctionBase*> Handlers;
		Handlers handlers_;
	};
}