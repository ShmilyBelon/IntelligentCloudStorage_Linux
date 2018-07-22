#include<bits/stdc++.h>
const int len = 8;
const int table_len = 256;
const int maxm = 1e2+10;
int datanum = 2;
typedef unsigned char UC;

UC InverseTable[table_len];

using namespace std;

vector<int>picked;


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

UC inv( UC in)
{
// 0 is self inverting 
    if(in == 0)
        return 0;
    else
        return InverseTable[in];

}


void MakeInverseTable(void)
{
    for(int i=1;i<table_len;i++)
    {
        for(int j=1;j<table_len;j++)
        {
            if(InverseTable[i])
                continue;

            UC mul_res = Multiply(i , j);
            for(int k=1;k<table_len;k++)
            {
                if(j == Multiply(mul_res , k))
                {
                    InverseTable[i] = k;
                }
                        
            
            }
        
        } 
    
    }


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
    ~Matrix(void)
    {
        for(int i=0;i<n;i++)
        {
            a[i].clear();
            inva[i].clear();
        }
        m=n=0;

    }
 

    void clear()
    {
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
                printf("%5d",(int)a[i][j]);
       
            printf("\n");
        }  
    
    }

 
};

Matrix PickLines(Matrix M , vector<int>picked)
{
    Matrix res(datanum,M.m);
    for(int i=0;i<picked.size();i++)
    {
        for(int j=0;j<M.m;j++)
        {
            res.a[i][j] = M.a[picked[i]][j];
        }
    
    }
    return res;

}





int main(void)
{
    
    int n,m;
    MakeInverseTable();

    while(
        printf("PLease input the number of rows(n) and the number of columns(m):\n") , scanf("%d %d",&n ,&m)!=EOF)
    {
   
        datanum = m; //the number of data sets must equals to m
        Matrix C(n,m);//coefficient matrix for encoding

        /*To read matrix C*/
        printf("\nPlease input the matrix of coefficients (named C)  you use to encode the data:\n");
        for(int i=0;i<C.n;i++)
            for(int j=0;j<C.m;j++)
            {
                int t;
                scanf("%d",&t);
                UC x=t;

                C.a[i][j]=x;

            }

        
        /*To read DATA u wanna encode, which is a column vector of datanum(m) rows */
        printf("\nBecause the number of data sets must equals to m,so...\n");
        printf("\nPlease input the data which is a column vector of %d rows  you wanna encode: \n",datanum);
        Matrix DATA(datanum , 1);

        for(int i=0;i<datanum;i++)
        {
            int temp;
            scanf("%d",&temp);
            DATA.a[i][0] = temp;
        }


        /*To encode the DATA and output the result*/
        Matrix encode(C.n,DATA.m);
        encode =  C * DATA;
        printf("\nEncoding result (%d rows  %d columns)\n\n",encode.n,encode.m);

        encode.print();

       
       
        /*For decoding, we must choose some lines of matrix C*/       
        printf("\nNow you need to pick m lines of the matrix you've just input to decode the encoded data.\nThe lines in the matrix are numbered from 1 to n \nThe data to input should be in ascending order:\n");        
        for(int i=0;i<m;i++)
        {
            int temp;
            scanf("%d",&temp);
            picked.push_back(temp-1);
        }

        
        /*To figure out the inverse of a submatrix of C and decode the encoded DATA( actually a submatrix fo DATA) */
        Matrix invC(datanum,datanum);//Obviously only square matrix might have an inverse
        Matrix PickedEncode(datanum, 1) ;
       
        invC  = PickLines(C,picked);
        PickedEncode = PickLines(encode , picked);
        invC.inverse();
        
        printf("The inverse of the submatrix of C you've just picked:\n");
        invC.print();
        picked.clear();

        



        Matrix decode(invC.n,PickedEncode.m) ;
        decode = invC * PickedEncode;

        printf("\n\nAfter decoding:\n"); 
        decode.print();
   
    }

    return 0;

}
