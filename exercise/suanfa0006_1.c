#include <stdio.h>
#include <math.h>

#define MAX_N 100
#define A 1
#define B 2
#define C 3  //边abc
typedef char state;


int n;//number
int length[MAX_N];//Board length
state length_state[MAX_N];
state length_state_final[MAX_N];
double area=-1;
double length_all;

int tell_opera(int length_a,int length_b,int length_c){
	if (length_a+length_b<=length_c){
	}else if (length_a+length_c<=length_b){
	}else if (length_b+length_c<=length_a){
	}else{
		double area_temp=length_all*(length_all-length_a)
			*(length_all-length_b)*(length_all-length_c);
		if (area==-1||area<area_temp){
			area=area_temp;
			int j;
			for(j=0;j<n;j++){
				length_state_final[j]=length_state[j];
			}
		}
	}
	return 0;
}

int set(int i,int length_a,int length_b,int length_c){
	if (i>=n)
	{
		tell_opera(length_a,length_b,length_c);
	}else{
		// int j;
		// for (j = A; j < =C; ++j)
		// {
		// 	/* code */
		// }
		length_state[i]=A;
		set(i+1,length_a+length[i],length_b,length_c);

		length_state[i]=B;
		set(i+1,length_a,length_b+length[i],length_c);

		length_state[i]=C;
		set(i+1,length_a,length_b,length_c+length[i]);
		//不用循环 提高速度
	}
	return 0;
}

int main(int argc, char const *argv[])
{
	scanf("%d",&n);
	int i;
	for (i = 0; i < n; ++i)
	{
		scanf("%d",&length[i]);
		length_all+=length[i];
	}
	length_all/=2;
	length_state[0]=A;
	set(1,length[0],0,0);
	if (area==-1)
	{
		printf("Are you kidding?\n");
	}else{
		printf("the area is %d\n",(int)(sqrt(area)*100));
		printf("length of  A : ");
		for (i = 0; i < n; ++i){
			if (length_state_final[i]==A)
			{
				printf("%d ",length[i]);
			}
		}
		printf("\nlength of  B : ");
		for (i = 0; i < n; ++i){
			if (length_state_final[i]==B)
			{
				printf("%d ",length[i]);
			}
		}printf("\nlength of  C  ");
		for (i = 0; i < n; ++i){
			if (length_state_final[i]==C)
			{
				printf("%d ",length[i]);
			}
		}
	}
	return 0;
}
