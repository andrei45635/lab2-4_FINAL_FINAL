#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "service.h"
#include "offer.h"
#include "repository.h"
#include "vectDynamic.h"

service* createService(offers* offer_repo)
{
	service* serv = (service*)malloc(sizeof(service));
	if (serv != NULL)
	{
		serv->offer_repo = offer_repo;
		return serv;
	}
}

void destroyService(service* serv)
{
	free(serv->offer_repo);
	free(serv);
}

int addOfferToService(service* serv, char* type, float area, char* address, float price)
{
	offer* ofr = createOffer(type, area, address, price);
	return addOfferRepo(serv->offer_repo, ofr);
}

int deleteServiceOffer(service* serv, char* type, float area, char* address, float price)
{
	offer* ofr = createOffer(type, area, address, price);
	//addOfferRepo(serv->offer_repo, ofr);
	//int ofr3 = deleteElement(serv->offer_repo->repo_offer, ofr);
	int ofr2 = deleteOffer(serv->offer_repo, ofr);
	destroyOffer(ofr);
	if (ofr2 == -1)
	{
		return -1;
	}
	else return 1;
}

int modifyOfferService(service* serv, char* type, float area, char* address, float price, char* new_type, float new_area, char* new_address, float new_price)
{
	offer* ofr_vechi = createOffer(type, area, address, price);
	offer* ofr_nou = createOffer(new_type, new_area, new_address, new_price);
	//addOfferRepo(serv->offer_repo, ofr_vechi);
	//addOfferToService(serv, type, area, address, price);
	int ofr_after = modifyOffer(serv->offer_repo, ofr_vechi, ofr_nou);
	destroyOffer(ofr_vechi);
	if (ofr_after == -1)
	{
		destroyOffer(ofr_nou);
		return -1; //nu am putut distruge oferta
	}
	else return 1;
}

int searchOfferService(service* serv, char* type, float area, char* address, float price)
{
	offer* oferta_wtf = createOffer(type, area, address, price);
	//addOfferRepo(serv->offer_repo, oferta_wtf);
	//addOfferToService(serv, type, area, address, price);
	int poz = searchPosOffer(serv->offer_repo, oferta_wtf);
	if (poz < 0)
	{
		destroyOffer(oferta_wtf);
		return -1; // nu am gasit oferta
	} 
	else return poz;
}

VectDinamic* filter_price(service* serv, int command, float filter_price)
{
	VectDinamic* vect_filter = copyVect(serv->offer_repo->repo_offer);
	if (command == 1)
	{
		for (int i = 0; i < vect_filter->lg; i++)
		{
			offer* ofr = copyOffer(vect_filter->elems[i]);
			if (getPrice(ofr) <= filter_price)
			{
				deleteElement(vect_filter, vect_filter->elems[i]);
				i--;
			}
			destroyOffer(ofr);
		}
	}
	else if (command == 2) 
	{
		for (int i = 0; i < vect_filter->lg; i++)
		{
			offer* ofr = copyOffer(vect_filter->elems[i]);
			if (getPrice(ofr) >= filter_price)
			{
				deleteElement(vect_filter, vect_filter->elems[i]);
				i--;
			}
			destroyOffer(ofr);
		}
	}
	return vect_filter;
}

VectDinamic* filter_area(service* serv, int command, float filter_area)
{
	VectDinamic* vect_filter = copyVect(serv->offer_repo->repo_offer);
	if (command == 1)
	{
		for (int i = 0; i < vect_filter->lg; i++)
		{
			offer* ofr = copyOffer(vect_filter->elems[i]);
			if (getArea(ofr) <= filter_area)
			{
				deleteElement(vect_filter, vect_filter->elems[i]);
				i--;
			}
			destroyOffer(ofr);
		}
	}
	else if (command == 2)
	{
		for (int i = 0; i < vect_filter->lg; i++)
		{
			offer* ofr = copyOffer(vect_filter->elems[i]);
			if (getArea(ofr) >= filter_area)
			{
				deleteElement(vect_filter, vect_filter->elems[i]);
				i--;
			}
			destroyOffer(ofr);
		}
	}
	return vect_filter;
}

