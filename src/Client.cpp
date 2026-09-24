#include "Client.h"

Client::Client() : m_isLoggedIn(false) {
}

Client& Client::instance() {
    static Client s_instance;
    return s_instance;
}

void Client::setCurrentUser(const QString& login) {
    m_currentUser = login;
    if (!login.isEmpty()) {
        logOperation("Вход пользователя: " + login);
    }
}

QString Client::currentUser() const {
    return m_currentUser;
}

void Client::setLoggedIn(bool status) {
    m_isLoggedIn = status;
    if (!status && !m_currentUser.isEmpty()) {
        logOperation("Выход пользователя: " + m_currentUser);
    }
}

bool Client::isLoggedIn() const {
    return m_isLoggedIn;
}

void Client::logOperation(const QString& operation) {
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    m_history.append(QString("[%1] %2").arg(timestamp, operation));

    if (m_history.size() > 100) {
        m_history.removeFirst();
    }
}

QVector<QString> Client::getHistory() const {
    return m_history;
}

void Client::clearHistory() {
    m_history.clear();
}