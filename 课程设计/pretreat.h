#ifndef PRETREAT_H
#define PRETREAT_H

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "state.h"

#define PRENUM 3
#define PRENAM "pre"
#define INTERNUM 5
#define INTERNAM "inter"
#define CHAR_NUMBER 100//��ȡÿ�д�������
#define varDefNam 30//define ������
#define varDefValue 100//define��ֵ���ַ���
#define DEFINEVARNUM 20//define �б����ĸ���
#define MENU 0
#define DEF_ONE 1
#define DEF_VAR 2
#define DEF_FUN 3//define ��������ʽ
#define END 10
#define _NEXT 11//define �Ķ���
#define VAR 1
#define NO 0
#define IF 1
#define ELSE 2
#define ELIF 1
#define ENDIF 0
#define IFDEF 1
#define IFNDEF 1
#define CHAR2INT(x) (((int)x)&0Xff)
#define WHILE_T0(x) while(*x==' '||*x=='\t') x++;
#define FILEWHILE_T0(x,file) while(*x==' '||*x=='\t'){fputc(*x,file);x++;}
#define WORDSTRUC(c) (c>='a'&&c<='z')||(c>='A'&&c<='Z')||c=='_'
typedef struct deffunc{
	state type;
	char c;
	struct  deffunc *next;
} DEFATOM;
typedef struct defhash
{
	state type;
	char name[varDefNam];
	union{
		char infor[varDefValue];
		struct deffunc *next;
	}value;
	struct  defhash *next;
} DEFINES;

char path[100];//�洢·��
char pathSystem[100]="C:\\";//û���趨���ľͺ�
DEFINES defineMenu[27];//0:'_';1~26:A~Z
char defineName[DEFINEVARNUM][varDefNam];
state defineState;
DEFATOM *token;
state state_double;//˫���ŵ�

state pretreatment(char *filename);
//�˴�ʹ�ù�extern "C" ���Ǳ���expected identifier or '(' before string constant
//����û�ܽ�������Խ�.c�ļ���׺��Ϊ.cpp
//Ȼ���ֻ����У���ֻ�ܰ�main�е� ����.h ��Ϊ����.c


#endif
