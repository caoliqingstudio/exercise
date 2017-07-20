#include <stdio.h>
int main(int argc, char const *argv[])
{
	int n;
	int a[1010];
	int i,j,x,k;
	scanf("%d",&n);
	scanf("%d",a);
	for ( i = 1; i < n; ++i)
	{
		j=i;
		scanf("%d",&x);
		do{
			a[j]=a[j-1];
			j--;
		}while(j>0&&x<a[j]);
		a[j+1]=x;
	}
	k=n/2;
	x=a[k];
	i=k;
	j=k;
	while(i>=0&&a[i]==x)i--;
	while(j<n&&a[j]==x)j++;
	if ((i+1)==(n-j))
	{
		printf("%d",x );
	}else{
		printf("%d",-1);
	}
	return 0;
}
