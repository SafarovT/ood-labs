#pragma once
#include "modern_graphics_lib.h"
#include "graphics_lib.h"

class CModernGraphicsRendererAdapter
    : public graphics_lib::ICanvas
    , private modern_graphics_lib::CModernGraphicsRenderer
{
public:
    CModernGraphicsRendererAdapter(std::ostream& strm)
        : modern_graphics_lib::CModernGraphicsRenderer(strm)
        , m_currentPoint(0, 0)
        , m_color(0, 0, 0, 0)
    {
        BeginDraw();
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
            DrawLine(m_currentPoint, endPoint, m_color);
            m_currentPoint = endPoint;
        }
        catch (std::exception& e)
        {
        }
    }

    void SetColor(uint32_t rgbColor) override
    {
        m_color =
        {
            static_cast<float>((rgbColor >> 16) / 255.0),
            static_cast<float>(((rgbColor >> 8) & 0xFF) / 255.0),
            static_cast<float>((rgbColor & 0xFF) / 255.0),
            1,
        };
    }

private:
    modern_graphics_lib::CPoint m_currentPoint;
    modern_graphics_lib::CRGBAColor m_color;
};