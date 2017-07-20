#include <stdio.h>
#include <stdlib.h>

int info[100001]={0};
int main()
{
    int n,m,i;
    int a,b,c,result=0;
    scanf("%d%d",&n,&m);
    for(i=0;i<m;i++){
        scanf("%d%d%d",&a,&b,&c);
        if(info[a]==0){
            info[a]=c;
        }else{
            info[a]=(info[a]>c?c:info[a]);
        }
        if(info[b]==0){
            info[b]=c;
        }else{
            info[b]=(info[b]>c?c:info[b]);
        }
    }
    for(i=1;i<=n;i++){
        result=(result>info[i]?result:info[i]);
    }
    printf("%d",result);
    return 0;
}