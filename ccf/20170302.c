#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,m;
    int i,j;
    int x,y;
    int state[1010];
    scanf("%d",&n);
    scanf("%d",&m);
    for(i=1;i<=n;i++){
        state[i]=i;
    }
    while(m--){
        scanf("%d%d",&x,&y);
        for(j=1;state[j]!=x;j++);
        if(y>0){
            for(i=j;i<j+y;i++){
                state[i]=state[i+1];
            }
            state[i]=x;
        }else{
            for(i=j;i>j+y;i--){
                state[i]=state[i-1];
            }
            state[i]=x;
        }
    }
    for(i=1;i<n;i++){
        printf("%d ",state[i]);
    }
    printf("%d",state[i]);
    return 0;
}
