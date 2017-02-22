int gcd_cal(int n1,int n2){
int c=n1%n2;
if(c){
n2=gcd_cal(n2,c);
}
return n2;
}
int main(){
int a,b;
scanf("%d%d",&a,&b);
int gcd=gcd_cal(a,b);
printf("gcd = %d; lcm = %d\n",gcd,a*b/gcd);
return 0;
}
