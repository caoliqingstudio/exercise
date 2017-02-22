#include "lexer.h"

/** name2pre�õ� pre���ļ���**/
char * name2pre(char *name,char *pre){
	int i,j=0;
	i=strlen(name);
	char * prename= (char *)malloc(i+strlen(pre)+6);//����ռ䣬+1����
	if (prename==NULL)
	{
		exit(OVERFLOW);
	}
	while(--i){
		if(name[i]=='\\'||name[i]=='/')
			break;
	}
	if(i!=0)
	{
		j=i+1;
	}
	while(i){
		prename[i]=name[i];
		i--;
	}
	prename[i]=name[i];
	prename[j]='\0';
	strcat(prename,pre);
	strcat(prename,&(name[j]));
	return prename;
}

/** name2lex �õ���׺�ļ��� **/
char *name2lex(char *name,char *aim){
	int i,j=0;
	i=strlen(name);
	char *aimname= (char *)malloc(i+strlen(aim)+6);
	if (aimname==NULL)
	{
		exit(OVERFLOW);
	}
	j=i;
	while(--i){
		if(name[i]=='\\'||name[i]=='/')
		{
			break;
		}
		if(name[i]=='.')
		{
			j=i;
			break;
		}
	}
	i=j-1;
	while(i){
		aimname[i]=name[i];
		i--;
	}
	aimname[i]=name[i];
	aimname[j]='\0';
	strcat(aimname,aim);
	return aimname;
}

/** �ʷ����� **/
/**
*�е����⣬�����м�ʹ�õ��ļ�����pre
*����Ӧ��ֻ��һ���ļ����Ϳ���
*��Ӧ�ô��� �õ�pre�ļ���
**/
state lexicalAnalysisEnter(char *name){
	FILE * file;
	FILE * aimfile;
	char *fileName;
	char *aimFileName;
	int i=0;
	fileName=name2pre(name,"pre");
	aimFileName=name2lex(name,".lex");
	lexerStart();
	if (file=fopen(fileName,"r"))
	{
		aimfile=fopen(aimFileName,"w");
		readFile(file,aimfile);
	}else{
		printf("%s�ļ���������\n������ļ��Ƿ���ڣ�\n",fileName);
		return ERROR;
	}
	lexerEnd(fileName,aimFileName);
	fclose(file);
	fclose(aimfile);
	return OK;
}

/** hash   ��hash��ƥ���n**/
int hashChar_lexer(char c){
	int n=0;
	if (c>='a'&&c<='z')
	{
		n=c-'a';
	}else if(c>='A'&&c<='Z'){
		n=c-'A';
	}else if(c>='0'&&c<='9'){
		n=c-'0';
	}else{
		n=0;
	}
	return n;
}

