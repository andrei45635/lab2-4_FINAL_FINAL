#pragma warning(disable : 4996)
/*
10. Agentie imobiliara

Creati o aplicatie care permite gestiunea ofertelor de la o agentie imobiliara.

Fiecare oferta are: tip (teren, casa, apartament), suprafata, adresa, pret

Aplicatia permite:

 a) Adaugarea de noi oferte.

 b) Actualizare oferte

 c) Stergere oferta

 d) Vizualizare oferete ordonat dupa pret, tip (crescator/descrescator)

 e) Vizualizare oferta filtrate dupa un criteriu (suprafata, tip, pret)
*/
#include <stdio.h>
#include <stdlib.h>
#include "offer.h"
#include "vectDynamic.h"
#include "repository.h"
#include "service.h"
#include <math.h>

void testAll()
{
	testCreateOffer();
	testEq();
	testCmp();
	testVectDinamic();
	testCreateRepo();
	testAddOfferRepo();
	testDeleteOffer();
	testModifyOffer();
	testCreateService();
	testAddOfferService();
	testdeleteServiceOffer();
	testModifyServiceOffer();
	testSearchOfferService();
	testFilterPrice();
	testFilterArea();
	testFilterType();
	testSorting();
}

void printVect(VectDinamic* vect)
{
	/*
	* printeaza vectorul 
	* pre: vect - vector dinamic
	* post: vectorul este printat
	*/
	int i = 0;
	for (i = 0; i < vect->lg; i++)
	{
		offer* ofr = copyOffer(vect->elems[i]);
		printf("Tipul ofertei este: %s, suprafata sa este: %.2f, adresa este: %s si pretul este: %.2f\n ", ofr->type, ofr->area, ofr->address, ofr->price);
		destroyOffer(ofr);
	}
	clearVectDinamic(vect);
}

