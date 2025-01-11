#include "test.h"

// Тест функции root
int test_root() {
    int iterations;

    // Тест 1: Корень уравнения f1(x) = f2(x) на интервале [0, 4]
    double root1 = root(f1, f2, df1, df2, 0, 4, 1e-6, &iterations);
    ASSERT_EQUAL(root1, 3.847760, 1e-6); // Ожидаемое значение корня: 3.847760

    // Тест 2: Корень уравнения f2(x) = f3(x) на интервале [1, 5]
    double root2 = root(f2, f3, df2, df3, 1, 5, 1e-6, &iterations);
    ASSERT_EQUAL(root2, 3.243929, 1e-6); // Ожидаемое значение корня: 3.243929

    printf("All root tests passed.\n");
    return 0;
}

// Тест функции integral
int test_integral() {
    // Тест 1: Интеграл f1(x) на интервале [0, 1]
    double integral1 = integral(f1, 0, 1, 1e-6);
    ASSERT_EQUAL(integral1, 3.3, 1e-6); // Ожидаемая площадь: 3.3

    // Тест 2: Интеграл f2(x) на интервале [1, 2]
    double integral2 = integral(f2, 1, 2, 1e-6);
    ASSERT_EQUAL(integral2, -1.25, 1e-6); // Ожидаемая площадь: -1.25

    printf("All integral tests passed.\n");
    return 0;
}
