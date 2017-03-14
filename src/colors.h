#ifndef COLORS_H
#define COLORS_H

#include <QString>
#include <QDebug>

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

QDebug operator<<(QDebug debug, const Color &color);
QDebug operator<<(QDebug debug, const Colors &colors);
Colors operator|(const Color &color1, const Color &color2);
Colors operator|(const Colors &colors, const Color &color);

} // namespace InteractiveShell
} // namespace Engnr

#endif // COLORS_H
