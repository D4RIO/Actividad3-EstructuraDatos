/********************************************************************************************
 Cree un programa utilizando listas enlazadas con puntero a cabeza y cola que contenga las
  siguientes funciones:
  - Eliminar todos los nodos con un valor dado por el usuario.
  - Diseña una función que devuelva un “corte” de la lista. Se recibirán dos índices i y j y se
  devolverá una nueva lista con punteros a cabeza y cola con una copia de los nodos que
  van del que ocupa la posición i al que ocupa la posición j − 1, ambos incluidos. La lista
  devuelta tendrá punteros a cabeza y cola
**********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct struct_node
{
	int num;
	struct struct_node *next;

} node;

typedef struct
{
	node *head;
	node *tail;
	int  longitude;

} st_lista;

int menu ();
st_lista ingresar_cabeza (st_lista list);
st_lista ingresar_cola (st_lista list);
void mostrar_lista (st_lista list);
void borrar_item_por_numero (st_lista list, int n);

int main (void)
{
	int option, n;

	st_lista list;

	list.head = list.tail = NULL;

	do
	{
		option = menu ();

		switch (option)
		{
		case 1:
			list = ingresar_cabeza (list);
			break;
		case 2:
			mostrar_lista (list);
			break;
		case 3:
			list = ingresar_cola (list);
			break;
		case 4:
			printf ("index of the number to be deleted: ");
			scanf ("%d", &n);
			borrar_item_por_numero (list, n);
		case 5:
			printf ("Thanks for using app");
			break;
		default:
			puts ("Option Incorrect");
			break;
		}
	} while (option != 5);


	return 0;
}

void borrar_nodo (node* node)
{
	free (node);
}

int contar (st_lista* list)
{
	return list->longitude;
}

st_lista ingresar_cabeza (st_lista list)
{
	node *nuevo_item = (node *) malloc (sizeof (node));

	if (nuevo_item)
	{
		puts("Enter a number: ");
		scanf("%d", &nuevo_item->num);
		nuevo_item->next = NULL;
	}
	if (! list.head)
	{
		list.head = list.tail = nuevo_item;
	}
	else
	{
		nuevo_item->next = list.head;
		list.head = nuevo_item;
	}

	list.longitude++;

	return list;
}

st_lista ingresar_cola (st_lista list)
{
	node *nuevo_item = (node *) malloc (sizeof (node));

	if (nuevo_item)
	{
		puts("Enter a number: ");
		scanf("%d", &nuevo_item->num);
		nuevo_item->next = NULL;
	}
	if (! list.head)
	{
		list.head = list.tail = nuevo_item;
	}
	else
	{
		list.tail->next = nuevo_item;
		list.tail = nuevo_item;
	}

	list.longitude++;

	return list;
}

void mostrar_lista (st_lista list)
{
	node *temp;

	for ( temp = list.head; temp; temp = temp->next)
	{
		printf("%d\t", temp->num);
	}
}

void borrar_item_por_numero(st_lista list, int n)
{
	if (list.head)
	{
		if(n == 0)
		{
			node *temp1 = list.head;
			list.head = list.head->next;
			borrar_nodo (temp1);
		}
		else if (n < list.longitude)
		{
			node *temp2 = list.head;
			int index = 0;
			while (index < (n-1))
			{
				temp2 = temp2->next;
				index++;
			}
			node *deleteItem = temp2->next;
			temp2->next = deleteItem->next;
			borrar_nodo (deleteItem);
			list.longitude--;
		}
	}
}

int menu()
{
	int option;
	puts ("");
	puts ("1- Enter head");
	puts ("2- Show list");
	puts ("3- Enter tail");
	puts ("4- Delete Item");
	puts ("5- Get Out");
	scanf ("%d", &option);

	return option;
}
