#include "VigenereCipher.h"

QString VigenereCipher::encrypt(const QString& text, const QString& key) {
    if (key.isEmpty()) return text;

    QString result;
    int keyIndex = 0;

    for (QChar c : text) {
        if (c.isLetter() && c.unicode() < 128) {
            QChar keyChar = key[keyIndex % key.length()];
            result += shiftChar(c, keyChar, true);
            keyIndex++;
        } else {
            result += c;
        }
    }
    return result;
}

QString VigenereCipher::decrypt(const QString& text, const QString& key) {
    if (key.isEmpty()) return text;

    QString result;
    int keyIndex = 0;

    for (QChar c : text) {
        if (c.isLetter() && c.unicode() < 128) {
            QChar keyChar = key[keyIndex % key.length()];
            result += shiftChar(c, keyChar, false);
            keyIndex++;
        } else {
            result += c;
        }
    }
    return result;
}

QChar VigenereCipher::shiftChar(QChar c, QChar keyChar, bool encrypt) {
    char base = c.isUpper() ? 'A' : 'a';
    char keyBase = keyChar.isUpper() ? 'A' : 'a';

    int shift = keyChar.unicode() - keyBase;
    if (!encrypt) shift = -shift;

    int offset = (c.unicode() - base + shift + 26) % 26;
    return QChar(base + offset);
}