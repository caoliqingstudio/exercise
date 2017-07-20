#include <stdio.h>
int main(int argc, char const *argv[])
{
	char str[]="BEEAKFYDJXUQYHYJIQRYHTYJIQFBQDUYJIIKFUHCQD";
	int i,length,j;
	char c;
	length=strlen(str);
	for (i = 0; i < 26; ++i)
	{
		printf("i = %d:\n",i );
		for (j = 0; j < length; ++j)
		{
			c=str[j]+i;
			if(c>'Z'){
				c-=26;
			}
			putchar(c-'A'+'a');
		}
		printf("\n");
	}
	return 0;
}
