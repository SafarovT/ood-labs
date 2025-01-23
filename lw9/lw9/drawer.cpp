#include "drawer.h"
#include <cstdlib>
#include <cassert>

namespace
{
	int Sign(int value)
	{
		return (0 < value) - (value < 0);
	}

	/**
	 * Ðèñóåò êðóòîé îòðåçîê (äëÿ êîòîðîãî |to.y - from.x| >= |to.x - from.x|).
	 */
	void DrawSteepLine(Image& image, Point from, Point to, char color)
	{
		const int deltaX = std::abs(to.x - from.x);
		const int deltaY = std::abs(to.y - from.y);

		assert(deltaY >= deltaX);

		if (from.y > to.y)
		{ // Êðóòûå îòðåçêè ðèñóåì ñâåðõó âíèç.
			std::swap(from, to);
		}

		const int stepX = Sign(to.x - from.x); // Øàã ïî îñè X (-1, 0 èëè 1).
		const int errorThreshold = deltaY + 1; // Ïîðîã îøèáêè âû÷èñëåíèÿ êîîðäèíàòû X.
		const int deltaErr = deltaX + 1; // Øàã íàêîïëåíèÿ îøèáêè.

		// Êîãäà íà÷àëüííîå çíà÷åíèå îøèáêè íà÷èíàåòñÿ íå ñ 0, à ñ deltaErr/2, îòðåçîê ïîëó÷àåòñÿ êðàñèâåå.
		int error = deltaErr / 2;

		for (Point p = from; p.y <= to.y; ++p.y)
		{
			image.SetPixel({ p.x, p.y }, color);
			assert((p.y != to.y) || (p.x == to.x));

			error += deltaErr; // Íàêàïëèâàåì îøèáêó âû÷èñëåíèÿ êîîðäèíàòû X.

			if (error >= errorThreshold)
			{ // Åñëè âûøëè çà ïðåäåëû òåêóùåé êîîðäèíàòû X
				p.x += stepX; // Ñìåùàåìñÿ ê ñëåäóþùåé êîîðäèíàòå X
				error -= errorThreshold; // Ñáðàñûâàåì îøèáêó
			}
		}
	}

	/**
	 * Ðèñóåò ïîëîãèé îòðåçîê (äëÿ êîòîðîãî |to.y - from.x| >= |to.y - from.y|).
	 */
	void DrawSlopeLine(Image& image, Point from, Point to, char color)
	{
		const int deltaX = std::abs(to.x - from.x);
		const int deltaY = std::abs(to.y - from.y);

		assert(deltaX >= deltaY);

		if (from.x > to.x)
		{ // Ïîëîãèå îòðåçêè ðèñóåì ñëåâà íàïðàâî.
			std::swap(from, to);
		}

		// Ïîëîãèå îòðåçêè ðèñóþòñÿ ïî àíàëîãèè ñ êðóòûìè.

		const int stepY = Sign(to.y - from.y);
		const int errorThreshold = deltaX + 1;
		const int deltaErr = deltaY + 1;

		int error = deltaErr / 2;

		for (Point p = from; p.x <= to.x; ++p.x)
		{
			image.SetPixel({ p.x, p.y }, color);
			assert((p.x != to.x) || (p.y == to.y));

			error += deltaErr;

			if (error >= errorThreshold)
			{
				p.y += stepY;
				error -= errorThreshold;
			}
		}
	}

} // namespace

/**
 * Ðèñóåò îòðåçîê ïðÿìîé ëèíèè ìåæäó òî÷êàìè from è to öâåòîì color íà èçîáðàæåíèè Image.
 *
 * Äëÿ ðèñîâàíèÿ èñïîëüçóåòñÿ àëãîðèòì Áðåçåíõýìà.
 * (https://ru.wikipedia.org/wiki/Àëãîðèòì_Áðåçåíõýìà)
 */
void DrawLine(Image& image, Point from, Point to, char color)
{
	const int deltaX = std::abs(to.x - from.x);
	const int deltaY = std::abs(to.y - from.y);

	if (deltaY > deltaX)
	{ // Îòðåçîê êðóòîé.
		DrawSteepLine(image, from, to, color);
	}
	else
	{ // Îòðåçîê ïîëîãèé.
		DrawSlopeLine(image, from, to, color);
	}
}