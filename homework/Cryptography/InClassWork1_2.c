/*#include <stdio.h>
int main(int argc, char const *argv[])
{
	char str[]="text";
	int x1,x2,y1,y2,length,j;
	char c;
	length=strlen(str);
	for (j = 0; j < length; j+=2)
	{
		x1=str[j]-'a';
		x2=str[j+1]-'a';
		y1=5*x1+14*x2;
		y2=14*x1+17*x2;
		y1=y1%26;
		y2=y2%26;
		printf("%c : %d : %d :%c \n",str[j],x1,y1,'a'+y1);
		printf("%c : %d : %d :%c \n",str[j+1],x2,y2,'a'+y2);
	}
	return 0;
}/*¼ÓÃÜ*/
/*½âÃÜ*/
#include <stdio.h>
int main(int argc, char const *argv[])
{
	char str[]="vwrv";
	int x1,x2,y1,y2,length,j;
	char c;
	length=strlen(str);
	for (j = 0; j < length; j+=2)
	{
		x1=str[j]-'a';
		x2=str[j+1]-'a';
		y1=5*x1+2*x2;
		y2=2*x1+3*x2;
		y1=y1%26;
		y2=y2%26;
		printf("%c : %d : %d :%c \n",str[j],x1,y1,'a'+y1);
		printf("%c : %d : %d :%c \n",str[j+1],x2,y2,'a'+y2);
	}
	return 0;
}
/**/
