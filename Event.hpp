#ifndef SWIFT_PRIVATE_EVENT_HPP
#define SWIFT_PRIVATE_EVENT_HPP

#include <functional>
#include <memory>
#include <set>

namespace swift
{
	template<typename... CallbackArgs>
	class Event
	{
		public:
			using Callback = std::function<void(CallbackArgs...)>;
			
			Event() = default;
			~Event() = default;
			
			bool addListener(const Callback& cb);
			bool removeListener(const Callback& cb);
			
			void operator()(CallbackArgs... args);
		
		private:
			std::set<std::shared_ptr<Callback>> listeners;
	};
	
	template<typename... CallbackArgs>
	bool Event<CallbackArgs...>::addListener(const Callback& cb)
	{
		return listeners.insert(std::make_shared<Callback>(cb)).second;
	}
	
	template<typename... CallbackArgs>
	bool Event<CallbackArgs...>::removeListener(const Callback& cb)
	{
		return listeners.erase(cb);
	}
	
	template<typename... CallbackArgs>
	void Event<CallbackArgs...>::operator()(CallbackArgs... args)
	{
		for(auto& l : listeners)
			(*l)(args...);
	}
}

#endif // SWIFT_PRIVATE_EVENT_HPP
