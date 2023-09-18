#include "CCommandHandler.h"
#include "common.h"

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
	separatorPos = paramsString.find(' ');
	while (separatorPos != string::npos)
	{
		params.push_back(Trim(paramsString.substr(0, separatorPos)));
		paramsString = Trim(paramsString.substr(separatorPos + 1));
		separatorPos = paramsString.find(' ');
	}
	params.push_back(paramsString);

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
	size_t paramsCount = m_command.params.size();
	if (paramsCount < 4)
	{
		m_output << ERROR_PARAMS_COUNT_MESSAGE << endl;
		return;
	}
	string id = m_command.params[0];
	auto color = ParseHex(m_command.params[1]);
	if (color == nullopt)
	{
		m_output << ERROR_SYNTAX_MESSAGE << endl;
		return;
	}
	string shapeType = m_command.params[2];
	vector<double> params;
	string text;
	for (size_t i = 3; i < paramsCount; i++)
	{
		auto number = StringToDouble(m_command.params[i]);
		if (!number)
		{
			text = m_command.params[i];
		}
		params.push_back(*number);
	}

	m_picture.AddShape(id, CColor(*color), shapeType, CShapeParams(std::move(params), std::move(text)));
}

void CCommandHandler::MoveShape()
{
	if (m_command.params.size() < 3)
	{
		m_output << ERROR_PARAMS_COUNT_MESSAGE << endl;
		return;
	}
	string id = m_command.params[0];
	auto dx = StringToDouble(m_command.params[1]);
	auto dy = StringToDouble(m_command.params[2]);
	if (!dx || !dy)
	{
		m_output << ERROR_SYNTAX_MESSAGE << endl;
		return;
	}
	m_picture.MoveShape(id, { *dx, *dy });
}

void CCommandHandler::MovePicture()
{
	if (m_command.params.size() < 2)
	{
		m_output << ERROR_PARAMS_COUNT_MESSAGE << endl;
		return;
	}
	auto dx = StringToDouble(m_command.params[1]);
	auto dy = StringToDouble(m_command.params[2]);
	if (!dx || !dy)
	{
		m_output << ERROR_SYNTAX_MESSAGE << endl;
		return;
	}
	m_picture.MovePicture({ *dx, *dy });
}

void CCommandHandler::DeleteShape()
{
	if (m_command.params.size() < 1)
	{
		m_output << ERROR_PARAMS_COUNT_MESSAGE << endl;
		return;
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
		m_output << ERROR_PARAMS_COUNT_MESSAGE << endl;
		return;
	}
	string id = m_command.params[0];
	auto color = ParseHex(m_command.params[1]);
	if (color == nullopt)
	{
		m_output << ERROR_SYNTAX_MESSAGE << endl;
		return;
	}
	m_picture.ChangeColor(id, CColor(*color));
}

void CCommandHandler::ChangeShape()
{
	size_t paramsCount = m_command.params.size();
	if (paramsCount < 3)
	{
		m_output << ERROR_PARAMS_COUNT_MESSAGE << endl;
		return;
	}
	string id = m_command.params[0];
	string shapeType = m_command.params[1];
	vector<double> params;
	string text;
	for (size_t i = 2; i < paramsCount; i++)
	{
		auto number = StringToDouble(m_command.params[i]);
		if (!number)
		{
			text = m_command.params[i];
		}
		params.push_back(*number);
	}

	m_picture.ChangeShape(id, shapeType, CShapeParams(std::move(params), std::move(text)));
}

void CCommandHandler::DrawShape()
{
	if (m_command.params.size() < 1)
	{
		m_output << ERROR_PARAMS_COUNT_MESSAGE << endl;
		return;
	}
	string id = m_command.params[0];
	m_picture.DrawShape(m_canvas, id);
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
		m_output << UNKNOWN_COMMAND_MESSAGE << endl;
	}
}


void CCommandHandler::StartListening()
{
	ReadUserCommand();
	while (m_command.keyWord != EXIT_COMMAND)
	{
		ProcessUserCommand();
		ReadUserCommand();
	}
}