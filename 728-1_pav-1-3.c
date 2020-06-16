#include <stdio.h>
#include <math.h>

int main() {
    double x, y, z; 
    int vozvrat;
    vozvrat = scanf ("%lf%lf", &x, &y);
    z = pow(x, y);
    printf("%lf", z);
    return 0;
}