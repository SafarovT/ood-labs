#include <iostream>
#include "CShapeFactory.h"
#include "CDesigner.h"
#include "CCanvas.h"
#include "CPainter.h"

using namespace std;
const string FILE_NAME = "image.svg";

int main()
{
	CShapeFactory shapeFactory;
	CDesigner designer(shapeFactory);
	CPictureDraft draft = designer.CreateDraft(std::cin);
	CCanvas canvas(FILE_NAME);
	CPainter painter;

	painter.DrawPicture(draft, canvas);
	try
	{
		canvas.Save();
	}
	catch (std::exception& e)
	{
		cout << e.what() << endl;
	}

	return EXIT_SUCCESS;
}