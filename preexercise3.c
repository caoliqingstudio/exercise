long long num=0;
void taijie(int n){
    if(n>1){
        taijie(n-1);
        taijie(n-2);
    }else {
        num++;
    }
}
int main(){
    int n;
    scanf("%d",&n);
    taijie(n);
    printf("the number = %lld",num);
    return 0;
}
