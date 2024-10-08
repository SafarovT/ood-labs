#pragma once
#include <optional>

class CRGBAColor
{
public:
    using ColorComponent = unsigned char;

    CRGBAColor(ColorComponent r, ColorComponent g, ColorComponent b, ColorComponent a) :r(r), g(g), b(b), a(a) {}
    ColorComponent r, g, b, a;
};

using CRGBAColorOptional = std::optional<CRGBAColor>;