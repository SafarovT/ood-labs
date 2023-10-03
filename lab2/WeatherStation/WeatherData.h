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
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity() const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure() const
	{
		return m_pressure;
	}

	double GetWindSpeed() const
	{
		return m_windSpeed;
	}

	double GetWindAngle() const
	{
		return m_windAngle;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, double windAngle)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_windSpeed = windSpeed;
		m_windAngle = windAngle;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.windAngle = GetWindAngle();
		info.windSpeed = GetWindSpeed();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	double m_windSpeed = 0;
	double m_windAngle = 0;
};

class CDisplay : public IObserver<SWeatherInfo>
{
public:
	void SetInStationPtr(CWeatherData* inStation)
	{
		m_inStation = inStation;
	}

	void SetOutStationPtr(CWeatherData* outStation)
	{
		m_outStation = outStation;
	}
private:
	CWeatherData* m_inStation = nullptr;
	CWeatherData* m_outStation = nullptr;

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
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>* sender) override
	{
		m_temperatureStats.UpdateData(data.temperature);
		m_windStatistic.UpdateData(VectorPolarCoord({ data.windAngle, data.windSpeed }));

		m_temperatureStats.Print();
		m_windStatistic.Print();
	} // добавить остальные измерения

	NumericStatistic m_temperatureStats{ "temperatrue" };
	VectorStatistic m_windStatistic{ "wind angle", "wind speed" };
};