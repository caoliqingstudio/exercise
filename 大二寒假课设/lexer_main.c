#include <stdio.h>
#include "lexer.c"
#include "state.h"

int main(int argc, char *argv[])
{
    int order=1;
	while(order<argc)//允许循环进行
	{
		printf("编译预处理正在进行！\n");
		if (lexicalAnalysisEnter(argv[order])==OK)
		{
			printf("pre%s词法分析完毕！\n",argv[order]);
		}else{
			printf("pre%s词法分析处理失败！\n",argv[order]);
		}
		order++;
	};
	printf("词法分析运行结束！\n");
	return 0;
}
