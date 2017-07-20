#include <stdio.h>
int main(int argc, char const *argv[])
{
	int n;
	int a,b,c,result;
	result=0;
	scanf("%d",&n);
	scanf("%d",&a);
	while(--n){
		scanf("%d",&b);
		c=a>b?a-b:b-a;
		if (c>result)
		{
			result=c;
		}
		a=b;
	}
	printf("%d",result);
	return 0;
}