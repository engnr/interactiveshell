#include "colors.h"

namespace Engnr {
namespace InteractiveShell {

const char *Clear      = "\e[0m";
const char *Bold       = "\e[1m";
const char *Black      = "\e[30m";
const char *Red        = "\e[31m";
const char *Green      = "\e[32m";
const char *Yellow     = "\e[33m";
const char *Blue       = "\e[34m";
const char *Magenta    = "\e[35m";
const char *Cyan       = "\e[36m";
const char *White      = "\e[37m";
const char *OnBlack    = "\e[40m";
const char *OnRed      = "\e[41m";
const char *OnGreen    = "\e[42m";
const char *OnYellow   = "\e[43m";
const char *OnBlue     = "\e[44m";
const char *OnMagenta  = "\e[45m";
const char *OnCyan     = "\e[46m";
const char *OnWhite    = "\e[47m";

Color Color::clear()
{
    return Color(Clear);
}

Color Color::bold()
{
    return Color(Bold);
}

Color Color::black()
{
    return Color(Black);
}

Color Color::red()
{
    return Color(Red);
}

Color Color::green()
{
    return Color(Green);
}

Color Color::yellow()
{
    return Color(Yellow);
}

Color Color::blue()
{
    return Color(Blue);
}

Color Color::magenta()
{
    return Color(Magenta);
}

Color Color::cyan()
{
    return Color(Cyan);
}

Color Color::white()
{
    return Color(White);
}

Color Color::onBlack()
{
    return Color(OnBlack);
}

Color Color::onRed()
{
    return Color(OnRed);
}

Color Color::onGreen()
{
    return Color(OnGreen);
}

Color Color::onYellow()
{
    return Color(OnYellow);
}

Color Color::onBlue()
{
    return Color(OnBlue);
}

Color Color::onMagenta()
{
    return Color(OnMagenta);
}

Color Color::onCyan()
{
    return Color(OnCyan);
}

Color Color::onWhite()
{
    return Color(OnWhite);
}

Color::Color(const char *color)
{
    m_color = color;
}

const char *Color::color() const
{
    return m_color.constData();
}

} // namespace InteractiveShell
} // namespace Engnr
