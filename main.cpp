#include <stdio.h>
#include <math.h>
#include <assert.h>

const double EPS = 1e-9;

enum NROOTS_STATUS {
    ZERO_ROOTS,
    ONE_ROOT,
    TWO_ROOTS,
    INF_ROOTS,
};

bool isEqual(double a, double b, double eps = EPS);
void testCornerCases();
NROOTS_STATUS solveLinearEquation(double a, double b, double *root);
NROOTS_STATUS solveQuadraticEquation(double a, double b, double c, double *root1, double *root2);

int main() {
    testCornerCases();
    printf("This program solves quadratic equation.\n\n");

    double a = 0, b = 0, c = 0;
    printf("Enter three coefficients to get roots:");
    scanf("%lg%lg%lg", &a, &b, &c);

    double root1 = 0, root2 = 0;
    NROOTS_STATUS nRoots = solveQuadraticEquation(a, b, c, &root1, &root2);

    switch(nRoots) {
        case TWO_ROOTS:
            printf("Two roots were found. x1 = %.4lg, x2 = %.4lg.\n", root1, root2);
            break;
        case ONE_ROOT:
            printf("One root was found. x = %.4lg.\n", root1);
            break;
        case ZERO_ROOTS:
            printf("No roots were found.\n");
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
bool isEqual(double a, double b, double eps) {
    return abs(a - b) < eps;
}

/**
 * Check corner cases in solveQuadraticEquation function.
 */
void testCornerCases() {
    struct testData {
        double a, b, c, root1, root2;
        NROOTS_STATUS status;
    };

    testData tests[] = {
            {1, 3, -4, 1, -4, TWO_ROOTS},
            {0, 2, -2, 1, 0,  ONE_ROOT},
            {1, 2, 1, -1, 0,  ONE_ROOT},
            {1, 2, 3, 0, 0,   ZERO_ROOTS},
            {0, 0, 30, 0, 0,  ZERO_ROOTS},
            {0, 0, 0, 0, 0,   INF_ROOTS},
    };

    int szTests = sizeof(tests) / sizeof(tests[0]);
    for (int i = 0; i < szTests; ++i) {
        double curRoot1 = 0, curRoot2 = 0;
        NROOTS_STATUS resultStatus = solveQuadraticEquation(
                tests[i].a, tests[i].b, tests[i].c, &curRoot1, &curRoot2);

        assert(tests[i].root1 == curRoot1);
        assert(tests[i].root2 == curRoot2);
        assert(tests[i].status == resultStatus);
    }
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
    assert(isfinite(a) && isfinite(b) && isfinite(c));

    *root1 = 0;
    *root2 = 0;

    if (isEqual(a, 0)) {
        return solveLinearEquation(b, c, root1);
    }

    double discriminant = b*b - 4*a*c;
    if (discriminant < 0) {
        return ZERO_ROOTS;
    }

    if (isEqual(discriminant, 0.)) {
        *root1 = -b / (2*a);
        return ONE_ROOT;
    }

    double sqrt_discriminant = sqrt(discriminant);
    *root1 = (-b + sqrt_discriminant) / (2*a);
    *root2 = (-b - sqrt_discriminant) / (2*a);
    return TWO_ROOTS;
}
