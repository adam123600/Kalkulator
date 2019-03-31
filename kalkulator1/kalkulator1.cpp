// kalkulator1.cpp : Defines the entry point for the console application.
//

//SKOÑCZYÆ W DOMU!!
//zrobiæ funkcje, implementujemy funkcje operacji na stosie, w calc tylko zamiana wyra¿enia na ONP
/////////////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "stos.h"
#include "dStack.h"
#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;

#define DOT '.'

/////////////////////////////////////////////////////////////////////////////////////////////////////

double GetNum();	//wczytanie liczby rzeczywistej
char getOper();		//wczytanie operatora
void SkipSpaces();	//pomijanie spacji wiod¹cych
int isOper( char c ); // sprawdza czy wpisany znak jest znakiem operatora
int isDigit( char c ); // sprawdza czy wpisany znak jest liczba
int prior( char cOper ); // priorytet operatorow
double Eval( char oper, double arg1, double arg2 ); // funkcja liczaca
void Calc(); // kalkulator

/////////////////////////////////////////////////////////////////////////////////////////////////////

int main( int argc, char* argv[] )
{
	Calc();

	system("pause");
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

double GetNum()
{
	char c;
	double res = 0; // liczba zwracana z funkcji
	int znak = 0; // do znaku liczby

	SkipSpaces();

	//////////////////////////////////////////////// znak liczby
	if( ( c = getchar() ) == '-' ) znak = 1;
	else res = res * 10 + ( c - '0' );
	////////////////////////////////////////////////

	SkipSpaces();

	while( isDigit( c = getchar() ) ) // (wczytanie znaku i sprawdzenie czy jest znakiem cyfry)
		res = res * 10 + ( c - '0' );

	if( c == DOT ) // czesc ulamkowa 
	{
		SkipSpaces();
		double coef = 0.1;

		while( isDigit( c = getchar() ) )
		{
			res += coef*( c - '0' );
			coef /= 10;
		}
		//wczytywanie ulamkowej czesci
	}

	ungetc( c, stdin ); // wazneeeee
	if( znak ) return -res;
	return res;

	//if( fabs( res ) <= 1e-14 && znak ) ungetc( '-', stdin );
	//return res*znak;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

char getOper()
{
	SkipSpaces();
	return getchar();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////

void SkipSpaces()
{
	// Skorzystac z ungetc()
	char c;
	while( ( c = getchar() ) == ' ' );
	ungetc( c, stdin );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int isOper( char c )
{

	switch( c )
	{
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '^': return 1;

	}
	return 0;

	//sprawdza czy c jest znakiem operatora + - * / ^, ()
	//znak pustego stosu ma najni¿szy priorytet
	//zastosowaæ switch
	//zwraca 0 lub 1(jest)
}

///////////////////////////////////////////////////////////////////////////////////////

int isDigit( char c )
{
	return (( c >= '0' ) && ( c <= '9' ));
	//jedna linijka
	//zwraca 0 kiedy c nie jest znakiem cyfry, a 1 kiedy jest
}

///////////////////////////////////////////////////////////////////////////////////////

int prior( char cOper )
{
	switch( cOper )
	{
	case '(': return 1;
	case '+':
	case '-': return 2;
	case '*':
	case '/': return 3;
	case '^': return 4;
	}
	return 0;

	//switch
}

/////////////////////////////////////////////////////////////////////////////////////////

double Eval( char oper, double arg1, double arg2 )
{
	switch( oper )
	{
	case '+': return ( arg1 + arg2 );
	case '-': return ( arg1 - arg2 );
	case '*': return ( arg1 * arg2 );
	case '/':	if( arg2 >= 1e-14 )
		return arg1 / arg2;
		perror( "ERROR: division by 0!!!\n\n" );
		break; // bez klamerek bo nie definiuje zmiennej lokalnej
	case '^': return pow( arg1, arg2 );
	}
	return 0;
	//switch
}

/////////////////////////////////////////////////////////////////////////////////

void Calc()
{
	char c; // znaki z klawiatury

	printf("Podaj dzialanie do obliczenia: \n");

	Stack* pStack = InitStack(); 
	DStack* ppStack = dInitStack(); 

	SkipSpaces();

	
	////////////////////////////////////////////////////
	// NOWE: MINUS PRZED PIERWSZYM NAWIASEM!
	if( ( c = getOper() ) == '-' ) push( c, &pStack );
	else ungetc( c, stdin );
	///////////////////////////////////////////////////
	
	while( ( c = getOper() ) == '(' )
		push( c, &pStack );
	
	ungetc( c, stdin );
		
	dpush( GetNum(), &ppStack ); // Pierwsza liczba

	while( isOper( c = getOper() ) )
	{
		SkipSpaces();
		if( c == ')' )
		{
			while( ( c = pop( &pStack ) ) != '(' )  // liczenie co w () dopoki nie trafi na '('
			{
				double temp = dpop( &ppStack );
				dpush( Eval( c, dpop( &ppStack ), temp ), &ppStack );
			}
		}
		else
		{
			while( prior( c ) <= prior( top( pStack ) ) )
			{
				double temp = dpop( &ppStack );
				dpush( Eval( pop( &pStack ), dpop( &ppStack ), temp ), &ppStack );
			}
			push( c, &pStack );

			while( ( c = getOper() ) == '(' )
			{
					push( c, &pStack );
			}

			ungetc( c, stdin );
			dpush( GetNum(), &ppStack );
		}
	}
	
	while( !isEmpty( pStack ) )
	{
		double temp = dpop( &ppStack );
		dpush( Eval( pop( &pStack ), dpop( &ppStack ), temp ), &ppStack );
	}

	
		printf( "Wynik: %.2f\n\n", dtop( ppStack ) );
		
	
	RemoveStack( &pStack );
	dRemoveStack( &ppStack );

	//ONP
	// Zamiana wyrazenia normalnego na ONP
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////