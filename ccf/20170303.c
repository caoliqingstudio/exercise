#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SS 101
#define QUKONG while(*start==' ')start++;
char name[100];
char href[100];
int tellState;
int tellState2;
int tellState3;
int tell(char **string){
    int i=0;
    tellState3=0;
    tellState2=0;
    tellState=0;
    while(**string!='\n'&&**string!='\0'){
        if(**string=='_'){
            if(tellState3==0){
                tellState3=1;
                printf("<em>");
            }else if(tellState==10){
                if(tellState2==0){
                    name[i++]='<';
                    name[i++]='e';
                    name[i++]='m';
                    name[i++]='>';
                    tellState2=1;
                }else{
                    tellState2=0;
                    name[i++]='<';
                    name[i++]='\\';
                    name[i++]='e';
                    name[i++]='m';
                    name[i++]='>';
                }
            }else{
                printf("<\em>");
                tellState3=0;
            }
            (*string)++;
        }else if(**string=='['){
            printf("<a href=\"");
            (*string)++;
            tellState=10;
            i=0;
        }else if(**string==']'){
            name[i]='\0';
            i=0;
            tellState=0;
            (*string)++;
        }else if(**string=='('){
            tellState=15;
            (*string)++;
            i=0;
        }else if(**string==')'){
            tellState=0;
            href[i]='\0';
            printf("%s\">%s<//a>",href,name);
            (*string)++;
        }else{
            if(tellState==0){
                putchar(**string);
            }else if(tellState==10){
                name[i++]=**string;
            }else if(tellState==15){
                href[i++]=**string;
            }else if(tellState2==1){
                name[i++]=**string;
            }
            (*string)++;
        }
    }
    return 0;
}
int main()
{
    char buf[101];
    char *start;
    int state=0;
    int level=0;
    int i,j,length;
    while(fgets(buf,BUF_SS,stdin)){
        length=strlen(buf);
        start=buf;
        if(length>1){
            while(*start!='\n'&&*start!='\0'){
                if(*start=='#'){
                    level=0;
                    while(*start=='#'){
                        level++;
                        start++;
                    }
                    printf("<h%d>",level);
                    QUKONG;
                    tell(&start);
                    printf("<\\h%d>\n");
                }else if(*start=='*'){
                    start++;
                    if(state==0){
                        printf("<ul>\n");
                    }
                    printf("<li>");
                    QUKONG;
                    state=20;
                    tell(&start);
                    printf("<\\li>\n");
                }else{
                    if(state==0) printf("<p>");
                    state=1;
                    tell(&start);
                    start++;
                }
            }
        }else{
            if(state==1){
                printf("<\\p>\n");
                state=0;
            }else if(state==20){
                printf("<\\ul>\n");
                state=0;
            }
        }
    }
    if(state==1){
        printf("<\\p>\n");
    }
    return 0;
}
