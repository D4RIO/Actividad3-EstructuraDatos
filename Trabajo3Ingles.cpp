/*Cree un programa utilizando listas enlazadas con puntero a cabeza y cola que contenga las
siguientes funciones:
- Eliminar todos los nodos con un valor dado por el usuario.
- Diseña una función que devuelva un “corte” de la lista. Se recibirán dos índices i y j y se
devolverá una nueva lista con punteros a cabeza y cola con una copia de los nodos que
van del que ocupa la posición i al que ocupa la posición j − 1, ambos incluidos. La lista
devuelta tendrá punteros a cabeza y cola.*/

#include <stdio.h>
#include <stdlib.h>

struct List
{
    int num;
    struct List *next;
};

typedef struct Node
{
    struct List *head;
    struct List *tail;
    int  longitude;
}SNode;

int Menu();
SNode EnterHead(SNode list);
SNode EnterTail(SNode list);
void ShowList(SNode List);
void DeleteItem(SNode list,int n);

int main(void)
{
    int option;

    SNode list;
    
    list.head=list.tail=NULL;

    do
    {
        option=Menu();

        switch (option)
        {
        case 1:
            list=EnterHead(list);
            break;
        case 2:
            ShowList(list);
            break;
        case 3:
            list=EnterTail(list);
            break;
        case 4:
            int n;
            printf("index of the number to be deleted: ");
            scanf("%d",&n);
            DeleteItem(list,n);
        case 5:
            printf("Thanks for using app");
            break;
        default:
            puts("Option Incorrect");
            break;
        }
    } while (option!=5);
    

    return 0;
}

void DeleteNode(List* node)
{
    free(node);
}

int Count(SNode* list)
{
    return list->longitude;
}

SNode EnterHead(SNode list)
{
    struct List *new_Item=(List *)malloc(sizeof(List));

    if (new_Item!=NULL)
    {
        puts("Enter a number: ");
        scanf("%d",&new_Item->num);
        new_Item->next=NULL;
    }
    if (list.head==NULL)
    {
        list.head=list.tail=new_Item;
    }
    else
    {
        new_Item->next=list.head;
        list.head=new_Item;
    }
    list.longitude++;

    return list;
}

SNode EnterTail(SNode list)
{
    struct List *new_Item=(List *)malloc(sizeof(List));

    if (new_Item!=NULL)
    {
        puts("Enter a number: ");
        scanf("%d",&new_Item->num);
        new_Item->next=NULL;
    }
    if (list.head==NULL)
    {
        list.head=list.tail=new_Item;
    }
    else
    {
        list.tail->next=new_Item;
        list.tail=new_Item;
    }
    list.longitude++;

    return list;
}

void ShowList(SNode list)
{
    List *temp;

    for ( temp = list.head; temp != NULL; temp = temp->next)
    {
        printf("%d\t",temp->num);
    }
}

void DeleteItem(SNode list, int n)
{
    List *temp;

    if (list.head)
    {
        if(n==0)
        {
            List *temp1=list.head;
            list.head=list.head->next;
            DeleteNode(temp1);
        }
        else if (n<list.longitude)
        {
            List *temp2=list.head;
            int index=0;
            while (index<(n-1))
            {
                temp2=temp2->next;
                index++;
            }
            List *deleteItem=temp2->next;
            temp2->next=deleteItem->next;
            DeleteNode(deleteItem);
            list.longitude--;
        }
    }
}

int Menu()
{
    int option;
    puts("");
    puts("1- Enter head");
    puts("2- Show Node");
    puts("3- Enter tail");
    puts("4- Delete Item");
    puts("5- Get Out");
    scanf("%d",&option);

    return option;
}
