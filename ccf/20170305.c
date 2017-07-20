#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int n,m;
    long long a,b,q,x[1002];
    long long result=0;
    scanf("%d%d",&n,&m);
    scanf("%ld%ld%ld%ld",&a,&b,&q,&x[0]);
    int i;
    for(i=1;i<=m;i++){
        x[i]=((a*x[i-1]+b)mod q);
        result+=x[i];
    }
    printf("%ld",result);
    return 0;
}
