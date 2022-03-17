/* 
*	header pentru repository
*/

#ifndef REPOSITORY_H_
#define REPOSITORY_H_

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "vectDynamic.h"
#include "offer.h"

typedef struct {
	VectDinamic* repo_offer;
}offers;

/* creeaza un repo
* pre: marimea repo-ului
* post: repository, construit pe baza unui vector dinamic
*/
offers* createRepo(int size);

/* distruge repo-ul
* pre:-
* post: repo-ul este distrus
*/
void destroyRepo(offers* repo);

/* adauga un element in repo
* pre: repo - vector dinamic, elem - oferta
* post: 1 daca elementul a fost adaugat, -1 altfel
*/
int addOfferRepo(offers* repo, offer* elem);

/* cauta pozitia unei oferte
* pre: repo - vector dinamic, elem - oferta
* post: pozitia ofertei elem in repo
*/
int searchPosOffer(offers* repo, offer* elem);

/* sterge o oferta din repo 
* pre: repo - vector dinamic, elem - oferta
* post: 1 daca s-a sters oferta, -1 altfel
*/
int deleteOffer(offers* repo, offer* elem);

/* modifica o oferta
* pre: repo - vector dinamic, elem, new_elem - oferte
*	   new_elem - oferta noua
* post: repo' - repository cu oferta new_elem
*/
offer* modifyOffer(offers* offer_repo, offer* elem, offer* new_elem);

/* 
*	gets all elements
*/
VectDinamic* getAll(offers* repo);

void testCreateRepo();

void testAddOfferRepo();

void testDeleteOffer();

void testModifyOffer();

#endif REPOSITORY _H_