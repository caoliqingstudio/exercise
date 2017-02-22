int main()
{
	int n,x,result=0;
	int i;
	int j;
	int a[100000];
	scanf("%d %d",&n,&x);
	for (i=0; i < n; ++i)
	{
		scanf("%d",&a[i]);
		for (j = 0; j < i; ++j)
		{
			if ((a[j]^a[i])==x)
			{
				result++;
			}
		}
	}
	printf("%d",result);
	return 0;
}
