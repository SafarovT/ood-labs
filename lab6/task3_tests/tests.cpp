#include <sstream>
#include "../../external/catch2/catch.hpp"
#include "../task3/CModernGraphicsRendererAdapter.h"
#include "../task3/shape_drawing_lib.h"

SCENARIO("Adapter tests")
{
	std::ostringstream output;
	CModernGraphicsRendererAdapter renderer(output);
	shape_drawing_lib::CCanvasPainter painter(renderer);

	WHEN("Draw nothing")
	{
		THEN("Draw begin, nothing drew")
		{
			CHECK(output.str() == "<draw>\n");
		}
	}

	WHEN("Draw a line with maximum possible color")
	{
		renderer.SetColor(0xFFFFFF);
		renderer.LineTo(10, 15);
		std::ostringstream expectedOutput;
		expectedOutput << "<draw>" << std::endl
			<< "<line fromX=\"0\" fromY=\"0\" toX=\"10\" toY=\"15\">" << std::endl
			<< "  <color r=\"1\" g=\"1\" b=\"1\" a=\"1\" />" << std::endl
			<< "</line>" << std::endl;

		THEN("Color is transformed to (1, 1, 1, 1)")
		{
			CHECK(output.str() == expectedOutput.str());
		}
	}

	WHEN("Draw a line with minumum possible color")
	{
		renderer.SetColor(0);
		renderer.LineTo(10, 15);
		std::ostringstream expectedOutput;
		expectedOutput << "<draw>" << std::endl
			<< "<line fromX=\"0\" fromY=\"0\" toX=\"10\" toY=\"15\">" << std::endl
			<< "  <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />" << std::endl
			<< "</line>" << std::endl;

		THEN("Color is transformed to (0, 0, 0, 1)")
		{
			CHECK(output.str() == expectedOutput.str());
		}
	}

	WHEN("Drawing a triangle without color")
	{
		shape_drawing_lib::CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 });
		painter.Draw(triangle);
		std::ostringstream expectedOutput;
		expectedOutput << "<draw>" << std::endl
			<< "<line fromX=\"10\" fromY=\"15\" toX=\"100\" toY=\"200\">" << std::endl
			<< "  <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />" << std::endl
			<< "</line>" << std::endl
			<< "<line fromX=\"100\" fromY=\"200\" toX=\"150\" toY=\"250\">" << std::endl
			<< "  <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />" << std::endl
			<< "</line>" << std::endl
			<< "<line fromX=\"150\" fromY=\"250\" toX=\"10\" toY=\"15\">" << std::endl
			<< "  <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />" << std::endl
			<< "</line>" << std::endl;

		THEN("Rectangle drew")
		{
			CHECK(output.str() == expectedOutput.str());
		}
	}

	WHEN("Drawing a rectangle")
	{
		shape_drawing_lib::CRectangle rectangle({ 30, 40 }, 18, 24, 0x8811AA);
		painter.Draw(rectangle);
		std::ostringstream expectedOutput;
		expectedOutput << "<draw>" << std::endl
			<< "<line fromX=\"30\" fromY=\"40\" toX=\"48\" toY=\"40\">" << std::endl
			<< "  <color r=\"0.533333\" g=\"0.0666667\" b=\"0.666667\" a=\"1\" />" << std::endl
			<< "</line>" << std::endl
			<< "<line fromX=\"48\" fromY=\"40\" toX=\"48\" toY=\"64\">" << std::endl
			<< "  <color r=\"0.533333\" g=\"0.0666667\" b=\"0.666667\" a=\"1\" />" << std::endl
			<< "</line>" << std::endl
			<< "<line fromX=\"48\" fromY=\"64\" toX=\"30\" toY=\"64\">" << std::endl
			<< "  <color r=\"0.533333\" g=\"0.0666667\" b=\"0.666667\" a=\"1\" />" << std::endl
			<< "</line>" << std::endl
			<< "<line fromX=\"30\" fromY=\"64\" toX=\"30\" toY=\"40\">" << std::endl
			<< "  <color r=\"0.533333\" g=\"0.0666667\" b=\"0.666667\" a=\"1\" />" << std::endl
			<< "</line>" << std::endl;

		THEN("Triangel drew")
		{
			CHECK(output.str() == expectedOutput.str());
		}
	}
}