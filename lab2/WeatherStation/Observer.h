#pragma once
#include <optional>
#include <map>
#include <vector>
#include <algorithm>
#include <functional>

template <typename T>
class IObservable;

// нарисовать схему

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

	void RegisterObserver(ObserverType & observer) override
	{
		//m_observers.emplace_back(0, &observer);
	}

	void RegisterObserver(ObserverType& observer, int priority) override
	{
		//m_observers.insert(priority, &observer);
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		for (auto & observer : m_observers)
		{
			//observer->Update(data, this);
		}
	}

	void RemoveObserver(ObserverType & observer) override
	{
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;
	
private:
	using ObserversWithPriority = std::map<int, ObserverType*>;
	ObserversWithPriority m_observers;

	std::optional GetPriorityObserversPair(int priority)
	{
		if (auto foundPair = m_observers.find(priority); foundPair != m_observers.end())
		{
			return foundPair;
		}

		return std::nullopt;
	}

	std::optional<std::vector<ObserverType*>> GetObserversCopy(int priority) const
	{
		if (auto foundPair = GetPriorityObserversPair(priority); foundPair != std::nullopt)
		{
			return std::copy(foundPair->second.begin(), foundPair->second.end());
		}

		return std::nullopt;
	}
};
