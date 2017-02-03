#include "pretreat.h"
/**********/
/*待删除，用于方便写代码*/

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1

typedef int state;
#define MENU 0
#define DEF_ONE 1
#define DEF_VAR 2
#define DEF_FUN 3//difine 中三种形式
typedef struct defhash
{
	int type;
	char name[varDefNam];
	struct  defhash *next;
} DEFINES;

#define WHILE_T0(x,i) while(x[i]==' '||x[i]=='\t') i++;

DEFINES defineMenu[27];//0:'_';1~26:A~Z
#define NO 0
#define IF 1
#define ELSE 2
#define ELIF 3
#define ENDIF 4
#define IFDEF 5
#define IFNDEF 6

/******截止到这里****/
state pretreatment(const char * name){
	FILE * file;
	FILE * prefile;
	if (file=fopen(name,"r"))
	{
		prefile=fopen(name_2_pre(name,INTERNAM,INTERNUM),"w");
		includeHandle(file,prefile);
	}else{
		printf("%s文件名称有误，\n请检查该文件是否存在！\n",name);
	}
	fclose(file);
	fclose(prefile);
	if (file=fopen(name_2_pre(name,INTERNAM,INTERNUM),"r"))
	{
		prefile=fopen(name_2_pre(name,PRENAM,PRENUM),"w");
		defineHandle(file,prefile);
	}else{
		printf("%s文件名称有误，\n请检查该文件是否存在！\n",name);
	}
	remove(name_2_pre(name,INTERNAM,INTERNUM));
	return OK;
}

/** pretreatstart用于初始化定义的变量**/
state pretreatStart(){
	int i;
	for (i = 0; i < 27; ++i)
	{
		defineMenu[i].next=NULL;
	}
	defineState=NO;
}

/**转化为预处理文件名**
*name:原来文件名
*pre:前置文件名头
*num:前置文件名开头
*/
char * name_2_pre(char * name,char *pre,int num){
	char * prename= (char*)malloc(strlen(name)+num+6);//分配空间，+1即可
	if (prename==NULL)
	{
		exit(OVERFLOW);
	}
	strcpy(prename,pre);
	strcpy(prename+num,name);
	return prename;
}

/** includeHandle 处理include以及条件编译指令**/
state includeHandle(FILE *file,FILE *prefile){
	char character,c;
	char rowString[CHAR_NUMBER];
	int i=0;
	while((character=fgetc(file)) != EOF){
		if (character!='\n'){
			if (character!='/')
			{
				rowString[i++]=character;
			}else{//此处用来去注释
				c=fgetc(file);
				if (c=='*')
				{
					while((character=fgetc(file)) !='*'||(character=fgetc(file)) !='/');
				}else if (c=='/')
				{				
					rowString[i]='\0';
					i=0;
					string2file(rowString,prefile);
					while((character=fgetc(file)) !='\n');
				}else{
					rowString[i++]=character;
					rowString[i++]=c;//将c写入，自己认为不会有问题，待考证
				}
			}
		}else{
			rowString[i]='\0';
			i=0;
			string2file(rowString,prefile);
		}
	}
	if (i!=0)
	{
		rowString[i]='\0';
		string2file(rowString,prefile);
	}
	return OK;
}

/**string2file 为includeHandle的子程序，用来处理一行命令 **/
state string2file(char *rowString,FILE *prefile){
	int i=0;
	WHILE_T0(rowString);
	if (*rowString=='#')
	{
		if (strcmp_key(rowString,"include")==TRUE)
		{
			while(*rowString!='\"'&&*rowString!='<') rowString++;
			while(rowString[i]!='\"'&&rowString[i]!='>') i++;
			rowString[i]='\0';
			FILE *newFile;
			if (newFile=fopen(rowString))
			{
				includeHandle(newFile,prefile);
			}else{
				printf("%s文件未找到\n",rowString);
			}
		}else if (strcmp_key(rowString,"define"))
		{
			while(*rowString!=' '&&*rowString!='\t') rowString++;
			WHILE_T0(rowString);
			if (pushDefineOne(rowString)==ERROR)
			{
				while(rowString[i]!='\0') fputc(rowString[i++],prefile);
				fputc('\n',prefile);		
			}
		}else if (strcmp_key(rowString,"if"))
		{
			if (popDefine(rowString)!=TRUE)
			{
				defineState= IF;
			}else{
				defineState=NO;
			}
		}else if (strcmp_key(rowString,"ifdef"))
		{
			if (popDefine(rowString)!=TRUE)
			{
				defineState= IFDEF;
			}else{
				defineState=NO;
			}
		}else if (strcmp_key(rowString,"ifndef"))
		{
			if (popDefine(rowString)==TRUE)
			{
				defineState= IFNDEF;
			}else{
				defineState=NO;
			}
		}else if (strcmp_key(rowString,"elif"))
		{
			if (defineState!=NO)
			{
				if (popDefine(rowString)!=TRUE)
				{
					defineState= ELIF;
				}else{
					defineState=NO;
				}
			}
		}else if (strcmp_key(rowString,"endif"))
		{
			defineState=ENDIF;
		}
	}else{
		if (defineState!=NO)
		{
			return NO;
		}
		while(rowString[i]!='\0') fputc(rowString[i++],prefile);
		fputc('\n',prefile);	
	}
	return NO;
}

/**str cmp判断字符串前几位是否相同**/
state strcmp_key(char *aimstr,char *conststr){
	int i=0;
	WHILE_T0(aimstr);
	while(conststr[i]!='\0'){
		if (aimstr[i]!=conststr[i])
		{
			return FALSE;
		}
	}
	if ((aimstr[i]>='a'&&aimstr[i]<='z')||(aimstr[i]>='A'&&aimstr[i]<='Z')||aimstr[i]='_')
	{
		return FALSE;
	}
	return TRUE;
}

/** push define 元素入define**/
state pushDefineOne(char *aimstr){
	int i=0,n;
	DEFINES *state;
	if (*aimstr=='_')
	{
		n=0;
	}else if (*aimstr>='a'&&*aimstr<='z')
	{
		n=*aimstr-'a';	
	}else{
		n=*aimstr-'A';
	}
	defineMenu[n].next=(DEFINES *)malloc(sizeof(DEFINES));
	state=defineMenu.next;
	state->next=NULL;
	while(*aimstr!=' '&&*aimstr!='\t'&&*aimstr!='\n'){
		i=0;
		state->name[i++]=*aimstr;
		aimstr++;	
	}
	state->name[i]='\0';
	WHILE_T0(aimstr);
	if (*aimstr=='\n')
	{
		state->type=DEF_ONE;
		return OK;
	}
	free(state);
	defineMenu[n].next=NULL;
	return FALSE;
}

/**POP DEFINE 查找define内容**/
state popDefine(char *aimstr){
	WHILE_T0(aimstr);
	int i=0,n;
	DEFINES *state;
	if (*aimstr=='_')
	{
		n=0;
	}else if (*aimstr>='a'&&*aimstr<='z')
	{
		n=*aimstr-'a';	
	}else{
		n=*aimstr-'A';
	}
	state=defineMenu[n].next;
	while(state){
		if (strcmp_key(aimstr,state->name)==TRUE)
		{
			return TRUE;
		}
	}
	return FALSE;
}


/**define Handle 处理define **/
state defineHandle(FILE *file,FILE *prefile){
	char character,c;
	char rowString[CHAR_NUMBER];
	int i=0;
}