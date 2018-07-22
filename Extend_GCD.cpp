#include<bits/stdc++.h>
typedef long long ll;
using namespace std;


ll extend_gcd(ll a, ll b, ll &x , ll &y)
{
    if(b == 0)
    {
        x=1; y=0;
        return a;
    }

    else
    {
        ll r = extend_gcd(b , a%b , y , x);
        y -= x*(a/b);
        
        printf("a*x + b*y :  %lld*%lld + %lld*%lld\n",a,x,b,y);
        //printf("x: %lld y: %lld\n",x,y);
        
        return r;
    }

}



int main(void)
{
    ll a,b;
    ll x,y;
    while(scanf("%lld %lld",&a , &b)!=EOF)
    {
        extend_gcd(a,b,x,y);
        //printf("gcdres:%lld",a*x+b*y ); 

        ll MOD = abs(b);

        ll inv = ( x%MOD + MOD ) % MOD; 
        printf("The inverse of (%lld): %lld\n " , a , inv );
        printf("test res : %lld \n" , a*inv %MOD);

    }

   /* // A test that shows how "%" operator works
    ll MOD = -1e3;
    printf("%lld\n",(ll)(1e3+10)%MOD );
    printf("%lld\n",(ll)(-1e3-10)%MOD );
    printf("%lld\n",(ll)(10)%MOD );
    printf("%lld\n",(ll)(-10)%MOD );
  */
    

    return 0;
}
