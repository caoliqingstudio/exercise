/***
*�ַ�������ֵ��˫����δ���������ο�������˵
*�ַ�������ֵ����˫���ţ������Ҳ�֪����˫���ŷ�������ͼӽ�ȥ��
*�ַ��ĵ�������Ҳû�ܰ�
*�����ֳ����� ���ڱ����ʽ��ͬ����ֵ��ͬ��������Ҳû����
**/
#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "state.h"

#define PRENAME "pre"
#define LEX "lex"
#define ROW_STRING_LENGTH 100//��ȡÿ�д�������
#define STRING_LENGTH_MAX 100//ò��û�á�����ɾ��
#define CON_CHAR_MAX 8
#define OTHER_TOKEN_MAX 3//Ŀǰ���������������ģ�sizeof����ؼ���
#define KEY_TOKEN_MAX  10//�ؼ��֣�8����������������
#define IDENTIFIERS 0 //�趨�����б�ʶ����λ��
//#define CONSTANTS 1//�趨�����г�����λ��
#define STRINGLITERALS 1//�趨�������ַ��������λ��
#define WORDSTRUC(c) (c>='a'&&c<='z')||(c>='A'&&c<='Z')||c=='_'
#define NUMBSTRUC(c) (c>='0'&&c<='9')
#define TOKEN_IDE 1//����Ϊ��� 1����ʶ��
#define TOKEN_KEY 2//2.�ؼ���
#define TOKEN_CON 3//3.����
#define TOKEN_STR 4//4.�ַ���
#define TOKEN_OPR 5//5.�����
#define TOKEN_SEP 6//6.�ָ���
#define OPRNUM 39
#define OPR_ opr[OPRNUM][OTHER_TOKEN_MAX]={"++","--","+","-","(",")","[","]","->",".","!",\
					"~","*","&","/","%","<<",">>","<","<=",">=",">",\
					"==","!=","^","|","&&","||","=","+=","-=","*=",\
					"/=","&=","^=","|=","<<=",">>=",",","?:"}//��Ȼ�鲻��ʹ��Ƶ��,������ǰ��
//attention:û�����������źͼӼ���û������ȡ��ַ&�Ͱ�λ��&��û��sizeof,?:
#define SEPNUM 5
#define SEP_ sep[SEPNUM][OTHER_TOKEN_MAX]={",",";",":","{","}"}
//SEP�ָ���Ŀǰ����Щ��
#define KEYNUM 32
#define KEY_ key[KEYNUM][KEY_TOKEN_MAX]={"auto","break","case","char","const","continue",\
					"double","default","do","else","enum","extern","float","for","goto",\
					"int","if","long","register","return","struct","switch","short","signed",\
					"sizeof","static","typedef","union","unsigned","void","volatile","while"}

typedef struct word_key
{
	int num;
	char value[KEY_TOKEN_MAX];
	struct word_key *next;
} SET_TOKEN_KEY;//�ؼ���
typedef struct word_char
{
	int num;
	char value[CON_CHAR_MAX];
	struct word_char *next;
} SET_TOKEN_CONCHAR;
typedef struct word_other
{
	int num;
	char value[OTHER_TOKEN_MAX];
	struct word_other *next;
} SET_TOKEN_OTHER;//������ͷָ�����
typedef struct word
{
	int num;
	char *value;
	struct word *next;
} SET_TOKEN;//��ʶ�� �ַ�������
/**
*SET_TOKEN tokens[5][27];
*���У�0��ʾ��ʶ��;
*1��ʾ�ַ�������ֵ;
**/
SET_TOKEN tokens[2][27];//1~26��ʾ��ĸa��z,0��ʾ�»���
SET_TOKEN_KEY tokens_key[27];
SET_TOKEN tokens_conNum[10];//���ֳ�������ϣ����Ϊ%10
SET_TOKEN_OTHER tokens_opr,tokens_sep;
SET_TOKEN_CONCHAR tokens_conChar[10];//�ַ���������ϣ����Ϊ%10
int rowNumber;//c�ļ��к�
int rowNumFile;//Ŀ���ļ����к�

state lexicalAnalysis(char *name);//�ʷ�����
//�˴�ʹ�ù�extern "C" ���Ǳ���expected identifier or '(' before string constant
//����û�ܽ�������Խ�.c�ļ���׺��Ϊ.cpp
//Ȼ���ֻ����У���ֻ�ܰ�main�е� ����.h ��Ϊ����.c
//����֣�����ڹ�����.h�ǿ����õ�

#endif
