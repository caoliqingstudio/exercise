#include<stdio.h>

int make(int month){
    int number=0;
    for(month-=2;month>=0;month--){
        number+=(make(month)+1);
    }
    return number;
}

int main(){
    int n=12;
    int rab=1;
    printf("number = %d\n",make(n)+1);
    return 0;
}