/** lexerStart**/
/**
*���ùؼ��ֵ�����
*����ͷ��㣬����һ���˷ѿռ䣬���ǿ��ľͺ�
**/
state lexerStart(void){
	int i,j;
	char OPR_;
	char SEP_;
	char KEY_;
	SET_TOKEN_OTHER *atom_other;
	SET_TOKEN_KEY *atom_key;
	//��һ����ʶ�����ַ���
	for (i = 0; i < 2; ++i)
	{
		for (j = 0; j < 27; ++j)
		{
			tokens[i][j].next=NULL;
		}
	}
	//�ڶ����������
	atom_other=&tokens_opr;
	for (i = 0; i < OPRNUM; ++i)
	{
		atom_other->next=(SET_TOKEN_OTHER *)malloc(sizeof(SET_TOKEN_OTHER));
		atom_other=atom_other->next;
		atom_other->num=0;
		strcpy(atom_other->value,opr[i]);
	}
	atom_other->next=NULL;
	//���������ָ���
	atom_other=&tokens_sep;
	for (i = 0; i < SEPNUM; ++i)
	{
		atom_other->next=(SET_TOKEN_OTHER *)malloc(sizeof(SET_TOKEN_OTHER));
		atom_other=atom_other->next;
		atom_other->num=0;
		strcpy(atom_other->value,sep[i]);
	}
	atom_other->next=NULL;
	//���Ĳ����ؼ���
	for (i = 0,j = 0; i < 27; ++i)
	{
		atom_key=&tokens_key[i];
		for (; j < KEYNUM; ++j)
		{
			if (hashChar_lexer(key[j][0])!=i)
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
	//���岽,2017/2/6 10:14Ŀǰû�õ�
	rowNumber=1;//�кŹ�0��
	rowNumFile=1;
	//�����������������޸ģ��������ʶ����ͬ
	//�ַ�����
	for (i = 0; i < 10; ++i)
	{
		tokens_conChar[i].next=NULL;
	}
	//���ֳ���
	for (i = 0; i < 10; ++i)
	{
		tokens_conNum[i].next=NULL;
	}
	return OK;
}

/**lexerEnd **/
state lexerEnd(char *name1,char *name2){
	SET_TOKEN *token_134,*token_134_a;
	SET_TOKEN_CONCHAR *token_3char,*token_3char_a;
	int i,j;
	free(name1);
	free(name2);
	//�ͷ� ��ʶ�����ַ�������
	for (i = 0; i <2; ++i)
	{
		for (j = 0; j < 27; ++j)
		{
			token_134=tokens[i][j].next;
			tokens[i][j].next=NULL;
			while(token_134){
				free(token_134->value);
				token_134_a=token_134;
				token_134=token_134->next;
				free(token_134_a);
			}
		}
	}
	//�ͷ����ֳ���
	for (i = 0; i < 10; ++i)
	{
		token_134=tokens_conNum[i].next;
		tokens_conNum[i].next=NULL;
		while(token_134){
			free(token_134->value);
			token_134_a=token_134;
			token_134=token_134->next;
			free(token_134_a);
		}
	}
	//�ͷ��ַ�����
	for (i = 0; i < 10; ++i)
	{
		token_3char=tokens_conChar[i].next;
		tokens_conChar[i].next=NULL;
		while(token_3char){
			token_3char_a=token_3char;
			token_3char=token_3char->next;
			free(token_3char);
		}
	}
	return OK;
}

/** readFile �ļ�������**/
state readFile(FILE *file,FILE *aimfile){
	char rowString[ROW_STRING_LENGTH];
	char character;
	int i=0;
	while((character=fgetc(file)) != EOF){
		if (character!='\n')
		{
			rowString[i++]=character;
		}else{
			rowString[i]='\0';
			i=0;
			string2file_lexer(rowString,aimfile);
			rowNumber++;
		}
	}
	if (i!=0)
	{
		rowString[i]='\0';
		string2file_lexer(rowString,aimfile);
	}
	return OK;
}
/** sepTell �ж��Ƿ��Ƿָ���,�����������ָ��**/
SET_TOKEN_OTHER *sepOprTell(SET_TOKEN_OTHER *local,char *string){
	int i;
	local=local->next;
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
		local=local->next;
	}
	return NULL;
}

/** keyTell �ж��Ƿ��ǹؼ���**/
SET_TOKEN_KEY *keyTell(char *string){
	int i;
	SET_TOKEN_KEY *local=tokens_key[hashChar_lexer(*string)].next;
	while(local){
		for (i = 0;local->value[i]!='\0'; ++i)
		{
			if (string[i]!=local->value[i])
			{
				break;
			}
		}
		if (local->value[i]=='\0'&&!(WORDSTRUC(string[i])||NUMBSTRUC(string[i])))
		{
			if (strcmp(local->value,"?:")==0)
			{
				while(*string!=":") string++;
				*string=' ';
			}//������Ŀ���������ʹ�䣺Ϊ�ո񲻴���
			return local;
		}
		local=local->next;
	}
	return NULL;
}

/** idenTell ��ʶ���ж� �����**/
SET_TOKEN *idenTell(char *string){
	int i,n;
	n=hashChar_lexer(*string);
	SET_TOKEN *local=tokens[IDENTIFIERS][n].next;
	while(local){
		for (i=0;local->value[i]!='\0';++i)
		{
			if (string[i]!=local->value[i])
			{
				break;
			}
		}
		if (local->value[i]=='\0'&&!(WORDSTRUC(string[i])||NUMBSTRUC(string[i])))
		{
			return local;
		}
		local=local->next;
	}
	local=(SET_TOKEN *)malloc(sizeof(SET_TOKEN));
	local->next=tokens[IDENTIFIERS][n].next;
	tokens[IDENTIFIERS][n].next=local;
	local->num=0;
	i=0;
	while(WORDSTRUC(string[i])||NUMBSTRUC(string[i])) i++;
	local->value=(char *)malloc(i*sizeof(char)+4);
	i=0;
	while(WORDSTRUC(string[i])||NUMBSTRUC(string[i])){
		local->value[i]=string[i];
		i++;
	}
	local->value[i]='\0';
	return local;
}

/**strTELl �ж��ַ����� **/
SET_TOKEN *strTell(char *string){
	int i=1,n;
	n=hashChar_lexer(string[1]);
	SET_TOKEN *local=tokens[IDENTIFIERS][n].next;
	while(local){
		for (i=1;local->value[i]!='\0';++i)
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
		local=local->next;
	}//����Ƿ��У�û����������
	local=(SET_TOKEN *)malloc(sizeof(SET_TOKEN));
	local->next=tokens[IDENTIFIERS][n].next;
	tokens[IDENTIFIERS][n].next=local;
	local->num=0;
	i=1;
	while(string[i]!='"'||string[i-1]=='\\') i++;
	local->value=(char *)malloc(i*sizeof(char)+4);
	local->value[++i]='\0';
	while(i--){
		local->value[i]=string[i];
	}
	return local;
}

/** ConNumTell  ���ֳ���**/
SET_TOKEN *ConNumTell(char *string){
	int i,n;
	SET_TOKEN *local;
	n=(int)string[0]%10;
	local=tokens_conNum[n].next;
	while(local){
		for (i=0;local->value[i]!='\0';++i)
		{
			if (string[i]!=local->value[i])
			{
				break;
			}
		}
		if (local->value[i]=='\0'&&!(NUMBSTRUC(string[i]))&&!(WORDSTRUC(string[i])))
		{
			return local;
		}
		local=local->next;
	}//����Ƿ��У�û����������
	local=(SET_TOKEN *)malloc(sizeof(SET_TOKEN));
	local->next=tokens_conNum[n].next;
	tokens_conNum[n].next=local;
	local->num=0;
	i=0;
	if(string[1]=='X'||string[1]=='x')
	{
		i=2;
		while(string[i]>='a'&&string[i]<='f'||string[i]>='A'&&string[i]<='F'||NUMBSTRUC(string[i]))
			i++;
	}
	while(NUMBSTRUC(string[i])) i++;
	if(string[i]=='.'){
		i++;
		while(NUMBSTRUC(string[i])) i++;
	}
	if(string[i]=='e'||string[i]=='E')
	{
		i++;
		if(string[i]=='+'||string[i]=='-')
		{
			i++;
		}
		while(NUMBSTRUC(string[i])) i++;
	}
	while(string[i]>='a'&&string<='z'||string[i]>='A'&&string<='Z') i++;
	local->value=(char *)malloc(i*sizeof(char)+4);
	local->value[i]='\0';
	while(i--){
		local->value[i]=string[i];
	}
	return local;
}

/** ConCharTell �ַ�����**/
SET_TOKEN_CONCHAR *ConCharTell(char *string){
	int i,n;
	SET_TOKEN_CONCHAR *local;
	n=(int)string[1]%10;
	local=tokens_conChar[n].next;
	while(local){
		for (i=1;local->value[i]!='\0';++i)
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
		local=local->next;
	}//����Ƿ��У�û����������
	local=(SET_TOKEN_CONCHAR *)malloc(sizeof(SET_TOKEN_CONCHAR));
	local->next=tokens_conChar[n].next;
	tokens_conChar[n].next=local;
	local->num=0;
	local->value[0]='\'';
	i=1;
	while(string[i]!='\''||string[i-1]=='\\'){
		local->value[i]=string[i];
		i++;
	}
	local->value[i]=string[i];
	local->value[i+1]='\0';
	return local;
}

/** string2file_lexer**/
/**
*����һ�д��벢д��
*�������֣�ö��δ����
**/
state string2file_lexer(char *rowString,FILE *aimfile){
	int lineNumber=0,tokenNumber,number;//����Ϊc�ļ����кţ�token��ţ����ִ���
	char *tokenStr;//token����
	int length;
	int i;
	SET_TOKEN *token_134;
	SET_TOKEN_KEY *token_2;
	SET_TOKEN_OTHER *token_56;
	SET_TOKEN_CONCHAR *token_3char;
	while(rowString[lineNumber]!='\0'){
		if (rowString[lineNumber]==' '||rowString[lineNumber]=='\t')
		{
			length=1;
		}else{//����˳�򾭹����ǵ�
			if (rowString[lineNumber]=='"')
			{//�ַ���
				token_134=strTell(&rowString[lineNumber]);
				length=strlen(token_134->value);
				tokenNumber=TOKEN_STR;
				tokenStr=token_134->value;
				number=++(token_134->num);
			}else if (rowString[lineNumber]=='\'')
			{//�ַ�����
				token_3char=ConCharTell(&rowString[lineNumber]);
				length=strlen(token_3char->value);
				tokenNumber=TOKEN_CON;
				tokenStr=token_3char->value;
				number=++(token_3char->num);
			}else if (rowString[lineNumber]>='0'&&rowString[lineNumber]<='9')
			{//���ֳ���
				token_134=ConNumTell(&rowString[lineNumber]);
				length=strlen(token_134->value);
				tokenNumber=TOKEN_CON;
				tokenStr=token_134->value;
				number=++(token_134->num);
			}else if (rowString[lineNumber]>='a'&&rowString[lineNumber]<='z'||
				rowString[lineNumber]>='A'&&rowString[lineNumber]<='Z'||
				rowString[lineNumber]=='_')//��ʶ�� �ؼ���
			{
				if (token_2=keyTell(&rowString[lineNumber]))
				{//�ؼ���
					length=strlen(token_2->value);
					tokenNumber=TOKEN_KEY;
					tokenStr=token_2->value;
					number=++(token_2->num);
				}else{//��ʶ��
					token_134=idenTell(&rowString[lineNumber]);
					length=strlen(token_134->value);
					tokenNumber=TOKEN_IDE;
					tokenStr=token_134->value;
					number=++(token_134->num);
				}
			}else {
				if(token_56=sepOprTell(&tokens_sep,&rowString[lineNumber]))
				{//�ָ���
					length=strlen(token_56->value);
					tokenNumber=TOKEN_SEP;
					tokenStr=token_56->value;
					number=++(token_56->num);
				}else if (token_56=sepOprTell(&tokens_opr,&rowString[lineNumber]))
				{//�����
					length=strlen(token_56->value);
					tokenNumber=TOKEN_OPR;
					tokenStr=token_56->value;
					number=++(token_56->num);
				}else{
					printf("%s����ɶ����!\n",rowString);
				}
			}
			fprintf(aimfile, "%-4d %-4d %-40s ",rowNumFile++,tokenNumber,tokenStr);
			fprintf(aimfile,"%-4d %-4d %-4d\n",rowNumber,lineNumber+1,number);
		}
		lineNumber+=length;
	}
	return OK;
}
