#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "oferta.h"

/**
 * Test pentru crearea unei oferte
 */
static void testCreeazaOferta()
{
    Oferta o = createOferta(7, "apartament", 55.5f, "Str. Lalelelor 10", 90000);

    assert(ofertaGetId(&o) == 7);
    assert(ofertaGetSuprafata(&o) == 55.5f);
    assert(ofertaGetPret(&o) == 90000);

    assert(strcmp(ofertaGetTip(&o), "apartament") == 0);
    assert(strcmp(ofertaGetAdresa(&o), "Str. Lalelelor 10") == 0);

    destroyOferta(&o);
}

/**
 * Test pentru modificarea unei oferte 
 */
static void testModificaOferta()
{
    Oferta o = createOferta(7, "apartament", 55.5f, "Str. Lalelelor 10", 90000);
    ofertaSetTip(&o, "casa");
    ofertaSetSuprafata(&o, 120.0f);
    ofertaSetAdresa(&o, "Str. Florilor 5");
    ofertaSetPret(&o, 150000);
    assert(ofertaGetId(&o) == 7);
    assert(ofertaGetSuprafata(&o) == 120.0f);
    assert(ofertaGetPret(&o) == 150000);
    assert(strcmp(ofertaGetTip(&o), "casa") == 0);
    assert(strcmp(ofertaGetAdresa(&o), "Str. Florilor 5") == 0);

    destroyOferta(&o);

}

void testeDomain()
{
    testCreeazaOferta();
    testModificaOferta();
    printf("testDomain() - toate testele au trecut cu succes!\n");
}