int main()
{	char type[21], address[21];
	float area, price;
	offers* repo = createRepo(5);
	service* serv = createService(repo);
	int exit = 0;
	testAll();
	while (!exit)
	{
		int cmd = readCommand();
		if (cmd == 0)
		{
			printf("Bye bye!");
			exit = 1;
		}
		else if (cmd == 1)
		{
			
			printf("Introduceti tipul ofertei (casa, apartament, teren): ");
			if (scanf("%s", type) != 1)
			{
				printf("tip gresit!\n");
			}
			//else if (strcmp(type, "apartament") != 0 || strcmp(type, "casa") != 0 || strcmp(type, "teren") != 0)
			//{
				//printf("tip gresit introdus!\n");
			//}
			else
			{
				printf("Introduceti suprafata ofertei: ");
				if (scanf("%f", &area) != 1 || area < 0)
				{
					printf("suprafata incorecta!\n");
				}
				else
				{
					printf("Introduceti adresa ofertei: ");
					if (scanf("%s", address) != 1)
					{
						printf("adresa gresita!\n");
					}
					else
					{
						printf("Introduceti pretul ofertei: ");
						if (scanf("%f", &price) != 1 || abs(price - 0.0001) < 0)
						{
							printf("pret gresit!\n");
						}
						else
						{
							int val = addOfferToService(serv, type, area, address, price);
							if (val == 1)
							{
								printf("oferta adaugata cu succes!\n");
							}
							else
							{
								printf("memorie insuficienta sau date gresite!\n");
							}
						}
					}
				}
			}
		}
		else if (cmd == 2)
		{
			printf("Introduceti tipul ofertei (casa, apartament, teren): ");
			if (scanf("%s", type) != 1)
			{
				printf("tip gresit!\n");
			}
			//else if (strcmp(type, "apartament") < 0 || strcmp(type, "casa") < 0 || strcmp(type, "teren") < 0)
			//{
				//printf("tip gresit introdus!\n");
			//}
			else
			{
				printf("Introduceti suprafata ofertei: ");
				if (scanf("%f", &area) != 1 || area < 0)
				{
					printf("suprafata incorecta!\n");
				}
				else
				{
					printf("Introduceti adresa ofertei: ");
					if (scanf("%s", address) != 1)
					{
						printf("adresa gresita!\n");
					}
					else
					{
						printf("Introduceti pretul ofertei: ");
						if (scanf("%f", &price) != 1 || abs(price - 0.0001) < 0)
						{
							printf("pret gresit!\n");
						}
						else
						{
							//offer* ofr_del = createOffer(type, area, address, price);
							//int val_repo = deleteOffer(repo, ofr_del);
							int val = deleteServiceOffer(serv, type, area, address, price);
							//printf("%d\n", val);
							if (val == 1)
							{
								printf("oferta stearsa este: tip %s, area %.2f, adresa %s, pret %.2f\n", type, area, address, price);
								printf("oferta stearsa cu succes!\n");
							}
							else
							{
								//printf("oferta stearsa este: tip %s, area %.2f, adresa %s, pret %.2f\n", type, area, address, price);
								//printf("val repo ii %d\n", val);
								printf("memorie insuficienta sau date gresite!\n");
							}
						}
					}
				}
			}
		}
		else if(cmd == 3)
		{
			char new_type[21], new_address[21];
			float new_area, new_price;
			printf("Introduceti tipul ofertei (casa, apartament, teren): ");
			if (scanf("%s", type) != 1)
			{
				printf("tip gresit!\n");
			}
			//else if (strcmp(type, "apartament") < 0 || strcmp(type, "casa") < 0 || strcmp(type, "teren") < 0)
			//{
				//printf("tip gresit introdus!\n");
			//}
			else
			{
				printf("Introduceti suprafata ofertei: ");
				if (scanf("%f", &area) != 1 || area < 0)
				{
					printf("suprafata incorecta!\n");
				}
				else
				{
					printf("Introduceti adresa ofertei: ");
					if (scanf("%s", address) != 1)
					{
						printf("adresa gresita!\n");
					}
					else
					{
						printf("Introduceti pretul ofertei: ");
						if (scanf("%f", &price) != 1 || abs(price - 0.0001) < 0)
						{
							printf("pret gresit!\n");
						}
						else
						{
							printf("Introduceti noul tip al ofertei (casa, apartament, teren): ");
							if (scanf("%s", new_type) != 1)
							{
								printf("nou tip gresit!\n");
							}
							//else if (strcmp(new_type, "apartament") < 0 || strcmp(new_type, "casa") < 0 || strcmp(new_type, "teren") < 0)
							//{
								//printf("nou tip introdus gresit!\n");
							//}
							else
							{
								printf("Introduceti noua suprafata a ofertei: ");
								if (scanf("%f", &new_area) != 1 || new_area < 0)
								{
									printf("suprafata incorecta!\n");
								}
								else
								{
									printf("Introduceti noua adresa a ofertei: ");
									if (scanf("%s", new_address) != 1)
									{
										printf("adresa gresita!\n");
									}
									else
									{
										printf("Introduceti noul pret al ofertei: ");
										if (scanf("%f", &new_price) != 1 || abs(new_price - 0.0001) < 0)
										{
											printf("pret gresit!\n");
										}
										else
										{
											int val = modifyOfferService(serv, type, area, address, price, new_type, new_area, new_address, new_price);
											if (val == 1)
											{
												printf("oferta modificata este: noul tip %s, new area %.2f, noua adresa %s, noul pret %.2f\n", new_type, new_area, new_address, new_price);
												printf("oferta modificata cu succes!\n");
											}
											else
											{
												printf("bad memory");
											}
										}
									}
								}
							}
						}
					}
				}
			}		
		}
		else if (cmd == 4)
		{
			VectDinamic* all = getAll(repo);
			printVect(all);
		}
		else if (cmd == 5)
		{
			addOfferToService(serv, "teren", 1241, "zorilor", 12432);
			addOfferToService(serv, "teren", 1324, "bucuresti", 12422);
			addOfferToService(serv, "apartament", 140, "observator", 12232);
			addOfferToService(serv, "casa", 324, "galati", 122);
			printf("populat cu succes!\n");
		}
		else if (cmd == 6)
		{
			float filterPrice;
			int command;
			printf("Introduceti pretul dupa care doriti sa filtrati: ");
			if (scanf("%f", &filterPrice) == NULL)
				return;
			printf("Introduceti ordinea dupa care doriti sa filtrati (1 ascending, 2 descending): ");
			if (scanf("%d", &command) == NULL)
				return;
			VectDinamic* filtered = filter_price(serv, command, filterPrice);
			printVect(filtered);
		}
		else if (cmd == 7)
		{
			float filterArea;
			int command;
			printf("Introduceti suprafata dupa care doriti sa filtrati: ");
			if(scanf("%f", &filterArea) == NULL)
				return;
			printf("Introduceti ordinea dupa care doriti sa filtrati (1 ascending, 2 descending): ");
			if (scanf("%d", &command) == NULL)
				return;
			VectDinamic* filtered = filter_price(serv, command, filterArea);
			printVect(filtered);
		}
		else if (cmd == 8)
		{
			int type_to_filter;
			printf("Introduceti tipul dupa care doriti sa filtrati (1 - apartament, 2 - casa, 3 - teren): ");
			if (scanf("%d", &type_to_filter) == NULL)
				return;
			VectDinamic* filtered = filter_type(serv, type_to_filter);
			printVect(filtered);
		}
		else if (cmd == 9)
		{
			int command;
			printf("Introduceti ordinea dupa care doriti sa filtrati: ");
			if (scanf("%d", &command) == NULL)
				return;
			//VectDinamic* sorted = sortVect(serv->offer_repo->repo_offer, command);
			VectDinamic* sorted = sortPrice(serv, command);
			printVect(sorted);
		}
		else if (cmd == 10)
		{
			int command;
			printf("Introduceti ordinea dupa care doriti sa filtrati: ");
			if (scanf("%d", &command) == NULL)
				return;
			//VectDinamic* sorted = sortVect(serv->offer_repo->repo_offer, command);
			VectDinamic* sorted = sortType(serv, command);
			printVect(sorted);
		}
		else if (cmd == 11)
		{
		printf("1) adauga oferta\n2) sterge oferta\n3) modifica oferta\n4) printeaza oferte\n5) populeaza cu 4 oferte\n6) filtreaza pret\n7) filtreaza suprafata\n8) filtreaza tip\n9) sorteaza pret\n10) sorteaza tip\n");
		}
		else
		{
			printf("wrong command!\n");
		}
	}
}

int readCommand()
{
	/* metoda citeste input de la user si returneaza comanda
	* pre: -
	* post: command, integer
	*/
	int command = 0;
	printf("Introduceti comanda: ");
	scanf_s("%d", &command);
	return command;
}
