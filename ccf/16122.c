#include <stdio.h>
int main(int argc, char const *argv[])
{
	int sss;
	int a;
	int s=0;
	int x;
	scanf("%d",&sss);
	if (sss<=3500)
	{
		s=sss;
	}else{
		a=sss-3500;
		if (a<=1455)
		{
			x=a*100/97;
			s=3500+x;
		}else if (a-=1455,a<=2700)
		{
			x=a*10/9;
			s=5000+x;
		}else if (a-=2700,a<=3600)
		{
			x=a*10/8;
			s=x+8000;
		}else if (a-=3600,a<=19500)
		{
			x=a*4/3;
			s=x+12500;
		}else if (a-=19500,a<=14000)
		{
			x=a*10/7;
			s=x+38500;
		}else if (a-=14000,a<=16250)
		{
			x=a*100/65;
			s=x+58500;
		}else
		{
			a-=16250;
			x=a*100/55;
			s=x+83500;
		}
	}
	printf("%d",s);
	return 0;
}
