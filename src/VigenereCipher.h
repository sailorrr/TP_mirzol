#ifndef VIGENERECIPHER_H
#define VIGENERECIPHER_H

#include <QString>

class VigenereCipher {
public:
    // Шифрование текста ключом
    static QString encrypt(const QString& text, const QString& key);

    // Расшифровка текста ключом
    static QString decrypt(const QString& text, const QString& key);

private:
    // Сдвиг одной буквы
    static QChar shiftChar(QChar c, QChar keyChar, bool encrypt);
};

#endif // VIGENERECIPHER_H