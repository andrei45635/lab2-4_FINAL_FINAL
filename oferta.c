#include "offer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define LENTYPE 21
#define LENADDRS 21

/* metoda care creeaza o oferta
* pre: 
* - type = char*, tipul ofertei (teren, casa, apartament)
* - area = float, suprafata imobilului
* - address = char*, adresa imobilului
* - price = float, pretul imobilului
* post: returneaza oferta ofr
*/
offer* createOffer(char* type, float area, char* address, float price)
{
	offer* ofr = (offer*)malloc(sizeof(offer));
	if (ofr != NULL)
	{
		ofr->type = (char*)malloc(LENTYPE * sizeof(char));
		if (ofr->type != NULL)
		{
			strcpy(ofr->type, type);
		}
		ofr->area = area;
		ofr->address = (char*)malloc(LENADDRS * sizeof(char));
		if (ofr->address != NULL)
		{
			strcpy(ofr->address, address);
		}
		ofr->price = price;
		return ofr;
	}
}

/* metoda care elibereaza memoria alocata
* pre: o oferta ofr
* post: elibereaza memoria
*/
void destroyOffer(offer* ofr)
{
	free(ofr->type);
	ofr->area = -1;
	free(ofr->address);
	ofr->price = -1;
	//free(ofr);
}

// getter pentru type
char* getType(offer* ofr)
{
	return ofr->type;
}

// getter pentru area
float getArea(offer* ofr)
{
	return ofr->area;
}

// getter pentru address
char* getAddress(offer* ofr)
{
	return ofr->address;
}

// getter pentru price
float getPrice(offer* ofr)
{
	return ofr->price;
}

/* metoda care verifica daca 2 oferte sunt egale
* pre: 2 oferte
* post: valoarea 1 daca sunt egale, 0 altfel
*/
int eq(offer* ofr1, offer* ofr2)
{
	if ((strcmp(ofr1->type, ofr2->type) == 0) && ofr1->area == ofr2->area && (strcmp(ofr1->address, ofr2->address) == 0) && ofr1->price == ofr2->price)
		return 1;
	else
		return 0;
}

/* metoda care compara preturile a 2 oferte
* pre: 2 oferte ofr1, ofr2
* post: 1, daca ofr1->price > ofr2-> price
*		0, altfel
*/
int cmpPrice(offer* ofr1, offer* ofr2)
{
	if (ofr1->price > ofr2->price)
		return 1;
	else if (ofr1->price < ofr2->price)
		return 0;
	else
		return -1;
}

/* metoda care compara tipurile a 2 oferte
* pre: 2 oferte ofr1, ofr2
* post: 1, daca ofr1->type > ofr2->type
*		-1, daca ofr1->type < ofr2->type
*		0, altfel
*/
int cmpType(offer* ofr1, offer* ofr2)
{
	if (strcmp(ofr1->type, ofr2->type) == 0)
		return 1;
	else if (strcmp(ofr1->type, ofr2->type) > 0)
		return -1;
	else
		return 0;
}

offer* copyOffer(offer* ofr)
{
	offer* new_offer = createOffer(ofr->type, ofr->area, ofr->address, ofr->price);
	return new_offer;
}

void testCreateOffer()
{
	offer* ofr = createOffer("apartament", 55, "zorilor", 700);
	char* type = getType(ofr);
	assert(strcmp(type, "apartament") == 0);
	assert(getArea(ofr) == 55);
	char* address = getAddress(ofr);
	assert(strcmp(address, "zorilor") == 0);
	assert(getPrice(ofr) == 700);
	offer* copy = copyOffer(ofr);
	assert(eq(ofr, copy) == 1);
	destroyOffer(copy);
	destroyOffer(ofr);
}

void testEq()
{
	offer* ofr1 = createOffer("apartament", 55, "zorilor", 700);
	offer* ofr2 = createOffer("apartament", 55, "zorilor", 700);
	offer* ofr3 = createOffer("apartament", 60, "zorilor", 700);
	assert(eq(ofr1, ofr2) == 1);
	assert(eq(ofr1, ofr3) == 0);
	destroyOffer(ofr1);
	destroyOffer(ofr2);
	destroyOffer(ofr3);
}

void testCmp()
{
	offer* ofr1 = createOffer("apartament", 55, "zorilor", 700);
	offer* ofr2 = createOffer("apartament", 55, "zorilor", 500);
	offer* ofr3 = createOffer("casa", 60, "zorilor", 900);
	offer* ofr4 = createOffer("teren", 60, "galati", 900);
	assert(cmpPrice(ofr1, ofr2) == 1);
	assert(cmpPrice(ofr1, ofr3) == 0);
	assert(cmpPrice(ofr3, ofr4) == -1);
	assert(cmpType(ofr1, ofr2) == 1);
	assert(cmpType(ofr4, ofr1) == -1);
	assert(cmpType(ofr1, ofr3) == 0);
	destroyOffer(ofr1);
	destroyOffer(ofr2);
	destroyOffer(ofr3);
	destroyOffer(ofr4);
}