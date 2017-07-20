#include <stdio.h>

int main(){
    int n,x,result=0,temp;
    int s[1001];
    int i,j;
    scanf("%d",&n);
    scanf("%d",&s[0]);
    for(i=1;i<n;i++){
        scanf("%d",&x);
        j=i;
        while(j&&x<s[j-1]){
            s[j]=s[j-1];
            j--;
        }
        s[j]=x;
    }
    x=s[0];
    j=x;
    temp=1;
    for(i=1;i<n;i++){
        if(x==s[i]){
            temp++;
            if(temp>result){
                result=temp;
                j=x;
            }
        }else{
            temp=1;
            x=s[i];
        }
    }
    printf("%d",j);
}
