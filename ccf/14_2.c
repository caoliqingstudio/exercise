#include <stdio.h>

int main(int argc, char const *argv[])
{
	int x1[10],x2[10],y1[10],y2[10];
	int number[10];
	int n,m;
	int x,y,z;
	int i,j;
	scanf("%d%d",&n,&m);
	for (i = 0; i < n; ++i)
	{
		number[i]=i;
	}
	for (i = 0; i < n; ++i)
	{
		scanf("%d%d%d%d",&x1[i],&y1[i],&x2[i],&y2[i]);
	}
	for (i = 0; i < m; ++i)
	{
		scanf("%d%d",&x,&y);
		for (j = n-1; j>=0; --j)
		{
			if (x >= x1[number[j]]&&x <= x2[number[j]]&&y >= y1[number[j]]&&y <= y2[number[j]])
			{
				z=number[j];
				for (;j<n-1;j++)
				{
					number[j]=number[j++];
				}
				number[n-1]=z;
				break;
			}
		}
		if (j<0)
		{
			printf("IGNORED\n");
		}else{
			printf("%d\n",z+1);
		}
	}
	return 0;
}
