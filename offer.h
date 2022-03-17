/* header file pentru oferta.c
* domain pentru tipul TElement oferta
*/

#ifndef OFFER_H_
#define OFFER_H_

typedef struct Oferta {
	char* type;
	float area;
	char* address;
	float price;
}offer;

/* metoda care creeaza o oferta
* pre: 
* - type = char*, tipul ofertei (teren, casa, apartament)
* - area = float, suprafata imobilului
* - address = char*, adresa imobilului
* - price = float, pretul imobilului
* post: //
*/
offer* createOffer(char* type, float area, char* address, float price);

/* destructor pentru Oferta
* pre:
* - Oferta = oferta
* post: elibereaza memoria alocata
*/
void destroyOffer(offer* ofr);

//getter pentru type
char* getType(offer*);

//getter pentru suprafata
float getArea(offer*);

//getter pentru adresa
char* getAddress(offer*);

//getter pentru pret
float getPrice(offer*);

/* metoda care verifica daca 2 oferte sunt egale
* pre: 2 oferte
* post: valoarea 1 daca sunt egale, 0 altfel
*/
int eq(offer* ofr1, offer* ofr2);

/* metoda care compara preturile a 2 oferte
* pre: 2 oferte ofr1, ofr2
* post: 1, daca ofr1->price > ofr2-> price
*		0, altfel
*/
int cmpPrice(offer* ofr1, offer* ofr2);

/* metoda care compara tipurile a 2 oferte
* pre: 2 oferte ofr1, ofr2
* post: 1, daca ofr1->type > ofr2->type
*		-1, daca ofr1->type < ofr2->type
*		0, altfel
*/
int cmpType(offer* ofr1, offer* ofr2);

/* copiaza oferta
*/
offer* copyOffer(offer* offer);

void testCreateOffer();

void testEq();

void testCmp();

#endif OFFER_H_
