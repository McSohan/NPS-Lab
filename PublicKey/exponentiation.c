#include "exponentiation.h"


int exponentiation (int a, int x, int n)
{
    //computes (a^x) (mod n)
    //perform this in a dynamic programming fashion (make sure that x<1023)
    int dp[1024];
    dp[0] = 1;
    dp[1] = a % n;
    for (int i = 2;i<=x;i++)
    {
        dp[i] = (dp[i/2]*dp[i/2])%n;
        if (i%2)
        {
            dp[i] = (dp[i]*dp[1])%n;
        }
    }
    if (x>=0)
        return dp[x];
    else 
        return 0;
}

