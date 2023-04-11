#include<stdio.h>
int main()
{
  int i,j,x,y;
  printf("Êä³ö¾Å¾Å³Ë·¨±í\n");

  printf("  |");
  
  for(x=1;x<=9;x++)
    printf("%3d",x);
  putchar('\n');
  
  printf("-------------------------------\n");
  
  for(y=1;y<=9;y++){
    printf("%d |",y);
    for(j=1;j<=9;j++)
      printf("%3d",j*y);
    putchar('\n');}

  return 0;
}