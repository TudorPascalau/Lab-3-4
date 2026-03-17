#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ui.h"

/**
 * Afiseaza meniul principal al aplicatiei.
 */
static void printMenu()
{
	printf("\n=== AGENTIE IMOBILIARA ===\n");
	printf("1. Adauga oferta\n");
	printf("2. Sterge oferta\n");
	printf("3. Modifica oferta\n");
	printf("4. Afiseaza toate ofertele\n");
	printf("5. Sorteaza ofertele\n");
	printf("6. Filtreaza ofertele\n");
	printf("9. Populeaza cu date de test\n");
	printf("0. Iesire\n");
	printf(">>> ");
}


UI createUI(ServiceOferta* service)
{
	UI ui;
	ui.service = service;
	return ui;
}

/**
 * Adauga o noua oferta citind datele de la utilizator.
 * param: ui - pointer catre interfata de utilizator
 * pre: ui trebuie sa fie valid
 * post: daca datele sunt valide, oferta este adaugata in sistem; altfel, se afiseaza erorile
 */
static void uiAddOferta(UI* ui)
{
	int id, pret;
	float suprafata;
	char tip[OFERTA_MAX_STRING], adresa[OFERTA_MAX_STRING];

	printf("Id: ");
	if (scanf_s("%d", &id) != 1)
	{
		printf("Id invalid!\n");
		while (getchar() != '\n');
		return;
	}

	printf("Tip: ");
	while (getchar() != '\n');
	fgets(tip, OFERTA_MAX_STRING, stdin);
	tip[strcspn(tip, "\n")] = '\0';

	printf("Suprafata: ");
	if (scanf_s("%f", &suprafata) != 1)
	{
		printf("Suprafata invalida!\n");
		while (getchar() != '\n');
		return;
	}

	printf("Adresa: ");
	while (getchar() != '\n');
	fgets(adresa, OFERTA_MAX_STRING, stdin);
	adresa[strcspn(adresa, "\n")] = '\0';


	printf("Pret: ");
	if (scanf_s("%d", &pret) != 1)
	{
		printf("Pret invalid!\n");
		while (getchar() != '\n');
		return;
	}

	int result = addOferta(ui->service, id, tip, suprafata, adresa, pret);
	if (result == SERVICE_SUCCESS)
		printf("Oferta adaugata cu succes!\n");
	else if (result == SERVICE_VALIDATION_ERROR)
	{
		printf("Date invalide:\n");
		for (int i = 0; i < ui->service->validator->size; i++)
			printf("%s\n", ui->service->validator->errors[i]);
	}
	else if (result == SERVICE_REPO_ERROR)
		if (result == LIST_DUPLICATE)
			printf("O oferta cu acest id exista deja!\n");
		else if (result == LIST_FULL)
			printf("Nu se pot adauga mai multe oferte!\n");
}

/**
 * Sterge o oferta existenta citind id-ul de la utilizator.
 * param: ui - pointer catre interfata de utilizator
 * pre: ui trebuie sa fie valid
 * post: daca id-ul este valid si exista, oferta este stearsa; altfel, se afiseaza un mesaj de eroare
 */
static void uiDeleteOferta(UI* ui)
{
	int id;
	printf("Id-ul ofertei de sters: ");
	if (scanf_s("%d", &id) != 1)
	{
		printf("Id invalid!\n");
		while (getchar() != '\n');
		return;
	}

	int result = stergeOferta(ui->service, id);
	if (result == SERVICE_SUCCESS)
		printf("Oferta stearsa cu succes.\n");
	else
		printf("Nu exista oferta cu id-ul dat.\n");
}

/**
 * Modifica o oferta existenta citind datele de la utilizator.
 * param: ui - pointer catre interfata de utilizator
 * pre: ui trebuie sa fie valid
 * post: daca datele sunt valide si oferta exista, aceasta este modificata; altfel, se afiseaza erorile
 */
