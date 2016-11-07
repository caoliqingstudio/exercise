#include<stdio.h>
#define M 37
#define N 20

int nums[M]={1,2,3,4,5,6,7,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,9,8,7,6,5,4,3,2,1,2,3,4,5,6};
long result=0x7FFFFFFF;//此处可以用第一次运算值；
int set[M]={0};
int set_state[M]={0};

long operat();
int add_set();

int main(int argc, char const *argv[])
{
	if (N>M-1)
	{
		printf("wrong!\n");
	}else{
		add_set(1,20);
		printf("%ld=",result);
		int i;
		for (i=0; i < M; ++i)
		{
			printf("%d",nums[i]);
		}
	}
	return 0;
}

long operat(){
	long  number[N+1]={0};
	int i=0,j=0;
	while(i<M){
		do{
			number[j]=nums[i]+number[j]*10;
			i++;
		}while(set[i]!=1);
		j++;
	}
	long result_return;
	for (i = 0; i < N+1; ++i)
	{
		result_return+=number[i];
	}
	return result_return;
}

int add_set(int i,int state){
	if (state==0)
	{
		long add_result=operat();
		if (result<add_result)
		{
			int j=0;
			for (; j < M; ++j)
			{
				set_state[j]=set[j];
				result=add_result;
			}
		}
	}else{
		for(;i<=M-state;i++){
			set[i]=1;
			add_set(i+1,state-1);
			set[i]=0;
		}
	}
	return 0;
}



