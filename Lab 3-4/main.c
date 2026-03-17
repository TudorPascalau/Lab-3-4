#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>

#include "test_domain.h"
#include "test_list.h"
#include "test_validator.h"
#include "test_service.h"

#include "ui.h"

int main()
{
	testeDomain();
	testeLista();
	testeValidator();
	testeService();

	if (_CrtDumpMemoryLeaks() == 1)
		printf("S-au gasit memory leaks");
	else
		printf("Nu avem memory leaks");

	Lista lista = createList();
	ValidatorOferta validator = createValidator();
	ServiceOferta service = createService(&lista, &validator);
	UI ui = createUI(&service);

	run(&ui);
	destroyService(&service);

	return 0;
}