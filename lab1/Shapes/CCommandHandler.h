#pragma once
#include <istream>
#include <vector>
#include <optional>
#include "CPicture.h"
#include "CCanvas.h"

class CCommandHandler
{
public:
	CCommandHandler(std::istream& input, std::ostream& output, std::string&& outputFilePath)
		: m_input(input)
		, m_output(output)
		, m_canvas(std::move(outputFilePath))
	{
	};

	void StartListening();
private:
	using Params = std::vector<std::string>;
	struct Command
	{
		std::string keyWord;
		Params params;
	};

	Command m_command;
	shapes::CPicture m_picture;
	CCanvas m_canvas;
	std::istream& m_input;
	std::ostream& m_output;

	const std::string BEFORE_USER_INPUT_MESSAGE = ">";
	const std::string UNKNOWN_COMMAND_MESSAGE = "Unknown command";
	const std::string ERROR_PARAMS_COUNT_MESSAGE = "Wrong params count";
	const std::string ERROR_SYNTAX_MESSAGE = "Error syntax";
	const std::string EXIT_COMMAND = "exit";

	const std::string ADD_SHAPE_KEY_WORD = "AddShape";
	const std::string MOVE_SHAPE_KEY_WORD = "MoveShape";
	const std::string MOVE_PICTURE_KEY_WORD = "MovePicture";
	const std::string DELETE_SHAPE_KEY_WORD = "DeleteShape";
	const std::string LIST_KEY_WORD = "List";
	const std::string CHANGE_COLOR_KEY_WORD = "ChangeColor";
	const std::string CHANGE_SHAPE_KEY_WORD = "ChangeShape";
	const std::string DRAW_SHAPE_KEY_WORD = "DrawShape";
	const std::string DRAW_PICTURE_KEY_WORD = "DrawPicture";
	

	static Command ParseUserInput(std::string const& input);

	void ReadUserCommand();
	void ProcessUserCommand();
	void AddShape();
	void MoveShape();
	void MovePicture();
	void DeleteShape();
	void List();
	void ChangeColor();
	void ChangeShape();
	void DrawShape();
	void DrawPicture();
};