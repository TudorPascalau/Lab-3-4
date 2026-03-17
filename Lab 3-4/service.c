#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "service.h"


ServiceOferta createService(Lista* l, ValidatorOferta* v)
{
	ServiceOferta s;
	s.oferte = l;
	s.validator = v;
	return s;
}


void destroyService(ServiceOferta* s)
{
	destroyList(s->oferte);
	destroyValidator(s->validator);

	s->oferte = NULL;
	s->validator = NULL;
}


int addOferta(ServiceOferta* s, int id, const char* tip, float suprafata, const char* adresa, int pret)
{
	Oferta o = createOferta(id, tip, suprafata, adresa, pret);
	int validationResult = validateOferta(s->validator, o);
	if (validationResult != VALIDATION_SUCCESS)
	{
		destroyOferta(&o);
		return SERVICE_VALIDATION_ERROR;
	}

	int repoResult = addList(s->oferte, o);
	if (repoResult != LIST_SUCCESS)
	{
		destroyOferta(&o);
		return SERVICE_REPO_ERROR;
	}

	return SERVICE_SUCCESS;
}


int stergeOferta(ServiceOferta* s, int id)
{
	int repoResult = deleteList(s->oferte, id);
	if (repoResult != LIST_SUCCESS)
		return SERVICE_REPO_ERROR;
	return SERVICE_SUCCESS;
}


int updateOferta(ServiceOferta* s, int id, const char* tip, float suprafata, const char* adresa, int pret)
{
	Oferta o = createOferta(id, tip, suprafata, adresa, pret);
	int validationResult = validateOferta(s->validator, o);
	if (validationResult != VALIDATION_SUCCESS)
	{
		destroyOferta(&o);
		return SERVICE_VALIDATION_ERROR;
	}


	int repoResult = updateList(s->oferte, o);
	if (repoResult != LIST_SUCCESS)
	{
		destroyOferta(&o);
		return SERVICE_REPO_ERROR;
	}


	return SERVICE_SUCCESS;
}


Oferta* getOferte(ServiceOferta* s)
{
	return getAll(s->oferte);
}

int getSize(ServiceOferta* s)
{
	return listSize(s->oferte);
}

int cmpPret(Oferta* o1, Oferta* o2)
{
	return o1->pret > o2->pret;
}

int cmpPretDescresc(Oferta* o1, Oferta* o2)
{
	return o1->pret < o2->pret;
}

int cmpTip(Oferta* o1, Oferta* o2)
{
	return strcmp(o1->tip, o2->tip);
}

int cmpTipDescresc(Oferta* o1, Oferta* o2)
{
	return strcmp(o1->tip, o2->tip) < 0;
}

int sortOferte(ServiceOferta* s, Oferta** rez, FunctieComparare cmpF)
{
	int n = listSize(s->oferte);
	const Oferta* v = getAll(s->oferte);
	*rez = malloc(sizeof(Oferta) * n);
	if (*rez != NULL)
	{

		for (int i = 0; i < n; i++)
			(*rez)[i] = v[i];

		for (int i = 0; i < n - 1; i++)
		{
			for (int j = i + 1; j < n; j++)
			{
				int schimb = 0;

				/*if (criteriu == CRITERIU_PRET)
				{
					if (ordine == ORDINE_CRESCATOR && (*rez)[i].pret > (*rez)[j].pret)
						schimb = 1;
					if (ordine == ORDINE_DESCRESCATOR && (*rez)[i].pret < (*rez)[j].pret)
						schimb = 1;

				}
				else if (criteriu == CRITERIU_TIP)
				{
					if (ordine == ORDINE_CRESCATOR && strcmp((*rez)[i].tip, (*rez)[j].tip) > 0)
						schimb = 1;
					if (ordine == ORDINE_DESCRESCATOR && strcmp((*rez)[i].tip, (*rez)[j].tip) < 0)
						schimb = 1;
				}*/

				if (cmpF(&(*rez)[i], &(*rez)[j]) > 0)
					schimb = 1;

				if (schimb)
				{
					Oferta aux = (*rez)[i];
					(*rez)[i] = (*rez)[j];
					(*rez)[j] = aux;
				}
			}
		}
	}
	return n;
}

int filterOferte(ServiceOferta* s, Oferta** rez, int criteriu, const char* tip, float suprafata, int pret)
{
	int n = listSize(s->oferte);
	*rez = malloc(sizeof(Oferta) * n);
	int k = 0;
	if (*rez != NULL)
	{

		const Oferta* v = getAll(s->oferte);

		for (int i = 0; i < n; i++)
		{
			if (criteriu == FILTRU_SUPRAFATA && v[i].suprafata >= suprafata)
				(*rez)[k++] = v[i];
			else if (criteriu == FILTRU_TIP && strcmp(v[i].tip, tip) == 0)
				(*rez)[k++] = v[i];
			else if (criteriu == FILTRU_PRET && v[i].pret <= pret)
				(*rez)[k++] = v[i];
		}

	}

	return k;

}