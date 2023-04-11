#include<stdio.h>
int main(void)
{
	int a,b,c,d;
	do{
		printf("请输入矩阵1行数:"); scanf("%d",&a);
		printf("请输入矩阵2列数:"); scanf("%d",&b);
		printf("请输入矩阵2行数:"); scanf("%d",&c);
		printf("请输入矩阵2列数:"); scanf("%d",&d);
		if(b!=c)
			printf("\a这两个矩阵不能相乘!\n");
	}while(b!=c);
	
	int mat1[100][100]={0};
	int mat2[100][100]={0};
	int sum[100][100]={0};
	int i,j,k;

	printf("请输入%d行%d列矩阵1:\n",a,b);
	for(i=0;i<a;i++){
		for(j=0;j<b;j++)
			scanf("%d",&mat1[i][j]);
	}

	printf("请输入%d行%d列矩阵2:\n",c,d);
	for(i=0;i<c;i++){
		for(j=0;j<d;j++)
			scanf("%d",&mat2[i][j]);
	}

	printf("两个矩阵乘积为:\n");
	for(i=0;i<a;i++){
		for(j=0;j<d;j++){
			for(k=0;k<b;k++)
				sum[i][j]+=(mat1[i][k] *mat2[k][j]);
		}
	}
    for(i=0;i<a;i++){
		for(j=0;j<d;j++)
			printf("%d\t",sum[i][j]);
		printf("\n");
	}
	return 0;
}