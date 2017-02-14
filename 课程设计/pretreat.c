#include "pretreat.h"

/**ת��ΪԤ�����ļ���**
*name:ԭ���ļ���
*pre:ǰ���ļ���ͷ
*num:ǰ���ļ�����ͷ
*/
char * name_2_pre(char *name,char *pre,int num){
	char * prename= (char *)malloc(strlen(name)+num+6);//����ռ䣬+1����
	if (prename==NULL)
	{
		exit(OVERFLOW);
	}
	strcpy(prename,pre);
	strcpy(prename+num,name);
	return prename;
}

/****Ԥ����������******/
state pretreatment(char * name){
	FILE * file;
	FILE * prefile;
	char *interFileName;
	char *preFileName;
	interFileName=name_2_pre(name,INTERNAM,INTERNUM);
	preFileName=name_2_pre(name,PRENAM,PRENUM);
	if (file=fopen(name,"r"))
	{
		prefile=fopen(interFileName,"w");
		includeHandle(file,prefile);
	}else{
		printf("%s�ļ���������\n������ļ��Ƿ���ڣ�\n",name);
		return ERROR;
	}
	fclose(file);
	fclose(prefile);
	if (file=fopen(interFileName,"r"))
	{
		prefile=fopen(preFileName,"w");
		defineHandle(file,prefile);
	}else{
		printf("%s�ļ���������\n������ļ��Ƿ���ڣ�\n",interFileName);
	}
	remove(interFileName);
	pretreatEnd(interFileName,preFileName);
	return OK;
}

/** pretreatstart���ڳ�ʼ������ı���**/
state pretreatStart(){
	int i;
	for (i = 0; i < 27; ++i)
	{
		defineMenu[i].next=NULL;
	}
	state_double=FALSE;
	defineState=NO;
	return OK;
}

/** pretreatEnd �ͷ�ʹ�õĿռ� **/
state pretreatEnd(char * name1,char *name2){
	free(name1);
	free(name2);
	int i;
	DEFINES *defineState,*defSta_;
	DEFATOM *_token,*tok_;
	for (i = 0; i < 27; ++i)
	{
		defineState=defineMenu[i].next;
		while(defineState){
			if (defineState->type==DEF_FUN)
			{
				_token=defineState->value.next;
				while(_token){
					tok_=_token;
					_token=_token->next;
					free(tok_);
				}
			}
			defSta_=defineState;
			defineState=defineState->next;
		}
	}
}

