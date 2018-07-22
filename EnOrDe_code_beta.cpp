#include<bits/stdc++.h>
const int len = 8;
const int maxm = 1e2+10;
typedef unsigned char UC;

using namespace std;


unsigned char  Logtable[256] = 
{ 0, 0, 25, 1, 50, 2, 26, 198, 75, 199, 27, 104, 51, 238, 223, 3, 
100, 4, 224, 14, 52, 141, 129, 239, 76, 113, 8, 200, 248, 105, 28, 193, 
125, 194, 29, 181, 249, 185, 39, 106, 77, 228, 166, 114, 154, 201, 9, 120, 
101, 47, 138, 5, 33, 15, 225, 36, 18, 240, 130, 69, 53, 147, 218, 142, 
150, 143, 219, 189, 54, 208, 206, 148, 19, 92, 210, 241, 64, 70, 131, 56, 
102, 221, 253, 48, 191, 6, 139, 98, 179, 37, 226, 152, 34, 136, 145, 16, 
126, 110, 72, 195, 163, 182, 30, 66, 58, 107, 40, 84, 250, 133, 61, 186, 
43, 121, 10, 21, 155, 159, 94, 202, 78, 212, 172, 229, 243, 115, 167, 87, 
175, 88, 168, 80, 244, 234, 214, 116, 79, 174, 233, 213, 231, 230, 173, 232, 
44, 215, 117, 122, 235, 22, 11, 245, 89, 203, 95, 176, 156, 169, 81, 160, 
127, 12, 246, 111, 23, 196, 73, 236, 216, 67, 31, 45, 164, 118, 123, 183, 
204, 187, 62, 90, 251, 96, 177, 134, 59, 82, 161, 108, 170, 85, 41, 157, 
151, 178, 135, 144, 97, 190, 220, 252, 188, 149, 207, 205, 55, 63, 91, 209, 
83, 57, 132, 60, 65, 162, 109, 71, 20, 42, 158, 93, 86, 242, 211, 171, 
68, 17, 146, 217, 35, 32, 46, 137, 180, 124, 184, 38, 119, 153, 227, 165, 
103, 74, 237, 222, 197, 49, 254, 24, 13, 99, 140, 128, 192, 247, 112, 7};

 


unsigned char Alogtable[256] = 
{ 1, 3, 5, 15, 17, 51, 85, 255, 26, 46, 114, 150, 161, 248, 19, 53, 
95, 225, 56, 72, 216, 115, 149, 164, 247, 2, 6, 10, 30, 34, 102, 170, 
229, 52, 92, 228, 55, 89, 235, 38, 106, 190, 217, 112, 144, 171, 230, 49, 
83, 245, 4, 12, 20, 60, 68, 204, 79, 209, 104, 184, 211, 110, 178, 205, 
76, 212, 103, 169, 224, 59, 77, 215, 98, 166, 241, 8, 24, 40, 120, 136, 
131, 158, 185, 208, 107, 189, 220, 127, 129, 152, 179, 206, 73, 219, 118, 154, 
181, 196, 87, 249, 16, 48, 80, 240, 11, 29, 39, 105, 187, 214, 97, 163, 
254, 25, 43, 125, 135, 146, 173, 236, 47, 113, 147, 174, 233, 32, 96, 160, 
251, 22, 58, 78, 210, 109, 183, 194, 93, 231, 50, 86, 250, 21, 63, 65, 
195, 94, 226, 61, 71, 201, 64, 192, 91, 237, 44, 116, 156, 191, 218, 117, 
159, 186, 213, 100, 172, 239, 42, 126, 130, 157, 188, 223, 122, 142, 137, 128, 
155, 182, 193, 88, 232, 35, 101, 175, 234, 37, 111, 177, 200, 67, 197, 84, 
252, 31, 33, 99, 165, 244, 7, 9, 27, 45, 119, 153, 176, 203, 70, 202, 
69, 207, 74, 222, 121, 139, 134, 145, 168, 227, 62, 66, 198, 81, 243, 14, 
18, 54, 90, 238, 41, 123, 141, 140, 143, 138, 133, 148, 167, 242, 13, 23, 
57, 75, 221, 124, 132, 151, 162, 253, 28, 36, 108, 180, 199, 82, 246, 1};

UC  div(UC a,UC b)
{
    int j;
    if (b == 0) 
    {
        printf( "Division by zero\n" );
        abort();
    }
    if (a == 0)
        return (0);
    
    if ((j = Logtable[a] - Logtable[b]) < 0) j += 255;
        return (Alogtable[j]);
}

UC inv(UC in) {
/* 0 is self inverting */
    if(in == 0) 
        return 0;
    else
        return Alogtable[(255 - Logtable[in])];
}



UC MulTwo(UC x)
{
    return ((x<<1) ^ ((x&0x80) ? 0x1b : 0x00 ) );
}

UC Multiply(UC a , UC b )
{
    UC temp = a ,res =0x00;

    for(int i=0;i<len;i++)
    {
        if(b&0x01)
            res ^= temp;
        

        b >>= 1;
        temp = MulTwo(temp);
    }

    return res;

}

