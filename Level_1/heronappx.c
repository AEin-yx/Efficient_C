#include <stdlib.h>
#include <stdio.h>
#include <tgmath.h>

int main(void) {
    const double eps = 1E-9;
    const double a = 34.0;
    double x = 1.0 / a; // Start with the true reciprocal (to ensure convergence)

    int max_iter = 100;
    int i = 0;

    while (fabs(1.0 - a * x) >= eps && i++ < max_iter) {
        printf("Iteration %2d: x = %.10f, error = %.10f\n", i, x, fabs(1.0 - a * x));
        x *= (2.0 - a * x);
    }

    if (i >= max_iter) {
        printf("Failed to converge after %d iterations\n", max_iter);
    } else {
        printf("Heron approximation of 1/%.1f is %.10f\n", a, x);
        printf("Actual value is %.10f\n", 1.0 / a);
    }

    return EXIT_SUCCESS;
}
