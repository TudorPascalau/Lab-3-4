#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "service.h"

/**
 * Test pentru crearea unui serviciu de oferte.
 */
static void testCreateService()
{
	Lista repo = createList();
	ValidatorOferta validator = createValidator();
	ServiceOferta service = createService(&repo, &validator);

	assert(service.oferte == &repo);
	assert(service.validator == &validator);

	destroyService(&service);
}

/**
 * Test pentru distrugerea unui serviciu de oferte.
 */
static void testeDestroyService()
{
	Lista repo = createList();
	ValidatorOferta validator = createValidator();
	ServiceOferta service = createService(&repo, &validator);

	destroyService(&service);
	assert(service.oferte == NULL);
	assert(service.validator == NULL);
}

/**
 * Test pentru adaugarea unei oferte in serviciu.
 */
static void testAddOferta()
{
	Lista r = createList();
	ValidatorOferta v = createValidator();
	ServiceOferta s = createService(&r, &v);

	int result = addOferta(&s, 1, "apartament", 50.0f, "Strada A", 100000);
	assert(result == SERVICE_SUCCESS);
	assert(getSize(&s) == 1);

	result = addOferta(&s, 1, "", 50.0f, "Strada A", 100000);
	assert(result == SERVICE_VALIDATION_ERROR);
	assert(getSize(&s) == 1);

	result = addOferta(&s, 1, "apartament", 50.0f, "Strada A", 100000);
	assert(result == SERVICE_REPO_ERROR);
	assert(getSize(&s) == 1);

	destroyService(&s);
}

/**
 * Test pentru stergerea unei oferte din serviciu.
 */
static void testStergeOferta()
{
	Lista r = createList();
	ValidatorOferta v = createValidator();
	ServiceOferta s = createService(&r, &v);

	int result = stergeOferta(&s, 1);
	assert(result == SERVICE_REPO_ERROR);
	assert(getSize(&s) == 0);

	addOferta(&s, 1, "apartament", 50.0f, "Strada A", 100000);
	assert(getSize(&s) == 1);
	result = stergeOferta(&s, 1);
	assert(result == SERVICE_SUCCESS);
	assert(getSize(&s) == 0);

	result = stergeOferta(&s, 1);
	assert(result == SERVICE_REPO_ERROR);
	assert(getSize(&s) == 0);

	destroyService(&s);
}

/**
 * Test pentru actualizarea unei oferte din serviciu.
 */
static void testUpdateOferta()
{
	Lista r = createList();
	ValidatorOferta v = createValidator();
	ServiceOferta s = createService(&r, &v);

	int result = updateOferta(&s, 1, "", 50.0f, "Strada A", 100000);
	assert(result == SERVICE_VALIDATION_ERROR);
	assert(getSize(&s) == 0);

	result = updateOferta(&s, 1, "apartament", 50.0f, "Strada A", 100000);
	assert(result == SERVICE_REPO_ERROR);
	assert(getSize(&s) == 0);

	addOferta(&s, 1, "apartament", 50.0f, "Strada A", 100000);
	assert(getSize(&s) == 1);
	result = updateOferta(&s, 1, "casa", 100.0f, "Strada B", 200000);
	assert(result == SERVICE_SUCCESS);
	assert(strcmp(s.oferte->elems[0].tip, "casa") == 0);
	assert(s.oferte->elems[0].suprafata == 100.0f);
	assert(strcmp(s.oferte->elems[0].adresa, "Strada B") == 0);
	assert(s.oferte->elems[0].pret == 200000);

	destroyService(&s);
}

static void testGetOferte()
{
	Lista repo = createList();
	ValidatorOferta val = createValidator();
	ServiceOferta service = createService(&repo, &val);

	addOferta(&service, 1, "casa", 120.5f, "Strada A", 90000);
	addOferta(&service, 2, "teren", 300.0f, "Strada B", 50000);
	addOferta(&service, 3, "apartament", 70.0f, "Strada C", 70000);

	Oferta* oferte = getOferte(&service);
	assert(oferte != NULL);
	assert(getSize(&service) == 3);

	assert(oferte[0].id == 1);
	assert(strcmp(oferte[0].tip, "casa") == 0);
	assert(oferte[0].suprafata == 120.5f);
	assert(strcmp(oferte[0].adresa, "Strada A") == 0);
	assert(oferte[0].pret == 90000);

	destroyService(&service);
}


