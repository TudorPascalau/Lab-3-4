#pragma once

#include "oferta.h"

#define VALIDATOR_MAX_ERROR 101
#define VALIDATION_SUCCESS 0

typedef struct
{
	char** errors;
	int size;
} ValidatorOferta;

/**
 * Creaza un validator pentru oferta
 * pre: -
 * post: validatorul a fost creat si initializat
 * return: validatorul creat
 */
ValidatorOferta createValidator();

/**
 * Distruge validatorul pentru oferta
 * param v: validatorul de distrus
 * pre: v a fost creat
 * post: v este distrus, memoria eliberata
 */
void destroyValidator(ValidatorOferta* v);

/**
 * Valideaza o oferta
 * param v: validatorul de utilizat
 *		 o: oferta de validat
 * pre: v a fost creat, o a fost creata
 * post: v contine erorile gasite in o, daca exista
 * return: numarul de erori gasite in o
 */
int validateOferta(ValidatorOferta* v, Oferta o);




