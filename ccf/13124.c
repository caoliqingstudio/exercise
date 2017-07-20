#include <stdio.h>

int main() 
{
	int n;
	scanf("%d", &n);
	long long int kind[5][1000];
	int i = 1,k=0;
	for ( k= 0; k < 5; k++)
		kind[k][0] = 0;
	for (i = 1; i < n; i++) {
		kind[0][i] = (kind[0][i - 1]*2 + 1) % 1000000007;
		kind[1][i] = (kind[1][i - 1] + 1) % 1000000007;
		kind[2][i] = (kind[2][i - 1]*2 + kind[0][i - 1]) % 1000000007;
		kind[3][i] = (kind[3][i - 1]*2 + kind[0][i - 1]+kind[1][i-1]) % 1000000007;
		kind[4][i]=(kind[4][i - 1]*2 + kind[3][i - 1]+kind[2][i-1]) % 1000000007;
	}
	printf("%lld", kind[4][n - 1]);
	return 0;
}
