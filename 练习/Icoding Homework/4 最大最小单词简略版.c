/*��д�����ҳ�һ�鵥���С���С�����ʺ͡���󡱵��ʡ�

�û����뵥�ʺ󣬳�������ֵ�˳�����������ǰ��������ĵ��ʡ�

���û�����4����ĸ�ĵ���ʱ������ֹͣ���롣�������е��ʶ�������20����ĸ��*/
#include <stdio.h>
#include <string.h>
 
 
int main()
{
    
    char current[21];
    char max[21],min[21];
   
    scanf("%s",current);
     strcpy(max,current);
     strcpy(min,current);
    for(;;)
    {
    scanf("%s",current);
    if(strlen(current)!= 4)
    {
     
        if(strcmp(current,max)>=0)
        {
          
          strcpy(max,current);
        }
        if(strcmp(current,min)<=0){
           strcpy(min,current);
          
        }
    }
    
        else 
		{if(strcmp(current,max)>=0)
		        {
		          
		          strcpy(max,current);
		        }
		        if(strcmp(current,min)<=0){
		           strcpy(min,current);
		          
		        }
		
		break;}
    }
    printf("Smallest word: %s\n",min);
    printf("Largest word: %s\n",max);
    return 0;
}