#include<stdio.h>
int main()
{
	int i,j,k;
	int chengji[50];
	int fenbu[11]={0};

	do{
		printf("请输入样本个数(少于50):"); 
		scanf("%d",&k);
		if(k<1||k>50){
			printf("\a请输入合适个数!\n");
			printf("请输入%d个样本数据:\n",k);
		}
	}while(k<1||k>50);

	for(i=0;i<k;i++){
		do{
			printf("%2d号:",i+1);
			scanf("%d",&chengji[i]);
			if(chengji[i]<0||chengji[i]>100)
				printf("\a请输入合适的样本数据\n");
		}while(chengji[i]<0||chengji[i]>100);
	fenbu[chengji[i] /10]++;
	}
	printf("---分布表---\n");

	for(i=0;i<10;i++){
		printf("%3d -%3d:",i*10,i*10+9);
		for(j=0;j<fenbu[i];j++)
			printf("*");
		printf("\n");
	}
	printf("     100:");
	for(j=0;j<fenbu[10];j++)
		printf("*");
	
	return 0;
}