/**
 * Test pentru sortarea ofertelor din serviciu.
 */
static void testSortOferte()
{
	Lista repo = createList();
	ValidatorOferta val = createValidator();
	ServiceOferta service = createService(&repo, &val);

	addOferta(&service, 1, "casa", 120.5f, "Strada A", 90000);
	addOferta(&service, 2, "teren", 300.0f, "Strada B", 50000);
	addOferta(&service, 3, "apartament", 70.0f, "Strada C", 70000);

	Oferta* rez = NULL;
	int n = sortOferte(&service, &rez, cmpPret);

	assert(rez != NULL);
	assert(n == 3);
	assert(rez[0].pret == 50000);
	assert(rez[1].pret == 70000);
	assert(rez[2].pret == 90000);
	free(rez);

	n = sortOferte(&service, &rez, cmpPretDescresc);

	assert(rez != NULL);
	assert(n == 3);
	assert(rez[0].pret == 90000);
	assert(rez[1].pret == 70000);
	assert(rez[2].pret == 50000);
	free(rez);

	n = sortOferte(&service, &rez, cmpTip);

	assert(rez != NULL);
	assert(n == 3);
	assert(strcmp(rez[0].tip, "apartament") == 0);
	assert(strcmp(rez[1].tip, "casa") == 0);
	assert(strcmp(rez[2].tip, "teren") == 0);
	free(rez);

	n = sortOferte(&service, &rez, cmpTipDescresc);

	assert(rez != NULL);
	assert(n == 3);
	assert(strcmp(rez[0].tip, "teren") == 0);
	assert(strcmp(rez[1].tip, "casa") == 0);
	assert(strcmp(rez[2].tip, "apartament") == 0);
	free(rez);

	destroyService(&service);
}

/**
 * Test pentru filtrarea ofertelor din serviciu.
 */
void testFilterOferte(void)
{
	Lista repo = createList();
	ValidatorOferta val = createValidator();
	ServiceOferta service = createService(&repo, &val);

	addOferta(&service, 1, "casa", 120.5f, "Strada A", 90000);
	addOferta(&service, 2, "teren", 300.0f, "Strada B", 50000);
	addOferta(&service, 3, "apartament", 70.0f, "Strada C", 70000);
	addOferta(&service, 4, "teren", 150.0f, "Strada D", 65000);

	Oferta* rez = NULL;
	int n = filterOferte(&service, &rez, FILTRU_SUPRAFATA, "", 100.0f, 0);

	assert(rez != NULL);
	assert(n == 3);
	assert(rez[0].suprafata >= 100.0f);
	assert(rez[1].suprafata >= 100.0f);
	assert(rez[2].suprafata >= 100.0f);
	free(rez);

	n = filterOferte(&service, &rez, FILTRU_TIP, "teren", 0, 0);

	assert(rez != NULL);
	assert(n == 2);
	assert(strcmp(rez[0].tip, "teren") == 0);
	assert(strcmp(rez[1].tip, "teren") == 0);
	free(rez);

	n = filterOferte(&service, &rez, FILTRU_PRET, "", 0, 70000);

	assert(rez != NULL);
	assert(n == 3);
	assert(rez[0].pret <= 70000);
	assert(rez[1].pret <= 70000);
	assert(rez[2].pret <= 70000);
	free(rez);

	destroyService(&service);
}

void testeService()
{
	testCreateService();
	testeDestroyService();
	testAddOferta();
	testStergeOferta();
	testUpdateOferta();
	testGetOferte();
	testSortOferte();
	testFilterOferte();
	printf("testeService() - toate testele au trecut cu succes!\n");
}