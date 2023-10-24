#pragma once

#include <functional>
#include <memory>
#include <vector>

template<typename ...Args>
using Listener = std::shared_ptr<std::function<void(Args...)>>;

template<typename ...Args>
Listener<Args...> makeListener(std::function<void(Args...)> function)
{
	return std::make_shared<std::function<void(Args...)>>(function);
}

template<typename ...Args>
class Delegate
{
public:
	
	void attach(Listener<Args...> listener);
	void detach(Listener<Args...> listener);

	void invoke(Args... args) const;

private:
	
	std::vector<std::shared_ptr<std::function<void(Args...)>>> listeners;
};

template<typename ...Args>
inline void Delegate<Args...>::attach(Listener<Args...> listener)
{
	listeners.push_back(listener);
}

template<typename ...Args>
inline void Delegate<Args...>::detach(Listener<Args...> listener)
{
	for (auto i = listeners.begin(); i != listeners.end(); i++)
	{
		if (*i == listener)
		{
			listeners.erase(i);
		}
	}
}

template<typename ...Args>
inline void Delegate<Args...>::invoke(Args ...args) const
{
	for (auto i : listeners)
	{
		i->operator()(args...);
	}
}
