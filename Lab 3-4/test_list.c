#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "lista.h"

/**
 * Test pentru creare unui repository de oferte
 */
static void testCreate()
{
	Lista l = createList();
	assert(l.size == 0);

	destroyList(&l);
}

/**
 * Test pentru adaugarea unei oferte intr-un repo
 */
static void testAdd()
{
	Lista l = createList();
	Oferta o1 = createOferta(1, "teren", 100.0f, "Str. A", 50000);
	Oferta o2 = createOferta(2, "casa", 60.5f, "Str. B", 120000);

	assert(addList(&l, o1) == LIST_SUCCESS);
	assert(l.size == 1);

	assert(addList(&l, o2) == LIST_SUCCESS);
	assert(l.size == 2);

	assert(addList(&l, o2) == LIST_DUPLICATE);
	assert(l.size == 2);

	destroyList(&l);
}

static void testResize()
{
	Lista l = createList();

	for (int i = 0; i < LIST_CAP; i++)
	{
		char adresa[30];
		sprintf_s(adresa, sizeof(adresa), "Str. %d", i);

		Oferta o = createOferta(i + 1, "teren", 100.0f + i, adresa, 50000 + i);
		assert(addList(&l, o) == LIST_SUCCESS);
	}

	assert(l.size == LIST_CAP);
	assert(l.cap == LIST_CAP);

	Oferta extra = createOferta(1000, "casa", 200.0f, "Str. Extra", 150000);
	assert(addList(&l, extra) == LIST_SUCCESS);

	assert(l.size == LIST_CAP + 1);
	assert(l.cap == 2 * LIST_CAP + 1);

	destroyList(&l);
}

/**
 * Test pentru stergerea unui oferte dintr-un repository
 */
static void testDelete()
{
	Lista l = createList();
	assert(l.size == 0);

	Oferta o1 = createOferta(1, "teren", 100.0f, "Str. A", 50000);
	assert(addList(&l, o1) == LIST_SUCCESS);
	assert(l.size == 1);

	assert(deleteList(&l, 2) == LIST_NOT_FOUND);
	assert(deleteList(&l, 1) == LIST_SUCCESS);
	assert(l.size == 0);

	Oferta o2 = createOferta(1, "teren", 100.0f, "Str. A", 50000);
	Oferta o3 = createOferta(2, "casa", 60.5f, "Str. B", 120000);

	assert(addList(&l, o2) == LIST_SUCCESS);
	assert(addList(&l, o3) == LIST_SUCCESS);
	assert(l.size == 2);

	assert(deleteList(&l, 1) == LIST_SUCCESS);
	assert(l.size == 1);

	destroyList(&l);
}

/**
 * Test pentru actualizarea unei oferte dintr-un repository
 */
static void testUpdate()
{
	Lista l = createList();
	Oferta oVeche = createOferta(1, "teren", 100.0f, "Str. A", 50000);
	assert(updateList(&l, oVeche) == LIST_EMPTY);
	assert(addList(&l, oVeche) == LIST_SUCCESS);

	Oferta oNoua = createOferta(1, "casa", 60.5f, "Str. B", 120000);
	assert(updateList(&l, oNoua) == LIST_SUCCESS);
	assert(l.size == 1);
	assert(l.elems[0].id == 1);

	Oferta oInexistenta = createOferta(2, "apartament", 80.0f, "Str. C", 90000);
	assert(updateList(&l, oInexistenta) == LIST_NOT_FOUND);

	destroyList(&l);
	destroyOferta(&oInexistenta);
}

/**
 * Test pentru obtinerea tuturor ofertelor dintr-un repository
 */
static void testGetAll()
{
	Lista l = createList();
	Oferta o1 = createOferta(1, "teren", 100.0f, "Str. A", 50000);
	assert(addList(&l, o1) == LIST_SUCCESS);

	Oferta* oferte = getAll(&l);

	assert(listSize(&l) == 1);
	assert(oferte[0].id == o1.id);
	assert(strcmp(oferte[0].tip, "teren") == 0);
	assert(oferte[0].pret == 50000);

	destroyList(&l);
}

/**
 * Test pentru obtinerea dimensiunii unui repository
 */
static void testSize()
{
	Lista r = createList();
	assert(listSize(&r) == 0);

	Oferta o1 = createOferta(1, "teren", 100.0f, "Str. A", 50000);
	assert(addList(&r, o1) == LIST_SUCCESS);
	assert(listSize(&r) == 1);

	Oferta o2 = createOferta(2, "casa", 60.5f, "Str. B", 120000);
	assert(addList(&r, o2) == LIST_SUCCESS);
	assert(listSize(&r) == 2);

	destroyList(&r);
	assert(listSize(&r) == 0);

}


void testeLista()
{
	testCreate();
	testAdd();
	testResize();
	testDelete();
	testUpdate();
	testGetAll();
	testSize();
	printf("testLista() - toate testele au trecut cu succes!\n");
}