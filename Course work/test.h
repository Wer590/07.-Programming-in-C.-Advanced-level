#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <math.h>
#include "math_utils.h"

// Макрос для проверки условий
#define ASSERT_EQUAL(actual, expected, tolerance) \
    if (fabs((actual) - (expected)) > (tolerance)) { \
        printf("Test failed: %s (line %d): Expected %.6f, got %.6f\n", __func__, __LINE__, (expected), (actual)); \
        return 1; \
    }

// Тест функции root
int test_root();

// Тест функции integral
int test_integral();

#endif // TEST_H