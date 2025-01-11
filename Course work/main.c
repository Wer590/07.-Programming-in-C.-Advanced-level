#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "math_utils.h"
#include "test.h"

void print_help() {
    printf("Usage: program [OPTIONS]\n");
    printf("Options:\n");
    printf("  --help          Show this help message\n");
    printf("  --intersections Prints the intersection points of the curves and the number of iterations\n");
    printf("  --test          Performs root and integral function testing\n");
}

int main(int argc, char *argv[]) {
    double epsilon1 = 1e-6, epsilon2 = 1e-6;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;
        } else if (strcmp(argv[i], "--intersections") == 0) {
            int iterations1 = 0, iterations2 = 0, iterations3 = 0;
            double x1, x2, x3;
            x1 = root(f1, f2, df1, df2, 3.5, 4, epsilon1, &iterations1);
            x2 = root(f2, f3, df2, df3, 2.5, 3.5, epsilon1, &iterations2);
            x3 = root(f1, f3, df1, df3, 0, 1, epsilon1, &iterations3);

            printf("Intersection points for equations:\n");
            printf("    f1 = 0.6x + 3\n");
            printf("    f2 = (x - 2)^3 - 1\n");
            printf("    f3 = 3/x\n");
            printf("f1 and f2: x = %.6f (iterations: %d)\n", x1, iterations1);
            printf("f2 and f3: x = %.6f (iterations: %d)\n", x2, iterations2);
            printf("f1 and f3: x = %.6f (iterations: %d)\n", x3, iterations3);

            double area = integral(f1, x1, x2, epsilon2) -
                  integral(f2, x1, x2, epsilon2) -
                  integral(f3, x2, x3, epsilon2);
            printf("Area: %.6f\n", area);
            return 0;
        } else if (strcmp(argv[i], "--test") == 0) {
            int result = 0;

            // Запуск тестов
            result |= test_root();
            result |= test_integral();

            if (result == 0) {
                printf("All tests passed successfully.\n");
                } else {
                    printf("Some tests failed.\n");
                }
                return result;
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            return EXIT_FAILURE;
        }        
    }
    print_help();
    return 0;
}
