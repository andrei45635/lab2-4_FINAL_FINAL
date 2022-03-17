#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "repository.h"
#include "offer.h"
#include "vectDynamic.h"
#define INIT_SIZE 11

offers* createRepo(int size)
{
	offers* offer_repo = (offers*)malloc(size * sizeof(offers));
	if (offer_repo == NULL)
		return NULL;
	offer_repo->repo_offer = createVectDinamic(size, cmpPrice, cmpType, eq); //vectorul dinamic
	return offer_repo;
}

void destroyRepo(offers* offer_repo)
{
	destroyVector(offer_repo->repo_offer);
	free(offer_repo);
}

int searchPosOffer(offers* offer_repo, offer* elem)
{
	int pos = searchElem(offer_repo->repo_offer, elem);
	return pos;
}

int addOfferRepo(offers* offer_repo, offer* elem)
{
	//int poz = searchPosOffer(offer_repo->repo_offer, elem);
	int poz = searchElem(offer_repo->repo_offer, elem);
	if (poz < 0)
	{
		addElement(offer_repo->repo_offer, elem);
		return 1;}
	else return -1;
}

int deleteOffer(offers* offer_repo, offer* elem)
{
	int pos = searchPosOffer(offer_repo, elem);
	if (pos < 0)
	{
		return -1;} // oferta nu exista
	else
	{
		offer* ofr1 = offer_repo->repo_offer->elems[pos];
		deleteElement(offer_repo->repo_offer, ofr1);
		return 1;
	}
}

offer* modifyOffer(offers* offer_repo, offer* elem, offer* new_elem)
{
	int pos = searchPosOffer(offer_repo, elem);
	if (pos < 0)
	{
		return -1;} // oferta nu exista
	else
	{
		offer* ofr1 = offer_repo->repo_offer->elems[pos];
		modifyElement(offer_repo->repo_offer, elem, new_elem);
		deleteElement(offer_repo->repo_offer, ofr1);
		//deleteOffer(offer_repo, elem);
		return ofr1;
	}
}

VectDinamic* getAll(offers* offer_repo)
{
	return copyVect(offer_repo->repo_offer);
}

void testCreateRepo()
{
	offers* test_repo = createRepo(5);
	//printf("%d\n", test_repo->repo_offer->cap);
	assert(test_repo->repo_offer->cap == 5);
	assert(test_repo->repo_offer->lg == 0);
	assert(getAll(test_repo)->lg == 0);
	destroyRepo(test_repo);
}

void testAddOfferRepo()
{
	offers* test_repo = createRepo(5);
	assert(test_repo->repo_offer->lg == 0);
	offer* ofr1 = createOffer("apartament", 55, "zorilor", 700);
	offer* ofr2 = createOffer("apartament", 55, "zorilor", 500);
	offer* ofr3 = createOffer("casa", 60, "zorilor", 900);
	addOfferRepo(test_repo, ofr1);
	addOfferRepo(test_repo, ofr2);
	addOfferRepo(test_repo, ofr3);
	assert(searchPosOffer(test_repo, ofr2) == 1); //indexarea este de la 0 
	assert(addOfferRepo(test_repo, ofr2) == -1);
	assert(test_repo->repo_offer->lg == 3);
	destroyRepo(test_repo);
	destroyOffer(ofr1);
	destroyOffer(ofr2);
	destroyOffer(ofr3);
}

void testDeleteOffer()
{
	offers* test_repo = createRepo(5);
	assert(test_repo->repo_offer->lg == 0);
	offer* ofr1 = createOffer("apartament", 55, "zorilor", 700);
	offer* ofr2 = createOffer("apartament", 55, "zorilor", 500);
	offer* ofr3 = createOffer("casa", 60, "zorilor", 900);
	offer* ofr4 = createOffer("castel", 69, "galati", 420);
	addOfferRepo(test_repo, ofr1);
	addOfferRepo(test_repo, ofr2);
	addOfferRepo(test_repo, ofr3);
	assert(test_repo->repo_offer->lg == 3);
	int val_delete = deleteOffer(test_repo, ofr2);
	assert(val_delete == 1);
	assert(deleteOffer(test_repo, ofr4) == -1);
	assert(eq(test_repo->repo_offer->elems[0], ofr1) == 1);
	assert(eq(test_repo->repo_offer->elems[1], ofr3) == 1);
	assert(test_repo->repo_offer->lg == 2);
	destroyRepo(test_repo);
	destroyOffer(ofr1);
	destroyOffer(ofr2);
	destroyOffer(ofr3);
	destroyOffer(ofr4);
}

void testModifyOffer()
{
	offers* test_repo = createRepo(5);
	assert(test_repo->repo_offer->lg == 0);
	offer* ofr1 = createOffer("apartament", 55, "zorilor", 700);
	offer* ofr2 = createOffer("apartament", 55, "zorilor", 500);
	offer* ofr3 = createOffer("casa", 60, "zorilor", 900);
	offer* ofr4 = createOffer("castel", 69, "galati", 420);
	offer* ofr5 = createOffer("teren", 1241, "nush", 12412);
	addOfferRepo(test_repo, ofr1);
	addOfferRepo(test_repo, ofr2);
	addOfferRepo(test_repo, ofr3);
	assert(test_repo->repo_offer->lg == 3);
	assert(eq(test_repo->repo_offer->elems[1], ofr2) == 1);
	modifyOffer(test_repo, ofr2, ofr4);
	modifyOffer(test_repo, ofr5, ofr3);
	assert(eq(test_repo->repo_offer->elems[1], ofr4) == 1);
	assert(test_repo->repo_offer->lg == 3);
	destroyOffer(ofr1);
	destroyOffer(ofr2);
	destroyOffer(ofr3);
	destroyOffer(ofr4);
	destroyOffer(ofr5);
	destroyRepo(test_repo);
}