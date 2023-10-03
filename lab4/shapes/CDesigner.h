#pragma once
#include <stdexcept>
#include <iostream>
#include "IShapeFactory.h"
#include "IDesigner.h"

class CDesigner : public IDesigner
{
public:
	CDesigner(IShapeFactory& factory)
		: m_factory(factory)
	{}

	CPictureDraft CreateDraft(std::istream& strm) const override
	{
		CPictureDraft draft;
		std::string input;

		while (std::getline(strm, input))
		{
			try
			{
				draft.AddShape(m_factory.CreateShape(input));
			}
			catch (std::exception const& e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		return draft;
	}

private:
	IShapeFactory& m_factory;
};