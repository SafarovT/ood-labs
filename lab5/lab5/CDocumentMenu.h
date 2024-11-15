#pragma once
#include <iostream>
#include <sstream>
#include <vector>
#include "CDocument.h"

class CDocumentMenu
{
public:
    CDocumentMenu(std::shared_ptr<IDocument> document)
        : m_document(document)
    {}

    void ListenUserInput()
    {
        HandleHelp();
        std::string input;
        bool stop = false;
        while (!stop)
        {
            std::cout << "> ";
            std::getline(std::cin, input);
            try
            {
                stop = !ProcessCommand(input);
            }
            catch (const std::exception& e)
            {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
        std::cout << "The end." << std::endl;
    }

private:
    std::shared_ptr<IDocument> m_document;

    enum class CommandType
    {
        InsertParagraph,
        InsertImage,
        SetTitle,
        List,
        ReplaceText,
        ResizeImage,
        DeleteItem,
        Help,
        Undo,
        Redo,
        Save,
        Exit,
        Unknown
    };

    static void LeftTrim(std::string& s)
    {
        s.erase
        (
            s.begin(),
            std::find_if(s.begin(), s.end(), [](unsigned char ch) {return !std::isspace(ch); }
        ));
    }

    bool ProcessCommand(const std::string& input)
    {
        std::istringstream stream(input);
        std::string commandName;
        stream >> commandName;

        CommandType commandType = ParseCommandType(commandName);

        switch (commandType)
        {
        case CommandType::InsertParagraph:
            HandleInsertParagraph(stream);
            break;
        case CommandType::InsertImage:
            HandleInsertImage(stream);
            break;
        case CommandType::SetTitle:
            HandleSetTitle(stream);
            break;
        case CommandType::List:
            HandleList();
            break;
        case CommandType::ReplaceText:
            HandleReplaceText(stream);
            break;
        case CommandType::ResizeImage:
            HandleResizeImage(stream);
            break;
        case CommandType::DeleteItem:
            HandleDeleteItem(stream);
            break;
        case CommandType::Help:
            HandleHelp();
            break;
        case CommandType::Undo:
            HandleUndo();
            break;
        case CommandType::Redo:
            HandleRedo();
            break;
        case CommandType::Save:
            HandleSave(stream);
            break;
        case CommandType::Exit:
            return false; 
        case CommandType::Unknown:
            std::cout << "Unknown command. Enter Help to see list of commands." << std::endl;
            break;
        }
        return true;
    }

    CommandType ParseCommandType(const std::string& command)
    {
        if (command == "InsertParagraph") return CommandType::InsertParagraph;
        if (command == "InsertImage") return CommandType::InsertImage;
        if (command == "SetTitle") return CommandType::SetTitle;
        if (command == "List") return CommandType::List;
        if (command == "ReplaceText") return CommandType::ReplaceText;
        if (command == "ResizeImage") return CommandType::ResizeImage;
        if (command == "DeleteItem") return CommandType::DeleteItem;
        if (command == "Help") return CommandType::Help;
        if (command == "Undo") return CommandType::Undo;
        if (command == "Redo") return CommandType::Redo;
        if (command == "Save") return CommandType::Save;
        if (command == "Exit") return CommandType::Exit;
        return CommandType::Unknown;
    }

    std::optional<size_t> StringToSizeT(const std::string& str)
    {
        try
        {
            size_t value = std::stoul(str);
            return value;
        }
        catch (const std::invalid_argument& e)
        {}
        catch (const std::out_of_range& e)
        {
            std::cout << "Position number is out of range, it will be placed in the end" << std::endl;
        }

        return std::nullopt;
    }

    void HandleInsertParagraph(std::istringstream& stream)
    {
        std::string position, text;
        stream >> position;
        auto posNumber = StringToSizeT(position);
        std::getline(stream, text);
        LeftTrim(text);

        m_document->InsertParagraph(text, posNumber);
    }

    void HandleInsertImage(std::istringstream& stream)
    {
        std::string position, path;
        int width, height;
        stream >> position >> width >> height >> path;
        auto posNumber = StringToSizeT(position);

        m_document->InsertImage(path, width, height, posNumber);
    }

    void HandleSetTitle(std::istringstream& stream)
    {
        std::string title;
        std::getline(stream, title);
        LeftTrim(title);

        m_document->SetTitle(title);
    }

    void HandleList()
    {
        m_document->List();
    }

    void HandleReplaceText(std::istringstream& stream)
    {
        int position;
        std::string text;
        stream >> position;
        std::getline(stream, text);
        LeftTrim(text);
        try
        {
            auto paragraph = m_document->GetItem(position).GetParagraph();
            if (paragraph != nullptr)
            {
                paragraph->SetText(text);
            }
            else
            {
                std::cout << "Item is not paragraph" << std::endl;
            }
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    void HandleResizeImage(std::istringstream& stream)
    {
        int position, width, height;
        stream >> position >> width >> height;
        try
        {
            auto image = m_document->GetItem(position).GetImage();
            if (image != nullptr)
            {
                image->Resize(width, height);
            }
            else
            {
                std::cout << "Item is not image" << std::endl;
            }
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }

    void HandleDeleteItem(std::istringstream& stream)
    {
        size_t position;
        stream >> position;

        m_document->DeleteItem(position);
    }

    void HandleUndo()
    {
        m_document->Undo();
    }

    void HandleRedo()
    {
        m_document->Redo();
    }

    void HandleSave(std::istringstream& stream)
    {
        std::string path;
        stream >> path;
        
        m_document->Save(path);
    }

    void HandleHelp()
    {
        std::cout << "Available commands:" << std::endl;
        std::cout << "- InsertParagraph <position>|end <text>" << std::endl;
        std::cout << "- InsertImage <position>|end <width> <height> <path/to/image>" << std::endl;
        std::cout << "- SetTitle <title>" << std::endl;
        std::cout << "- List" << std::endl;
        std::cout << "- ReplaceText <position> <text>" << std::endl;
        std::cout << "- ResizeImage <position> <width> <height>" << std::endl;
        std::cout << "- DeleteItem <position>" << std::endl;
        std::cout << "- Help" << std::endl;
        std::cout << "- Undo" << std::endl;
        std::cout << "- Redo" << std::endl;
        std::cout << "- Save <path>" << std::endl;
        std::cout << "- Exit" << std::endl;
    }
};
