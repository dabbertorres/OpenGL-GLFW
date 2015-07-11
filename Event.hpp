#ifndef SWIFT_PRIVATE_EVENT_HPP
#define SWIFT_PRIVATE_EVENT_HPP

#include <set>

namespace swift
{
	template<typename... CallbackArgs>
	class Event
	{
		friend class Window;
		
		public:
			using Callback = void (*)(CallbackArgs...);
			
			Event() = default;
			~Event() = default;
			
			bool addListener(const Callback& cb);
			bool removeListener(const Callback& cb);
		
		private:
			void operator()(CallbackArgs... args);
			
			std::set<Callback> listeners;
	};
	
	template<typename... CallbackArgs>
	bool Event<CallbackArgs...>::addListener(const Callback& cb)
	{
		return listeners.insert(cb).second;
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
			l(args...);
	}
}

#endif // SWIFT_PRIVATE_EVENT_HPP
