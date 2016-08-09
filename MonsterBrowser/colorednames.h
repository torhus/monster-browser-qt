#ifndef COLOREDNAMES_H
#define COLOREDNAMES_H

#include <vector>
#include <QColor>
#include <QString>


/* A color and a range to apply it to. */
struct ColorRange {
    QColor color;
    int start;        // The first character this ColorRange applies to.
    int end;          // The last character this ColorRange applies to.
};


std::vector<ColorRange> parseColors(const QString& s, bool useEtColors=false);
QString stripColorCodes(const QString& s);



#endif // COLOREDNAMES_H