static void uiUpdateOferta(UI* ui)
{
	int id, pret;
	float suprafata;
	char tip[OFERTA_MAX_STRING], adresa[OFERTA_MAX_STRING];

	printf("Id: ");
	if (scanf_s("%d", &id) != 1)
	{
		printf("Id invalid!\n");
		while (getchar() != '\n');
		return;
	}

	printf("Tip: ");
	while (getchar() != '\n');
	fgets(tip, OFERTA_MAX_STRING, stdin);
	tip[strcspn(tip, "\n")] = '\0';

	printf("Suprafata: ");
	if (scanf_s("%f", &suprafata) != 1)
	{
		printf("Suprafata invalida!\n");
		while (getchar() != '\n');
		return;
	}

	printf("Adresa: ");
	while (getchar() != '\n');
	fgets(adresa, OFERTA_MAX_STRING, stdin);
	adresa[strcspn(adresa, "\n")] = '\0';


	printf("Pret: ");
	if (scanf_s("%d", &pret) != 1)
	{
		printf("Pret invalid!\n");
		while (getchar() != '\n');
		return;
	}

	int result = updateOferta(ui->service, id, tip, suprafata, adresa, pret);
	if (result == SERVICE_SUCCESS)
		printf("Oferta modificata cu succes!\n");
	else if (result == SERVICE_VALIDATION_ERROR)
	{
		printf("Date invalide:\n");
		for (int i = 0; i < ui->service->validator->size; i++)
			printf("%s\n", ui->service->validator->errors[i]);
	}
	else if (result == SERVICE_REPO_ERROR)
		printf("O oferta cu acest id exista deja!\n");

}

/**
 * Afiseaza o lista de oferte in consola.
 * param: oferte - array de oferte care trebuie afisate
 * param: size - numarul de oferte din array
 * pre: oferte trebuie sa fie un array valid, size trebuie sa fie >= 0
 * post: toate ofertele sunt afisate in consola; daca size este 0, se afiseaza un mesaj corespunzator
 */
static void printListaOferte(Oferta oferte[], int size)
{
	if (size == 0)
	{
		printf("Nu exista oferte.\n");
		return;
	}

	for (int i = 0; i < size; i++)
	{
		printf("Id: %d | Tip: %s | Suprafata: %.2f | Adresa: %s | Pret: %d\n",
			oferte[i].id,
			oferte[i].tip,
			oferte[i].suprafata,
			oferte[i].adresa,
			oferte[i].pret);
	}
}

/**
 * Afiseaza toate ofertele existente in sistem.
 * param: ui - pointer catre interfata de utilizator
 * pre: ui trebuie sa fie valid
 * post: toate ofertele sunt afisate in consola; daca nu exista oferte, se afiseaza un mesaj corespunzator
 */
static void uiPrintAll(UI* ui)
{
	Oferta* oferte = getOferte(ui->service);
	int size = getSize(ui->service);
	printListaOferte(oferte, size);
}

/**
 * Sorteaza ofertele dupa un criteriu si o ordine specificate de utilizator, apoi le afiseaza.
 * param: ui - pointer catre interfata de utilizator
 * pre: ui trebuie sa fie valid
 * post: ofertele sunt sortate si afisate in consola; daca nu exista oferte, se afiseaza un mesaj corespunzator
 */
static void uiSortOferte(UI* ui)
{
	int criteriu, ordine;
	Oferta* rez = NULL;

	printf("\nSortare dupa:\n");
	printf("1. Pret\n");
	printf("2. Tip\n");
	printf(">>> ");
	if (scanf_s("%d", &criteriu) != 1)
	{
		printf("Criteriu invalid!\n");
		while (getchar() != '\n');
		return;
	}

	printf("\nOrdine:\n");
	printf("1. Crescator\n");
	printf("0. Descrescator\n");
	printf(">>> ");
	if (scanf_s("%d", &ordine) != 1)
	{
		printf("Ordine invalida!\n");
		while (getchar() != '\n');
		return;
	}

	if ((criteriu != 1 && criteriu != 2) || (ordine != 0 && ordine != 1))
	{
		printf("Optiuni invalide!\n");
		return;
	}

	if (criteriu == 1 && ordine == 1)
	{
		int size = sortOferte(ui->service, &rez, cmpPret);
		printListaOferte(rez, size);
	}

	else if (criteriu == 1 && ordine == 0)
	{
		int size = sortOferte(ui->service, &rez, cmpPretDescresc);
		printListaOferte(rez, size);
	}

	else if (criteriu == 2 && ordine == 1)
	{
		int size = sortOferte(ui->service, &rez, cmpTip);
		printListaOferte(rez, size);
	}

	else
	{
		int size = sortOferte(ui->service, &rez, cmpTipDescresc);
		printListaOferte(rez, size);
	}

	free(rez);
}

