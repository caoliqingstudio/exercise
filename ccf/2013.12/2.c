#include <stdio.h>
int main(int argc, char const *argv[])
{
	char a[20];
	unsigned int temp;
	scanf("%s",a);
	temp=a[0]-'0';
	temp+=(a[2]-'0')*2;
	temp+=(a[3]-'0')*3;
	temp+=(a[4]-'0')*4;
	temp+=(a[6]-'0')*5;
	temp+=(a[7]-'0')*6;
	temp+=(a[8]-'0')*7;
	temp+=(a[9]-'0')*8;
	temp+=(a[10]-'0')*9;
	temp%=11;
	if(temp==10){
		temp='X';
	}else{
        temp+='0';
	}
	if(temp==a[12]){
		printf("Right");
	}else{
		a[12]=temp;
		printf("%s", a);
	}
	return 0;
}
