#include "exponentiation.h"
#include <stdlib.h>
#include <string.h>

int main (int argc, char* argv[])
{

    int p, q, n, a, x, d, len;
    if (argc != 5)
    {
        printf ("Format: ./a.out p q x d");
        return 0;
    }

    char input[10];
    int arr[10];
    printf ("Enter a string of not more than 9 english alphabets\n");
    scanf ("%s", input);
    len = strlen (input);
    printf ("%d", len);

    p = atoi(argv[1]);
    q = atoi(argv[2]);
    x = atoi(argv[3]);
    d = atoi(argv[4]);
    n = p*q;
    printf ("\nEncrypted message: \n");
    for (int i =0;i<len; i++)
    {
        a = input[i]-'A';
        arr[i] = exponentiation(a, x, n);
        printf ("%d ", arr[i]);
    }
    
    printf ("Decrypting the same message:\n");
    for (int i=0;i<len;i++)
    {
        printf ("%c", (char)(exponentiation(arr[i], d, n)+'A'));
    }
    /*
    */
    return 0;
}
