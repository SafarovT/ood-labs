#include "../../external/catch2/catch.hpp"
#include <sstream>
#include <iostream>

#include "../lib/DuckFunctions.h"
#include "../lib/Duck/MallardDuck.h"
#include "../lib/Duck/RedheadDuck.h"
#include "../lib/Duck/DecoyDuck.h"
#include "../lib/Duck/ModelDuck.h"
#include "../lib/Duck/RubberDuck.h"

struct CoutBufferFixture
{
	std::stringstream buffer;
	std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());
};

SCENARIO_METHOD(CoutBufferFixture, "Mallard duck test")
{
	WHEN("Play with mallard duck")
	{
		MallardDuck duck;
		PlayWithDuck(duck);

		THEN("Mallard duck крякнула, полетела и станцевала вальс")
		{
			CHECK(buffer.str() == "I'm mallard duck\nQuack Quack!!!\nFlight number: 1\nI'm flying with wings!!\n*Dancing waltz*\n");
		}
	}
}

SCENARIO_METHOD(CoutBufferFixture, "Read head test")
{
	WHEN("Play with readhead duck")
	{
		RedheadDuck duck;
		PlayWithDuck(duck);

		THEN("Readhead duck крякнула, полетела и станцевала вальс")
		{
			CHECK(buffer.str() == "I'm readhead duck\nQuack Quack!!!\nFlight number: 1\nI'm flying with wings!!\n*Dancing minuette*\n");
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
			CHECK(buffer.str() == "I'm decoy duck\n");
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
			CHECK(buffer.str() == "I'm model duck\nQuack Quack!!!\n");
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
			CHECK(buffer.str() == "I'm rubber duck\nQuack Quack!!!\n");
		}
	}
}