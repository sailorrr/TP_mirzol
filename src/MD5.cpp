#include "MD5.h"
#include <QCryptographicHash>

QString MD5::hash(const QString& input) {
    QByteArray data = input.toUtf8();
    QByteArray hashBytes = QCryptographicHash::hash(data, QCryptographicHash::Md5);
    return QString::fromLatin1(hashBytes.toHex());
}