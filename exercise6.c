/*********************/
/*      递归         */
/*    行列式计算     */
/*********************/
//未完成
//
#include<stdio.h>

#define N 2

int a[N][N]={1,1,1,1};

int cal(int n){
    int result=0,state;
    if(n==1){
        result=a[0][0];
    }else{
        int i;
        for(i=0;i<n;i++){
            if((i+n+1)%2){
                state=-1;
            }else{
                state=1;
            }
            result+=(cal(n-1)*state*a[N-n+1][i]);
        }
    }
    return result;
}

int main(){
//    int i,j;
//    for(i=0;i<N;i++)
//        for(j=0;j<N;j++)
//            scanf("%d",&a[i][j]);
    printf("result = %d\n",cal(N));
    return 0;
}
