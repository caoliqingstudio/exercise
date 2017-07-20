#include <stdio.h>
int main(int argc, char const *argv[])
{
	int set[21]={0};
	int n;
	int a;
	int i,j,x;
	scanf("%d",&n);
	while(n--){
		scanf("%d",&a);
		for (i = 0; i < 20; ++i)
		{
			if ((a+set[i])<=5)
			{
				break;
			}
		}
		if (i>=20)
		{
			i=0;
			while(a>0){
				if (set[i]<=4)
				{
					set[i]++;
					a--;
					x=i*5+set[i];
					printf("%d ",x);			
				}else{
					i++;
				}
			}
			printf("\n");
		}else{
			x=i*5+1+set[i];
			set[i]+=a;
			while(a--){
				printf("%d ",x++);
			}
			printf("\n");
		}
	}
	return 0;
}