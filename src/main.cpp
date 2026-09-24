#include <QCoreApplication>
#include <QDebug>
#include <QVector>

#include "VigenereCipher.h"
#include "MD5.h"
#include "SecantMethod.h"
#include "GraphCycle.h"
#include "ServerStub.h"

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    qDebug() << "===== ТЕСТ 1: Шифр Виженера =====";
    QString encrypted = VigenereCipher::encrypt("HELLO WORLD", "KEY");
    qDebug() << "Зашифровано:" << encrypted;
    QString decrypted = VigenereCipher::decrypt(encrypted, "KEY");
    qDebug() << "Расшифровано:" << decrypted;
    qDebug() << "Совпадает с оригиналом:" << (decrypted == "HELLO WORLD");

    qDebug() << "\n===== ТЕСТ 2: md5 =====";
    QString hash = MD5::hash("hello");
    qDebug() << "md5(\"hello\") =" << hash;
    qDebug() << "Ожидается:      5d41402abc4b2a76b9719d911017c592";

    qDebug() << "\n===== ТЕСТ 3: Метод секущих =====";
    double root = SecantMethod::solve(SecantMethod::defaultFunction, 2.0, 3.0, 1e-6);
    qDebug() << "Корень f(x) = x^3 - 2x - 5:" << root;
    qDebug() << "Ожидается ≈ 2.0945514815";
    qDebug() << "f(root) =" << SecantMethod::defaultFunction(root);

    qDebug() << "\n===== ТЕСТ 4: Проверка цикла в графе =====";
    // Матрица смежности 5x5:
    //   1-2, 1-3, 2-4, 3-4, 3-5
    QVector<QVector<int>> adj = {
        {0, 1, 1, 0, 0},  // 1
        {1, 0, 0, 1, 0},  // 2
        {1, 0, 0, 1, 1},  // 3
        {0, 1, 1, 0, 0},  // 4
        {0, 0, 1, 0, 0}   // 5
    };

    QVector<int> path1 = {0, 2, 3, 1, 0};  // 1-3-4-2-1 — цикл ✅
    QVector<int> path2 = {0, 1, 2};        // 1-2-3 — не цикл ❌ (не замкнут)
    QVector<int> path3 = {0, 4, 2, 0};     // 1-5-3-1 — не цикл ❌ (нет ребра 1-5)

    qDebug() << "Путь [1,3,4,2,1] — цикл?" << GraphCycle::isCycle(adj, path1);
    qDebug() << "Путь [1,2,3]     — цикл?" << GraphCycle::isCycle(adj, path2);
    qDebug() << "Путь [1,5,3,1]   — цикл?" << GraphCycle::isCycle(adj, path3);

    qDebug() << "\n===== ТЕСТ 5: Заглушка сервера =====";
    qDebug() << "Правильный вход:" << ServerStub::processRequest("auth&admin&12345");
    qDebug() << "Неверный пароль:" << ServerStub::processRequest("auth&admin&wrong");

    qDebug() << "\n===== ВСЕ ТЕСТЫ ЗАВЕРШЕНЫ =====";
    return 0;
}