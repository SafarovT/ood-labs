#include "../../external/catch2/catch.hpp"
#include "CoutBufferFixture.h"

#include "../SimUDuckFn/lib/DuckFunctions.h"
#include "../SimUDuckFn/lib/Duck/MallardDuck.h"
#include "../SimUDuckFn/lib/Duck/RedheadDuck.h"
#include "../SimUDuckFn/lib/Duck/DecoyDuck.h"
#include "../SimUDuckFn/lib/Duck/ModelDuck.h"
#include "../SimUDuckFn/lib/Duck/RubberDuck.h"

SCENARIO_METHOD(CoutBufferFixture, "Mallard duck test")
{
	WHEN("Play with mallard duck")
	{
		MallardDuck duck;
		PlayWithDuck(duck);

		THEN("Mallard duck крякнула, полетела и станцевала вальс")
		{
			CHECK(GetBufferValue() == "I'm mallard duck\nQuack Quack!!!\nFlight number: 1\nI'm flying with wings!!\n*Dancing waltz*\n\n");
		}

		AND_WHEN("Утка летит во второй раз")
		{
			ClearBuffer();
			duck.Fly();

			THEN("Flies count = 2")
			{
				CHECK(GetBufferValue() == "Flight number: 2\nI'm flying with wings!!\n");
			}

			AND_WHEN("Меняется стратегия полета")
			{
				ClearBuffer();
				duck.SetFlyBehavior(MakeFlyWithWings());

				THEN("Утка полетит в свой первый полет")
				{
					duck.Fly();
					CHECK(GetBufferValue() == "Flight number: 1\nI'm flying with wings!!\n");
				}
			}
		}
	}
}

SCENARIO_METHOD(CoutBufferFixture, "Red head test")
{
	WHEN("Play with redhead duck")
	{
		RedheadDuck duck;
		PlayWithDuck(duck);

		THEN("Redhead duck крякнула, полетела и станцевала вальс")
		{
			CHECK(GetBufferValue() == "I'm redhead duck\nQuack Quack!!!\nFlight number: 1\nI'm flying with wings!!\n*Dancing minuette*\n\n");
		}
	}
}

SCENARIO_METHOD(CoutBufferFixture, "Decoy duck test")
{
	WHEN("Play with decoy duck")
	{
		DecoyDuck duck;
		PlayWithDuck(duck);

		THEN("Decoy duck не крякнула, не полетела и не станцевала")
		{
			CHECK(GetBufferValue() == "I'm decoy duck\n\n");
		}
	}
}

SCENARIO_METHOD(CoutBufferFixture, "Model duck test")
{
	WHEN("Play with decoy duck")
	{
		ModelDuck duck;
		PlayWithDuck(duck);

		THEN("Model duck не крякнула, не полетела и не станцевала")
		{
			CHECK(GetBufferValue() == "I'm model duck\nQuack Quack!!!\n\n");
		}
	}
}

SCENARIO_METHOD(CoutBufferFixture, "Rubber duck test")
{
	WHEN("Play with rubber duck")
	{
		RubberDuck duck;
		PlayWithDuck(duck);

		THEN("Rubber duck не крякнула, не полетела и не станцевала")
		{
			CHECK(GetBufferValue() == "I'm rubber duck\nSqueek!!!\n\n");
		}
	}
}