/**
 * Filtreaza ofertele dupa un criteriu specificat de utilizator, apoi le afiseaza.
 * param: ui - pointer catre interfata de utilizator
 * pre: ui trebuie sa fie valid
 * post: ofertele sunt filtrate si afisate in consola; daca nu exista oferte care sa corespunda filtrului, se afiseaza un mesaj corespunzator
 */
static void uiFilterOferte(UI* ui)
{
	int criteriu;
	Oferta* rez = NULL;

	printf("\nFiltrare dupa:\n");
	printf("1. Suprafata\n");
	printf("2. Tip\n");
	printf("3. Pret\n");
	printf(">>> ");
	if (scanf_s("%d", &criteriu) != 1)
	{
		printf("Criteriu invalid!\n");
		while (getchar() != '\n');
		return;
	}

	if (criteriu == 1)
	{
		float suprafata;
		printf("Suprafata minima: ");
		if (scanf_s("%f", &suprafata) != 1)
		{
			printf("Valoare invalida!\n");
			while (getchar() != '\n');
			return;
		}

		int size = filterOferte(ui->service, &rez, criteriu, "", suprafata, 0);
		printListaOferte(rez, size);
	}
	else if (criteriu == 2)
	{
		char tip[OFERTA_MAX_STRING];

		printf("Tip: ");
		while (getchar() != '\n');
		fgets(tip, OFERTA_MAX_STRING, stdin);
		tip[strcspn(tip, "\n")] = '\0';

		int size = filterOferte(ui->service, &rez, criteriu, tip, 0, 0);
		printListaOferte(rez, size);
	}
	else if (criteriu == 3)
	{
		int pret;
		printf("Pret maxim: ");
		if (scanf_s("%d", &pret) != 1)
		{
			printf("Valoare invalida!\n");
			while (getchar() != '\n');
			return;
		}

		int size = filterOferte(ui->service, &rez, criteriu, "", 0, pret);
		printListaOferte(rez, size);
	}
	else
	{
		printf("Criteriu invalid!\n");
	}

	free(rez);

}

/**
 * Populeaza sistemul cu date de test pentru a facilita testarea si demonstrarea functionalitatilor.
 * param: service - pointer catre serviciul de oferte care va fi populat
 * pre: service trebuie sa fie valid
 * post: 10 oferte de test sunt adaugate in sistem
 */
static void populateSampleData(ServiceOferta* service)
{
	addOferta(service, 1, "apartament", 54.5, "Str. Observatorului 12", 120000);
	addOferta(service, 2, "casa", 120.0, "Str. Republicii 45", 250000);
	addOferta(service, 3, "teren", 500.0, "Str. Fagetului 3", 80000);
	addOferta(service, 4, "apartament", 70.0, "Str. Memorandumului 18", 150000);
	addOferta(service, 5, "casa", 140.0, "Str. Buna Ziua 22", 270000);
	addOferta(service, 6, "teren", 1000.0, "Str. Campului 10", 120000);
	addOferta(service, 7, "apartament", 45.0, "Str. Dorobantilor 5", 95000);
	addOferta(service, 8, "casa", 200.0, "Str. Borhanciului 8", 320000);
	addOferta(service, 9, "teren", 750.0, "Str. Lombului 15", 90000);
	addOferta(service, 10, "apartament", 60.0, "Str. Fabricii 21", 130000);
}

void run(UI* ui)
{
	int cmd;
	while (1)
	{
		printMenu();
		if (scanf_s("%d", &cmd) != 1)
		{
			printf("Comanda invalida!\n");
			while (getchar() != '\n');
			continue;
		}

		switch (cmd)
		{
		case 1:
			uiAddOferta(ui);
			break;
		case 2:
			uiDeleteOferta(ui);
			break;
		case 3:
			uiUpdateOferta(ui);
			break;
		case 4:
			uiPrintAll(ui);
			break;
		case 5:
			uiSortOferte(ui);
			break;
		case 6:
			uiFilterOferte(ui);
			break;
		case 9:
			populateSampleData(ui->service);
			printf("Date de test adaugate.\n");
			break;
		case 0:
			return;
		default:
			printf("Optiune invalida!\n");
		}
	}
}