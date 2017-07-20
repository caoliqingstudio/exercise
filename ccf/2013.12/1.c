#include <stdio.h>
int num=0;
int move(int i,int **a,int temp){
    int j=num;
    for(;i<j;--j){
        a[j][0]=a[j-1][0];
        a[j][1]=a[j-1][1];
    }
    num++;
    a[i][0]=temp;
    a[i][1]=1;
    return 0;
}
int main(){
    int n,i,j,k,m,temp;
    int a[1001][2]={0};
    scanf("%d",&n);
    scanf("%d",&a[0][0]);
    a[0][0]=1;
    for(i=1;i<n;++i){
        scanf("%d",&temp);
        if(temp<a[0][0]){
            move(0,a,temp);
        }else if(temp>a[num][0]){
            a[num][0]=temp;
            a[num][1]=1;
        }else{
            for(j=0,k==num;j<=k;){
                m=(j+k)/2;
                if(a[m][0]<temp){
                    j=m+1;
                }else if(a[m][0]==temp){
                    ++a[m][1];
                    break;
                }else{
                    k=m-1;
                }
            }
            if(a[m][0]!=temp){
                move(j,a,temp);
            }
        }
    }
    j=0;
    for(i=0;i<=num;++i){
        if(a[i][1]>j){
            j=a[i][1];
            k=a[i][0];
        }else if(a[i][1]==j){
            if(a[i][0]<k){
                k=a[i][0];
            }
        }
    }
    printf("%d",k);
    return 0;
}
