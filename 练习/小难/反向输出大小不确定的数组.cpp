/*�Զ�������Ԫ�ظ���*/
#include<stdio.h>

int main()
{
    int v[1000];
    int cnt = 0;
    char a;
    do{
        scanf("%d", &v[cnt]);
        cnt++;
    }while(a=getchar()!='\n');

    printf("�������\n");
    
    for(int i=cnt-1;i>=0;i--)
        printf("v[%d]=%d\n",cnt-1-i,v[i]);
    
    return 0;
}