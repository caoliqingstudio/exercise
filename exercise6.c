/*********************/
/*      递归         */
/*    行列式计算     */
/*********************/
//未完成
//
#include<stdio.h>

#define N 2

int cal(int n,int *a[N]){
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
            int b[n-1][n-1];
            int j,b_i;
            for(j=1;j<n;j++){
                int m;
                b_i=0;
                for(m=0;m<n;m++){
                    if(m!=i)
                        b[j-1][b_i++]=a[j][m];
                }
            }
            result+=(cal(n-1,b)*state*a[N-n+1][i]);
        }
    }
    return result;
}

int main(){
//    int i,j;
//    for(i=0;i<N;i++)
//        for(j=0;j<N;j++)
//            scanf("%d",&a[i][j]);

    int a[N][N]={1,1,1,1};
    printf("result = %d\n",cal(N,a));
    return 0;
}
