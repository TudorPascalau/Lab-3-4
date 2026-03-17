#pragma once

#include "oferta.h"

#define LIST_CAP 10

#define LIST_SUCCESS 0
#define LIST_FULL 1
#define LIST_EMPTY 2
#define LIST_DUPLICATE 3
#define LIST_NOT_FOUND 4
#define LIST_INVALID 5

typedef Oferta TElem;

typedef struct
{
	TElem* elems;
	int size;
	int cap;
} Lista;


/**
 * Creeaza o lista dinamica pentru gestionarea ofertelor imobiliare.
 * pre: -
 * post: a fost creata o lista pentru gestionarea ofertelor imobiliare
 * return: lista creata
 */
Lista createList();

/**
 * Distruge lista pentru gestionarea ofertelor imobiliare dat
 * param l: adresa listei de distrus
 * pre: l a fost creat
 * post: l este distrus, memoria eliberata
 */
void destroyList(Lista* l);


int ensureCapacity(Lista* l);

/**
 * Adauga o oferta imobiliara in lista
 * param l: adresa lista-ului in care se adauga oferta
 *		 o: oferta de adaugat
 * pre: l a fost creat, o este valida
 * post: daca nu exista deja o oferta cu id-ul dat si lista nu este plina, oferta este adaugata in lista;
 * 		 altfel, nu se face nicio modificare
 * return: LIST_SUCCESS daca oferta a fost adaugata cu succes,
 * 		   LIST_FULL daca lista este plina,
 * 		   LIST_DUPLICATE daca exista deja o oferta cu id-ul dat
 */
int addList(Lista* l, Oferta o);

/**
 * Sterge o oferta imobiliara din lista
 * param l: adresa listei din care se sterge oferta
 *		 id: id-ul ofertei de sters
 * pre: l a fost creat, id este valid
 * post: daca exista o oferta cu id-ul dat, aceasta este stearsa din list;
 * 		 altfel, nu se face nicio modificare
 * return: LIST_SUCCESS daca oferta a fost stearsa cu succes,
 * 		   LIST_EMPTY daca list este gol,
 * 		   LIST_NOT_FOUND daca nu exista nicio oferta cu id-ul dat
 */
int deleteList(Lista* l, int id);

/**
 * Modifica o oferta imobiliara din lista
 * param l: adresa listtei in care se modifica oferta
 *		 o: oferta cu datele modificate
 * pre: r a fost creat, o este valida
 *		id-ul trebuie sa fie acelasi ca al ofertei de modificat
 * post: daca exista o oferta cu id-ul dat, aceasta este modificata cu noile date;
 * 		 altfel, nu se face nicio modificare
 * return: LIST_SUCCESS daca oferta a fost modificata cu succes,
 * 		   LIST_EMPTY daca listsitory-ul este gol,
 * 		   LIST_NOT_FOUND daca nu exista nicio oferta cu id-ul dat
 */
int updateList(Lista* l, Oferta o);

/**
 * Returneaza toate ofertele imobiliare din lista
 * param l: adresa listtei din care se returneaza ofertele
 * pre: l a fost creat
 * post: nu se face nicio modificare
 * return: un pointer la vectorul de oferte din lista
 */
Oferta* getAll(Lista* l);

/**
 * Returneaza dimensiunea listei (numarul de oferte stocate)
 * param l: adresa lista din care se returneaza dimensiunea
 * pre: l a fost creat
 * post: nu se face nicio modificare
 * return: numarul de oferte stocate in lista
 */
int listSize(const Lista* l);