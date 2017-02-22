int number=0;
int run(int m,int stack){
if(m>0){
run(m-1,stack+1);
}
if(stack>0){
if (m==0&&stack==1)
{
number++;
}else{
run(m,stack+-1);
}
}
return 0;
}
int main(int argc, char const *argv[])
{
int m;
scanf("%d",&m);
run(m,0);
printf("%d\n",number);
return 0;
}
