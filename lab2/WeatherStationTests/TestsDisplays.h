#pragma once
#include "../WeatherStation/WeatherData.h"

class CDisplayMock : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>* sender) override
	{
		std::cout << "Test\n";
	}
};

class CDisplaySelfRemove : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>* sender) override
	{
		std::cout << "Self delete\n";
		sender->RemoveObserver(*this);
	}
};

class CDisplayPrinter : public IObserver<SWeatherInfo>
{
public:
	CDisplayPrinter(std::string&& message)
		: m_message(message)
	{}
private:
	std::string m_message;

	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>* sender) override
	{
		std::cout << m_message << "\n";
	}
};