VectDinamic* filter_type(service* serv, int type_to_filter)
{
	VectDinamic* vect_filter = copyVect(serv->offer_repo->repo_offer);
	char* filter_type = (char*)malloc(11 * sizeof(char));
	if (type_to_filter == 1)
	{
		strcpy(filter_type, "apartament");
	}
	else if (type_to_filter == 2)
	{
		strcpy(filter_type, "casa");
	}
	else if (type_to_filter == 3)
	{
		strcpy(filter_type, "teren");
	}
	for (int i = 0; i < vect_filter->lg; i++)
	{
		offer* ofr = copyOffer(vect_filter->elems[i]);
		if (strcmp(getType(ofr), filter_type) != 0)
		{
			deleteElement(vect_filter, vect_filter->elems[i]);
			i--;
		}
		destroyOffer(ofr);
	}
	free(filter_type);
	return vect_filter;
}

VectDinamic* sortPrice(service* serv, int command)
{
	return sortVect(serv->offer_repo->repo_offer, command);
}

VectDinamic* sortType(service* serv, int command)
{
	serv->offer_repo->repo_offer->cmpCrit1 = serv->offer_repo->repo_offer->cmpCrit2;
	return sortVect(serv->offer_repo->repo_offer, command);
}

void testCreateService()
{
	offers* test_repo = createRepo(5);
	service* test_serv = createService(test_repo);
	assert(test_serv->offer_repo == test_repo);
	assert(test_serv->offer_repo->repo_offer->cap == 5);
	destroyService(test_serv);
}

void testAddOfferService()
{
	offers* test_repo = createRepo(5);
	service* test_serv = createService(test_repo);
	assert(test_serv->offer_repo == test_repo);
	offer* ofr1 = createOffer("apartament", 55, "zorilor", 700);
	offer* ofr2 = createOffer("casa", 65, "zorilor", 750);
	offer* ofr3 = createOffer("teren", 1200, "galati", 70000);
	addOfferToService(test_serv, "apartament", 55, "zorilor", 700);
	addOfferToService(test_serv, "casa", 65, "zorilor", 750);
	addOfferToService(test_serv, "teren", 1200, "galati", 70000);
	assert(test_serv->offer_repo->repo_offer->lg == 3);
	assert(eq(test_serv->offer_repo->repo_offer->elems[0], ofr1) == 1);
	assert(eq(test_serv->offer_repo->repo_offer->elems[1], ofr2) == 1);
	assert(eq(test_serv->offer_repo->repo_offer->elems[2], ofr3) == 1);
	destroyService(test_serv);
	destroyOffer(ofr1);
	destroyOffer(ofr2);
	destroyOffer(ofr3);
}

void testdeleteServiceOffer()
{
	offers* test_repo = createRepo(5);
	service* test_serv = createService(test_repo);
	assert(test_serv->offer_repo == test_repo);
	offer* ofr1 = createOffer("apartament", 55, "zorilor", 700);
	offer* ofr2 = createOffer("casa", 65, "zorilor", 750);
	offer* ofr3 = createOffer("teren", 1200, "galati", 70000);
	addOfferToService(test_serv, "apartament", 55, "zorilor", 700);
	addOfferToService(test_serv, "casa", 65, "zorilor", 750);
	addOfferToService(test_serv, "teren", 1200, "galati", 70000);
	assert(getAll(test_serv->offer_repo)->lg == 3);
	assert(test_serv->offer_repo->repo_offer->lg == 3);
	assert(eq(test_serv->offer_repo->repo_offer->elems[0], ofr1) == 1);
	assert(eq(test_serv->offer_repo->repo_offer->elems[1], ofr2) == 1);
	assert(eq(test_serv->offer_repo->repo_offer->elems[2], ofr3) == 1);
	assert(deleteServiceOffer(test_serv, "apartament", 55, "zorilor", 700) == 1);
	assert(test_serv->offer_repo->repo_offer->lg == 2);
	assert(deleteServiceOffer(test_serv, "teren", 65, "zorilor", 750) == -1);
	destroyService(test_serv);
	destroyOffer(ofr1);
	destroyOffer(ofr2);
	destroyOffer(ofr3);
}

