#include "exponentiation.h"
#include <stdlib.h>

int main (int argc, char* argv[])
{

    int p, q, n, a, x;
    if (argc != 5)
    {
        printf ("Format: ./a.out p q x a");
        return 0;
    }

    p = atoi(argv[1]);
    q = atoi(argv[2]);
    x = atoi(argv[3]);
    a = atoi(argv[4]);
    n = p*q;

    printf ("%d\n", exponentiation(a, x, n));
    return 0;
}