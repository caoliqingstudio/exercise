int main()
{
	int n;
	scanf("%d",&n);
	if (!n)
	{
		printf("1");
	}else{
		n=n%4;
		if (n==0)
		{
			printf("6");
		}else if (n==1)
		{
			printf("8");
		}else if (n==2)
		{
			printf("4");
		}else{
			printf("2");
		}
	}
	return 0;
}
