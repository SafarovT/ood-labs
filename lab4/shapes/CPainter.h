#pragma once
#include "ICanvas.h"
#include "CPictureDraft.h"

class CPainter
{
public:
	void DrawPicture(CPictureDraft& draft, ICanvas& canvas) const
	{
		size_t shapesCount = draft.GetShapesCount();
		for (size_t i = 0; i < shapesCount; i++)
		{
			draft.GetShape(shapesCount)->Draw(canvas);
		}
	}
};