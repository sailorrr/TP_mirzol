#ifndef SERVERSTUB_H
#define SERVERSTUB_H

#include <QString>

class ServerStub {
public:
    // Заглушка сервера: авторизация
    // Формат запроса: "auth&login&password"
    // Формат ответа: "auth&ok" или "auth&fail"
    static QString processRequest(const QString& request);

private:
    static QString handleAuth(const QString& login, const QString& password);
};

#endif // SERVERSTUB_H