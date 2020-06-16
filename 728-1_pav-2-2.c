#include <stdio.h>

int main()
{
    double n, x, count = 0, i;
    int vozvrat;
    vozvrat = scanf("%lf", &n);
    for(i = 1; i<=n; i++){
        vozvrat = scanf("%lf", &x);
        count = count+(x-i);
    }
    printf("%lf", count);
    return 0;
}