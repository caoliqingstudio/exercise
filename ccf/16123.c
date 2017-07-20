//没有完成，对题意理解有误，写到最后一步发现有问题了
//先停在这里了
#include <stdio.h>

int main(int argc, char const *argv[])
{
	int p;
	char powerName[101][34];
	int power[101];
	int r;
	char role[101][35];
	int roleNum[101];
	int roleInfo[101][11][2];
	int u;
	int roleSonNum[101];
	int roleSon[101][11];
	int q;
	char findRole[35];
	char findPower[35];
	int findLevel;
	int i,j,k,l,m,n;
	char c;
	scanf("%d",&p);
	for (i = 0; i < p; ++i)
	{
		while(!((c=getchar())>='a'&&c<='z'));
		powerName[i][0]=c;
		j=1;
		while((c=getchar())>='a'&&c<='z'){
			powerName[i][j++]=c;
		}
		powerName[i][j]='\0';
		if (c==':')
		{
			scanf("%d",&power[i]);
		}else{
			power[i]=-1;
		}
	}
	scanf("%d",&r);
	for (i = 0; i < r; ++i)
	{
		while(!((c=getchar())>='a'&&c<='z'));
		role[i][0]=c;
		j=1;
		while((c=getchar())>='a'&&c<='z'){
			role[i][j++]=c;
		}
		role[i][j]='\0';
		scanf("%d",&roleNum[i]);
		for (j = 0; j < roleNum[i]; ++j)
		{
			while(!((c=getchar())>='a'&&c<='z'));
			findRole[0]=c;
			k=1;
			while((c=getchar())>='a'&&c<='z'){
				findRole[k++]=c;
			}
			findRole[k]='\0';
			for (l = 0; l < p; ++l)
			{
				if (strcmp(findRole,powerName[l])==0)
				{
					role
					break;
				}
			}
		}
	}
	scanf("%d",&u);
	for (i = 0; i < u; ++i)
	{
		while(!((c=getchar())>='a'&&c<='z'));
		findRole[0]=c;
		k=1;
		while((c=getchar())>='a'&&c<='z'){
			findRole[k++]=c;
		}
		findRole[k]='\0';
		for (l = 0; l < r; ++l)
		{
			if (strcmp(findRole,role[l])==0)
			{
				m=l;
				break;
			}
		}
		scanf("%d",&roleSonNum[i]);
		n=0;
		for (j = 0; j < roleSonNum[i]; ++j)
		{
			while(!((c=getchar())>='a'&&c<='z'));
			findRole[0]=c;
			k=1;
			while((c=getchar())>='a'&&c<='z'){
				findRole[k++]=c;
			}
			findRole[k]='\0';
			for (l = 0; l < r; ++l)
			{
				if (strcmp(findRole,role[l])==0)
				{
					roleSon[m][n++]=l;
					break;
				}
			}
		}
	}
	scanf("%d",&q);
	for (i = 0; i < q; ++i)
	{
		while(!((c=getchar())>='a'&&c<='z'));
		findRole[0]=c;
		k=1;
		while((c=getchar())>='a'&&c<='z'){
			findRole[k++]=c;
		}
		findRole[k]='\0';
		while(!((c=getchar())>='a'&&c<='z'));
		findPower[0]=c;
		k=1;
		while((c=getchar())>='a'&&c<='z'){
			findPower[k++]=c;
		}
		findPower[k]='\0';
		for (l = 0; l < p; ++l)
		{
			if (strcmp(findPower,powerName[l])==0)
			{
				m=l;
				break;
			}
		}
	}
	return 0;
}