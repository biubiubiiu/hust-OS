#include "utils.h"

QString getElidedText(QFont font, QString str, int maxWidth)
{
    QFontMetrics fontWidth(font);
    int width = fontWidth.width(str);
    if(width >= maxWidth)
        str = fontWidth.elidedText(str, Qt::ElideRight, maxWidth);
    return str;
}
