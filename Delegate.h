#pragma once

#include <functional>
#include <memory>
#include <vector>

template<typename ...Args>
class Delegate
{
public:
	
	void attach(std::shared_ptr<std::function<void(Args...)>> listener);
	void detach(std::shared_ptr<std::function<void(Args...)>> listener);

	void invoke(Args&&... args);

private:
	
	std::vector<std::shared_ptr<std::function<void(Args...)>>> listeners;
};

template<typename ...Args>
inline void Delegate<Args...>::attach(std::shared_ptr<std::function<void(Args...)>> listener)
{
	listeners.push_back(listener);
}

template<typename ...Args>
inline void Delegate<Args...>::detach(std::shared_ptr<std::function<void(Args...)>> listener)
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
inline void Delegate<Args...>::invoke(Args&& ...args)
{
	for (auto i : listeners)
	{
		i->oprator()(std::forward<Args>(args)...);
	}
}
