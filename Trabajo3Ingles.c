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
#include <string.h>

// esta es la estructura de cada nodo
typedef struct struct_node
{
	int num;
	struct struct_node *next;

} node;

// esta estructura es solo para un handler de la lista
typedef struct
{
	node *cabeza;
	node *cola;
	int  longitud;

} st_lista;

int menu ();
void ingresar_cabeza (st_lista *list); // procedimiento que modifica la lista
void ingresar_cola (st_lista *list); // procedimiento que modifica la lista
void mostrar_lista (st_lista list);
void borrar_item_por_numero (st_lista *list, int n); // procedimiento que modifica la lista
void imprimir_corte (st_lista l, int i, int j);
st_lista *obtener_corte (st_lista l, int i, int j); // se debe borrar la lista creada
void destruir_contenido_de_lista (st_lista *l); // no hace free sobre l

int main (void)
{
	int option, n, i, j;

	st_lista list;

	list.cabeza = list.cola = NULL;
	list.longitud = 0; // no estabas inicializando (!)

	do
	{
		option = menu ();

		switch (option)
		{
		case 1:
			ingresar_cabeza (&list);
			break;
		case 2:
			mostrar_lista (list);
			break;
		case 3:
			ingresar_cola (&list);
			break;
		case 4:
			printf ("index of the number to be deleted: ");
			scanf ("%d", &n);
			borrar_item_por_numero (&list, n);
			break;
		case 5:
			printf ("Thanks for using app");
			break;
		case 6:
			printf ("lower index: ");
			scanf ("%d", &i);
			printf ("higher index: ");
			scanf ("%d", &j);
			imprimir_corte (list, i, j);
			break;
		default:
			puts ("Option Incorrect");
			break;
		}
	} while (option != 5);

	destruir_contenido_de_lista (&list);

	return 0;
}

void borrar_nodo (node* node)
{
	free (node);
}

int contar (st_lista* list)
{
	return list->longitud;
}

void ingresar_cabeza (st_lista *list)
{
	node *nuevo_item = (node *) malloc (sizeof (node));

	if (nuevo_item)
	{
		puts("Enter a number: ");
		scanf("%d", &nuevo_item->num);
		nuevo_item->next = NULL;
	}
	if (! list->cabeza)
	{
		list->cabeza = list->cola = nuevo_item;
	}
	else
	{
		nuevo_item->next = list->cabeza;
		list->cabeza = nuevo_item;
	}

	list->longitud++;
}

void ingresar_cola (st_lista *list)
{
	node *nuevo_item = (node *) malloc (sizeof (node));

	if (nuevo_item)
	{
		puts("Enter a number: ");
		scanf("%d", &nuevo_item->num);
		nuevo_item->next = NULL;
	}
	if (! list->cabeza)
	{
		list->cabeza = list->cola = nuevo_item;
	}
	else
	{
		list->cola->next = nuevo_item;
		list->cola = nuevo_item;
	}

	list->longitud++;
}

void mostrar_lista (st_lista list)
{
	node *temp;

	for ( temp = list.cabeza; temp; temp = temp->next)
	{
		printf("%d\t", temp->num);
	}
}

void borrar_item_por_numero(st_lista *list, int n)
{
	if (list->cabeza)
	{
		// nadie va a borrar el elemento 0, lo normal
		// es pensarlo que el elemento 1 es el 1ro
		if(n == 1)
		{
			node *temp1 = list->cabeza;
			list->cabeza = list->cabeza->next;
			borrar_nodo (temp1);
		}
		// n hasta la longitud de la lista, sino no podés borrar el último
		else if (n <= list->longitud)
		{
			node *temp2 = list->cabeza;

			// el 'while' implementado acá era un 'for'
			// y debía ir desde 1 a (n-1), o un intervalo equivalente
			// (el intervalo era muy grande)
			for (int i = 1; i < (n-1); i++)
				temp2 = temp2->next;

			node *deleteItem = temp2->next;
			temp2->next = deleteItem->next;
			borrar_nodo (deleteItem);
			list->longitud--;
		}
	}
}

void destruir_contenido_de_lista(st_lista *l)
{
	node *proximo = l->cabeza;
	node *del;

	while (proximo)
	{
		del = proximo;
		proximo = proximo->next;
		free (del);
	}
}

st_lista *obtener_corte (st_lista l, int i, int j)
{
	printf ("l-longitud[%d]\n",l.longitud);
	if ((i > l.longitud) || (j > l.longitud))

		return NULL;

	else
	{
		// nueva lista
		st_lista *r = (st_lista*) malloc (sizeof (st_lista));
		node *tmp, *tmp_copia;

		// saltear los primeros
		tmp = l.cabeza;
		for (int it = 1; it < i; it++)
		{
			tmp = tmp->next;
		}

		// crear un nodo copiado
		node *copia = (node*) malloc (sizeof (node));
		memcpy ((void*) copia, (void*) tmp, sizeof(node));

		// poner como único nodo de la nueva lista
		r->cabeza = r->cola = copia;

		// nodo a nodo del corte
		tmp_copia = r->cabeza;
		for (int it = i; it < j; it++)
		{
			tmp = tmp->next;
			printf ("2do for [%d] it=[%d]\n", tmp->num, it);
			// crear copias
			copia = (node*) malloc (sizeof (node));
			memcpy ((void*) copia, (void*) tmp, sizeof(node));

			// avance y construcción de la lista copiada
			tmp_copia->next = copia;
			tmp_copia = copia;
		}

		tmp_copia->next = NULL;

		return r;
	}
}

void imprimir_corte (st_lista l, int i, int j)
{
	st_lista *l2 = obtener_corte (l, i, j);

	if (l2)
	{
		mostrar_lista ( *l2 );

		destruir_contenido_de_lista ( l2 );
		free ( l2 );
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
	puts ("6- Get Sublist");
	scanf ("%d", &option);

	return option;
}
