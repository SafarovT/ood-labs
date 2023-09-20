#include "CCommandHandler.h"

std::optional<std::string> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid argument count" << std::endl
            << "Usage: shapes.exe <outputFile.txt>" << std::endl;
        return std::nullopt;
    }

    return argv[1];
}

int main(int argc, char* argv[])
{
    auto outputFilePath = ParseArgs(argc, argv);
    if (!outputFilePath)
    {
        return EXIT_FAILURE;
    }

    CCommandHandler handler(std::cin, std::cout, std::move(*outputFilePath));
    try
    {
        handler.StartListening();
    }
    catch (std::exception& exception)
    {
        std::cout << exception.what() << std::endl;
        
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

// TODO: CShapeParams убрать хранение text