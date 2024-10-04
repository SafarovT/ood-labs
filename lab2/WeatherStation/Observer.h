#pragma once
#include <optional>
#include <map>
#include <unordered_map>
#include <vector>
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

		m_priorities.emplace(&observer, priority);
		auto observersWithGivenPriority = m_observers.find(priority);
		if (observersWithGivenPriority != m_observers.end())
		{
			observersWithGivenPriority->second.push_back(&observer);
		}
		else
		{
			m_observers.emplace(priority, std::vector<ObserverType*>({ &observer }));
		}
	}

	void RegisterObserver(ObserverType& observer) override
	{
		RegisterObserver(observer, 0);
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		for (auto i = m_observers.rbegin(); i != m_observers.rend(); i++)
		{
			std::vector<ObserverType*> observerCopy;
			std::copy(i->second.begin(), i->second.end(), std::back_inserter(observerCopy));
			for (auto& observer : observerCopy)
			{
				observer->Update(data, this);
			}
		}
	}

	void RemoveObserver(ObserverType & observer) override
	{
		if (auto observerPriorityPair = m_priorities.find(&observer); observerPriorityPair != m_priorities.end())
		{
			auto foundObserversWithGivenPriority = m_observers.find(observerPriorityPair->second);
			if (foundObserversWithGivenPriority != m_observers.end())
			{
				auto comparePtrs = [&observer](ObserverType* observerPtr)
				{
					return &observer == observerPtr;
				};
				std::erase_if(foundObserversWithGivenPriority->second, comparePtrs);
			}
			m_priorities.erase(observerPriorityPair);
		}
	}

protected:
		// Классы-наследники должны перегрузить данный метод, 
		// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;
	
private:
	using PriorityOfObservers = std::unordered_map<ObserverType*, int>;
	// использовать пример с доски для нелинейного времени
	using ObserversWithPriority = std::map<int, std::vector<ObserverType*>>;
	ObserversWithPriority m_observers;
	PriorityOfObservers m_priorities;
};
