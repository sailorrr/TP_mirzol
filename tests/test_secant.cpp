#include <QtTest>
#include <cmath>
#include "../src/SecantMethod.h"

class TestSecant : public QObject {
    Q_OBJECT

private slots:
    void test_default_function_root() {
        double root = SecantMethod::solve(SecantMethod::defaultFunction, 2.0, 3.0, 1e-6);
        QVERIFY(std::abs(root - 2.0945514815) < 1e-3);
    }

    void test_root_is_zero_of_function() {
        double root = SecantMethod::solve(SecantMethod::defaultFunction, 2.0, 3.0, 1e-6);
        double fRoot = SecantMethod::defaultFunction(root);
        QVERIFY(std::abs(fRoot) < 1e-5);
    }

    void test_not_converge() {
        // f(x) = 1 (постоянная) — метод не должен сойтись
        auto constFunc = [](double) { return 1.0; };
        double root = SecantMethod::solve(constFunc, 0.0, 1.0, 1e-6, 10);
        QVERIFY(std::isnan(root));
    }

    void test_different_starting_points() {
        double root1 = SecantMethod::solve(SecantMethod::defaultFunction, 1.0, 4.0, 1e-6);
        double root2 = SecantMethod::solve(SecantMethod::defaultFunction, 2.0, 3.0, 1e-6);
        QVERIFY(std::abs(root1 - root2) < 1e-3);
    }

    void test_accuracy() {
        double root = SecantMethod::solve(SecantMethod::defaultFunction, 2.0, 3.0, 1e-8);
        QVERIFY(std::abs(SecantMethod::defaultFunction(root)) < 1e-7);
    }
};

QTEST_MAIN(TestSecant)
#include "test_secant.moc"