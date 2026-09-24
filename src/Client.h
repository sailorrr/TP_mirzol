#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>
#include <QDateTime>
#include <QVector>

class Client : public QObject {
    Q_OBJECT

public:
    static Client& instance();

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

    void setCurrentUser(const QString& login);
    QString currentUser() const;

    void setLoggedIn(bool status);
    bool isLoggedIn() const;

    void logOperation(const QString& operation);
    QVector<QString> getHistory() const;
    void clearHistory();

private:
    Client();
    ~Client() = default;

    QString m_currentUser;
    bool m_isLoggedIn;
    QVector<QString> m_history;
};

#endif