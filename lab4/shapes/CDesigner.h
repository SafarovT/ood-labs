#pragma once
#include "IDesigner.h"

class CDesigner : public IDesigner
{
	CPictureDraft CreateDraft(std::istream& strm) const override;
};