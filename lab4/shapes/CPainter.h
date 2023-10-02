#pragma once
#include "ICanvas.h"
#include "CPictureDraft.h"

class CPainter
{
public:
	void DrawPicture(CPictureDraft& draft, ICanvas& canvas) const;
};