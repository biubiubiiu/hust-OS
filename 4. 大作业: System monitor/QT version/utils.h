#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QFont>
#include <QFontMetrics>

QString getElidedText(QFont font, QString str, int maxWidth);

#endif // UTILS_H
