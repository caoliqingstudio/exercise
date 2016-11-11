#include<stdio.h>
#define M 37
#define N 20
//int nums[M]={1,2,3,4,5,6,7,8,9,7,8,9,4,5,6,1,2,3};

int nums[M]={1,2,3,4,5,6,7,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,9,8,7,6,5,4,3,2,1,2,3,4,5,6};
long long result=1000000;//0x7FFFFFFF;//此处可以用第一次运算值；
int set[M]={0};
int set_state[M]={0};

long long operat();
int add_set();

int main(int argc, char const *argv[])
{
	if (N>M-1)
	{
		printf("wrong!\n");
	}else{
		add_set(1 ,N);
		printf("%ld=",result);
		int i;
		for (i=0; i < M; ++i)
		{
		    if(set_state[i]) printf("+");
			printf("%d",nums[i]);
		}
	}
	return 0;
}

long long operat(){
	long  long number[N+1]={0};
	int i=0,j=0;
	while(i<M){
		do{
			number[j]=nums[i]+number[j]*10;
			i++;
		}while(set[i]!=1&&i<M);
		j++;
	}
	long long result_return=0;
	for (i = 0; i < N+1; ++i)
	{
		result_return+=number[i];
	}
	return result_return;
}

int add_set(int i,int state){
   // printf("state_1=%d\n",state);
	if (state==0)
	{
		long long add_result=operat();
		if (result>add_result)
		{
			int j=0;
			for (; j < M; ++j)
			{
				set_state[j]=set[j];
			}
			result=add_result;
		}
	}else{
		for(;i<=M-state&&i<(M/N+2)*(N-state+1);i++){
			set[i]=1;
			add_set(i+1,state-1);
			set[i]=0;
		}
		//printf("state=%d\n",state);
	}
	return 0;
}



