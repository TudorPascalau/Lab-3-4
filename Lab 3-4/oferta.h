#pragma once

#define OFERTA_MAX_STRING 70
#define OFERTA_MEMORY_ERROR -1

typedef struct {
	int id;
	char* tip;
	float suprafata;
	char* adresa;
	int pret;
} Oferta;

/**
 * Creeaza o oferta cu id-ul, tipul, suprafata, adresa si pretul specificate.
 * param id: id-ul ofertei
 *		 tip: tipul ofertei (ex: "apartament", "casa", "teren")
 *		 suprafata: suprafata ofertei
 *		 adresa: adresa imobilului
 *		 pret: pretul ofertei
 * pre: -
 * post: este creeata o oferta cu id-ul, tipul, suprafata, adresa si pretul specificate
 * return: oferta creata
 */
Oferta createOferta(int id, const char* tip, float suprafata, const char* adresa, int pret);

/**
 * Disruge oferta data
 * param o: adresa ofertei de distrus
 * pre: o este o adresa valida
 * post: este "distrusa" oferta, memoria este eliberata
 */
void destroyOferta(Oferta* o);

/**
 * Getter pentru id-ul ofertei
 * param o: oferta
 * pre: o creata
 * post: este returnat id-ul ofertei
 * return: id-ul ofertei
 */
int ofertaGetId(const Oferta* o);

/**
 * Getter pentru tipul ofertei
 * param o: oferta
 * pre: o creata
 * post: este returnat tipul ofertei
 * return: tipul ofertei
 */
const char* ofertaGetTip(const Oferta* o);

/**
 * Getter pentru suprafata ofertei
 * param o: oferta
 * pre: o creata
 * post: este returnata suprafata ofertei
 * return: suprafata ofertei
 */
float ofertaGetSuprafata(const Oferta* o);

/**
 * Getter pentru adresa ofertei
 * param o: oferta
 * pre: o creata
 * post: este returnata adresa ofertei
 * return: adresa ofertei
 */
const char* ofertaGetAdresa(const Oferta* o);

/**
 * Getter pentru pretul ofertei
 * param o: oferta
 * pre: o creata
 * post: este returnat pretul ofertei
 * return: pretul ofertei
 */
int ofertaGetPret(const Oferta* o);

/**
 * Setter pentru id-ul ofertei
 * param o: oferta
 *		 id: id-ul ofertei
 * pre: o creata
 * post: id-ul ofertei este setat la id
 */
void ofertaSetTip(Oferta* o, const char* tip);

/**
 * Setter pentru suprafata ofertei
 * param o: oferta
 *		 suprafata: suprafata ofertei
 * pre: o creata
 * post: suprafata ofertei este setata la suprafata
 */
void ofertaSetSuprafata(Oferta* o, float suprafata);

/**
 * Setter pentru adresa ofertei
 * param o: oferta
 *		 adresa: adresa ofertei
 * pre: o creata
 * post: adresa ofertei este setata la adresa
 */
void ofertaSetAdresa(Oferta* o, const char* adresa);

/**
 * Setter pentru pretul ofertei
 * param o: oferta
 *		 pret: pretul ofertei
 * pre: o creata
 * post: pretul ofertei este setat la pret
 */
void ofertaSetPret(Oferta* o, int pret);
