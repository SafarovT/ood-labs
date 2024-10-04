#pragma once
#include <optional>
#include <map>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <functional>

template <typename T>
class IObservable;

/*
	Шаблонный интерфейс IObserver. Его должен реализовывать класс, 
	желающий получать уведомления от соответствующего IObservable
	Параметром шаблона является тип аргумента,
	передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data, IObservable<T>* sender) = 0;
	virtual ~IObserver() = default;
};

/*
	Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
	инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer) = 0;
	virtual void RegisterObserver(IObserver<T>& observer, int priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, int priority) override
	{
		auto foundObserver = m_priorities.find(&observer);
		if (foundObserver != m_priorities.end())
		{
			return;
		}

		auto& observerList = m_observers[priority];
		observerList.emplace_back(&observer);
		auto it = std::prev(observerList.end());

		m_priorities.emplace(&observer, std::make_pair(priority, it));
	}

	void RegisterObserver(ObserverType& observer) override
	{
		RegisterObserver(observer, 0);
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		for (auto it = m_observers.rbegin(); it != m_observers.rend(); it++)
		{
			ObserverList observerCopy = it->second;
			for (auto& observer : observerCopy)
			{
				observer->Update(data, this);
			}
		}
	}

	void RemoveObserver(ObserverType & observer) override
	{
		auto observerIt = m_priorities.find(&observer);
		if (observerIt != m_priorities.end())
		{
			int priority = observerIt->second.first;
			auto listIt = observerIt->second.second;

			m_observers.at(priority).erase(listIt);

			if (m_observers.at(priority).empty())
			{
				m_observers.erase(priority);
			}
			m_priorities.erase(observerIt);
		}
	}

protected:
		// Классы-наследники должны перегрузить данный метод, 
		// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;
	
private:
	using ObserverList = std::list<ObserverType*>;
	using ObserversWithPriority = std::map<int, ObserverList>;
	using PriorityIteratorPair = std::pair<int, typename ObserverList::iterator>;
	using PriorityOfObservers = std::unordered_map<ObserverType*, PriorityIteratorPair>;
	ObserversWithPriority m_observers;
	PriorityOfObservers m_priorities;
};
