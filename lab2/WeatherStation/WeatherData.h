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

struct SWeatherInfoIndoor
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 760;
};

struct SWeatherInfo : public SWeatherInfoIndoor
{
	double windSpeed = 0;
	double windAngle = 0;
};
// доработать чтоыбы бли разные сигнал
class CWeatherIndoorData : public CObservable<SWeatherInfo>
{
public:
	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(SWeatherInfoIndoor measurements)
	{
		m_weatherInfo = measurements;

		MeasurementsChanged();
	}

protected:
	SWeatherInfo GetChangedData() const override
	{
		return
		{
			m_weatherInfo.temperature,
			m_weatherInfo.humidity,
			m_weatherInfo.pressure,
		};
	}
private:
	SWeatherInfoIndoor m_weatherInfo;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
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
	SWeatherInfo GetChangedData() const
	{
		return m_weatherInfo;
	}

private:
	SWeatherInfo m_weatherInfo;
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

	/*
		Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
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
			std::cout << "Data from outside-placed station:" << std::endl
				<< "Current Wind Speed: " << data.windSpeed << std::endl
				<< "Current Wind Angle: " << data.windAngle << std::endl;
		}
		std::cout << "Current Temp " << data.temperature << std::endl
				<< "Current Hum " << data.humidity << std::endl
				<< "Current Pressure " << data.pressure << std::endl
				<< "----------------" << std::endl;
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

	void PrintData(std::string const& dataName, IStatistic<double>& statistic)
	{
		PrintData(dataName, statistic.GetMax(), statistic.GetMin(), statistic.GetAverage());
	}

	/*
		Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo>* sender) override
	{
		m_temperatureStats.UpdateData(data.temperature);
		m_pressureStatistic.UpdateData(data.pressure);
		m_humStatistic.UpdateData(data.humidity);
		m_windStatistic.UpdateData(VectorPolarCoord({ data.windAngle, data.windSpeed }));

		PrintData("Temperature", m_temperatureStats);
		PrintData("Pressure", m_pressureStatistic);
		PrintData("Humidity", m_humStatistic);
		PrintData("Wind", m_windStatistic);
	}

	NumericStatistic m_temperatureStats, m_pressureStatistic, m_humStatistic;
	VectorStatistic m_windStatistic;
};