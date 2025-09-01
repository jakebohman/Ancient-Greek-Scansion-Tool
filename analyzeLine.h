#ifndef ANALYZELINE_H
#define ANALYZELINE_H

#include <QVector>
#include <QString>

QVector<QString> splitLine(QString line, bool synizesis = false);
QString findLengths(QVector<QString> syllables, bool canCorrept = false, bool usesPloLiqRules = false);

#endif // ANALYZELINE_H
