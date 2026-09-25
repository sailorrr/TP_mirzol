#include <QtTest>
#include "../src/ServerStub.h"

class TestServer : public QObject {
    Q_OBJECT

private slots:
    void test_correct_auth() {
        QCOMPARE(ServerStub::processRequest("auth&admin&12345"), QString("auth&ok"));
    }

    void test_wrong_password() {
        QCOMPARE(ServerStub::processRequest("auth&admin&wrong"), QString("auth&fail"));
    }

    void test_wrong_login() {
        QCOMPARE(ServerStub::processRequest("auth&user&12345"), QString("auth&fail"));
    }

    void test_empty_request() {
        QCOMPARE(ServerStub::processRequest(""), QString("error&empty"));
    }

    void test_unknown_command() {
        QCOMPARE(ServerStub::processRequest("unknown&param"), QString("error&unknown_command"));
    }
};

QTEST_MAIN(TestServer)
#include "test_server.moc"