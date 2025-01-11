#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// Тип функции
typedef double (*function)(double);

// Объявления функций
double root(function f, function g, function df, function dg, double a, double b, double eps, int *iterations);
double integral(function f, double a, double b, double eps);

// Уравнения и их производные
double f1(double x);
double f2(double x);
double f3(double x);
double df1(double x);
double df2(double x);
double df3(double x);

#endif // MATH_UTILS_H
