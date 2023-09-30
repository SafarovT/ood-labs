#include "WeatherData.h"

int main()
{
	CWeatherData wd;

	CDisplay display;
	wd.RegisterObserver(display);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay);

	wd.SetMeasurements(3, 0.7, 760, 100, 45);
	wd.SetMeasurements(4, 0.8, 761, 50, 90);

	wd.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 761, 100, 100);
	wd.SetMeasurements(-10, 0.8, 761, 100, 100);

	return EXIT_SUCCESS;
}