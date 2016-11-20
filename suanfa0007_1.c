/*********************/
/**    blast.in     **/
/**  内容输入文件   **/
/**    blast.out    **/
/**  内容输出 文件  **/
/*********************/
#include <stdio.h>
#include <stdlib.h>

#define FILENAME_1 "blast.in"
#define FILENAME_2 "blast.out"

char string_1[2000];
char string_2[2000];
int length;
int  distance;
int length_1=0,length_2=0;

int run();
int file_read();
int file_write();

int main(int argc, char const *argv[])
{
	int  least=0;
	if(file_read()==0){
		file_write(run(0,0));
	}
	return 0;
}

int cmp(char c_a,char c_b){
	if (c_a==c_b)
	{
		return 0;
	}else if (c_a==' '||c_b==' '){
		return distance;
	}else{
		int diff_distance;
		diff_distance=c_a-c_b;
		return (diff_distance>0?diff_distance:-diff_distance);
	}
	return 0;
}

int run(int i,int j){
	if (i<length_1||j<length_2)
	{
		if (i>=length_1)
		{
			return run(i,j+1)+cmp(' ',string_2[j]);
		}
		if (j>=length_2)
		{
			return run(i+1,j)+cmp(string_1[i],' ');
		}
		int min=0;
		int min_v;
		/***************************/
		min=run(i+1,j+1)+cmp(string_1[i],string_2[j]);
		/***************************/
		min_v=run(i+1,j)+cmp(string_1[i],' ');
		if (min_v<min)
		{
			min=min_v;
		}
		/****************************/
		min_v=run(i,j+1)+cmp(' ',string_2[j]);
		if (min_v<min)
		{
			min=min_v;
		}
		return min;
	}
	return 0;
}

int file_read(){
	FILE  *fp;
	char c;
	if ((fp=fopen(FILENAME_1,"r"))==NULL){
	    fclose(fp);
		printf("can't find the file!\n");
		return 1;
	}
	while(c=(char)fgetc(fp),c!='\n'){
		string_1[(length_1)++]=c;
	}
	while(c=(char)fgetc(fp),c!='\n'){
		string_2[(length_2)++]=c;
	}
	distance=fgetc(fp)-'0';
	fclose(fp);
	return 0;
}

int file_write(int least){
    printf("%d",least);
    FILE * fp=fopen(FILENAME_2,"w");
	fprintf(fp, "%d\n",least);
	fclose(fp);
	return 0;
}