/** includeHandle ����include�Լ���������ָ��**/
state includeHandle(FILE *file,FILE *prefile){
	char character,c;
	char rowString[CHAR_NUMBER];
	int i=0;
	while((character=fgetc(file)) != EOF){
		if (character!='\n'){
			if (character!='/')
			{
				rowString[i++]=character;
			}else{//�˴�����ȥע��
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
					rowString[i++]=c;//��cд�룬�Լ���Ϊ���������⣬����֤
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

/**string2file ΪincludeHandle���ӳ�����������һ������ **/
state string2file(char *rowString,FILE *prefile){
	int i=0;
	WHILE_T0FILE(rowString,prefile);
	if (*rowString=='#')
	{
		rowString++;
		if (strcmp_key(rowString,"include")==TRUE)
		{
			while(*rowString!='\"'&&*rowString!='<') rowString++;
			rowString++;
			while(rowString[i]!='\"'&&rowString[i]!='>') i++;
			rowString[i]='\0';
			FILE *newFile;
			if ((newFile=fopen(rowString,"r"))!=NULL)
			{
				includeHandle(newFile,prefile);
			}else{
				printf("%s�ļ�δ�ҵ�\n",rowString);
			}
		}else if (strcmp_key(rowString,"define"))
		{
			while(*rowString!=' '&&*rowString!='\t') rowString++;
			WHILE_T0FILE(rowString,prefile);
			if (pushDefineOne(rowString)==ERROR)
			{
				fprintf(prefile,"#define ");
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
		}else{
			fputc('#',prefile);
			while(rowString[i]!='\0') fputc(rowString[i++],prefile);
			fputc('\n',prefile);
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

/**str cmp�ж��ַ���ǰ��λ�Ƿ���ͬ**/
state strcmp_key(char *aimstr,char conststr[]){
	int i=0;
	WHILE_T0(aimstr);
	while(conststr[i]!='\0'){
		if (aimstr[i]!=conststr[i])
		{
			return FALSE;
		}
		i++;
	}
	if ((aimstr[i]>='a'&&aimstr[i]<='z')||
		(aimstr[i]>='A'&&aimstr[i]<='Z')||
		aimstr[i]=='_'||(aimstr[i]>='0'&&aimstr[i]<='9'))
	{
		return FALSE;
	}
	return TRUE;
}

/** push define Ԫ����define**/
state pushDefineOne(char *aimstr){
	int i=0,n;
	DEFINES *atoms;
	if (*aimstr=='_')
	{
		n=0;
	}else if (*aimstr>='a'&&*aimstr<='z')
	{
		n=*aimstr-'a';
	}else{
		n=*aimstr-'A';
	}
	atoms=(DEFINES *)malloc(sizeof(DEFINES));
	atoms->next=defineMenu[n].next;
	defineMenu[n].next=atoms;
	while(*aimstr!=' '&&*aimstr!='\t'&&*aimstr!='\n'){
		i=0;
		atoms->name[i++]=*aimstr;
		aimstr++;
	}
	atoms->name[i]='\0';
	WHILE_T0(aimstr);
	if (*aimstr=='\n')
	{
		atoms->type=DEF_ONE;
		return OK;
	}
	free(atoms);
	defineMenu[n].next=NULL;
	return FALSE;
}

/**POP DEFINE ����define����**/
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


/**define Handle ����define **/
state defineHandle(FILE *file,FILE *prefile){
	char character,c;
	char rowString[CHAR_NUMBER];
	char keyWord[varDefNam];
	int i=0;
	defineState=NO;
	while((character=fgetc(file)) != EOF){
		if (character!='\n')
		{
			rowString[i++]=character;
		}else{
			rowString[i]='\0';
			rowStringDeal(rowString,file,prefile);
			i=0;
		}
	}
	if (i!=0)
	{
		rowString[i]='\0';
		rowStringDeal(rowString,file,prefile);
	}
	return OK;
}

/** hash   ��hash��ƥ���n**/
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

/** rowStringDeal ��������define�е� **/
/** �� defineȥ�� **/
state rowStringDeal(char *rowString,FILE *file,FILE *prefile){
	int i=0;
	WHILE_T0(rowString);
	DEFINES *local;
	DEFATOM *local_token;
	if (strcmp_key(rowString,"#define")==TRUE)//��undef ����--�����
	{
		while(*rowString!=' '&&*rowString!='\t') rowString++;
		definePush(rowString);
	}else if (strcmp_key(rowString,"#undef")==TRUE){
		while(*rowString!=' '&&*rowString!='\t') rowString++;
		defineDelete(rowString);
	} else{
		if (defineState==NO)//��define���
		{
			while(*rowString!='\0'){
				if(state_double==TRUE||(*rowString=='\"'&&*(rowString-1)!='\\'))
				{
					if(*rowString=='\"'&&*(rowString-1)!='\\')
					{
						state_double=!state_double;
					}
				}else if (WORDSTRUC(*rowString))
				{
					local=defineMenu[hashChar(*rowString)].next;
					while(local)
					{
						if (strcmp_key(rowString,local->name)==TRUE)
						{
							rowString+=strlen(local->name);
							if (local->type==DEF_VAR)
							{
								fprintf(prefile, "%s",local->value.infor);
							}else if (local->type==DEF_FUN)
							{
								WHILE_T0(rowString);
								rowString++;
								defineName[0][0]=1;
								while(*rowString!=')'){
									if(*rowString==',')
									{
										defineName[defineName[0][0]][i]='\0';
										i=0;
										defineName[0][0]++;
									}else{
										defineName[defineName[0][0]][i++]=*rowString;
									}
									rowString++;
								}
								defineName[defineName[0][0]][i]='\0';//�����������
								local_token=local->value.next->next;
								while(local_token->type!=END){
									switch(local_token->type){
										case VAR:
											fprintf(prefile, "%s",defineName[(int)local_token->c]);
											break;
										case NO:
											fputc(local_token->c,prefile);
											break;
										case _NEXT:
											fputc('\n',prefile);
											break;
										default:
											printf("���ж���\n");
									}
									local_token=local_token->next;
								}
							}else{
								printf("ERROR!\n");
							}
							break;
						}
						local=local->next;
					}
					if (local==NULL)
					{
						while(WORDSTRUC(*rowString)||*rowString>='0'&&*rowString<='9'){
							fputc(*rowString,prefile);
							rowString++;
						}
					}//����β�Ӵ�
				}
				fputc(*rowString,prefile);
				if (*rowString!='\0')
				 {
				 	rowString++;
				 }
			}
			fputc('\n',prefile);
		}else{//��define�ж��е�ʱ��
			if (defineState==DEF_FUN)
			{
				define_help(rowString);
			}else{
				printf("�����������㻹д���а���\n");//lazy to finish it
			}
		}
	}
}

/** defineDelete ��defineɾ��**/
state defineDelete(char *aimstr){
	DEFINES *local;
	DEFATOM *local_token;
	WHILE_T0(aimstr);
	local=defineMenu[hashChar(*aimstr)].next;
	while(local)
	{
		if (strcmp_key(aimstr,local->name)==TRUE)
		{
			local_token=local->next;
			free(local);
			return OK;
		}
		local_token=local;
		local=local->next;
	}
	return ERROR;
}

/** definePush ��define ���� **/
state definePush(char *aimstr){
	int i=0,n;
	char j;//����
	char c;
	state type;
	DEFINES *atoms;
	WHILE_T0(aimstr);
	n=hashChar(*aimstr);
	atoms=(DEFINES *)malloc(sizeof(DEFINES));
	atoms->next=defineMenu[n].next;
	defineMenu[n].next=atoms;
	i=0;
	while(*aimstr!=' '&&*aimstr!='\t'&&*aimstr!='('){
		atoms->name[i++]=*aimstr;
		aimstr++;
	}
	atoms->name[i]='\0';
	i=0;
	switch(*aimstr){
		case ' ':
		case '\t':
			WHILE_T0(aimstr);
			while(*aimstr!='\0'&&*aimstr!='\\') atoms->value.infor[i++]=*(aimstr++);
			atoms->value.infor[i]='\0';
			atoms->type=DEF_VAR;
			if (*aimstr=='\\')
			{
				defineState=DEF_VAR;
			}
			break;
		case '(':
			atoms->type=DEF_FUN;
			defineName[0][0]=1;
			while(*aimstr!=')'){
				if(*aimstr==',')
				{
					defineName[defineName[0][0]][i]='\0';
					i=0;
					defineName[0][0]++;
				}else{
					defineName[defineName[0][0]][i++]=*aimstr;
				}
				aimstr++;
			}
			defineName[j][i]='\0';//�����������
			WHILE_T0(aimstr);
			atoms->next=(DEFATOM *)malloc(sizeof(DEFATOM));
			token=atoms->next;
			define_help(aimstr);
			break;
		default:
			printf("%s ERROR!\n",aimstr);
			return ERROR;
	}

}

/** define _help ������������define���� **/
state define_help(char *aimstr){
	char c;
	char j;
	state type;
	token->next=(DEFATOM *)malloc(sizeof(DEFATOM));
	token=token->next;
	while(*aimstr!='\0'&&*aimstr!='\\'){
		c=*aimstr;
		type=NO;
		if (WORDSTRUC(*aimstr))
		{
			for (j = 1; j <= defineName[0][0]; ++j)
			{
				if (strcmp_key(aimstr,defineName[j])==TRUE)
				{
					c=j;
					type=VAR;
					aimstr+=strlen(defineName[j]);
					break;
				}
			}
			if (j>defineName[0][0])
			{
				while(WORDSTRUC(*aimstr)||*aimstr>='0'&&*aimstr<='9'){
					token->c=*(aimstr++);
					token->type=NO;
					token->next=(DEFATOM *)malloc(sizeof(DEFATOM));
					token=token->next;
				}//��ֹβ�Ӵ�
			}
		}
		token->c=c;
		token->type=type;
		token->next=(DEFATOM *)malloc(sizeof(DEFATOM));
		token=token->next;
	}
	token->type=END;
	if (*aimstr=='\\')
	{
		defineState=DEF_FUN;
		token->type=_NEXT;
	}else{
		defineState=NO;
	}
	token->next=NULL;
	return OK;
}
