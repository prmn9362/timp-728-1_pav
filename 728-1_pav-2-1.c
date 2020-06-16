#include <stdio.h>

int main() {
    double n, x, count = 0, i;
    int vozvrat;
    vozvrat = scanf("%lf", &n);
    for(i = 0; i<n; i++) {
        vozvrat = scanf("%lf", &x);
        if(x<=0){
            count++;
        }
    }
    printf("%lf", count);
    return 0;
}