#ifndef COLORS_H
#define COLORS_H

#include <QString>

namespace Engnr {
namespace InteractiveShell {

class Color
{
public:
    Color(const char *color);
    const char *color() const;

    static Color clear();
    static Color bold();
    static Color black();
    static Color red();
    static Color green();
    static Color yellow();
    static Color blue();
    static Color magenta();
    static Color cyan();
    static Color white();
    static Color onBlack();
    static Color onRed();
    static Color onGreen();
    static Color onYellow();
    static Color onBlue();
    static Color onMagenta();
    static Color onCyan();
    static Color onWhite();

private:
    QByteArray m_color;
};

typedef QList<Color> Colors;

} // namespace InteractiveShell
} // namespace Engnr

#endif // COLORS_H
