#include "analyzeLine.h"

// These lists are likely incomplete, which will cause errors.
QString vowels = "ΆᾺἈἌἎἊἉἍἏἋᾸᾹᾼᾈᾌᾎᾊᾉᾍᾏᾋάᾶὰἀἄἆἂἁἅἇἃᾰᾱᾳᾴᾷᾲᾀᾄᾆᾂᾁᾅᾇᾃΈῈἘἜἚἙἝἛέὲἐἔἒἑἕἓΉῊἨἬἮἪἩἭἯἫῌᾘᾜᾞᾚᾙᾝᾟᾛᾒᾑᾕᾗᾓήἥὴῃἤἡἦἠῆἢἣῇἧᾐῂῄᾔᾖΊῚἸἼἾἺἹἽἿἻῘῙΪίῖὶἰἴἶἲἱἵἷἳῐῑϊΐῗῒΌῸὈὌὊὉὍὋόὸὀὄὂὁὅὃΎῪὙὝὟὛῨῩΫύὺὐὔὖὒὑὕὗῦὓῠῡϋΰῧῢΏῺὨᾨὬὮὪὩὭὯὫῼᾨᾬᾮᾪᾩᾭᾯᾫώῶὼὠὤὦὢὡὥὧὣῳῴῷῲᾠᾤᾦᾢᾡᾥᾧᾣΑαΕεΗηΙιΟοΥυΩω";
QString longVowels = "ᾹᾼᾈᾌᾎᾊᾉᾍᾏᾋᾱᾳᾴᾷᾲᾀᾄᾆᾂᾁᾅᾇᾃΉῊἨἬἮἪἩἭἯἫῌᾘᾜᾞᾚᾙᾝᾟᾛᾒᾑᾕᾗᾓήῃἤἡἦἠῆἣἢῇἧᾐῂᾔῄᾖῙῑῩῡΏῺὨᾨὬὮὪὩὭὯὫῼᾨᾬᾮᾪᾩᾭᾯᾫώῶὼὠὤὦὢὡὥὧὣῳῴῷῲᾠᾤᾦᾢᾡᾥᾧᾣΗηΩωῦᾶἆἇἇἶῖἷῗὖὗῧ";
QString consonants = "ΒβϐΓγΔδΖζΘθϑΚκϰΛλΜμΝνΞξΠπϖΡῬρϱῥῤΣσςΤτΦφϕΧχΨψϜϝ";
QString doubleConsonants = "ΖζΞξΨψ";
QString dipthongs[] = {
    "Αι", "Αἰ", "Αἱ", "Αί", "Αἴ", "Αἵ", "Αὶ", "Αἳ", "Αἲ", "αι", "αἰ", "αἱ", "αί", "αἴ", "αἵ", "αὶ", "αἳ", "αἲ", "αἶ",
    "Αυ", "Αύ", "Αὺ", "Αὐ", "Αὔ", "Αὒ", "Αὑ", "Αὕ", "Αὓ", "αυ", "αύ", "αὺ", "αὐ", "αὔ", "αὒ", "αὑ", "αὕ", "αὓ",
    "Ει", "Εί", "Εὶ", "Εἰ", "Εἴ", "Εἲ", "Εἱ", "Εἵ", "Εἳ", "ει", "εί", "εὶ", "εἰ", "εἴ", "εἲ", "εἱ", "εἵ", "εἳ", "εἶ",
    "Οι", "Οἰ", "Οἱ", "Οί", "Οἴ", "Οἵ", "Οὶ", "Οἳ", "Οἲ", "οι", "οἰ", "οἱ", "οί", "οἴ", "οἵ", "οὶ", "οἳ", "οἲ", "οἶ", "Οἶ", "οἷ", "Οἶ",
    "Υι", "Υἰ", "Υἱ", "Υί", "Υἴ", "Υἵ", "Υὶ", "Υἳ", "Υἲ", "υι", "υἰ", "υἱ", "υί", "υἴ", "υἵ", "υὶ", "υἳ", "υἲ",
    "Ευ", "Εύ", "Εὺ", "Εὐ", "Εὔ", "Εὒ", "Εὑ", "Εὕ", "Εὓ", "ευ", "εύ", "εὺ", "εὐ", "εὔ", "εὒ", "εὑ", "εὕ", "εὓ",
    "Ου", "Ού", "Οὺ", "Οὐ", "Οὔ", "Οὒ", "Οὑ", "Οὕ", "Οὓ", "ου", "ού", "οὺ", "οὐ", "οὔ", "οὒ", "οὑ", "οὕ", "οὓ", "οὗ",
    "Ηυ", "Ηύ", "Ηὺ", "Ηὐ", "Ηὔ", "Ηὒ", "Ηὑ", "Ηὕ", "Ηὓ", "ηυ", "ηύ", "ηὺ", "ηὐ", "ηὔ", "ηὒ", "ηὑ", "ηὕ", "ηὓ",
    "Αῖ", "αῖ", "Αῦ", "αῦ", "Εῖ", "εῖ", "Εῦ", "εῦ", "Οῖ", "οῖ", "Οῦ", "οῦ", "Ηῦ", "ηῦ", "Υῖ", "υῖ", "οὖ", "εὖ", "αὖ", "εὗ", "εἷ"
};

