/* 
*	metode care creeaza si manipuleaza service-ul
*/

#ifndef SERVICE_H_
#define SERVICE_H_
#include "repository.h"
#include "offer.h"
#include "vectDynamic.h"

typedef struct Service{
	offers* offer_repo;
}service;

/* creeaza service
* pre: repo-ul care va fi adaugat in service
* post: service-ul este creat
*/
service* createService(offers* offer_service);

/* dezaloca memoria rezervata pentru service
* pre: service
* post: memoria este dezalocata
*/
void destroyService(service* serv);

/* adauga oferta in service
* pre: service serv
*	   tipul ofertei - char*
*	   suprafata - float
*	   adresa - char*
*	   pret - float
* post: 1 daca oferta este adaugata in service, -1 altfel
*/
int addOfferToService(service* serv, char* type, float area, char* address, float price);

/* sterge oferta introdusa de utilizator
* pre: service serv
*	   tipul ofertei - char*
*	   suprafata - float
*	   adresa - char*
*	   pret - float
* post: 1 daca oferta a fost stearsa, -1 altfel
*/
int deleteServiceOffer(service* serv, char* type, float area, char* address, float price);

/* modifica oferta din service 
* pre: service serv, type, area, address, price pentru oferta pe care vrem sa o modificam
*	   new_type, new_area, new_address, new_price este oferta noua
* post: 1 daca s-a modificat oferta, -1 altfel
*/
int modifyOfferService(service* serv, char* type, float area, char* address, float price, char* new_type, float new_area, char* new_address, float new_price);

/* cauta oferta introdusa de utilizator
* pre: service serv
*	   tipul ofertei - char*
*	   suprafata - float
*	   adresa - char*
*	   pret - float
* post: pozitia ofertei daca a gasit-o, -1 altfel
*/
int searchOfferService(service* serv, char* type, float area, char* address, float price);

/*
* filtreaza dupa pret
* pre: vect - vect dinamic
*      command -> 1 crescator
*              -> 2 descrescator
*	   filterPrice - float, pretul dupa care se va filtra
* post: vector sortat 
*/
VectDinamic* filter_price(service* serv, int command, float filterPrice);

/*
* filtreaza dupa suprafata
* pre: vect - vect dinamic
*      command -> 1 crescator
*              -> 2 descrescator
*	   filter_area - float, pretul dupa care se va filtra
* post: vector sortat
*/
VectDinamic* filter_area(service* serv, int command, float filter_area);

/*
* filtreaza dupa tip
* pre: vect - vect dinamic
*	   type_to_filter - tipul care trebuie filtrat
*					    1 -> apartament
*						2 -> casa
*						3 -> teren
* post: vector sortat
*/
VectDinamic* filter_type(service* serv, int type_to_filter);

/*
* sorteaza dupa pret, in ordine crescatoare sau descrescatoare
* pre: serv - service
*	   command - int 
*      1 -> crescator
*	   2 -> descrescator
* post: vectorul este sortat
*/
VectDinamic* sortPrice(service* serv, int command);

/*
* sorteaza dupa tip, in ordine crescatoare sau descrescatoare
* pre: serv - service
*	   command - int
*      1 -> crescator
*	   2 -> descrescator
* post: vectorul este sortat
*/
VectDinamic* sortType(service* serv, int command);

void testCreateService();

void testAddOfferService();

void testdeleteServiceOffer();

void testModifyServiceOffer();

void testSearchOfferService();

void testFilterPrice();

void testFilterArea();

void testFilterType();

void testSorting();

#endif SERVICE_H_
