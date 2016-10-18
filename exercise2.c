/*********************/
/*      递归         */
/*      汉诺塔问题   */
/*********************/
#include<stdio.h>

int num=0;//记录步数

void hannoi(int n,char first,char second,char aim){
    if(n>1){
        hannoi(n-1,first,aim,second);

        num++;
        printf("%d : %c to %c\n",num,first,aim);

        hannoi(n-1,second,first,aim);
    }else{
        num++;
        printf("%d : %c to %c\n",num,first,aim);
    }
}

int main(){
    int n;//盘子个数
    scanf("%d",&n);
    char first='A',second='B',aim='C';
    hannoi(n,first,second,aim);
    printf("%d",num);
    return 0;
}
