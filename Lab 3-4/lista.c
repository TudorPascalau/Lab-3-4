#include <string.h>
#include <stdlib.h>
#include "lista.h"

Lista createList()
{
	Lista l;

	l.size = 0;
	l.cap = LIST_CAP;

	l.elems = malloc(sizeof(Oferta) * l.cap);
	if (l.elems == NULL)
		l.cap = 0;

	return l;
}

void destroyList(Lista* l)
{
	for (int i = 0; i < l->size; i++)
		destroyOferta(&l->elems[i]);

	free(l->elems);
	l->size = 0;
	l->elems = NULL;
}


int ensureCapacity(Lista* l)
{
	if (l->size < l->cap)
		return LIST_SUCCESS;

	int newCap = l->cap * 2 + 1;
	Oferta* newElems = (Oferta*)malloc(sizeof(Oferta) * newCap);

	if (newElems == NULL)
		return LIST_INVALID;

	for (int i = 0; i < l->size; i++)
		newElems[i] = l->elems[i];

	free(l->elems);
	l->elems = newElems;
	l->cap = newCap;

	return LIST_SUCCESS;
}


int addList(Lista* l, Oferta o)
{
	if (ensureCapacity(l) != LIST_SUCCESS)
		return LIST_INVALID;


	for (int i = 0; i < l->size; i++)
		if (l->elems[i].id == o.id)
			return LIST_DUPLICATE;

	l->elems[l->size] = o;
	l->size++;

	return LIST_SUCCESS;
}


int deleteList(Lista* l, int id)
{
	if (l->size == 0)
		return LIST_EMPTY;

	for (int i = 0; i < l->size; i++)
		if (l->elems[i].id == id)
		{
			destroyOferta(&l->elems[i]);
			for (int j = i; j < l->size - 1; j++)
				l->elems[j] = l->elems[j + 1];
			l->size--;
			return LIST_SUCCESS;
		}

	return LIST_NOT_FOUND;
}


int updateList(Lista* l, Oferta o)
{
	if (l->size == 0)
		return LIST_EMPTY;

	for (int i = 0; i < l->size; i++)
		if (l->elems[i].id == o.id)
		{
			destroyOferta(&l->elems[i]);
			l->elems[i] = o;
			return LIST_SUCCESS;
		}

	return LIST_NOT_FOUND;
}


Oferta* getAll(Lista* r)
{
	return r->elems;
}


int listSize(const Lista* r)
{
	return r->size;
}