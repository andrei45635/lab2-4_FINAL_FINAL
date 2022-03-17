#ifndef VECTDYNAMIC_H_
#define VECTDYNAMIC_H_

typedef void* Element;

typedef struct VectDinamic {
	Element* elems;
	int (*cmpCrit1)(Element, Element);
	int (*cmpCrit2)(Element, Element);
	int (*eq)(Element, Element);
	int cap; //capacitate
	int lg; //lungime 

}VectDinamic;

/* creeaza vector dinamic
* pre: v vector, capacitatea cap, int
* post: vectorul v este creat
*/
VectDinamic* createVectDinamic(int cap, int (*cmpCrit1)(Element, Element), int (*cmpCrit2)(Element, Element), int (*eq)(Element, Element));

/* adauga element in vector
* pre: vectorul v, elementul elem
* post: elementul elem este adaugat in vectorul v
*/
void addElement(VectDinamic* v, Element elem);

/* distruge vectorul v
* pre: vectorul v
* post: vectorul v este distrus
*/
void destroyVector(VectDinamic* v);

/* intoarce lungimea vectorului v
* pre: vectorul v
* post: lungimea vectorului v, int
*/
int getSize(VectDinamic* v);

/* 
* aloca memorie pentru a mari vectorul v
*/
void resizeVector(VectDinamic* v);

/* metoda care intoarce pozitia elementului cautat
* pre: vectorul v, elementul elem cautat
* post: pozitia elementului elem cautat, -1 altfel
*/
int searchElem(VectDinamic* v, Element elem);

/* sterge elementul elem
* pre: vectorul v
* post: elementul elem, intoarce 1 daca putem sa il stergem, 0 altfel
*/
int deleteElement(VectDinamic* v, Element elem);

/* modifica elementul elem
* pre: vectorul v, elementul elem
* post: elementul elem este inlocuit cu elementul elem_new
*		returneaza 1 daca se poate, -1 altfel
*/
int modifyElement(VectDinamic* v, Element elem, Element elem_new);

/* 
* gets the element from the position poz
* pre: v - vect dinamic
*	   poz - position, int 
* post: the element elem[poz] 
*/
Element* get(VectDinamic* v, int poz);

/* 
* copiaza vectorul dinamic
*/
VectDinamic* copyVect(VectDinamic* vect);

/*
* distruge vectorul dinamic 
* pre: vect - vect dinamic 
* post: vectorul dinamic este distrus
*/
void clearVectDinamic(VectDinamic* vect);

/*
* sorts the dynamic vector given the command (ascending/descending) 
* pre: vect - vect dinamic 
*      command -> 1 for ascending
*	           -> 2 for descending
*/
VectDinamic* sortVect(VectDinamic* vect, int command);

/* 
* quick sort
* pre: vect - vect dinamic 
*      left - int 
*      right - int 
* post: the vector is sorted
*/
void qSort(VectDinamic* vect, int left, int right);

/*
* dynamically copies the vector
* pre: vect - dynamic vector
* post: new_vect - the copy of the dynamic vector vect
*/
VectDinamic* copyDinamic(VectDinamic* v);

int cmpTest(Element A, Element B);

void testVectDinamic();
#endif VECTDYNAMIC_H_