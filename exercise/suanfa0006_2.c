#include <stdio.h>

#define POP -1
#define PUSH 1

int number=0;

int run(int m,int stack){
	//push
	if(m>0){
		run(m-1,stack+PUSH);
	}
	//pop
	if(stack>0){
		if (m==0&&stack==1)
		{
			number++;
		}else{
			run(m,stack+POP);
		}
	}
	return 0;
}

int main(int argc, char const *argv[])
{
	int m;// number
	scanf("%d",&m);
	run(m,0);
	printf("%d\n",number);
	return 0;
}
