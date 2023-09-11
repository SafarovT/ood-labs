#include "../../external/catch2/catch.hpp"
#include <sstream>
#include <iostream>

#include "../lib/DuckFunctions.h"
#include "../lib/Duck/MallardDuck.h"
#include "../lib/Duck/DecoyDuck.h"
#include "../lib/Duck/ModelDuck.h"
#include "../lib/Duck/RedheadDuck.h"
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
		/*PlayWithDuck(duck);

		THEN("Mallard duck крякнула, полетела и станцевала вальс")
		{
			CHECK(buffer.str() == "I'm mallard duck\nQuack Quack!!!\nFlight number: 1\nI'm flying with wings!!\n*Dancing waltz*\n");
		}*/
	}
}