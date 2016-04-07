#pragma once

//#include "Array.h"
#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur		*|
 \*-------------------------------------*/

template<typename T>
Array<T>::Array(int n) :
	tab(NULL), n(n)
    {
    tab = new T[n]; //Use default constructor of T
    }

template<typename T>
Array<T>::~Array(void)
    {
    delete[] tab;
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

template<typename T>
Array<T>::Array(const Array<T>& source) :
	tab(NULL), n(source.n)
    {
    tab = new T[n]; //Use default constructor of T

    for (int i = 0; i < n; i++)
	{
	tab[i] = source.tab[i]; //Operator= of T
	}
    }

//template<typename T>
//T Array<T>::operator[](int i)
//    {
//   // assert(i>=0 && i<n);
//
//    return tab[i];
//    }

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& source)
    {
    assert(n == source.n);

    for (int i = 0; i < n; i++)
	{
	tab[i] = source.tab[i]; //use operator= of T
	}

    return *this;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/



