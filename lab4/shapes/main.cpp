#include <iostream>
#include "CShapeFactory.h"
#include "CDesigner.h"
#include "CCanvas.h"
#include "CPainter.h"

int main()
{
	CShapeFactory shapeFactory;
	CDesigner designer(shapeFactory);
	CPictureDraft draft = designer.CreateDraft(std::cin);
	CCanvas canvas("image.svg");
	CPainter painter;

	painter.DrawPicture(draft, canvas);

	return EXIT_SUCCESS;
}