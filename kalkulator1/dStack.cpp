
#include "dStack.h"
#include <iostream>
#include <stdlib.h>
#include <memory.h>
using namespace std;


DStack* dInitStack()  // inicjacja wskaznika nullem
{
	return NULL;
}

void dRemoveStack(DStack** ppStack)
{
	while (!disEmpty(*ppStack))
		ddel(ppStack);
	*ppStack = NULL;
}



void dpush(double c, DStack** ppStack) // wrzuca na stos
{


	DStack* v = (DStack*)malloc(sizeof(DStack)); // malloc nalezy przerzutowac, to samo co w strukturze 
	if (v) // if ( v != NULL )
	{
		memset(v, 0, sizeof(DStack));
		v->fKey = c;// (*v).cKey = c; // operator strzalka
					// dowiazanie
		v->pNext = *ppStack;
		*ppStack = v;
	}


	else
		perror("ERROR push: stack overflow!");

}
double dpop(DStack** ppStack) // zdejmuje ze stosu
{
	//  cout << "NULL -->  " << ppStack << "  ->>>   " << *ppStack << "  -->>>   " << dtop(*ppStack) << "\n\n";
	if (!disEmpty(*ppStack))
	{
		double c = dtop(*ppStack);
		ddel(ppStack);
		return c;
	}
	return 0;
}

double dtop(DStack* ppStack) // sprawdza co jest na gorze stosu
{
	if (!disEmpty(ppStack))
		return ppStack->fKey;
	return 0;

}
void ddel(DStack** ppStack) // usuwa element
{
	if (!disEmpty(*ppStack))
	{
		DStack* p = *ppStack;
		*ppStack = p->pNext; // *pStack = (*)pStack -> pNext;
		free(p); // NIE GWARANTUJE NULL-a

	}
	else
		perror("ERROR pop: stack underflow!");

}

int disEmpty(DStack* ppStack) // sprawdzenie czy jest pusty
{
	return !ppStack;
}

