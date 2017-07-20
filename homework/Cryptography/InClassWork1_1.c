#include <stdio.h>
int main(int argc, char const *argv[])
{
	char str[]="XICFP";
	int x,y,length,j;
	char c;
	length=strlen(str);
	for (j = 0; j < length; ++j)
	{
		y=str[j]-'A';
		x=(y-10)*9+26*10;
		x=x % 26;
		c='A'+x;
		printf("%c : %d : %d :%c \n",str[j],y,x,c);
	}
	return 0;
}
