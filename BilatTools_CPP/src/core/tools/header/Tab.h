#pragma once

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Goal : Object with array and size
 *
 * see classe Array!
 */
template<typename  T>
class Tab
    {

	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	/**
	 * destructor delete array and the element in the array
	 */
	Tab(T** tab, int size);

	/**
	 * use set to fill object
	 */
	Tab();

	/**
	 * delete array and element in the array
	 */
	virtual ~Tab(void);

	/*--------------------------------------*\
	 |*		copie			*|
	 \*-------------------------------------*/

    private:

	/**
	 * constrcuteur copie en private pour empecher toute copie
	 */
	Tab(const Tab<T>& source);

	/**
	 * surcharge = en private pour eviter toute copie
	 */
	Tab<T>& operator=(const Tab<T>& source);

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	T** get();
	int size();

	void set(T** tab, int size);

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	T** tab;
	int n;

    };

// Implementaion should be in the same file!
#include "Tab_Imp.h"



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
