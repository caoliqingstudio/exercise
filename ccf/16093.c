#include <stdio.h>
int main(int argc, char const *argv[])
{
	struct dingdang{
		int health;
		int attack;
	} xxx1[8],xxx2[8],*state[2][8],*uuu;
	int n,i;
	for (i = 0; i < 8; ++i)
	{
		state[0][i]=&xxx1[i];
		state[1][i]=&xxx2[i];
	}
	xxx1[0].health=30;
	xxx1[0].attack=0;
	xxx2[0].health=30;
	xxx2[0].attack=0;
	char info[15];
	int dingdong[2]={0};
	int who=0,another=1;
	int a,b,c;
	int j;
	char m;
	scanf("%d",&n);
	while(n--){
        while((m=getchar())!='s'&&m!='e'&&m!='a');
		info[0]=m;
		scanf("%s",info+1);
		if (strcmp(info,"summon")==0)
		{
			scanf("%d%d%d",&a,&b,&c);
			dingdong[who]++;
			if (a>=dingdong[who])
			{
				state[who][a]->health=c;
				state[who][a]->attack=b;
			}else{
				i=dingdong[who];
				uuu=state[who][i];
				while(i>a){
					state[who][i]=state[who][i-1];
					i--;
				}
				state[who][a]=uuu;
				state[who][a]->health=c;
				state[who][a]->attack=b;
			}
		}else if (strcmp(info,"attack")==0)
		{
			scanf("%d%d",&a,&b);
			state[who][a]->health-=state[another][b]->attack;
			state[another][b]->health-=state[who][a]->attack;
			if (state[who][a]->health<=0)
			{
				dingdong[who]--;
				i=a;
				uuu=state[who][i];
				while(i<=dingdong[who]){
					state[who][i]=state[who][i+1];
					i++;
				}
				state[who][i]=uuu;
			}
			if (state[another][b]->health<=0)
			{
				dingdong[another]--;
				i=b;
				uuu=state[another][i];
				while(i<=dingdong[another]){
					state[another][i]=state[another][i+1];
					i++;
				}
				state[another][i]=uuu;
			}
		}else if (strcmp(info,"end")==0)
		{
			another=who;
			who=1-who;
		}
	}
	if (state[0][0]->health<=0)
	{
		printf("%d\n",-1);
	}else if (state[1][0]->health<=0)
	{
		printf("%d\n",1);
	}else{
		printf("%d\n",0);
	}
	for (i = 0; i < 2; ++i)
	{
		printf("%d\n",state[i][0]->health);
		printf("%d ",dingdong[i]);
		n=1;
		while(n<=dingdong[i]){
			printf("%d ",state[i][n]->health);
		}
		printf("\n");
	}
	return 0;
}
