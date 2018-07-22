#include<bits/stdc++.h>
const int N = 8;
typedef unsigned char UC;

UC MulTwo(UC x)
{
    return ((x<<1) ^ ( (x&0x80) ? 0x1b : 0x00 ) );
}

/*
UC Multiply(UC a, UC b)
{
    UC temp[8] = {a} , tempM = 0x00;
    
    for(int i=1;i<8;i++)
    {
        temp[i] = MulTwo(temp[i-1]);
    }

    for(int i=0;i<8;i++)
    {
        tempM ^=  ((b>>i)&0x01) ? temp[i] : 0x00;
    }

    return tempM;
}
*/

UC Multiply(UC a , UC b)
{
    UC temp = a , res = 0x00;
    
    for(int i=0;i<N;i++)
    {
        if(b&0x01)
        {
            res ^= temp;
        }
        
        b >>= 1;
        temp = MulTwo(temp);
    }

    return res;



}




int main(void)
{
    int x,y;
    while(scanf("%x %x",&x,&y)!=EOF)
    {
        UC a=x,b=y;
        printf("%x\n",Multiply(a,b^a));
        printf("%x\n",Multiply(a,b)^Multiply(a,a));
   
      //  printf("%x\n",a*(a^b));
      //  printf("%x\n",(a*a)^(a*b) );
   
   
    }

    return 0;
}


