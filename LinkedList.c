#include<stdio.h>
#include<malloc.h>

typedef struct node{
    char data;
    struct node *next;
}Node, *pList;

//初始化链表
void InisList(pList *L)
{
    *L = (Node*)malloc(sizeof(Node));
    (*L)->next = NULL;
}

//头插法建立链表
void CreateFromHead(pList L)
{
    char tmp;
    Node *p;
    int flag = 1;
    while(flag){
        tmp = getchar();
        if(tmp!='$'){
            p = (Node*)malloc(sizeof(Node));
            p->data = tmp;
            p->next = L->next;
            L->next = p;
        }
        else flag = 0;
    }
}

//尾插法建立链表
void CreateFromTail(pList L)
{
    char tmp;
    Node *p, *c;
    c = L;
    int flag = 1;
    while(flag){
        tmp = getchar();
        if(tmp!='$'){
            p = (Node*)malloc(sizeof(Node));
            p->data = tmp;
            c->next = p;
            c = p;
        }
        else
        {
            flag = 0;
            p->next = NULL;
        }
    }
}

//逆转链表
pList Reverse(pList L)
{
    Node *p1, *p2;
    p1 = p2 = NULL;
    while(L){
        p1 = L->next;
        L->next = p2;
        p2 = L;
        L = p1;
    }
    return p2;
}

int main()
{
    pList L;
    L = (pList)malloc(sizeof(Node));
    L->next = NULL;

    // InisList(&L);
    CreateFromTail(L);
    for(Node *p = L; p; p = p->next){
        printf("%c ", p->data);
    }

    return 0;
}