int nums[37]={1,2,3,4,5,6,7,5,6,7,8,9,0,1,2,3,4,5,6,7,8,9,0,9,8,7,6,5,4,3,2,1,2,3,4,5,6};
long long result=1000000;
int set[37]={0};
int set_state[37]={0};
long long operat();
int add_set();
int main(int argc, char const *argv[])
{
	if (20>37-1)
	{
		printf("wrong!\n");
	}else{
		add_set(1 ,20);
		printf("%ld=",result);
		int i;
		for (i=0; i < 37; ++i)
		{
		    if(set_state[i]) printf("+");
			printf("%d",nums[i]);
		}
	}
	return 0;
}
long long operat(){
	long  long number[20+1]={0};
	int i=0,j=0;
	while(i<37){
		do{
			number[j]=nums[i]+number[j]*10;
			i++;
		}while(set[i]!=1&&i<37);
		j++;
	}
	long long result_return=0;
	for (i = 0; i < 20+1; ++i)
	{
		result_return+=number[i];
	}
	return result_return;
}
int add_set(int i,int state){
	if (state==0)
	{
		long long add_result=operat();
		if (result>add_result)
		{
			int j=0;
			for (; j < 37; ++j)
			{
				set_state[j]=set[j];
			}
			result=add_result;
		}
	}else{
		for(;i<=37-state&&i<(37/20+2)*(20-state+1);i++){
			set[i]=1;
			add_set(i+1,state-1);
			set[i]=0;
		}
	}
	return 0;
}
