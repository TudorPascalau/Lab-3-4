#pragma once

#include "service.h"

typedef struct
{
	ServiceOferta* service;
} UI;


/**
 * Creeaza o noua interfata de utilizator.
 * param: service - pointer catre serviciul de oferte care va fi folosit de UI
 * pre: service trebuie sa fie valid
 * post: ui creat cu succes, legat de serviciul dat
 * return: o structura UI initializata
 */
UI createUI(ServiceOferta* service);

/**
 * Ruleaza bucla principala a aplicatiei, afisand meniul si procesand comenzile utilizatorului.
 * param: ui - pointer catre interfata de utilizator
 * pre: ui trebuie sa fie valid
 * post: aplicatia ruleaza pana cand utilizatorul alege sa iasa (comanda 0)
 */
void run(UI* ui);