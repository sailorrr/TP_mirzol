#include "SecantMethod.h"
#include <cmath>
#include <limits>

double SecantMethod::defaultFunction(double x) {
    return x * x * x - 2.0 * x - 5.0;
}

double SecantMethod::solve(std::function<double(double)> f,
                           double x0, double x1,
                           double eps, int maxIter) {
    double f0 = f(x0);
    double f1 = f(x1);

    for (int i = 0; i < maxIter; ++i) {
        double denom = f1 - f0;
        if (std::abs(denom) < 1e-15) {
            // Защита от деления на ноль
            return std::numeric_limits<double>::quiet_NaN();
        }

        double x2 = x1 - f1 * (x1 - x0) / denom;
        double f2 = f(x2);

        if (std::abs(f2) <= eps) {
            return x2;
        }

        // Сдвигаем
        x0 = x1; f0 = f1;
        x1 = x2; f1 = f2;
    }

    return std::numeric_limits<double>::quiet_NaN();
}