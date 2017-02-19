#include <stdio.h>

int main(int argc, char const *argv[])
{
	int t,number=1,i,j,k;
	int a,b,temp,length[11]={0};
	char result[11][35];
	scanf("%d",&t);
	while(number<=t){
		scanf("%d%d",&a,&b);
		printf("Case #%d:\n",number++);
		for (i = 2; i <= 10; ++i)
		{
			temp=a;
			for (j = 0; 1; j++)
			{
				result[i][j]=temp%i;
				temp/=i;
				length[i]++;
				if(temp==0){
					result[i][j+1]=20;
					break;
				}
			}
		}
		while(b--)
		{
			temp=0;
			for (i = 2; i <=10; ++i)
			{
				for (j = 0; j < length[i]; ++j)
				{
					result[i][j]+=1;
					if (result[i][j]<i)
					{
						break;
					}else{
						result[i][j]=0;
						if ((++j)>=length[i])
						{
							result[i][j]=1;
							result[i][j+1]=20;
							length[i]++;
							break;
						}
					}
				}
				for (j = 0,k=length[i]-1; j < k; ++j,--k)
				{
					if (result[i][j]!=result[i][k])
					{
						temp--;break;
					}
				}
				temp++;
				if (temp>=2)
				{
					break;
				}
			}
			if(temp>=2){
                for (j = length[i]-1; j >=0; --j)
                {
                    putchar(result[10][j]+'0');
                }
                putchar('\n');
            }
		}
	}
	return 0;
}
