#include "../../external/catch2/catch.hpp"
#include "CoutBufferFixture.h"
#include "TestsDisplays.h"
#include "../WeatherStation/VectorStatistic.h"
#define _USE_MATH_DEFINES
#include <math.h>

SCENARIO_METHOD(CoutBufferFixture, "Tests")
{
	CWeatherIndoorData wd;

	GIVEN("Three observers with one self-remove")
	{
		CDisplayPrinter display("Test 1"), display2("Test 2");
		CDisplaySelfRemove selfRemove;
		wd.RegisterObserver(display);
		wd.RegisterObserver(selfRemove);
		wd.RegisterObserver(display2);
		ClearBuffer();


		WHEN("Changing data")
		{
			wd.SetMeasurements({ 1, 2, 3 });

			THEN("All three displayes displayed")
			{
				CHECK(GetBufferValue() == "Test 1\nSelf delete\nTest 2\n");
			}

			AND_WHEN("Changing data again")
			{
				ClearBuffer();
				wd.MeasurementsChanged();

				THEN("No self delete output")
				{
					CHECK(GetBufferValue() == "Test 1\nTest 2\n");
				}
			}

			AND_WHEN("Adding first observer again")
			{
				ClearBuffer();
				wd.RegisterObserver(display, 100);

				THEN("Two observers remains in same order")
				{
					wd.MeasurementsChanged();
					CHECK(GetBufferValue() == "Test 1\nTest 2\n");
				}
			}
		}
	}
	
	GIVEN("Three observers with print update")
	{
		CDisplayPrinter d99("99"), d100("100"), d101("101");
		wd.RegisterObserver(d100, 100);
		wd.RegisterObserver(d99, 99);
		wd.RegisterObserver(d101, 101);
		ClearBuffer();

		WHEN("Changing data")
		{
			wd.SetMeasurements({ 100, 200, 300 });

			THEN("Observers updated in correct order")
			{
				CHECK(GetBufferValue() == "101\n100\n99\n");
			}
		}
	}

	GIVEN("One display and two wd")
	{
		CWeatherIndoorData iwd;
		CWeatherData owd;
		CDisplay d;
		d.SetInStationPtr(&iwd);
		d.SetOutStationPtr(&owd);
		ClearBuffer();

		WHEN("Changing input data")
		{
			iwd.SetMeasurements({ 1, 2, 3 });

			THEN("Data changed inside")
			{
				CHECK(GetBufferValue() == "Data from inside-placed station:\nCurrent Temp 1\nCurrent Hum 2\nCurrent Pressure 3\n----------------\n");
			}
		}

		WHEN("Changing output data")
		{
			owd.SetMeasurements({ 1, 2, 3, 4, 5 });
			
			THEN("Data changed outside")
			{
				CHECK(GetBufferValue() == "Data from outside-placed station:\nCurrent Wind Speed: 4\nCurrent Wind Angle: 5\nCurrent Temp 1\nCurrent Hum 2\nCurrent Pressure 3\n----------------\n");
			}
		}
	}
}

SCENARIO("Testing VecrtorStatistic calculations")
{
	VectorStatistic stat;

	GIVEN("North vector with length of 1")
	{
		stat.UpdateData(VectorPolarCoord({ 0, 1.0 }));
		CHECK(stat.GetAverage() == 0);

		WHEN("Adding oposite vector with same length")
		{
			stat.UpdateData(VectorPolarCoord({ M_PI, 1.0 }));

			THEN("Result is a point")
			{
				CHECK(stat.GetAverage() == 0);
			}
		}

		WHEN("Adding +90deg vector with same length")
		{
			stat.UpdateData(VectorPolarCoord({ M_PI / 2, 1.0 }));

			THEN("Result is a 45deg")
			{
				CHECK(stat.GetAverage() == M_PI / 4);
			}
		}
	}
}