#include "utils.h"

/*
 * 功能：返回隐藏过长内容后的字符串
 * 参数：
 * -font：字体信息
 * -str：源字符串
 * -maxWidth：最大显示宽度
 */
QString getElidedText(QFont font, QString str, int maxWidth)
{
    QFontMetrics fontWidth(font);
    int width = fontWidth.width(str);
    if(width >= maxWidth)
        str = fontWidth.elidedText(str, Qt::ElideRight, maxWidth);
    return str;
}

/*
 * 功能：将 cpu tick 的次数转换为 dd-hh-mm-ss 的字符串形式
 * 参数：
 * -tick：cpu 滴答数
 */
QString transformTime(unsigned long tick)
{
    unsigned long seconds = tick / 1000;
    unsigned long minute = 0, hour = 0, day = 0;
    if(seconds >= 60)
    {
        minute = seconds / 60;
        seconds %= 60;
    }
    if(minute >= 60)
    {
        hour = minute / 60;
        minute %= 60;
    }
    if(hour >= 24)
    {
        day = hour / 24;
        hour %= 24;
    }
    QString ret = QString("%1:%2:%3:%4").arg(day, 2, 10, QChar('0'))
                                        .arg(hour, 2, 10, QChar('0'))
                                        .arg(minute, 2, 10, QChar('0'))
                                        .arg(seconds, 2, 10, QChar('0'));
    return ret;
}
