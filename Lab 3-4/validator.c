#include <string.h>
#include <stdlib.h>
#include "validator.h"


ValidatorOferta createValidator()
{
	ValidatorOferta v;

	v.errors = (char**)malloc(sizeof(char*) * 5);
	if (v.errors)
		for (int i = 0; i < 5; i++)
			v.errors[i] = (char*)malloc(sizeof(char) * 101);

	v.size = 0;
	return v;
}


void destroyValidator(ValidatorOferta* v)
{
	for (int i = 0; i < 5; i++)
		free(v->errors[i]);
	free(v->errors);

	v->size = 0;
}


int validateOferta(ValidatorOferta* v, Oferta o)
{
	v->size = 0;
	if (o.id < 0)
	{
		strcpy_s(v->errors[v->size], VALIDATOR_MAX_ERROR, "Id-ul trebuie sa fie un numar natural!");
		v->size++;
	}

	if (o.tip == NULL || strlen(o.tip) == 0 ||
		(strcmp(o.tip, "teren") != 0 &&
			strcmp(o.tip, "casa") != 0 &&
			strcmp(o.tip, "apartament") != 0))
	{
		strcpy_s(v->errors[v->size], VALIDATOR_MAX_ERROR, "Tipul trebuie sa fie: teren, casa sau apartament!");
		v->size++;
	}

	if (o.suprafata <= 0)
	{
		strcpy_s(v->errors[v->size], VALIDATOR_MAX_ERROR, "Suprafata trebuie sa fie un numar pozitiv!");
		v->size++;
	}

	if (strlen(o.adresa) == 0 || o.adresa == NULL)
	{
		strcpy_s(v->errors[v->size], VALIDATOR_MAX_ERROR, "Adresa nu poate fi vida!");
		v->size++;
	}

	if (o.pret <= 0)
	{
		strcpy_s(v->errors[v->size], VALIDATOR_MAX_ERROR, "Pretul trebuie sa fie un numar pozitiv!");
		v->size++;
	}
	return v->size;
}