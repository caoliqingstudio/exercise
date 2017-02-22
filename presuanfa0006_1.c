typedef char state;
int n;
int length[100];
state length_state[100];
state length_state_final[100];
double area=-1;
double length_all;
int tell_opera(int length_a,int length_b,int length_c){
	if (length_a+length_b<=length_c){
	}else if (length_a+length_c<=length_b){
	}else if (length_b+length_c<=length_a){
	}else{
		double area_temp=length_all*(length_all-length_a)
			*(length_all-length_b)*(length_all-length_c);
		if (area==-1||area<area_temp){
			area=area_temp;
			int j;
			for(j=0;j<n;j++){
				length_state_final[j]=length_state[j];
			}
		}
	}
	return 0;
}
int set(int i,int length_a,int length_b,int length_c){
	if (i>=n)
	{
		tell_opera(length_a,length_b,length_c);
	}else{
		length_state[i]=1;
		set(i+1,length_a+length[i],length_b,length_c);
		length_state[i]=2;
		set(i+1,length_a,length_b+length[i],length_c);
		length_state[i]=3  ;
		set(i+1,length_a,length_b,length_c+length[i]);
	}
	return 0;
}
int main(int argc, char const *argv[])
{
	scanf("%d",&n);
	int i;
	for (i = 0; i < n; ++i)
	{
		scanf("%d",&length[i]);
		length_all+=length[i];
	}
	length_all/=2;
	length_state[0]=1;
	set(1,length[0],0,0);
	if (area==-1)
	{
		printf("Are you kidding?\n");
	}else{
		printf("the area is %d\n",(int)(sqrt(area)*100));
		printf("length of  A : ");
		for (i = 0; i < n; ++i){
			if (length_state_final[i]==1)
			{
				printf("%d ",length[i]);
			}
		}
		printf("\nlength of  B : ");
		for (i = 0; i < n; ++i){
			if (length_state_final[i]==2)
			{
				printf("%d ",length[i]);
			}
		}printf("\nlength of  C  ");
		for (i = 0; i < n; ++i){
			if (length_state_final[i]==3  )
			{
				printf("%d ",length[i]);
			}
		}
	}
	return 0;
}
