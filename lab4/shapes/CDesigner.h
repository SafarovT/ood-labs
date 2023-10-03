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
		if (!std::getline(strm, input))
		{
			return draft;
		}

		while (input != "exit")
		{
			try
			{
				draft.AddShape(m_factory.CreateShape(input));
			}
			catch (std::exception const& e)
			{
				std::cout << e.what() << std::endl;
			}
			std::getline(strm, input);
		}

		return draft;
	}

private:
	IShapeFactory& m_factory;
};