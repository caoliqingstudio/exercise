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
#define CHAR_NUMBER 100//读取每行代码数量
#define varDefNam 30//define 中名字
#define varDefValue 100//define中值的字符串
#define DEFINEVARNUM 20//define 中变量的个数
#define MENU 0
#define DEF_ONE 1
#define DEF_VAR 2
#define DEF_FUN 3//define 中三种形式
#define END 10
#define _NEXT 11//define 的多行
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

char path[100];//存储路径
char pathSystem[100]="C:\\";//没有设定开心就好
DEFINES defineMenu[27];//0:'_';1~26:A~Z
char defineName[DEFINEVARNUM][varDefNam];
state defineState;
DEFATOM *token;
state state_double;//双引号的
DEFINES *defStateLocal;

state pretreatment(char *filename);
//此处使用过extern "C" 但是报错expected identifier or '(' before string constant
//由于没能解决，所以将.c文件后缀改为.cpp
//然后发现还不行，就只能把main中的 包含.h 改为包含.c


#endif
