#pragma once
#ifndef DSTACK_H
#define DSTACK_H 100

typedef struct tagDStack
{
	double fKey;
	tagDStack* pNext;

} DStack;



DStack* dInitStack();
void dRemoveStack(DStack** ppStack);
void dpush(double c, DStack** ppStack);
double dpop(DStack** ppStack);
double dtop(DStack* ppStack);
void ddel(DStack** ppStack);
int disEmpty(DStack* ppStack);


#endif