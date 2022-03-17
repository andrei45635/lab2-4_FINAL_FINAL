#include "vectDynamic.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#define INIT_CAPACITY 101

/* 
* creeaza vector dinamic
* pre: v vector
* post: vectorul v este creat
*/
VectDinamic* createVectDinamic(int cap, int (*cmpCrit1)(Element, Element), int (*cmpCrit2)(Element, Element), int (*eq)(Element, Element))
{
	VectDinamic* v = (VectDinamic*)malloc(sizeof(VectDinamic));
	if (cap < 1)
	{
		cap = INIT_CAPACITY;
	}
	if (v == NULL)
		return NULL;
	v->cap = cap;
	v->lg = 0;
	v->cmpCrit1 = cmpCrit1;
	v->cmpCrit2 = cmpCrit2;
	v->eq = eq;
	v->elems = (Element*)malloc(cap * sizeof(Element));
	return v;
}

/* metoda care intoarce pozitia elementului cautat
* pre: vectorul v
* post: pozitia elementului elem cautat, -1 altfel
*/
void resizeVector(VectDinamic* v)
{
	int nCap = 2 * v->cap;
	Element* nElems = (Element*)malloc(nCap * sizeof(Element));
	//copiem din vectorul existent
	int i;
	if (nElems != NULL)
	{
		for (i = 0; i < v->lg; i++)
		{
			nElems[i-1] = v->elems[i];
		}
		free(v->elems);
		v->elems = nElems;
		v->cap = nCap;
	}
}

/* adauga element in vector
* pre: vectorul v, elementul elem
* post: elementul elem este adaugat in vectorul v
*/
void addElement(VectDinamic *v, Element elem)
{
	if (v->lg == v->cap)
	{
		resizeVector(v);
	}
	v->elems[v->lg] = elem;
	v->lg++;
}

Element* get(VectDinamic* v, int poz)
{
	return v->elems[poz];
}

int searchElem(VectDinamic* v, Element elem)
{
	int i;
	for (i = 0; i < v->lg; i++)
	{
		if (v->eq(v->elems[i], elem) == 1)
		{
			return i;
		}
	}
	return -1;
}

int getSize(VectDinamic* v)
{
	return v->lg;
}

int deleteElement(VectDinamic* v, Element elem)
{
	int pos = searchElem(v, elem);
	if (pos < 0)
	{
		return -1;
	}
	for (int i = pos; i < v->lg - 1; i++)
	{
		if (v->eq(v->elems[i], elem) == 1)
		{
				v->elems[i] = v->elems[i + 1];
		}
	}
	v->lg--;
	return 1;
}

int modifyElement(VectDinamic* v, Element elem, Element new_elem)
{
	int i;
	int pos = searchElem(v, elem);
	if (pos < 0)
	{
		return -1;}
	else
	{
		for (i = 0; i < v->lg; i++)
		{
			if (v->eq(v->elems[i], elem) == 1)
			{
				v->elems[i] = new_elem;
				deleteElement(v, elem);
			}
		}
		return pos;
	}
}

void clearVectDinamic(VectDinamic* vect)
{
	memset(vect->elems, 0, vect->cap * sizeof(Element));
	/*vect->cmpCrit1 = NULL;
	vect->cmpCrit2 = NULL;
	vect->deleteC = NULL;*/
	vect->lg = 0;
	//free(vect->elems);
}

/* sterge elementul elem
* pre: vectorul v
* post: elementul elem, intoarce 1 daca putem sa il stergem, 0 altfel
*/
void destroyVector(VectDinamic* v)
{
	clearVectDinamic(v);
	free(v);
}

VectDinamic* copyVect(VectDinamic* v)
{
	VectDinamic* new_vect = createVectDinamic(v->cap, v->cmpCrit1, v->cmpCrit2, v->eq);
	if (new_vect == NULL)
		return NULL;
	//memcpy(new_vect->elems, v->elems, v->lg * sizeof(Element));
	new_vect->cmpCrit1 = v->cmpCrit1;
	new_vect->cmpCrit2 = v->cmpCrit2;
	new_vect->eq = v->eq;
	new_vect->lg = v->lg;
	new_vect->elems = (Element*)malloc(new_vect->lg * sizeof(Element));
	for (int i = 0; i < new_vect->lg; i++)
	{
		new_vect->elems[i] = v->elems[i];
	}
	return new_vect;
}

