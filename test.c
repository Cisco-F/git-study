/*OPTR为运算符栈，OVS为操作数栈*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXSIZE 100

typedef struct stack{
    char data[MAXSIZE];
    int top;
}Stack, *pStack;

//初始化OPTR栈
void Init_Stack(pStack S)
{
    S->top = -1;
}

//判断进哪个栈 返回1进OVS栈，返回0进OPTR栈
bool catagory(char a)
{
    if(a >= '0' && a < '9')
        return true;
    else if(a == '+' || a == '-' || a == '*' || a == '/')
        return false;
    else{
        printf("非法算术表达式!");
        exit(0);
    }
    
}

//进栈
bool Push(pStack S, char a)
{
    if(S->top == -1)
        return false;
    S->top++;
    S->data[S->top] = a;
    return true;
}

//出栈
bool Pop(pStack S, char *a)
{
    if(S->top == -1)
        return false;
    *a = S->data[S->top];
    S->top--;
}

//获取OPTR栈顶元素
bool GetTop(pStack S, char *a)
{
    if(S->top == -1)
        return false;
    *a = S->data[S->top];
}

//运算符优先级比较 栈顶操作符优先级高则返回1
int Cmp(pStack S, char a)//a为待比较运算符，b为栈顶操作符
{
    char *b;
    int cmp;
    GetTop(S, b);
    switch(*b)
    {
        case '+': case '-':
            if(a == '*' || a == '/')
                cmp = 0;
            else
                cmp = 1;
            break;
        case '*': case '/':
            cmp = 1;
            break;
    }
    return cmp;
}

int main()
{
    Stack OPTR;    Init_Stack(&OPTR);
    Stack OVS;      Init_Stack(&OVS);

    printf("请输入无括号算术表达式:");
    char x;
    while(x = getchar() != '\n'){
        if(catagory(x)){
            Push(&OVS, x);
        }
        else
        {
            if(OPTR.top == -1)
                Push(&OPTR, x);
            else
            {
                switch(Cmp(&OPTR, x)){
                    case 0:
                        Push(&OPTR, x);

                }
            }
        }
    }
}