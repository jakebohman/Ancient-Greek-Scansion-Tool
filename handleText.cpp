#include <QVector>
#include <QString>
#include "analyzeLine.h"
#include "handleText.h"

/**
 * Scans a line of dactylic hexameter
 * Example: "ἄνδρα μοι ἔννεπε, μοῦσα, πολύτροπον, ὃς μάλα πολλὰ" -> "- u u | - u u | - u u | - u u | - u u | - -"
 *
 * @param line  the line to scan
 * @return the line's scansion
 */
QString scanDactylicHexameter(QString line){
    QVector<QString> syllables = splitLine(line);
    QString lengths = findLengths(syllables, true, true);
    QString savedLengths = lengths;
    if(lengths.length() < 2){
        if(lengths.length() == 0)
            return QString("Not a valid hexameter line");
        return QString("Not a valid hexameter line: " + savedLengths);
    }
    lengths[0] = '-';
    lengths[lengths.length()-1] = '-';
    lengths[lengths.length()-2] = '-';

    // Replace all ?s from potential correption
    for(int i = 1; i < lengths.length() - 2; i++){
        if(lengths[i] == '?'){
            if(lengths[i+1] == 'u' && lengths[i+2] == '-')
                lengths[i] = 'u';
            else if (i > 1 && lengths[i-1] == 'u' && lengths[i-2] == '-')
                lengths[i] = 'u';
            else
                lengths[i] = 'u';
        }
    }

    QString formatted;
    int i = 0;
    int numFeet = 0;
    while (i < lengths.length()) {
        if (i + 2 < lengths.length() && lengths[i+1] == 'u' && lengths[i+2] == 'u') {
            formatted += "- u u";
            i += 3;
            numFeet++;
        } else if (i + 1 < lengths.length() && lengths[i+1] == '-') {
            formatted += "- -";
            i += 2;
            numFeet++;
        } else if (i + 2 < lengths.length() && lengths[i+2] == '-') {
            formatted += "- -";
            i += 2;
            numFeet++;
        } else {
            return QString("Not a valid hexameter line: " + lengths);
        }
        // Add separator if not at end
        if (i < lengths.length())
            formatted += " | ";
    }
    if(numFeet != 6)
        return QString("Not a valid hexameter line: " + lengths);
    return formatted;
}

/**
 * Scans a line of dactylic pentameter.
 * Example: "κόσμον ἐπέων ᾠδὴν ἀντ᾽ ἀγορῆς θέμενος." -> "- u u | - - | - || - u u | - u u | -"
 *
 * @param line  the line to scan
 * @return the line's scansion
 */
QString scanDactylicPentameter(QString line){
    QVector<QString> syllables = splitLine(line);
    QString lengths = findLengths(syllables, true, true);
    QString savedLengths = lengths;
    if(lengths.length() < 2){
        if(lengths.length() == 0)
            return QString("Not a valid pentameter line");
        return QString("Not a valid pentameter line: " + savedLengths);
    }
    lengths[0] = '-';
    lengths[lengths.length()-1] = '-';

    // Replace all ?s from potential correption
    for(int i = 1; i < lengths.length() - 2; i++){
        if(lengths[i] == '?'){
            if(lengths[i+1] == 'u' && lengths[i+2] == '-')
                lengths[i] = 'u';
            else if (i > 1 && lengths[i-1] == 'u' && lengths[i-2] == '-')
                lengths[i] = 'u';
            else
                lengths[i] = '-';
        }
    }

    QString formatted;
    int i = 0;
    int count = 0;
    while (i < lengths.length() && count < 2) {
        if (i + 2 < lengths.length() && lengths[i+1] == 'u' && lengths[i+2] == 'u') {
            formatted += "- u u";
            i += 3;
        } else if (i + 1 < lengths.length() && lengths[i+1] == '-') {
            formatted += "- -";
            i += 2;
        } else if (lengths[i+3] != 'u' ||i + 2 < lengths.length() && lengths[i+2] == '-') {
            formatted += "- -";
            i += 2;
        } else {
            return QString("Not a valid pentameter line: " + savedLengths);
        }
        // Add separator if not at end
        if (i < lengths.length())
            formatted += " | ";
        count++;
    }
    if(lengths.length() != i+8 || lengths[i+2] != 'u' || lengths[i+3] != 'u' || lengths[i+5] != 'u' || lengths[i+6] != 'u')
        return QString("Not a valid pentameter line: " + savedLengths);
    return formatted + "- || - u u | - u u | -";
}

/**
 * Calls the correct function to scan the line's meter
 *
 * @param line  the line to scan
 * @param meter the type of meter
 * @param lineNumber    the line number (relevant for elegiac couplets)
 * @return  the line's scansion
 */
QString scanLine(QString line, QString meter, int lineNumber){
    if(meter == "Dactylic Hexameter")
        return scanDactylicHexameter(line);
    if(meter == "Elegiac Couplet"){
        if(lineNumber % 2 == 1)
            return scanLine(line, QString("Dactylic Hexameter"), lineNumber);
        else
            return scanLine(line, QString("Dactylic Pentameter"), lineNumber);
    }
    if(meter == QString("Dactylic Pentameter"))
        return scanDactylicPentameter(line);

    return QString("Error: unsupported meter type");
}

/**
 * Calls scanLine for each line in the text and outputs the result
 *
 * @param text  the text to scan
 * @param meter the type of meter
 * @return  the scansion
 */
QString scanText(QString text, QString meter){
    QStringList lines = text.split('\n');
    QString result;
    int lineNumber = 1;
    for (const QString& line : lines) {
        if (!line.trimmed().isEmpty()) {
            result += scanLine(line, meter, lineNumber) + "\n";
            lineNumber++;
        }
        else
            result += "\n";
    }
    return result;
}
