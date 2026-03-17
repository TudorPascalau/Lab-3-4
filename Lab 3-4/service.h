#pragma once

#include "lista.h"
#include "validator.h"

#define SERVICE_SUCCESS 0
#define SERVICE_REPO_ERROR 1
#define SERVICE_VALIDATION_ERROR 2

#define CRITERIU_PRET 1
#define CRITERIU_TIP 2

#define ORDINE_CRESCATOR 1
#define ORDINE_DESCRESCATOR 0

#define FILTRU_SUPRAFATA 1
#define FILTRU_TIP 2
#define FILTRU_PRET 3

typedef struct
{
	Lista* oferte;
	ValidatorOferta* validator;
} ServiceOferta;

typedef int(*FunctieComparare)(Oferta* o1, Oferta* o2);


/**
 * Creeaza un service pentru gestionarea ofertelor imobiliare.
 * param l: adresa repository de oferte
 *		 v: adresa validatorul de oferte
 * pre: l a fost creat, v a fost creat
 * post: a fost creat un service pentru gestionarea ofertelor imobiliare
 * return: service creat
 */
ServiceOferta createService(Lista* r, ValidatorOferta* v);

/**
 * Distruge service-ul pentru gestionarea ofertelor imobiliare dat
 * param s: adresa service-ului de distrus
 * pre: s a fost creat
 * post: s este distrus, memoria eliberata
 */
void destroyService(ServiceOferta* s);

/**
 * Adauga o oferta imobiliara in service
 * param s: adresa service-ului in care se adauga oferta
 *		 id: id-ul ofertei de adaugat
 *		 tip: tipul ofertei de adaugat
 *		 suprafata: suprafata ofertei de adaugat
 *		 adresa: adresa ofertei de adaugat
 *		 pret: pretul ofertei de adaugat
 * pre: s a fost creat, id este valid, tip este valid, suprafata este valida, adresa este valida, pretul este valid
 * post: daca datele sunt valide si nu exista deja o oferta cu id-ul dat, oferta este adaugata in service;
		 altfel, nu se face nicio modificare
 * return: SERVICE_SUCCESS daca oferta a fost adaugata cu succes,
		   SERVICE_VALIDATION_ERROR daca datele nu sunt valide,
		   SERVICE_REPO_ERROR daca exista deja o oferta cu id-ul dat
 */
int addOferta(ServiceOferta* s, int id, const char* tip, float suprafata, const char* adresa, int pret);

/**
 * Sterge o oferta imobiliara din service
 * param s: adresa service-ului din care se sterge oferta
 *		 id: id-ul ofertei de sters
 * pre: s a fost creat, id este valid
 * post: daca exista o oferta cu id-ul dat, aceasta este stearsa din service; altfel, nu se face nicio modificare
 * return: SERVICE_SUCCESS daca oferta a fost stearsa cu succes,
		   SERVICE_REPO_ERROR daca nu exista nicio oferta cu id-ul dat
 */
int stergeOferta(ServiceOferta* s, int id);

/**
 * Modifica o oferta imobiliara din service
 * param s: adresa service-ului in care se modifica oferta
 *		 id: id-ul ofertei de modificat
 *		 tip: noul tip al ofertei
 *		 suprafata: noua suprafata a ofertei
 *		 adresa: noua adresa a ofertei
 *		 pret: noul pret al ofertei
 * pre: s a fost creat, id este valid, tip este valid, suprafata este valida, adresa este valida, pretul este valid
 * post: daca exista o oferta cu id-ul dat si noile date sunt valide, oferta este modificata in service; altfel, nu se face nicio modificare
 * return: SERVICE_SUCCESS daca oferta a fost modificata cu succes,
		   SERVICE_VALIDATION_ERROR daca noile date nu sunt valide,
		   SERVICE_REPO_ERROR daca nu exista nicio oferta cu id-ul dat
 */
int updateOferta(ServiceOferta* s, int id, const char* tip, float suprafata, const char* adresa, int pret);

/**
 * Returneaza toate ofertele imobiliare din service
 * param s: adresa service-ului din care se returneaza ofertele
 * pre: s a fost creat
 * post: -
 * return: vector cu toate ofertele imobiliare din service, dimensiunea vectorului este stocata in size
 */
Oferta* getOferte(ServiceOferta* s);

/**
 * Returneaza numarul de oferte imobiliare
 * param s: adresa service-ului in care sunt retinute ofertele
 * pre: s a fost creat
 * post: -
 * return: numarul de oferte
 */
int getSize(ServiceOferta* s);

/**
 * Sorteaza ofertele imobiliare din service dupa un criteriu dat
 * param s: adresa service-ului din care se sorteaza ofertele
 *		 rez: vector in care se vor stoca ofertele sortate
 *		 criteriu: criteriul dupa care se sorteaza (1 - pret, 2 - tip)
 *		 ordine: ordinea de sortare (1 - crescator, 0 - descrescator)
 * pre: s a fost creat, rez are dimensiunea cel putin egala cu numarul de oferte din service, criteriu este valid, ordine este valid
 * post: ofertele imobiliare din service sunt sortate dupa criteriul si ordinea specificate, rezultatul este stocat in rez
 * return: numarul de oferte sortate
 */
int sortOferte(ServiceOferta* s, Oferta** rez, FunctieComparare cmpF);

/**
 * Filtreaza ofertele imobiliare din service dupa un criteriu dat
 * param s: adresa service-ului din care se filtreaza ofertele
 *		 rez: vector in care se vor stoca ofertele filtrate
 *		 criteriu: criteriul dupa care se filtreaza (1 - suprafata, 2 - tip, 3 - pret)
 *		 tip: tipul dupa care se filtreaza (folosit doar daca criteriu == 2)
 *		 suprafata: suprafata minima pentru filtrare (folosit doar daca criteriu == 1)
 *		 pret: pretul maxim pentru filtrare (folosit doar daca criteriu == 3)
 * pre: s a fost creat, rez are dimensiunea cel putin egala cu numarul de oferte din service, criteriu este valid, tip este valid daca criteriu == 2, suprafata este valida daca criteriu == 1, pret este valid daca criteriu == 3
 * post: ofertele imobiliare din service sunt filtrate dupa criteriul specificat, rezultatul este stocat in rez
 * return: numarul de oferte filtrate
 */
int filterOferte(ServiceOferta* s, Oferta** rez, int criteriu, const char* tip, float suprafata, int pret);

int cmpPret(Oferta* o1, Oferta* o2);

int cmpPretDescresc(Oferta* o1, Oferta* o2);

int cmpTip(Oferta* o1, Oferta* o2);

int cmpTipDescresc(Oferta* o1, Oferta* o2);


