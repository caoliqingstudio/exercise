#include "lexer.h"

/*************头文件内容*****//***************************************************************/
#define FILE_NAME_LENGTH 30
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1
typedef int state;
#define PRENAME "pre"
#define CHAR_NUMBER 100//读取每行代码数量
#define STRING_LENGTH_MAX 100
#define OTHER_TOKEN_MAX 3//目前发现最多就是两个的，sizeof划入关键字
#define KEY_TOKEN_MAX  10//关键字，8个，除非我数错了
#define IDENTIFIERS 0 //设定数组中标识符的位次
#define CONSTANTS 1//设定数组中常量的位次
#define STRINGLITERALS 2//设定数组中字符串字面的位次
#define TOKEN_IDE 1//以下为序号 1：标识符
#define TOKEN_KEY 2//2.关键字
#define TOKEN_CON 3//3.常量
#define TOKEN_STR 4//4.字符串
#define TOKEN_OPR 5//5.运算符
#define TOKEN_SEP 6//6.分隔符
#define
#define WHILE_T0(str,i) 
typedef struct word_key
{
	int num;
	char value[KEY_TOKEN_MAX];
	struct word_other *next; 
} SET_TOKEN_KEY;
typedef struct word_other
{
	int num;
	char value[OTHER_TOKEN_MAX];
	struct word_other *next; 
} SET_TOKEN_OTHER;//运算符和分隔符的
typedef struct word
{
	int num;
	char *value;
	struct word *next;
} SET_TOKEN;
/**
*SET_TOKEN tokens[5][27];
*其中，0表示标识符;
*1表示常量;2表示字符串字面值;
**/
SET_TOKEN tokens[3][27];//0~25表示字母a到z,26表示下划线
SET_TOKEN_KEY tokens_key[27];
SET_TOKEN_OTHER tokens_opr,tokens_sep;

/*********方便写代码***************************//*************************************************/
/** 词法分析 **/
/**
*有点问题，由于中间使用的文件名是pre 
*本质应该只用一个文件名就可以
*不应该存在 得到pre文件名
**/
state lexicalAnalysisEnter(char *name){
	FILE * file;
	FILE * aimfile;
	char fileName[FILE_NAME_LENGTH];
	char aimFileName[FILE_NAME_LENGTH];
	int i=0;

	strcat(fileName,PRENAME);
	strcat(fileName,name);//得到pre文件名
	strcat(aimFileName,name);
	while(aimFileName[i++]!='.');
	aimFileName[i]='\0';
	strcat(aimFileName,lex);//得得目标存储文件名
	lexerStart();
	if (file=fopen(fileName,"r"))
	{
		aimfile=fopen(aimFileName,"w");
		readFile(file,aimfile);
	}else{
		printf("%s文件名称有误，\n请检查该文件是否存在！\n",fileName);
		return ERROR;
	}
	return OK;
}

/** lexerStart**/
/**
*设置关键字等内容
*存在头结点，会有一点浪费空间，但是开心就好
**/
state lexerStart(void){
	int i,j;
	char OPR;
	char SEP;
	char KEY;
	SET_TOKEN_OTHER atom_other;
	SET_TOKEN_KEY atom_key;
	//第一步标识符，常量，字符串
	for (i = 0; i < 3; ++i)
	{
		for (j = 0; j < 27; ++j)
		{
			tokens[i][j].next=NULL;
		}
	}
	//第二步，运算符
	atom_other=&tokens_opr;
	for (i = 0; i < OPRNUM; ++i)
	{
		atom_other->next=(SET_TOKEN_OTHER *)malloc(sizeof(SET_TOKEN_OTHER));
		atom_other=atom_other->next;
		atom_other->num=0;
		strcpy(atom_other->value,opr[i]);
	}
	atom_other->next=NULL;
	//第三步，分隔符
	atom_other=&tokens_sep;
	for (i = 0; i < SEPNUM; ++i)
	{
		atom_other->next=(SET_TOKEN_OTHER *)malloc(sizeof(SET_TOKEN_OTHER));
		atom_other=atom_other->next;
		atom_other->num=0;
		strcpy(atom_other->value,sep[i]);
	}
	atom_other->next=NULL;
	//第四步，关键字
	for (i = 0,j = 0; i < 27; ++i)
	{
		atom_key=&tokens_key[i]
		for (; j < KEYNUM; ++j)
		{
			if (hashChar(key[j][0])!=i)
			{
				break;
			}else{
				atom_key->next=(SET_TOKEN_KEY *)malloc(sizeof(SET_TOKEN_KEY));
				atom_key=atom_key->next;
				atom_key->num=0;
				strcpy(atom_key->value,key[j]);
			}
		}
		atom_key->next=NULL;
	}
	//第五步,2017/2/6 10:14目前没用到
	rowNumber=1;//行号归0；
	rowNumFile=1;
}

/** hash   求hash中匹配的n**/
int hashChar(char c){
	int n;
	if (c=='_')
	{
		n=0;
	}else if (c>='a'&&c<='z')
	{
		n=c-'a';	
	}else{
		n=c-'A';
	}
	return n;
}

/** readFile 文件中内容**/
state readFile(FILE *file,FILE *aimfile){
	char rowString[ROW_STRING_LENGTH];
	char character;
	int i=0;
	while((character=fgetc(file)) != EOF){
		if (character!='\n')
		{
			rowString[i++]=character;
		}else{
			rowString[i]="\0";
			i=0;
			string2file(rowString,aimfile);
			rowNumber++;
		}
	}
	if (i!=0)
	{
		rowString[i]="\0";
		string2file(rowString,aimfile);
	}
	return OK;
}

/** string2file**/
/**
*处理一行代码并写入
**/
state string2file(char *rowString,FILE *aimfile){
	int lineNumber=0,tokenNumber,number;//依次为c文件中列号，token编号，出现次数
	char *tokenStr;//token内容
	int length;
	SET_TOKEN token_134;
	SET_TOKEN_KEY token_2;
	SET_TOKEN_OTHER token_56;
	while(rowString[lineNumber]!='\0'){
		if (rowString[lineNumber]==' '||"\t")
		{
			length=1;
		}else{
			if(token_56=sepOprTell(tokens_sep,&rowString[lineNumber]))
			{//分隔符
				length=strlen(local->value);
				tokenNumber=TOKEN_SEP;
				tokenStr=local->value;
				number=++(local->num);
			}else if (token_56=sepOprTell(tokens_opr,&rowString[lineNumber]))
			{//运算符
				length=strlen(local->value);
				tokenNumber=TOKEN_OPR;
				tokenStr=local->value;
				number=++(local->num);
			}//还没写符**********************************************************************************/
			fprintf(aimfile, "%d %d %s %d %d\n",rowNumFile++,tokenNumber,tokenStr,rowNumber,lineNumber+1,number);
		}
		lineNumber+=length;
	}
	return OK;
}

/** sepTell 判断是否是分隔符,运算符，返回指针**/
SET_TOKEN_OTHER *sepOprTell(SET_TOKEN_OTHER *local,char *string){
	int i;
	while(local){
		for (i = 0;local->value[i]!='\0'; ++i)
		{
			if (string[i]!=local->value[i])
			{
				break;
			}	
		}
		if (local->value[i]=='\0')
		{
			return local;
		}
	}
	return NULL;
}