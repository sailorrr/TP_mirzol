#include <QtTest>
#include "../src/VigenereCipher.h"

class TestVigenere : public QObject {
    Q_OBJECT

private slots:
    void test_encrypt_changes_text() {
        QString original = "HELLO WORLD";
        QString encrypted = VigenereCipher::encrypt(original, "KEY");
        QVERIFY(encrypted != original);
        QCOMPARE(encrypted.length(), original.length());
    }

    void test_decrypt_roundtrip() {
        QString original = "HELLO WORLD";
        QString key = "KEY";
        QString encrypted = VigenereCipher::encrypt(original, key);
        QString decrypted = VigenereCipher::decrypt(encrypted, key);
        QCOMPARE(decrypted, original);
    }

    void test_roundtrip_long() {
        QString original = "PROGRAMMING IS FUN";
        QString key = "SECRET";
        QString encrypted = VigenereCipher::encrypt(original, key);
        QString decrypted = VigenereCipher::decrypt(encrypted, key);
        QCOMPARE(decrypted, original);
    }

    void test_empty_key() {
        QCOMPARE(VigenereCipher::encrypt("HELLO", ""), QString("HELLO"));
    }

    void test_lowercase_roundtrip() {
        QString original = "hello world";
        QString key = "key";
        QString encrypted = VigenereCipher::encrypt(original, key);
        QString decrypted = VigenereCipher::decrypt(encrypted, key);
        QCOMPARE(decrypted, original);
    }
};

QTEST_MAIN(TestVigenere)
#include "test_vigenere.moc"