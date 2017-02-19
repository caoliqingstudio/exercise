#include <stdio.h>
int x[20],n,result;
int digui(int k,int i,int sub){
	int j,count;
	if (k)
	{
		if(k-1) digui(k-1,i+1,sub+x[i]);
		else{
            sub+=x[i];
            for (j = 2; j <=sub/2;j++)
            {
                if (sub%j==0)
                {
                    result++;
                    return 0;
                }

            }
		}
		if (n-i>k+1)
		{
			digui(k,i+1,sub);
		}
	}
	return 0;
}
int main(int argc, char const *argv[])
{
	int t,i=1;
	int k,j;
	scanf("%d",&t);
	while(i<=t){
		result=0;
		scanf("%d%d",&n,&k);
		for (j = 0; j < n; ++j)
		{
			scanf("%d",&x[j]);
		}
		digui(k,0,0);
		printf("Case #%d: %d\n",i++,result);
	}
	return 0;
}
