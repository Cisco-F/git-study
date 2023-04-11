#include<stdio.h>
#include<stdlib.h>

typedef struct _node{
        int value;
        struct _node *next;
    }Node;

typedef struct _list{
    Node *head;
    Node *tail;
}List;

//添加节点
void add(List* pList, int number);
//打印链表
void print(List *pList);
//查找节点,找到返回1
int search(List *pList, int number);
//删除节点
void delete(List *pList, int number);
//清空链表
void clear(List *pList);

int main()
{
    List list;
    int number;
    list.head = list.tail = NULL;
    do{
        scanf("%d",&number);
        if(number!=-1)
            add(&list, number);
    }while(number != -1);
    print(&list);

    return 0;
}

void add(List* pList, int number)
{
    Node *p = (Node*)malloc(sizeof(Node));
    p->value = number;
    p->next = NULL;
    Node *last = pList->head;
    if(last){
        while(last->next){
            last = last->next;
        }
        last->next = p;
    }
    else{
        pList->head = p;
    }
}

void print(List *pList)
{
    Node *p;
    for(p = pList->head; p; p = p->next){
        printf("%d\t",p->value);
    }
}

int search(List *pList, int number)
{
    Node *p;
    int isFound = 0;
    for(p = pList->head; p; p = p->next){
        if(p->value == number){
            isFound = 1;
        }
    }
    return isFound;
}

void delete(List *pList, int number)
{
    Node *p, *q;
    for(p = pList->head, q = NULL;p; q = p, p = p->next){
        if(p->value == number){
            if(q){
                q->next = p->next;
            }
            else{
                pList->head = p->next;
            }
            free(p);
            break;
        }
    } 
}

void clear(List *pList)
{
    Node *p, *q;
    for(p = pList->head; p; p=q){
        q = p->next;
        free(p);
    }
}