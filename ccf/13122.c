#include <stdio.h>

int main(int argc, char const *argv[])
{
	int result=0;
	char string[18];
	char c;
	scanf("%s",string);
	result=(string[0]-'0');
	result+=((string[2]-'0')*2);
	result+=((string[3]-'0')*3);
	result+=((string[4]-'0')*4);
	result+=((string[6]-'0')*5);
	result+=((string[7]-'0')*6);
	result+=((string[8]-'0')*7);
	result+=((string[9]-'0')*8);
	result+=((string[10]-'0')*9);
	result%=11;
	if (result==10)
	{
		c='X';
	}else{
		c=result+'0';
	}
	if (c==string[12])
	{
		printf("Right");
	}else{
		string[12]=c;
		puts(string);
	}
	return 0;
}
