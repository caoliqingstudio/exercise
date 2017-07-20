#include <stdio.h>
int main(int argc, char const *argv[])
{
	int a[1002];
	int n;
	int i,j,k;
	int s=0,result=0;
	int line=1;
	int height=0;
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d",a+i);
	}
	for (i = 0; i < n; ++i)
	{
		height=a[i];
		j=i;
		while(j>=0&&a[j]>=height)--j;
		k=i;
		while(k<n&&a[k]>=height)++k;
		s=height*(k-j-1);
		if (s>result)
		{
			result=s;
		}
	}
	printf("%d",result);
	return 0;
}