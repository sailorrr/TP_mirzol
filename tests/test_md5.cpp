#include <QtTest>
#include "../src/MD5.h"

class TestMD5 : public QObject {
    Q_OBJECT

private slots:
    void test_hello() {
        QCOMPARE(MD5::hash("hello"), QString("5d41402abc4b2a76b9719d911017c592"));
    }

    void test_empty() {
        QCOMPARE(MD5::hash(""), QString("d41d8cd98f00b204e9800998ecf8427e"));
    }

    void test_table() {
        QCOMPARE(MD5::hash("table"), QString("aab9e1de16f38176f86d7a92ba337a8d"));
    }

    void test_russian() {
        // Проверяем, что кириллица тоже обрабатывается
        QString hash = MD5::hash("привет");
        QVERIFY(hash.length() == 32);
        QVERIFY(hash != MD5::hash("пока"));
    }

    void test_same_input_same_hash() {
        QCOMPARE(MD5::hash("test123"), MD5::hash("test123"));
    }
};

QTEST_MAIN(TestMD5)
#include "test_md5.moc"