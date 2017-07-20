#include <stdio.h>

int main(int argc, char const *argv[])
{
	char string[53];
	char c,f;
	int i=0,n,state,number;
	int j=1;
	while((string[i]=getchar())!='\n'){
		if (string[i]==':')
		{
			state=i;
			i--;
		}
	}
	n=i;
	scanf("%d",&number);
	getchar();
	for (; j <= number; ++j)
	{
		printf("Case %d:",j);
		while(getchar()==' ');
		while(getchar()!=' ');
		c=getchar();
		while(c!='\n'){
			if (c=='-')
			{
				c=getchar();
				for (i = 0; i < n; ++i)
				{
					if (c==string[i])
					{
						putchar(' ');
						putchar('-');
						putchar(c);
						if(i>=state)
						{
							getchar();
							putchar(' ');
							while((c=getchar())!=' '&&c!='\n'){
								putchar(c);
							}
						}
						break;
					}
				}
				if (i>=n||c=='\n')
				{
					break;
				}
			}
		}
		putchar('\n');	
	}
	return 0;
}