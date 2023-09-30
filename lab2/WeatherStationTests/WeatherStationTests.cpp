#include "../../external/catch2/catch.hpp"
#include "CoutBufferFixture.h"
#include "TestsDisplays.h"

SCENARIO_METHOD(CoutBufferFixture, "Tests")
{

	CWeatherData wd;

	GIVEN("Three observers with self-remove")
	{
		CDisplayMock display, display2;
		CDisplaySelfRemove selfRemove;
		wd.RegisterObserver(display);
		wd.RegisterObserver(selfRemove);
		wd.RegisterObserver(display2);
		ClearBuffer();

		WHEN("Changing data")
		{
			wd.SetMeasurements(1, 2, 3, 4, 5);

			THEN("All three displayes displayed")
			{
				CHECK(GetBufferValue() == "Test\nSelf delete\nTest\n");
			}

			AND_THEN("Changing data again")
			{
				ClearBuffer();
				wd.SetMeasurements(3, 2, 1, 1, 1);

				THEN("No self delete output")
				{
					CHECK(GetBufferValue() == "Test\nTest\n");
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
			wd.SetMeasurements(100, 200, 300, 400, 500);

			THEN("Observers updated in correct order")
			{
				CHECK(GetBufferValue() == "101\n100\n99\n");
			}
		}
	}

	GIVEN("One display and two wd")
	{
		CWeatherData iwd, owd;
		CDisplay d;
		iwd.RegisterObserver(d);
		owd.RegisterObserver(d);
		d.SetInStationPtr(&iwd);
		d.SetOutStationPtr(&owd);
		ClearBuffer();

		WHEN("Changing input data")
		{
			iwd.SetMeasurements(1, 2, 3, 4, 5);

			THEN("Data changed inside")
			{
				CHECK(GetBufferValue() == "Data from inside-placed station:\nCurrent Temp 1\nCurrent Hum 2\nCurrent Pressure 3\n----------------\n");
			}
		}

		WHEN("Changing output data")
		{
			owd.SetMeasurements(1, 2, 3, 4, 5);
			
			THEN("Data changed outside")
			{
				CHECK(GetBufferValue() == "Data from outside-placed station:\nCurrent Temp 1\nCurrent Hum 2\nCurrent Pressure 3\n----------------\n");
			}
		}
	}
}