#include <stdio.h>
#include "lexer.c"
#include "state.h"

int main(int argc, char *argv[])
{
    int order=1;
	while(order<argc)//����ѭ������
	{
		printf("����Ԥ�������ڽ��У�\n");
		if (lexicalAnalysisEnter(argv[order])==OK)
		{
			printf("pre%s�ʷ�������ϣ�\n",argv[order]);
		}else{
			printf("pre%s�ʷ���������ʧ�ܣ�\n",argv[order]);
		}
		order++;
	};
	printf("�ʷ��������н�����\n");
	return 0;
}
