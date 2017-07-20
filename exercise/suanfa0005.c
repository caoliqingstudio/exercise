#include <stdio.h>

int nums[20]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
//数字设定
int state[20]={0};
//标记数字是否使用

//tell判断是否是素数 是1 否0
int tell(int n){
	if (n==1||n==2)
	{
		return 1;
	}else if (n%2){
		int i;
		for (i = 2; i <=n/2; ++i)
		{
			if (n%i==0)
			{
				return 0;
			}
		}
		return 1;
	}
	return 0;
}

//set 进行设置每一位是多少
int set(int *result,int j){
    //判断到最后的
	int i = 0;
	for (; i < 20; ++i)
	{
		if(state[i]==0&&tell(result[j]+nums[i])){
			result[j+1]=nums[i];
			state[i]=1;
			if(set(result,j+1)&&j!=19)
				return 1;
            state[i]=0;
		}
	}
	if (j==19&&tell(result[j]+result[0]))
	{
		return 1;
	}
	return 0;
}

int main(int argc, char const *argv[])
{
	int result[20];
	result[0]=nums[0];
	state[0]=1;
	if(set(result,0)){
		int i;
		for ( i = 0; i < 20; ++i)
		{
			printf("%d  ",result[i] );
		}
	}else{
		printf("fail to set it\n");
	}
	return 0;
}
