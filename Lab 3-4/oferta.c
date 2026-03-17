#include <string.h>
#include <stdlib.h>
#include "oferta.h"

Oferta createOferta(int id, const char* tip, float suprafata, const char* adresa, int pret)
{
	Oferta o;
	o.id = id;

	size_t sizeTip = strlen(tip) + 1;
	o.tip = malloc(sizeof(char) * sizeTip);
	if (o.tip) strcpy_s(o.tip, sizeTip, tip);

	o.suprafata = suprafata;

	size_t sizeAdresa = strlen(adresa) + 1;
	o.adresa = malloc(sizeof(char) * sizeAdresa);
	if (o.adresa) strcpy_s(o.adresa, sizeAdresa, adresa);

	o.pret = pret;
	return o;
}

void destroyOferta(Oferta* o)
{
	free(o->tip);
	free(o->adresa);

	o->id = -1;
	o->tip = NULL;
	o->adresa = NULL;

}


int ofertaGetId(const Oferta* o)
{
	return o->id;
}


const char* ofertaGetTip(const Oferta* o)
{
	return o->tip;
}


float ofertaGetSuprafata(const Oferta* o)
{
	return o->suprafata;
}


const char* ofertaGetAdresa(const Oferta* o)
{
	return o->adresa;
}


int ofertaGetPret(const Oferta* o)
{
	return o->pret;
}


void ofertaSetTip(Oferta* o, const char* tip)
{
	size_t sizeTip = strlen(tip) + 1;
	strcpy_s((o->tip), sizeTip, tip);
}


void ofertaSetSuprafata(Oferta* o, float suprafata)
{
	o->suprafata = suprafata;
}


void ofertaSetAdresa(Oferta* o, const char* adresa)
{
	size_t sizeAdresa = strlen(adresa) + 1;
	strcpy_s((o->adresa), sizeAdresa, adresa);
}

void ofertaSetPret(Oferta* o, int pret)
{
	o->pret = pret;
}

