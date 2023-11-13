#include <sstream>
#include "../../external/catch2/catch.hpp"
#include "../task1/CModernGraphicsRendererAdapter.h"
#include "../task1/shape_drawing_lib.h"

SCENARIO("Adapter tests")
{
	std::ostringstream output;
	modern_graphics_lib::CModernGraphicsRenderer renderer(output);
	CModernGraphicsRendererAdapter adapter(renderer);
	shape_drawing_lib::CCanvasPainter painter(adapter);

	WHEN("Draw nothing")
	{
		THEN("Draw begin, nothing drew")
		{
			CHECK(output.str() == "<draw>\n");
		}
	}

	WHEN("Drawing a triangle")
	{
		shape_drawing_lib::CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 });
		painter.Draw(triangle);
		std::ostringstream expectedOutput;
		expectedOutput << "<draw>" << std::endl
			<< "<line fromX=\"10\" fromY=\"15\" toX=\"100\" toY=\"200\"/>" << std::endl
			<< "<line fromX=\"100\" fromY=\"200\" toX=\"150\" toY=\"250\"/>" << std::endl
			<< "<line fromX=\"150\" fromY=\"250\" toX=\"10\" toY=\"15\"/>" << std::endl;

		THEN("Rectangle drew")
		{
			CHECK(output.str() == expectedOutput.str());
		}
	}

	WHEN("Drawing a rectangle")
	{
		shape_drawing_lib::CRectangle rectangle({ 30, 40 }, 18, 24);
		painter.Draw(rectangle);
		std::ostringstream expectedOutput;
		expectedOutput << "<draw>" << std::endl
			<< "<line fromX=\"30\" fromY=\"40\" toX=\"48\" toY=\"40\"/>" << std::endl
			<< "<line fromX=\"48\" fromY=\"40\" toX=\"48\" toY=\"64\"/>" << std::endl
			<< "<line fromX=\"48\" fromY=\"64\" toX=\"30\" toY=\"64\"/>" << std::endl
			<< "<line fromX=\"30\" fromY=\"64\" toX=\"30\" toY=\"40\"/>" << std::endl;

		THEN("Triangel drew")
		{
			CHECK(output.str() == expectedOutput.str());
		}
	}
}