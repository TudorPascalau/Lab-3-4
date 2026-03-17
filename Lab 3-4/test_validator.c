#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "validator.h"

/**
 * Test pentru validatorul de oferte
 */
void testeValidator()
{
	ValidatorOferta v = createValidator();
	Oferta o1 = createOferta(-1, "", -1, "", -5);

	assert(validateOferta(&v, o1) == 5);
	assert(strcmp(v.errors[0], "Id-ul trebuie sa fie un numar natural!") == 0);
	assert(strcmp(v.errors[1], "Tipul trebuie sa fie: teren, casa sau apartament!") == 0);
	assert(strcmp(v.errors[2], "Suprafata trebuie sa fie un numar pozitiv!") == 0);
	assert(strcmp(v.errors[3], "Adresa nu poate fi vida!") == 0);
	assert(strcmp(v.errors[4], "Pretul trebuie sa fie un numar pozitiv!") == 0);

	Oferta o2 = createOferta(1, "teren", 100.5, "Strada Florilor 10", 50000);
	assert(validateOferta(&v, o2) == 0);

	destroyValidator(&v);
	destroyOferta(&o1);
	destroyOferta(&o2);

	printf("testValidator() - toate testele au trecut cu succes!\n");
}