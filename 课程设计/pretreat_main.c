#include <stdio.h>
#include "pretreat.c"
#include "state.h"

int main(int argc, char *argv[])
{
    int order=1;
	while(order<argc)//允许循环进行
	{
		printf("编译预处理正在进行！\n");
		if(pretreatment(argv[order])==OK){
			printf("%s预处理完毕！\n",argv[order]);
		}else{
			printf("%s处理失败！\n",argv[order]);
		}
		order++;
	};
	printf("编译预处理运行结束!\n");
	return 0;
}
