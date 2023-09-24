#include "CCommandHandler.h"
#include "common.h"
#include "CShapeStrategyFactory.h"

using namespace std;

CCommandHandler::Command CCommandHandler::ParseUserInput(string const& input)
{
	size_t separatorPos = input.find(' ');
	string keyWord = Trim(input.substr(0, separatorPos));
	Params params;

	if (separatorPos == string::npos)
	{
		return { keyWord, params };
	}

	string paramsString = Trim(input.substr(separatorPos));
	CCommandHandler::Params params = Explode(paramsString, ' ');

	return { keyWord, params };
}

void CCommandHandler::ReadUserCommand()
{
	string commandText;
	do
	{
		getline(m_input, commandText);
	} while (commandText.empty());

	m_command = ParseUserInput(commandText);
}

void CCommandHandler::AddShape()
{
	if (m_command.params.size() < 3)
	{
		throw new std::exception("Invalid argument count");
	}
	string id = m_command.params[0];
	string color = m_command.params[1];
	string shapeType = m_command.params[2];
	
	m_picture.AddShape(id, CColor(color), shapeType, Params(m_command.params.begin() + 3, m_command.params.end()));
}

void CCommandHandler::MoveShape()
{
	if (m_command.params.size() < 3)
	{
		throw new std::exception("Invalid argument count");
	}
	string id = m_command.params[0];
	double dx = StringToDouble(m_command.params[1]);
	double dy = StringToDouble(m_command.params[2]);
	auto shape = m_picture.GetShapeById(id);
	if (shape)
	{
		shape->Move(dx, dy);
	}
}

void CCommandHandler::MovePicture()
{
	if (m_command.params.size() < 2)
	{
		throw new std::exception("Invalid argument count");
	}
	double dx = StringToDouble(m_command.params[1]);
	double dy = StringToDouble(m_command.params[2]);
	m_picture.MovePicture(dx, dy);
}

void CCommandHandler::DeleteShape()
{
	if (m_command.params.size() < 1)
	{
		throw new std::exception("Invalid argument count");
	}
	string id = m_command.params[0];
	m_picture.DeleteShape(id);
}

void CCommandHandler::List()
{
	m_picture.ListShapes(m_output);
}

void CCommandHandler::ChangeColor()
{
	if (m_command.params.size() < 2)
	{
		throw new std::exception("Invalid argument count");
	}
	string id = m_command.params[0];
	string color = m_command.params[1];
	auto shape = m_picture.GetShapeById(id);
	if (shape)
	{
		shape->SetColor(CColor(color));
	}
}

void CCommandHandler::ChangeShape()
{
	if (m_command.params.size() < 3)
	{
		throw new std::exception("Invalid argument count");
	}
	string id = m_command.params[0];
	string shapeType = m_command.params[1];

	auto shape = m_picture.GetShapeById(id);
	if (shape)
	{
		std::unique_ptr<IShapeStrategy> shapeStrategy = CShapeStrategyFactory::CreateShapeStrategy(
			shapeType,
			CCommandHandler::Params(m_command.params.begin() + 2, m_command.params.end())
		);
		shape->SetShapeStrategy(std::move(shapeStrategy));
	}
}

void CCommandHandler::DrawShape()
{
	if (m_command.params.size() < 1)
	{
		throw new std::exception("Invalid argument count");
	}
	string id = m_command.params[0];
	auto shape = m_picture.GetShapeById(id);
	if (shape)
	{
		shape->Draw(m_canvas);
	}
	m_canvas.Save();
}

void CCommandHandler::DrawPicture()
{
	m_picture.DrawPicture(m_canvas);
	m_canvas.Save();
}

void CCommandHandler::ProcessUserCommand()
{
	if (m_command.keyWord == ADD_SHAPE_KEY_WORD)
	{
		AddShape();
	}
	else if (m_command.keyWord == MOVE_SHAPE_KEY_WORD)
	{
		MoveShape();
	}
	else if (m_command.keyWord == MOVE_PICTURE_KEY_WORD)
	{
		MovePicture();
	}
	else if (m_command.keyWord == DELETE_SHAPE_KEY_WORD)
	{
		DeleteShape();
	}
	else if (m_command.keyWord == LIST_KEY_WORD)
	{
		List();
	}
	else if (m_command.keyWord == CHANGE_COLOR_KEY_WORD)
	{
		ChangeColor();
	}
	else if (m_command.keyWord == CHANGE_SHAPE_KEY_WORD)
	{
		ChangeShape();
	}
	else if (m_command.keyWord == DRAW_SHAPE_KEY_WORD)
	{
		DrawShape();
	}
	else if (m_command.keyWord == DRAW_PICTURE_KEY_WORD)
	{
		DrawPicture();
	}
	else
	{
		throw new std::invalid_argument("Unknown command");
	}
}


void CCommandHandler::StartListening()
{
	ReadUserCommand();
	while (m_command.keyWord != EXIT_COMMAND)
	{
		try
		{
			ProcessUserCommand();
		}
		catch (std::exception& e)
		{
			m_output << e.what() << endl;
		}
		ReadUserCommand();
	}
}