// A plosive followed by a liquid or nasal may or may not count as a double consonant if using iambics or elegy. Some exceptions apply.
QString shortConsonants[] = {
    "Πλ", "Πρ", "Πμ", "Πν", "πλ", "πρ", "πμ", "πν", "Βλ", "Βρ", "Βμ", "Βν", "βλ", "βρ", "βμ", "βν", "ϐλ", "ϐρ",
    "ϐμ", "ϐν", "Φλ", "Φρ", "Φμ", "Φν", "φλ", "φρ", "φμ", "φν", "ϕλ", "ϕρ", "ϕμ", "ϕν", "Τλ", "Τρ", "Τμ", "Τν",
    "τλ", "τρ", "τμ", "τν", "Δλ", "Δρ", "δλ", "δρ", "Θλ", "Θρ", "Θμ", "Θν", "θλ", "θρ",
    "θμ", "θν", "ϑλ", "ϑρ", "ϑμ", "ϑν", "Κλ", "Κρ", "Κμ", "Κν", "κλ", "κρ", "κμ", "κν", "ϰλ", "ϰρ", "ϰμ", "ϰν",
    "Γλ", "Γρ", "γλ", "γρ", "Χλ", "Χρ", "Χμ", "Χν", "χλ", "χρ", "χμ", "χν"
};

//Potential synizesis
QString synizesisCombos[] = {
    "εω", "έω", "εῶ", "εώ", "έῳ"
};

/**
 * Splits a line of poetry into syllables for metric analysis
 * Example: "ἄνδρα μοι ἔννεπε, μοῦσα, πολύτροπον, ὃς μάλα πολλὰ" -> "ἄνδρ", "α μ", "οι ", "ἔνν","επ"...
 *
 * @param line  the line to be split
 * @return vector of split strings
 */
QVector<QString> splitLine(QString line, bool synizesis)
{
    QVector<QString> syllables;

    // Keep only vowels, consonants, and spaces
    QString cleanedLine;
    QString forgotten;
    for (QChar c : line) {
        if (vowels.contains(c) || consonants.contains(c) || c == ' ')
            cleanedLine.append(c);
    }

    // Split syllables
    bool foundFirstVowel = false;
    QString temp;
    for (int i = 0; i < cleanedLine.size(); i++) {
        QChar c = cleanedLine[i];
        if (!foundFirstVowel) {
            if (vowels.contains(c))
                foundFirstVowel = true;
            else
                temp.append(c);
        }
        if(foundFirstVowel) {
            if (vowels.contains(c)) {
                // Check for dipthongs
                if(i != cleanedLine.size()-1)
                {
                    QString potentialDipthong;
                    potentialDipthong.append(c);
                    potentialDipthong.append(cleanedLine[i+1]);
                    if(std::find(std::begin(dipthongs), std::end(dipthongs), potentialDipthong) != std::end(dipthongs)){
                        syllables.append(temp);
                        temp.clear();
                        temp.append(potentialDipthong);
                        i++;
                        continue;
                    }
                    if(synizesis == true && std::find(std::begin(synizesisCombos), std::end(synizesisCombos), potentialDipthong) != std::end(synizesisCombos)){
                        syllables.append(temp);
                        temp.clear();
                        temp.append(potentialDipthong);
                        i++;
                        continue;
                    }
                }
                syllables.append(temp);
                temp.clear();
            }
            temp.append(c);
        }
    }
    if (!temp.isEmpty())
        syllables.append(temp);

    return syllables;
}

/**
 * Finds the natural lengths of each syllable and returns a string.
 * Example: "ἄνδρα μοι ἔννεπε, μοῦσα, πολύτροπον, ὃς μάλα πολλὰ" -> "-u?-uu-uu-uu-uu-u"
 *
 * @param syllables the line to be scanned
 * @param canCorrept    whether correption is allowed
 * @param usesPloLiqRules   whether the plosive-liquid/nasal rule applies
 * @return string with potential lengths (still to be fitted to each format)
 */
QString findLengths(QVector<QString> syllables, bool canCorrept, bool usesPloLiqRules){
    QString lengths = QString("");
    for(int i = 0; i < syllables.length(); i++){
        QString syllable = syllables[i];
        for(int j = 0; j < syllable.length(); j++){
            if(!vowels.contains(syllable[j]))
                continue;
            // If the vowel is long
            else if(longVowels.contains(syllable[j])){
                if(canCorrept && j < syllable.length()-1 && syllable[j+1] == ' ' && j+2 == syllable.length())
                    lengths.push_back("?");
                else
                    lengths.push_back("-");
                break;
            }
            // If the vowel is short
            else{
                // Dipthong
                if(j < syllable.length()-1 && vowels.contains(syllable[j+1])){
                    if(canCorrept && j < syllable.length()-2 && syllable[j+2] == ' ' && j+3 == syllable.length())
                        lengths.push_back("?");
                    else
                        lengths.push_back("-");
                    break;
                }
                // Non-dipthong
                else{
                    int numConsonants = 0;
                    bool followsPLrules = false;
                    for(int k = j; k < syllable.length(); k++){
                        if(consonants.contains(syllable[k])){
                            numConsonants++;
                            if(doubleConsonants.contains(syllable[k]))
                                numConsonants++;
                        }
                        if(usesPloLiqRules && k > 0){
                            QString potentialShortCombination;
                            potentialShortCombination.append(syllable[k-1]);
                            potentialShortCombination.append(syllable[k]);
                            if(std::find(std::begin(shortConsonants), std::end(shortConsonants), potentialShortCombination) != std::end(shortConsonants)){
                                numConsonants--;
                                followsPLrules = true;
                            }
                        }
                    }
                    if(numConsonants > 1)
                        lengths.push_back("-");
                    else if(followsPLrules)
                        lengths.push_back("?");
                    else
                        lengths.push_back("u");
                    break;
                }
            }
        }
    }
    return lengths;
}
