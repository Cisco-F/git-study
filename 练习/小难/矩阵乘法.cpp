#include<stdio.h>
int main(void)
{
	int a,b,c,d;
	do{
		printf("���������1����:"); scanf("%d",&a);
		printf("���������2����:"); scanf("%d",&b);
		printf("���������2����:"); scanf("%d",&c);
		printf("���������2����:"); scanf("%d",&d);
		if(b!=c)
			printf("\a���������������!\n");
	}while(b!=c);
	
	int mat1[100][100]={0};
	int mat2[100][100]={0};
	int sum[100][100]={0};
	int i,j,k;

	printf("������%d��%d�о���1:\n",a,b);
	for(i=0;i<a;i++){
		for(j=0;j<b;j++)
			scanf("%d",&mat1[i][j]);
	}

	printf("������%d��%d�о���2:\n",c,d);
	for(i=0;i<c;i++){
		for(j=0;j<d;j++)
			scanf("%d",&mat2[i][j]);
	}

	printf("��������˻�Ϊ:\n");
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