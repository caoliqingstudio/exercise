#include <stdio.h>
#include "pretreat.c"
#include "lexer.c"
#include "state.h"

int main(int argc, char *argv[])
{
    int order=1;
	while(order<argc)//����ѭ������
	{
		printf("����Ԥ�������ڽ��У�\n");
		if(pretreatment(argv[order])==OK){
			printf("%sԤ������ϣ�\n",argv[order]);
		}else{
			printf("%s����ʧ�ܣ�\n",argv[order]);
		}
		if (lexicalAnalysisEnter(argv[order])==OK)
		{
			printf("pre%s�ʷ�������ϣ�\n",argv[order]);
		}else{
			printf("pre%s�ʷ���������ʧ�ܣ�\n",argv[order]);
		}
		order++;
	};
	printf("��������");
	return 0;
}
