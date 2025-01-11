
#include "math_utils.h"

// Реализация функций
double f1(double x)
{ 
    return 0.6 * x + 3; 
}

double f2(double x)
{
    return pow(x - 2, 3) - 1;
}

double f3(double x)
{
    return 3 / x;
}

double df1(double x)
{
    (void)x; // Явно игнорируем параметр
    return 0.6;
}
double df2(double x)
{
    return 3 * pow(x - 2, 2);
}

double df3(double x) 
{
    return -3 / (x * x);
}

// Метод Ньютона для нахождения корней
double root(function f, function g, function df, function dg, double a, double b, double eps, int *iterations) {
    double x = (a + b) / 2.0;
    *iterations = 0;
    while (fabs(f(x) - g(x)) > eps) {
        double df_combined = df(x) - dg(x);
        if (fabs(df_combined) < 1e-10) {
            fprintf(stderr, "Derivative too small\n");
            exit(EXIT_FAILURE);
        }
        x = x - (f(x) - g(x)) / df_combined;
        (*iterations)++;
    }
    return x;
}

// Метод Симпсона для вычисления интеграла
double integral(function f, double a, double b, double eps) {
    int n = 2;
    double h, integral_prev, integral_current = 0.0;
    do {
        integral_prev = integral_current;
        integral_current = 0.0;
        h = (b - a) / n;
        for (int i = 0; i < n; i++) {
            double x0 = a + i * h;
            double x1 = x0 + h;
            integral_current += h / 6.0 * (f(x0) + 4.0 * f((x0 + x1) / 2.0) + f(x1));
        }
        n *= 2;
    } while (fabs(integral_current - integral_prev) > eps);
    return integral_current;
}

