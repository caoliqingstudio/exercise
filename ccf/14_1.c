#include <stdio.h>

int main(){
	int n,x;
	int a[500],b[500];
	int na=0,nb=0;
	scanf("%d",&n);
	int i,j;
	int result=0;
	for (i = 0; i < n; ++i)
	{
		scanf("%d",&x);
		if (x>0)
		{
			a[na++]=x;
		}else{
			b[nb++]=x;
		}
	}
	if(na>nb)
	{
		for(i=0;i<na;i++)
		{
			for (j = 0; j < nb; ++j)
			{
				if (!(a[i]+b[j]))
				{
					result++;
					break;
				}
			}
		}
	}else{
		for(i=0;i<nb;i++)
		{
			for (j = 0; j < na; ++j)
			{
				if (!(b[i]+a[j]))
				{
					result++;
					break;
				}
			}
		}
	}
	printf("%d",result );
	return 0;
}