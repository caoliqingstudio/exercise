/*********************/
/**    water.in     **/
/**  内容输入文件   **/
/**    water.out    **/
/**  内容输出 文件  **/
/*********************/
#include <stdio.h>
#include <stdlib.h>

#define FILENAME_1 "water.in"
#define FILENAME_2 "water.out"
#define CHANGE(a,b,c) c=a,a=b,b=c

int water_time[2000];
int number;
int people[2000];
long long all_time=0;
double avr_time;

int BubbleSort();
int run();
int file_read();
int file_write();

int main(int argc, char const *argv[])
{
	int  least=0;
	if(file_read()==0){
		BubbleSort();
		run(0,0);
		avr_time=((double)all_time)/number;
		file_write();
	}
	return 0;
}



int BubbleSort(){
	int i,j;
	int temp_time,temp_people;
	for (i = 0; i < number-1; ++i)
	{
		for (j = number-1; j >i; --j)
		{
			if (water_time[j]<water_time[j-1])
			{
				CHANGE(water_time[j],water_time[j-1],temp_time);
				CHANGE(people[j],people[j-1],temp_people);
			}
		}
	}
	return 0;
}
/*两个都一样*/
int run(int i,int temp_time){
	if (i<number)
	{
		all_time+=temp_time;
		temp_time+=water_time[i];
		run(i+1,temp_time);
	}
	return 0;
}
/*两个都可以*//*
int run(int i,int temp_time){
	for(i;i<number-1;i++){
        all_time+=water_time[i]*(number-i-1);
	}
}
*/
int file_read(){
	FILE  *fp;
	char c[10];
	int i=0;
	if ((fp=fopen(FILENAME_1,"r"))==NULL){
	    fclose(fp);
		printf("can't find the file!\n");
		return 1;
	}
	/***************/
	while(c[i]=(char)fgetc(fp),c[i]!='\n'){
		i++;
	}
	c[i]='\0';
	number=atoi(c);
	//printf("%d \n",number);//
	/****************/
	int j=0;
	i=0;
	while(c[i]=(char)fgetc(fp),c[i]!=EOF&&c[i]!='\n'){
		if (c[i]==' ')
		{
			c[i]='\0';
			water_time[j]=atoi(c);
			people[j]=j+1;
           // printf("%d ",water_time[j]);//
           //printf("%d ",people[j]);
			j++;
			i=-1;
		}
		i++;
	}
	c[i]='\0';
    water_time[j]=atoi(c);
    people[j]=j+1;
    //printf("%d ",water_time[j]);
    //printf("%d ",people[j]);
	fclose(fp);
	return 0;
}

int file_write(){
    FILE * fp=fopen(FILENAME_2,"w");
    int i;
    for (i = 0; i < number; ++i)
    {
        //printf("\n%d",people[i]);
    	fprintf(fp, "%d ",people[i]);
    }
    //printf("\n%.2lf",avr_time);
	fprintf(fp, "\n%.2lf",avr_time);
	fclose(fp);
	return 0;
}
