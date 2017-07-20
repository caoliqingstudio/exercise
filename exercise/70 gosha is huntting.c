#include <stdio.h>
#define MAXN 2002
#define max(a,b) ((a)>(b)?(a):(b))
#define min(a,b) ((a)<(b)?(a):(b))

	double dp[MAXN][MAXN];

int main(int argc, char const *argv[])
{
	double p_a[MAXN],p_b[MAXN],p_c[MAXN];
	int n,a,b,i,j,k;
	scanf("%d %d %d",&n,&a,&b);
	for (i = 0; i < n; ++i)
	{
		scanf("%lf",&p_a[i]);
	}
	for (i = 0; i < n; ++i)
	{
		scanf("%lf",&p_b[i]);
		p_c[i]=1.0-(1.0-p_a[i])*(1.0-p_b[i]);
	}
	for (i = 0; i < n; ++i)
	{//the number of peg
		for (j = min(i,a); j >= max(0,a-n+i); --j)
		{// a egg
			for (k = min(i,b); k >=max(0,b-n+i); --k)
			{//b egg
				dp[j+1][k]=max(dp[j+1][k],dp[j][k]+p_a[i]);
				dp[j][k+1]=max(dp[j][k+1],dp[j][k]+p_b[i]);
				dp[j+1][k+1]=max(dp[j+1][k+1],dp[j][k]+p_c[i]);
			}
		}
	}
	printf("%g",dp[a][b]);
	return 0;
}
