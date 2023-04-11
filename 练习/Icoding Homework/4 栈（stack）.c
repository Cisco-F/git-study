/*要求用户输入一串圆括号或花括号，然后指出它们之间的嵌套是否正确。*/
#include <stdbool.h>   /* C99 only */
#include <stdio.h>
#include <stdlib.h>
 
#define STACK_SIZE 100
 
/* external variables */
char contents[STACK_SIZE];
int top = 0;
 
 
void stack_overflow(void)
{
  printf("Stack overflow\n");
  exit(EXIT_FAILURE);
}
 
void stack_underflow(void)
{
  printf("Stack underflow\n");
  exit(EXIT_FAILURE);
}
 
 
void make_empty(void)
{
  top = 0;
}
 
bool is_empty(void)
{
  return top == 0;
}
 
bool is_full(void)
{
  return top == STACK_SIZE;
}
 
void push(char ch)
{
  if (is_full())
    stack_overflow();
  else
    contents[top++] = ch;
}
 
char pop(void)
{
  if (is_empty())
    stack_underflow();
  else
    return contents[--top];
 
  return '\0'; /* prevents compiler warning due to stack_underflow() call */
}
 
 
int main(void)
{
		char ch;
	int correct = 1;
	while(correct && (ch = getchar()) != '\n')
	{if(ch == '(' || ch == '{')
	push(ch);
	else if(ch == ')')
	correct = !is_empty() && pop() =='(';
	else if(ch == '}')
	correct = !is_empty() && pop() == '{';
	}
	if(correct && is_empty())
	{printf("Parentheses/braces are nested properly\n");}
	else printf("Parentheses/braces are NOT nested properly\n");
	return 0;
}