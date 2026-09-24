#ifndef SECANTMETHOD_H
#define SECANTMETHOD_H

#include <functional>

class SecantMethod {
public:
    // Решение f(x) = 0 методом секущих
    // Возвращает корень или NaN, если не сошлось
    static double solve(std::function<double(double)> f,
                        double x0, double x1,
                        double eps = 1e-6,
                        int maxIter = 100);

    // Классическая функция f(x) = x^3 - 2x - 5
    static double defaultFunction(double x);
};

#endif // SECANTMETHOD_H