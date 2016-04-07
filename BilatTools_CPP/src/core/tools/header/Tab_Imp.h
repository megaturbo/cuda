#pragma once

#include <iostream>

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur		*|
 \*-------------------------------------*/

template<typename T>
Tab<T>::Tab(T** tab, int size) :
	tab(tab), n(size)
    {
    // rien
    }

template<typename T>
Tab<T>::Tab()
    {
    // rien
    }

template<typename T>
Tab<T>::~Tab(void)
    {
    // cout<<"[Tab] : destructor : "<< this<<endl;

    if (tab != NULL)
	{
	for (int i = 0; i < n; i++)
	    {
	    if (tab[i] != NULL)
		{
		delete tab[i];
		tab[i] = NULL;
		}
	    }

	delete[] tab;
	tab = NULL;
	}

    //cout<<"[Tab] : destructor end"<<endl;
    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

template<typename T>
T** Tab<T>::get()
    {
    return tab;
    }

template<typename T>
int Tab<T>::size()
    {
    return n;
    }

template<typename T>
void Tab<T>::set(T** tab, int size)
    {
    this->tab = tab;
    this->n = size;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*------------------------*\
 |*	copie 		*|
 \*-----------------------*/

/**
 * constructeur copie
 * private to avoid use!
 */
template<typename T>
Tab<T>::Tab(const Tab<T>& source): tab(NULL)
    {
    // rien, never use
    }

/**
 * private to avoid use!
 */
template<typename T>
Tab<T>& Tab<T>::operator=(const Tab<T>& source)
    {
    // rien, never use
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/



