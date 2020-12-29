#include "exponentiation.h"
#include <stdlib.h>

int main  (int argc, char* argv[])
{
    int q, alpha, xa, xb;
    int ya, yb, key;
    if (argc != 5)
    {
        printf ("Format: ./a.out q alpha xa xb");
        return 0;
    }
    q = atoi(argv[1]);
    alpha = atoi(argv[2]);
    xa = atoi(argv[3]);
    xb = atoi(argv[4]);

    //now we compute for sides A and B
    ya = exponentiation(alpha, xa, q);
    yb = exponentiation (alpha, xb, q);
    printf ("\nYa = %d", ya);
    printf ("\nYb = %d", yb);

    printf ("\nKey computed at A side: %d", exponentiation(yb, xa, q));
    printf ("\nKey computed at B side: %d", exponentiation(ya, xb, q));

    printf ("\nEND\n");

    return 0;
}