#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n,m;
    int x;
    int state=0;
    int result=0;
    scanf("%d%d",&n,&m);
    while(n--){
        scanf("%d",&x);
        state+=x;
        if(state>=m){
            state=0;
            result++;
        }
    }
    if(state!=0) result++;
    printf("%d",result);
    return 0;
}
