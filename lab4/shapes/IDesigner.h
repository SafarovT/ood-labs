#pragma once
#include "CPictureDraft.h"

class IDesigner
{
	virtual CPictureDraft CreateDraft(std::istream& strm) const = 0;
};