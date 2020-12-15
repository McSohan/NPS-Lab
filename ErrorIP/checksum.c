#include <stdio.h>
#include <stdint.h>


unsigned int checksumGenerate (uint16_t *ipHeader)
{
    unsigned int sum = 0;
    ipHeader[5] = 0;
    for (int i =0;i<10;i++)
    {
        sum += ipHeader[i];
        while ((sum>>16))
        {
            sum = (sum & 0xFFFF) + 1u;
        }
    }
    ipHeader[5] = (sum & 0xFFFF);
    ipHeader[5] = ~ipHeader[5];
    return ipHeader[5];
}

int verifyChecksum (uint16_t* ipHeader)
{
    unsigned int sum = 0u;
    for (int i =0;i<10;i++)
    {
        sum += ipHeader[i];
        while ((sum>>16))
        {
            sum = (sum & 0xFFFF) + 1u;
        }
    }
    if (((~sum)&0xffff) == 0u)
        return 1;
    else
        return 0;
    
}

int main ()
{

    uint16_t ipfield[10];
    //these are the ip fields
    unsigned int sum;

    //read input here
    for (int i =0;i<10;i++)
        scanf ("%x", (ipfield+i));
    sum = checksumGenerate (ipfield) & 0xffff;
    printf ("Computed checksum: %x", sum);

    ipfield[0] = 0x0011;

    if (verifyChecksum(ipfield))
        printf ("\nValid checksum");
    else
    {
        printf ("\n invalid checksum");
    }
    

    return 0;
}