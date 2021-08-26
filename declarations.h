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