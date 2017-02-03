#include <stdio.h>
#include "pretreat.h"
//#include "state.h"

int main(int argc, char const *argv[])
{
    int order=1;
	while(argc--)//允许循环进行
	{
		printf("编译预处理正在进行！\n");
		if(pretreatment(argv[order])==1){

		}else{
			printf("%s处理失败！\n",argv[order]);
		}
		order++;
	};
	printf("可以运行");
	return 0;
}
