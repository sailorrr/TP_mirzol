#ifndef MD5_H
#define MD5_H

#include <QString>

class MD5 {
public:
    // Возвращает md5-хэш строки в hex (32 символа)
    static QString hash(const QString& input);
};

#endif // MD5_H