#include "WeatherData.h"

int main()
{
	CWeatherIndoorData wd;

	CDisplay display;
	wd.RegisterObserver(display);

	CStatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay);

	return EXIT_SUCCESS;
}