struct INVERSE
{

    vector<UC> op_mul (vector<UC>a, UC b)
    {
        int N = a.size();
        vector<UC>res(N,0);

        for(int i=0;i<N;i++)
            res[i] = Multiply(a[i] , b);
        return res;
    }

     vector<UC> op_mi (vector<UC>a  ,  vector<UC> b)
    {
        int N = a.size();
        int N_ = b.size();
        if(N!=N_)
            printf("error!\n");
        vector<UC>res(N,0);

        for(int i=0;i<N;i++)
            res[i] = a[i] ^ b[i];
;

        return res;
    
    }

    void inverse(vector<UC>A[] , vector<UC>C[] , int N)
    {
        for(int i=0;i<N;i++)
           C[i] = vector<UC>(N,0);
        
        for(int i=0;i<N;i++)
            C[i][i] = 1;

        for(int i=0;i<N;i++)
        {
        
            for(int j=i;j<N;j++)
                if(A[j][i]>0)
                {
                    swap(A[i] , A[j]);
                    swap(C[i] , C[j]);
                    break;
                }

            C[i] = op_mul( C[i] ,  inv(A[i][i]) );
            A[i] = op_mul( A[i] ,  inv(A[i][i]) );
            
            
            for(int j=0;j<N;j++)
            {
                if(j!=i&& A[j][i]>0)
                {
                     C[j] = op_mi(C[j] , op_mul( C[i] , A[j][i])) ;
                     A[j] = op_mi(A[j] , op_mul( A[i] , A[j][i])) ;
                }
            }
        }
    }

    
    


};

struct Matrix
{
    int n,m;
    vector<UC> a[maxm] ;
    vector<UC> inva[maxm];
    INVERSE inv;


     Matrix(int nn,int mm)
    {
        this->n=nn;
        this->m=mm;
        
        for(int i=0;i<nn;i++)
            for(int j=0;j<mm;j++)
                a[i].push_back(0);
    }
 
    
    
    

    void clear()
    {
        //m=n=0;
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                a[i][j] = 0;
    }

    Matrix operator + (const Matrix &b) const
    {
        Matrix tmp(n,m);
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
                tmp.a[i][j]=a[i][j] ^ b.a[i][j];

        return tmp;
    }

    Matrix operator - (const Matrix &b) const
    {
        return *(this)+b;
    }

    Matrix operator * (const Matrix &b)const
    {
        Matrix tmp(n,b.m);
        tmp.clear();
       // tmp.n=n;tmp.m=b.m;
        for(int i=0;i<n;i++)
            for(int j=0;j<b.m;j++)
                for(int k=0;k<m;k++)
                    tmp.a[i][j] ^= Multiply(a[i][k] , b.a[k][j]);

        return tmp;
    
    }

    void inverse(void)
    {
        inv.inverse(a,inva,n);
        for(int i=0;i<n;i++)
            a[i]=inva[i];

    
    }

    void print(void)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
                printf(" %d ",(int)a[i][j]);
       
            printf("\n");
        }  
    
    }

 
    void inv_print(void)
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
                printf(" %d ",(int)inva[i][j]);
       
            printf("\n");
        }  
    
    }   

    








};





int main(void)
{
   // printf("1111\n");
    
    int n,m;
    int A,B;
    printf("1111");

    while(scanf("%d %d",&n ,&m)!=EOF)
    {
   

        Matrix C(n,m);
      //  printf("1111\n");
       // m=C.m; n=C.n; 
        for(int i=0;i<C.n;i++)
            for(int j=0;j<C.m;j++)
            {
                int t;
                scanf("%d",&t);
                UC x=t;

                C.a[i][j]=x;

              //  printf(" %d ",(int)C.a[i][j]);
            }

       // C.print();

        
      //  Matrix c(2,2);
      //   for(int i=0;i<2;i++)
      //      for(int j=0;j<2;j++)





        scanf("%d %d",&A,&B);
        Matrix AB(2,1);
     //   AB.n=2;AB.m=1;
        AB.a[0][0]=A;
        AB.a[1][0]=B;

        printf("AB:\n");
        AB.print();


        Matrix encode(2,1);
        encode =  C * AB;
        printf("encode: %d %d\n",encode.n,encode.m);


        encode.print();


        Matrix invC(2,2);
        invC.a[0][0]=3;
        invC.a[0][1]=9;
        invC.a[1][0]=7;
        invC.a[1][1]=90;
        invC.inverse();
        invC.print();



       // Matrix invC(2,2);
       // invC.a = aencode.inva;i


        Matrix E(2,2);
        E = invC * C; 


        printf("E:\n");
        E.print();

        Matrix decode(2,2) ;
         decode = invC * encode;

        printf("decode:\n"); 
        decode.print();

        int asd=0;
        UC qwe = 141;
        qwe = MulTwo(qwe);
        printf("\nqwe: %d\n",qwe);




   
   
    }

    return 0;

}
