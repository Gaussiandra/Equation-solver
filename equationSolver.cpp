#include <cstdio>
#include <cmath>
#include <cassert>
#include "equationSolver.hpp"

const double EPS = 1e-9;

int main() {
    if (!testsPassed()) {
        return 1;
    }
    printf("This program solves quadratic equation.\n\n");

    double a = 0, b = 0, c = 0;
    printf("Enter three coefficients to get roots:");
    scanf("%lg%lg%lg", &a, &b, &c);

    double root1 = 0, root2 = 0;
    NROOTS_STATUS nRoots = solveQuadraticEquation(a, b, c, &root1, &root2);

    switch(nRoots) {
        case ZERO_ROOTS:
            printf("No roots were found.\n");
            break;
        case ONE_ROOT:
            printf("One root was found. x = %.4lg.\n", root1);
            break;
        case TWO_ROOTS:
            printf("Two roots were found. x1 = %.4lg, x2 = %.4lg.\n", root1, root2);
            break;
        case INF_ROOTS:
            printf("There are an infinite number of roots.\n");
            break;
        default:
            printf("main(): unknown nRoots value found!");
            return 1;
    }

    return 0;
}

/**
 * Checks whether doubles are equal with precision.
 * @a, @b - doubles to check for equality.
 */
bool isEqual(double a, double b, double eps = EPS) {
    return fabs(a - b) < eps;
}

/**
 * Check corner cases in solveQuadraticEquation function.
 */
bool testsPassed() {
    struct testData {
        double a, b, c, root1, root2;
        NROOTS_STATUS status;
    };

    bool hasErrors = false;
    testData tests[] = {
            {1, 3, -4,  1, -4, TWO_ROOTS},  // x^2 + 3x - 4, quadratic main case
            {0, 2, -2,  1,  0, ONE_ROOT},   // 2x - 2, linear main case
            {1, 2,  1, -1,  0, ONE_ROOT},   // x^2 + 2x + 1, D = 0
            {1, 2,  3,  0,  0, ZERO_ROOTS}, // x^2 + 2x + 3, quadratic zero roots case
            {0, 0, 30,  0,  0, ZERO_ROOTS}, // 30, linear zero roots case
            {0, 0,  0,  0,  0, INF_ROOTS},  // 0, the degenerate case
    };

    int szTests = sizeof(tests) / sizeof(tests[0]);
    for (int i = 0; i < szTests; ++i) {
        double curRoot1 = 0, curRoot2 = 0;
        NROOTS_STATUS resultStatus = solveQuadraticEquation(
                tests[i].a, tests[i].b, tests[i].c, &curRoot1, &curRoot2);

       if (tests[i].status != resultStatus ||
           tests[i].status == ONE_ROOT && tests[i].root1 != curRoot1 ||
           tests[i].status == TWO_ROOTS && (tests[i].root1 != curRoot1 || tests[i].root2 != curRoot2)) {
           hasErrors = true;
           printf("Test %d was not passed", i + 1);
       }
    }

    return !hasErrors;
}

/**
 * Solves linear equation.
 * @a, @b - coefficients of the equation.
 * @root - calculated root(if it exists) will be put here.
 * @return NROOTS_STATUS of found roots.
 */
NROOTS_STATUS solveLinearEquation(double a, double b, double *root) {
    if (isEqual(a, 0.)) {
        if (isEqual(b, 0.)) {
            return INF_ROOTS;
        }
        return ZERO_ROOTS;
    }

    *root = -b / a;
    return ONE_ROOT;
}

/**
 * Solves quadratic equation.
 * @a, @b, @c - coefficients of the equation.
 * @root1, @root2 - calculated roots(if they exist) will be put here in descending order.
 * @return NROOTS_STATUS of found roots.
 */
NROOTS_STATUS solveQuadraticEquation(double a, double b, double c, double *root1, double *root2) {
    assert(root1 != nullptr && root2 != nullptr);
    assert(root1 != root2);
    assert(std::isfinite(a) && std::isfinite(b) && std::isfinite(c));

    if (isEqual(a, 0)) {
        return solveLinearEquation(b, c, root1);
    }

    double discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        return ZERO_ROOTS;
    }

    if (isEqual(discriminant, 0)) {
        *root1 = -b / (2*a);
        return ONE_ROOT;
    }

    double sqrt_discriminant = sqrt(discriminant);
    *root1 = (-b + sqrt_discriminant) / (2*a);
    *root2 = (-b - sqrt_discriminant) / (2*a);
    return TWO_ROOTS;
}
