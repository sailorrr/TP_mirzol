#include "ServerStub.h"
#include <QStringList>

QString ServerStub::processRequest(const QString& request) {
    QStringList parts = request.split('&');

    if (parts.isEmpty()) {
        return "error&empty";
    }

    QString command = parts[0];

    if (command == "auth" && parts.size() >= 3) {
        return handleAuth(parts[1], parts[2]);
    }

    return "error&unknown_command";
}

QString ServerStub::handleAuth(const QString& login, const QString& password) {
    // Заглушка: правильный логин = "admin", пароль = "12345"
    if (login == "admin" && password == "12345") {
        return "auth&ok";
    }
    return "auth&fail";
}