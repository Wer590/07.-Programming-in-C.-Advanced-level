#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "math_utils.h"

void print_help() {
    printf("Usage: program [OPTIONS]\n");
    printf("Options:\n");
    printf("  --help         Show this help message\n");
    printf("  --epsilon1=VAL Set root finding precision\n");
    printf("  --epsilon2=VAL Set integration precision\n");
}

int main(int argc, char *argv[]) {
    double epsilon1 = 1e-6, epsilon2 = 1e-6;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0) {
            print_help();
            return 0;
        } else if (strncmp(argv[i], "--epsilon1=", 11) == 0) {
            epsilon1 = atof(argv[i] + 11);
        } else if (strncmp(argv[i], "--epsilon2=", 11) == 0) {
            epsilon2 = atof(argv[i] + 11);
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            return EXIT_FAILURE;
        }
    }

    double points[3][2] = {{-5, -1}, {-1, 1}, {1, 5}};
    int iterations;
    double roots[3];
    for (int i = 0; i < 3; i++) {
        roots[i] = root(f1, f2, df1, df2, points[i][0], points[i][1], epsilon1, &iterations);
        printf("Root %d: x = %.6f (iterations: %d)\n", i + 1, roots[i], iterations);
    }

    double area = integral(f1, roots[0], roots[1], epsilon2) -
                  integral(f2, roots[0], roots[1], epsilon2) +
                  integral(f3, roots[1], roots[2], epsilon2);
    printf("Area: %.6f\n", area);

    return 0;
}
