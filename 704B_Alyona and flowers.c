#include <stdio.h>

int main(){
	int n,m;
	int reslult=0,score;
	int a[100];
	int vi,vj;
	int i;
	scanf("%d %d",&n,&m);
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	for(i=0;i<m;i++){
		scanf("%d %d",&vi,&vj);
		score=0;
		for(vi--;vi<vj;vi++){
			score+=a[vi];
		}
		if(score>0){
			reslult+=score;
		}
	}
	printf("%d",reslult);
	return 0;
}