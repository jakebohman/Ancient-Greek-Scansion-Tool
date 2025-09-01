#ifndef HANDLETEXT_H
#define HANDLETEXT_H

#include <QString>

QString scanDactylicHexameter(QString line, bool synizesis = false);
QString scanDactylicPentameter(QString line, bool synizesis = false);
QString scanLine(QString line, QString meter, int lineNumber = 0);
QString scanText(QString text, QString meter);

#endif // HANDLETEXT_H
