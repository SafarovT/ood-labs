#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "Observer.h"

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

class CDisplay: public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	struct StatsData
	{
		double minValue = std::numeric_limits<double>::infinity();
		double maxValue = -std::numeric_limits<double>::infinity();
		double accValue = 0;
		unsigned countAcc = 0;
	};

	std::unordered_map<std::string, std::shared_ptr<StatsData>> m_stats;

	std::shared_ptr<StatsData> GetStatsData(std::string const& name)
	{
		auto foundPair = m_stats.find(name);
		if (foundPair != m_stats.end())
		{
			return foundPair->second;
		}
		std::shared_ptr<StatsData> statsDataPtr = std::make_shared<StatsData>();
		m_stats.emplace(name, statsDataPtr);

		return statsDataPtr;
	}

	void CalcStats(std::shared_ptr<StatsData> stats, double value)
	{
		if (stats->minValue > value)
		{
			stats->minValue = value;
		}
		if (stats->maxValue < value)
		{
			stats->maxValue = value;
		}
		stats->accValue += value;
		++stats->countAcc;
	}

	void PrintStats(std::shared_ptr<StatsData> stats, std::string const& name)
	{
		std::cout << "Max " << name << " " << stats->maxValue << std::endl;
		std::cout << "Min " << name << " " << stats->minValue << std::endl;
		std::cout << "Average " << name << " " << (stats->accValue / stats->countAcc) << std::endl;
		std::cout << "----------------" << std::endl;
	}

	void HandleStats(std::string const& name, double value)
	{
		std::shared_ptr<StatsData> statsData = GetStatsData(name);
		
		CalcStats(statsData, value);

		PrintStats(statsData, name);
	}

	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		HandleStats("temperature", data.temperature);
		HandleStats("humidity", data.humidity);
		HandleStats("pressure", data.pressure);
	}
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;	
};
