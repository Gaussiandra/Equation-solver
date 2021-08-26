enum NROOTS_STATUS {
    ZERO_ROOTS = 0,
    ONE_ROOT,
    TWO_ROOTS,
    INF_ROOTS,
};

bool isEqual(double a, double b, double eps);
bool testsPassed();
NROOTS_STATUS solveLinearEquation(double a, double b, double *root);
NROOTS_STATUS solveQuadraticEquation(double a, double b, double c, double *root1, double *root2);