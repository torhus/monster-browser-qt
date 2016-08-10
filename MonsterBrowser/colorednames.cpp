/**
 * Decoding of player and server name color codes.
 */

#include "colorednames.h"
using namespace std;


const QString Q3_DEFAULT_NAME("UnnamedPlayer");


const QColor etColors[32] = {
    QColor(  0,   0,   0),
    // red
    QColor(220,   0,   0),
    // green
    QColor(  0, 150,   0),
    // yellow
    QColor(198, 198,   0),
    // blue
    QColor(  0,   0, 204),
    // cyan
    QColor(  0, 204, 204),
    // magenta
    QColor(230,   0, 230),
    // For white color codes we use black.
    QColor(  0,   0,   0),

    // EXTENDED COLORS
    // See http://wolfwiki.anime.net/index.php/Color_Codes

    // #ff7f00 (orange)
    QColor(255, 127,   0),
    // #7f7f7f (grey)
    QColor(127, 127, 127),
    // #bfbfbf (light grey
    QColor(191, 191, 191),
    // Same as the above.
    QColor(191, 191, 191),
    // #007f00 (dark green)
    QColor(  0, 127,   0),
    // #7f7f00
    QColor(127, 127,   0),
    // #00007f
    QColor(  0,   0, 127),
    // #7f0000
    QColor(127,   0,   0),
    // #7f3f00
    QColor(127,  63,   0),
    // #ff9919
    QColor(255, 153,  25),
    // #007f7f
    QColor(  0, 127, 127),
    // #7f007f
    QColor(127,   0, 127),
    // #007fff
    QColor(  0, 127, 255),
    // #7f00ff
    QColor(127,   0, 255),
    // #3399cc
    QColor( 51, 153, 204),
    // #ccffcc
    QColor(204, 255, 204),
    // #006633
    QColor(  0, 102,  51),
    // #ff0033
    QColor(255,   0,  51),
    // #b21919
    QColor(178,  25,  25),
    // #993300
    QColor(153,  51,   0),
    // #cc9933
    QColor(204, 153,  51),
    // #999933
    QColor(153, 153,  51),
    // #ffffbf
    QColor(255, 255, 191),
    // #ffff7f
    QColor(255, 255, 127),
};


/*
 * Parse a string containing color codes.
 */
vector<ColorRange> parseColors(const QString& s, bool useEtColors)
{
    vector<ColorRange> ranges;
    ColorRange range{etColors[7], 0, 0};
    int cleanLength = 0;
    int bitMask = useEtColors ? 31 : 7;

    for (int i=0; i < s.size(); i++) {
        if (s[i] == '^' && (i == s.size()-1 || s[i+1] != '^')) {
            // terminate the previous range
            if (!ranges.empty())
                ranges.back().end = cleanLength - 1;
            if (i == s.size()-1)
                break;

            i++;

            range.start = cleanLength;

            /* The method of getting the index is straight from quake3 1.32b's
             * q_shared.h.
             */
            range.color = etColors[(s[i].cell() - '0') & bitMask];

            ranges.push_back(range);
        }
        else {
            cleanLength++;
        }
    }

    if (ranges.empty())
        ranges.push_back(range);

    // Terminate the last range.
    ranges.back().end = cleanLength - 1;

    return ranges;
}


/*
 *  Strip the color codes from a string.
 */
QString stripColorCodes(const QString& s)
{
    QString name;

    for (int i=0; i < s.size(); i++) {
        if (s[i] == '^' && (i == s.size()-1 || s[i+1] != '^')) {
            i++;
            continue;
        }
        name += s[i];
    }

    if (name.isEmpty())
        name = Q3_DEFAULT_NAME;

    return name;
}
