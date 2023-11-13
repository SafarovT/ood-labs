#pragma once
#include "modern_graphics_lib.h"
#include "graphics_lib.h"

class CModernGraphicsRendererAdapter : public graphics_lib::ICanvas
{
public:
	CModernGraphicsRendererAdapter(modern_graphics_lib::CModernGraphicsRenderer& canvas)
		: m_canvas(canvas)
        , m_currentPoint(0, 0)
	{
        m_canvas.BeginDraw();
    }

    ~CModernGraphicsRendererAdapter()
    {
        m_canvas.EndDraw();
    }

    void MoveTo(int x, int y) override
    {
        m_currentPoint = modern_graphics_lib::CPoint(x, y);
    }

    void LineTo(int x, int y) override
    {
        modern_graphics_lib::CPoint endPoint(x, y);
        try
        {
            m_canvas.DrawLine(m_currentPoint, endPoint);
            m_currentPoint = endPoint;
        }
        catch (std::exception& e)
        {
        }
    }

private:
	modern_graphics_lib::CModernGraphicsRenderer& m_canvas;
    modern_graphics_lib::CPoint m_currentPoint;

};