#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Observer.h"
#include "NumericStatistic.h"
#include "VectorStatistic.h"

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	double windSpeed = 0;
	double windAngle = 0;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature() const
	{
		return m_weatherInfo.temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity() const
	{
		return m_weatherInfo.humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure() const
	{
		return m_weatherInfo.pressure;
	}

	double GetWindSpeed() const
	{
		return m_weatherInfo.windSpeed;
	}

	double GetWindAngle() const
	{
		return m_weatherInfo.windAngle;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(SWeatherInfo measurements)
	{
		m_weatherInfo = measurements;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData() const override
	{
		return m_weatherInfo;
	}
private:
	SWeatherInfo m_weatherInfo = {
		0,
		0,
		760.0,
		0,
		0,
	};
};

class CDisplay : public IObserver<SWeatherInfo>
{
public:
	void SetInStationPtr(IObservable<SWeatherInfo>* inStation)
	{
		m_inStation = inStation;
		inStation->RegisterObserver(*this);
	}

	void SetOutStationPtr(IObservable<SWeatherInfo>* outStation)
	{
		m_outStation = outStation;
		outStation->RegisterObserver(*this);
	}
private:
	IObservable<SWeatherInfo>* m_inStation = nullptr;
	IObservable<SWeatherInfo>* m_outStation = nullptr;

	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>* sender) override
	{
		if (sender == m_inStation)
		{
			std::cout << "Data from inside-placed station:" << std::endl;
		}
		else if (sender == m_outStation)
		{
			std::cout << "Data from outside-placed station:" << std::endl;
		}
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	void PrintData(std::string const& dataName, double min, double max, double average)
	{
		std::cout << dataName << " statistic:" << std::endl
			<< "Max " << max << std::endl
			<< "Min " << min << std::endl
			<< "Average " << average << std::endl
			<< "----------------" << std::endl;
	}

	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>* sender) override
	{
		m_temperatureStats.UpdateData(data.temperature);
		m_pressureStatistic.UpdateData(data.pressure);
		m_humStatistic.UpdateData(data.humidity);
		m_windStatistic.UpdateData(VectorPolarCoord({ data.windAngle, data.windSpeed }));

		PrintData("Temperature", m_temperatureStats.GetMax(), m_temperatureStats.GetMin(), m_temperatureStats.GetAverage());
		PrintData("Pressure", m_pressureStatistic.GetMax(), m_pressureStatistic.GetMin(), m_pressureStatistic.GetAverage());
		PrintData("Humidity", m_humStatistic.GetMax(), m_humStatistic.GetMin(), m_humStatistic.GetAverage());
		PrintData("Wind", m_windStatistic.GetMin().GetLength(), m_windStatistic.GetMin().GetLength(), m_windStatistic.GetAverage().GetAngle());
	}

	NumericStatistic m_temperatureStats, m_pressureStatistic, m_humStatistic;
	VectorStatistic m_windStatistic;
};