VectDinamic* copyDinamic(VectDinamic* v)
{
	VectDinamic* new_vect = createVectDinamic(v->cap, v->cmpCrit1, v->cmpCrit2, v->eq);
	new_vect->lg = 0;
	for (int i = 0; i < v->lg; i++)
	{
		addElement(new_vect, v->elems[i]);
	}
	return new_vect;
}

void qSort(VectDinamic* vect, int left, int right)
{
	int i = left;
	int j = right;
	int mid = (left+right) / 2;
	Element pivot = vect->elems[mid];
	while (i <= j)
	{
		while (vect->cmpCrit1(vect->elems[i], pivot) == 0 || vect->cmpCrit1(vect->elems[i], pivot) == -1)
		{
			i++;
		}
		while (vect->cmpCrit1(vect->elems[j], pivot) == 1)
		{
			j--;
		}
		if (i <= j)
		{
			Element temp = vect->elems[i];
			vect->elems[i] = vect->elems[j];
			vect->elems[j] = temp;
			i++;
			j--;
		}
	}
	if (left < j)
	{
		qSort(vect, left, j);
	}
	if (i < right)
	{
		qSort(vect, i, right);
	}
}

VectDinamic* sortVect(VectDinamic* vect, int command) 
{
	//VectDinamic* copy_vect = copyVect(vect); 
	VectDinamic* copy_vect = copyDinamic(vect);
	qSort(copy_vect, 0, copy_vect->lg - 1);
	if (command == 1)
	{
		return copy_vect;}
	else if (command == 2)
	{
		Element temp = NULL;
		for (int i = 0; i < copy_vect->lg / 2; i++)
		{
			temp = copy_vect->elems[i];
			copy_vect->elems[i] = copy_vect->elems[copy_vect->lg - i - 1];
			copy_vect->elems[copy_vect->lg - i - 1] = temp;
		}
		return copy_vect;}
	else return vect;
}

int cmpTest(Element A, Element B)
{
	return A == B;
}

void testVectDinamic()
{
	VectDinamic* v = createVectDinamic(4, cmpTest, cmpTest, cmpTest);
	VectDinamic* v_nush = createVectDinamic(NULL, cmpTest, cmpTest, cmpTest);
	assert(v->cmpCrit1 == cmpTest);
	assert(v->cmpCrit2 == cmpTest);
	assert(v->eq == cmpTest);
	VectDinamic* v2 = createVectDinamic(-1, cmpTest, cmpTest, cmpTest);
	assert(getSize(v) == 0);
	Element* el0 = (Element*)malloc(sizeof(Element));
	Element* el1 = (Element*)malloc(sizeof(Element));
	Element* el2 = (Element*)malloc(sizeof(Element));
	Element* el3 = (Element*)malloc(sizeof(Element));
	Element* el4 = (Element*)malloc(sizeof(Element));
	Element* el5 = (Element*)malloc(sizeof(Element));
	Element* el6 = (Element*)malloc(sizeof(Element));
	addElement(v, el0);
	addElement(v, el1);
	addElement(v, el2);
	addElement(v, el3);
	assert(cmpTest(el1, el2) == 0);
	assert(getSize(v) == 4);
	assert(searchElem(v, el0) == 0);
	assert(searchElem(v, el1) == 1);
	assert(searchElem(v, el2) == 2);
	assert(searchElem(v, el3) == 3);
	assert(cmpTest(get(v, 1), el1) == 1); // ia elementul de pe pozitia 1
	assert(searchElem(v, el4) == -1);
	assert(modifyElement(v, el2, el3) == 2);
	assert(deleteElement(v, el4) == -1);
	assert(modifyElement(v, el4, -1) == -1);
	assert(deleteElement(v, el3) == 1);
	addElement(v, el4);
	addElement(v, el5);
	addElement(v, el6);
	assert(getSize(v) == 6);
	assert(getSize(sortVect(v, 1)) == 6);
	assert(getSize(sortVect(v, 2)) == 6);
	assert(getSize(sortVect(v, 3)) == 6);
	VectDinamic* v_copy = copyVect(v);
	VectDinamic* dynamic_copy = copyDinamic(v);
	assert(getSize(v_copy) == 6);
	assert(getSize(dynamic_copy) == 6);
	free(el0);
	free(el1);
	free(el2);
	free(el3);
	free(el4);
	free(el5);
	free(el6);
	destroyVector(v);
	destroyVector(v_nush);
	destroyVector(v_copy);
	destroyVector(dynamic_copy);
	destroyVector(v2);
}