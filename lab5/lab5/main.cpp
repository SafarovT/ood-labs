#include "CDocumentMenu.h"

int main()
{
    CDocument document;
    CDocumentMenu menu(std::make_shared<CDocument>(document));
    menu.ListenUserInput();

    return EXIT_SUCCESS;
}