int cal(int n,int *a[2]){
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
            result+=(cal(n-1,b)*state*a[2-n+1][i]);
        }
    }
    return result;
}
int main(){
    int a[2][2]={1,1,1,1};
    printf("result = %d\n",cal(2,a));
    return 0;
}
