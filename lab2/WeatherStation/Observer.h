#pragma once

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

	void RegisterObserver(ObserverType & observer) override
	{
		m_observers.emplace_back(0, &observer);
	}

	void RegisterObserver(ObserverType& observer, int priority) override
	{
		auto comparePairs = [](PriorityObserverPair const& pair1, PriorityObserverPair const& pair2)
		{
			return pair1.first > pair2.first;
		};
		m_observers.emplace_back(priority, &observer);
		std::sort(m_observers.begin(), m_observers.end(), comparePairs);
	}

	std::vector<ObserverType*> GetObservers()
	{
		std::vector<ObserverType*> observersCopy;
		for (auto& observer : m_observers)
		{
			observersCopy.push_back(observer.second);
		}

		return observersCopy;
	}

	void NotifyObservers() override
	{
		auto observersCopy = GetObservers();
		T data = GetChangedData();
		bool del = true;
		for (auto & observer : observersCopy)
		{
			observer->Update(data, this);
		}
	}

	void RemoveObserver(ObserverType & observer) override
	{
		auto compareObservers = [&observer](PriorityObserverPair& pair)
		{
			return pair.second == &observer;
		};
		std::erase_if(m_observers, compareObservers);
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;
	
private:
	using PriorityObserverPair = std::pair<int, ObserverType*>;
	std::vector<PriorityObserverPair> m_observers;
};
