#pragma once
#include "CPictureDraft.h"
#include "ICanvas.h"
#include <string>

class CClient
{
public:
	CClient(ICanvas& canvas)
		: m_canvas(&canvas)
	{}

	CClient() = default;

	void SetDraft(CPictureDraft const& draft)
	{
		m_draft = draft;
	}

	std::string DrawPicture() const
	{
		
	}

private:
	ICanvas* m_canvas = nullptr;
	CPictureDraft m_draft;
};