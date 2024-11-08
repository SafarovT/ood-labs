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

	CPictureDraft CreateDraft(std::istream& stream) const override
	{
		CPictureDraft draft;
		std::string input;
		if (!std::getline(stream, input))
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
			std::getline(stream, input);
		}

		return draft;
	}

private:
	IShapeFactory& m_factory;
};