void testModifyServiceOffer()
{
	offers* test_repo = createRepo(5);
	service* test_serv = createService(test_repo);
	assert(test_serv->offer_repo == test_repo);
	offer* ofr1 = createOffer("apartament", 55, "zorilor", 700);
	offer* ofr2 = createOffer("casa", 65, "zorilor", 750);
	offer* ofr3 = createOffer("teren", 1200, "galati", 70000);
	addOfferToService(test_serv, "apartament", 55, "zorilor", 700);
	addOfferToService(test_serv, "casa", 65, "zorilor", 750);
	addOfferToService(test_serv, "teren", 1200, "galati", 70000);
	assert(test_serv->offer_repo->repo_offer->lg == 3);
	int test_val = modifyOfferService(test_serv, "casa", 65, "zorilor", 750, "apartament", 69, "kiev", 420);
	assert(test_val == 1);
	assert(test_serv->offer_repo->repo_offer->lg == 3); //ar trb sa fie 3, dar la mine e 4
	assert(modifyOfferService(test_serv, "teren", 65, "zorilor", 750, "apartament", 69, "kiev", 420) == -1);
	destroyService(test_serv);
	destroyOffer(ofr1);
	destroyOffer(ofr2);
	destroyOffer(ofr3);
}

void testSearchOfferService()
{
	offers* test_repo = createRepo(5);
	service* test_serv = createService(test_repo);
	assert(test_serv->offer_repo == test_repo);
	offer* ofr1 = createOffer("apartament", 55, "zorilor", 700);
	offer* ofr2 = createOffer("casa", 65, "zorilor", 750);
	offer* ofr3 = createOffer("teren", 1200, "galati", 70000);
	assert(addOfferToService(test_serv, "apartament", 55, "zorilor", 700) == 1);
	assert(addOfferToService(test_serv, "casa", 65, "zorilor", 750) == 1);
	assert(addOfferToService(test_serv, "teren", 1200, "galati", 70000) == 1);
	assert(eq(test_serv->offer_repo->repo_offer->elems[1], ofr2) == 1);
	assert(getSize(test_serv->offer_repo->repo_offer) == 3);
	assert(searchOfferService(test_serv, "casa", 65, "zorilor", 750) == 1);
	assert(searchOfferService(test_serv, "teren", 65, "zorilor", 750) == -1);
	destroyService(test_serv);
	destroyOffer(ofr1);
	destroyOffer(ofr2);
	destroyOffer(ofr3);
}

void testFilterPrice()
{
	offers* test_repo = createRepo(5);
	service* test_serv = createService(test_repo);
	assert(test_serv->offer_repo == test_repo);
	offer* ofr1 = createOffer("apartament", 55, "zorilor", 700);
	offer* ofr2 = createOffer("casa", 65, "zorilor", 650);
	offer* ofr3 = createOffer("teren", 1200, "galati", 70000);
	addOfferToService(test_serv, "apartament", 55, "zorilor", 700);
	addOfferToService(test_serv, "casa", 65, "zorilor", 650);
	addOfferToService(test_serv, "teren", 1200, "galati", 70000);
	assert(test_serv->offer_repo->repo_offer->lg == 3);
	VectDinamic* test_filter = filter_price(test_serv, 2, 675);
	assert(test_filter->lg == 2);
	assert(eq(test_filter->elems[0], ofr2) == 1);
	assert(eq(test_filter->elems[2], ofr3) == 1);
	VectDinamic* test_filter2 = filter_price(test_serv, 1, 800); 
	assert(test_filter2->lg == 0);
	clearVectDinamic(test_filter);
	clearVectDinamic(test_filter2);
	destroyService(test_serv);
	destroyOffer(ofr1);
	destroyOffer(ofr2);
	destroyOffer(ofr3);
}

