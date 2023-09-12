#include "../../external/catch2/catch.hpp"
#include <sstream>
#include <iostream>

#include "../lib/DuckFunctions.h"
#include "../lib/Duck/MallardDuck.h"
#include "../lib/Duck/RedheadDuck.h"
#include "../lib/Duck/DecoyDuck.h"
#include "../lib/Duck/ModelDuck.h"
#include "../lib/Duck/RubberDuck.h"

class CoutBufferFixture
{
public:
	~CoutBufferFixture()
	{
		std::cout.rdbuf(backupBuffer);
	}

	std::stringstream buffer;
	std::streambuf* backupBuffer = std::cout.rdbuf(buffer.rdbuf());
};

SCENARIO_METHOD(CoutBufferFixture, "Mallard duck test")
{
	WHEN("Play with mallard duck")
	{
		MallardDuck duck;
		PlayWithDuck(duck);

		THEN("Mallard duck крякнула, полетела и станцевала вальс")
		{
			CHECK(buffer.str() == "I'm mallard duck\nQuack Quack!!!\nFligth number: 1\nI'm flying with wings!!\n*Dancing waltz*\n\n");
		}

		AND_WHEN("Duck flies one more time")
		{
			buffer.str("");
			duck.Fly();

			THEN("Flies count = 2")
			{
				CHECK(buffer.str() == "Fligth number: 2\nI'm flying with wings!!\n");
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
			CHECK(buffer.str() == "I'm redhead duck\nQuack Quack!!!\nFligth number: 1\nI'm flying with wings!!\n*Dancing minuette*\n\n");
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
			CHECK(buffer.str() == "I'm decoy duck\n\n");
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
			CHECK(buffer.str() == "I'm model duck\nQuack Quack!!!\n\n");
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
			CHECK(buffer.str() == "I'm rubber duck\nSqueek!!!\n\n");
		}
	}
}