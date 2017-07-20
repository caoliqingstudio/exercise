#include <stdio.h>
int main()
{
	int n,a,b,i=1,j,k,l;
	char string[100010];
	scanf("%d%d%d",&n,&a,&b);
	while(getchar()!='\n');
	while(i<=n){
		string[i++]=getchar();
	}
	if (string[a]==string[b])
	{
		printf("0");
	}else{
		i=b;j=b;
		while(string[i]==string[b]){
            i++;
            if(i>n){
                i=200000;
                break;
            }
		}
		while(string[j]==string[b]){
            j--;
            if(j<1){
                j=-100000;
                break;
            }
		}
		k=a;l=a;
		while(string[k]==string[a]){
            k++;
            if(k>n){
                k=200000;
                break;
            }
		}
		while(string[l]==string[a]){
            l--;
            if(l<1){
                l=-100000;
                break;
            }
		}
		n=a-b>0?a-b:b-a;
		n=n>a-l?a-l:n;
		n=n>k-a?k-a:n;
		n=n>b-j?b-j:n;
		n=n>i-b?i-b:n;
        printf("%d",n);
	}
	return 0;
}