void testFilterArea()
{
	offers* test_repo = createRepo(5);
	service* test_serv = createService(test_repo);
	assert(test_serv->offer_repo == test_repo);
	offer* ofr1 = createOffer("apartament", 55, "zorilor", 700);
	offer* ofr2 = createOffer("casa", 65, "zorilor", 650);
	offer* ofr3 = createOffer("teren", 1200, "galati", 70000);
	addOfferToService(test_serv, "apartament", 55, "zorilor", 700);
	addOfferToService(test_serv, "casa", 65, "zorilor", 650);
	addOfferToService(test_serv, "teren", 1200, "galati", 70000);
	assert(test_serv->offer_repo->repo_offer->lg == 3);
	VectDinamic* test_filter = filter_area(test_serv, 1, 60);
	assert(test_filter->lg == 2);
	assert(eq(test_filter->elems[0], ofr2) == 1);
	assert(eq(test_filter->elems[2], ofr3) == 1);
	VectDinamic* test_filter2 = filter_area(test_serv, 2, 100);
	assert(test_filter2->lg == 2);
	assert(eq(test_filter2->elems[0], ofr1) == 1);
	assert(eq(test_filter2->elems[1], ofr2) == 1);
	clearVectDinamic(test_filter);
	clearVectDinamic(test_filter2);
	destroyService(test_serv);
	destroyOffer(ofr1);
	destroyOffer(ofr2);
	destroyOffer(ofr3);
}

void testFilterType()
{
	offers* test_repo = createRepo(5);
	service* test_serv = createService(test_repo);
	assert(test_serv->offer_repo == test_repo);
	offer* ofr1 = createOffer("apartament", 55, "zorilor", 700);
	offer* ofr2 = createOffer("casa", 65, "zorilor", 650);
	offer* ofr3 = createOffer("teren", 1200, "galati", 70000);
	addOfferToService(test_serv, "apartament", 55, "zorilor", 700);
	addOfferToService(test_serv, "casa", 65, "zorilor", 650);
	addOfferToService(test_serv, "teren", 1200, "galati", 70000);
	assert(test_serv->offer_repo->repo_offer->lg == 3);
	VectDinamic* test_filter = filter_type(test_serv, 2);
	assert(test_filter->lg == 2);
	VectDinamic* test_filter2 = filter_type(test_serv, 1);
	assert(test_filter->lg == 2);
	VectDinamic* test_filter3 = filter_type(test_serv, 3);
	assert(test_filter->lg == 2);
	assert(eq(test_serv->offer_repo->repo_offer->elems[0], ofr1) == 1);
	assert(eq(test_serv->offer_repo->repo_offer->elems[2], ofr3) == 1);
	clearVectDinamic(test_filter);
	clearVectDinamic(test_filter2);
	clearVectDinamic(test_filter3);
	destroyService(test_serv);
	destroyOffer(ofr1);
	destroyOffer(ofr2);
	destroyOffer(ofr3);
}

void testSorting()
{
	offers* test_repo = createRepo(5);
	service* test_serv = createService(test_repo);
	assert(test_serv->offer_repo == test_repo);
	offer* ofr1 = createOffer("apartament", 55, "zorilor", 700);
	offer* ofr2 = createOffer("casa", 65, "zorilor", 650);
	offer* ofr3 = createOffer("teren", 1200, "galati", 70000);
	addOfferToService(test_serv, "apartament", 55, "zorilor", 700);
	addOfferToService(test_serv, "casa", 65, "zorilor", 650);
	addOfferToService(test_serv, "teren", 1200, "galati", 70000);
	assert(test_serv->offer_repo->repo_offer->lg == 3);
	sortPrice(test_serv, 1);
	assert(test_serv->offer_repo->repo_offer->cmpCrit1 == cmpPrice);
	assert(test_serv->offer_repo->repo_offer->lg == 3);
	sortPrice(test_serv, 2);
	assert(test_serv->offer_repo->repo_offer->lg == 3);
	sortType(test_serv, 1);
	assert(test_serv->offer_repo->repo_offer->cmpCrit2 == cmpType);
	assert(test_serv->offer_repo->repo_offer->lg == 3);
	sortType(test_serv, 2);
	assert(test_serv->offer_repo->repo_offer->lg == 3);
	destroyService(test_serv);
	destroyOffer(ofr1);
	destroyOffer(ofr2);
	destroyOffer(ofr3);
}