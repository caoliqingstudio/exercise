#include <stdio.h>
int main(int argc, char const *argv[])
{
	int t;
	double p;
	scanf("%d",&t);
	while(t--){
		scanf("%lf",&p);
		printf("%d\n",(int)(1/p+1/(1-p)-0.5));
	}
	return 0;
}
