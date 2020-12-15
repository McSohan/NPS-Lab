#include<stdio.h>
 
int main() {
    int bit[8];
    int rcvbit[8];
    int s,s0,s1,s2,i;

    //scan the bits into proper position
 
    printf("Enter four bit data: \n");
    scanf("%d",&bit[0]);
    scanf("%d",&bit[1]);
    scanf("%d",&bit[2]);
    scanf("%d",&bit[4]);
 
    //calculate R
    bit[6]=bit[0]^bit[2]^bit[4];
	bit[5]=bit[0]^bit[1]^bit[4];
	bit[3]=bit[0]^bit[1]^bit[2];
 
	printf("\nEncoded bits:\n");
    printf ("d3 d2 d1 r2 d0 r1 r0\n");
	for(i=0;i<7;i++)
        printf("%d  ",bit[i]);
 
    printf("\nInput recieved bits: \n");
    for(i=0;i<7;i++)
        scanf("%d",&rcvbit[i]);

    //Calculate syndrome for the recieved msg
 
    s0=rcvbit[6]^rcvbit[4]^rcvbit[2]^rcvbit[0];
	s1=rcvbit[5]^rcvbit[4]^rcvbit[1]^rcvbit[0];
	s2=rcvbit[3]^rcvbit[2]^rcvbit[1]^rcvbit[0];
	s=(s2<<2)+(s1<<1)+s0 ;
 
    if(s==0) {
		printf("\nNo error found!\n");
    }
	else {
        
		printf("\nRecieved sequence: \n");
        printf ("d3 d2 d1 r2 d0 r1 r0\n");
        for(i=0;i<7;i++)
        	printf("%d  ",rcvbit[i]);
        
        printf("\nError in position %d",s);
		
		printf("\nCorrected message :");
 
		//if errorneous bit is 0 we complement it else vice versa
		if(rcvbit[7-s]==0)
			rcvbit[7-s]=1;
        else
			rcvbit[7-s]=0;
		
		for (i=0;i<7;i++) {
			printf("%d",rcvbit[i]);
		}
	}
    printf ("\n");
    return 0;
}