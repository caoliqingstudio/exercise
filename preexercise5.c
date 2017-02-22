int a[10]={0};
void _call(int n){
    int i;
    if(n<1){
        for(i=9;i>=0;i--){
            printf("%d",a[i]);
        }
        printf(" ");
    }else{
        for(i=0;i<10;i++){
            a[n-1]=i;
            _call(n-1);
        }
    }
}
int main(){
    _call(10);
    return 0;
}
