#include "stos.h"
#include <iostream>
#include <stdlib.h>
#include <memory.h>
using namespace std;


Stack* InitStack() // inicjuje wskaznik nullem
{
	return NULL;
}

void RemoveStack(Stack** pStack) 
{
	while (!isEmpty(*pStack))
		del(pStack);
	*pStack = NULL;
}



void push(char c, Stack** pStack) // wrzuca na stos
{


	Stack* v = (Stack*)malloc(sizeof(Stack)); // malloc nalezy przerzutowac, to samo co w strukturze 
	if (v) // if ( v != NULL )
	{
		memset(v, 0, sizeof(Stack));
		v->cKey = c;// (*v).cKey = c; // operator strzalka
		// dowiazanie
		v->pNext = *pStack;
		*pStack = v;
	}


	else
	perror ( "ERROR push: stack overflow!" );

}
char pop(Stack** pStack) // zdejmuje ze stosu
{
	if (!isEmpty(*pStack))
	{
		char c = top(*pStack);
		del(pStack);
		return c;
	}
	return 0;

}
char top(Stack* pStack) // sprawdza co jest na gorze stosu
{
	if (!isEmpty(pStack))
		return pStack->cKey;
	return 0;

}
void del(Stack** pStack) // usuwa element
{
	if (!isEmpty(*pStack))
	{
		Stack* p = *pStack;
		*pStack = p->pNext; // *pStack = (*)pStack -> pNext;
		free(p); // NIE GWARANTUJE NULL-a

	}
	else
		perror("ERROR pop: stack underflow!" );
}
int isEmpty(Stack* pStack) // sprawdzenie czy jest pusty
{
	return !pStack;
}