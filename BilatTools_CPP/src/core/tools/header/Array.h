#pragma once

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Rappel C++
 *
 * 	Banane b1(...);
 * 	Banane b2(...);
 *
 * 	Banane bCopy1=b1; 	// Utilise le constructeur de copie (CC) de Banane
 * 	Banane b2=b1;		// Utilise la surcharge de l'operateur =
 *
 * 	Banane tab[N]; 		// N+1 objet creer, le tableau et N Banane avec le constructeur sans parametre.
 * 	tab[0]=b1; 		// Utilise la surcharge de l'operateur = car tab[0] contient deja une banane!
 *
 * Important:
 *
 * 	La surcharge de l'operateur = est utilisez quand l'objet de destination existe deja.
 * 	Si l'objet de destination doit etre crer, c'est le CC qui est utiliser.
 *
 * Note:
 *
 * 	Par defaut toute classe possede:
 *
 * 		- un cc
 * 		- un operateur =
 *
 * 	Dans les deux cas, les attributs sont copiers bit à bit!
 * 	à moins qu'un cc ou une surcharge de = existe.
 *
 * Consequence:
 *
 * 	Si une classe possede un attribut de type ptr, lors d'une copie par CC ou =, l'adresse sera copie bit à bit.
 * 	On se retrouvera non pas avec un clone mais avec une adresse partagre dans deux instances!
 * 	Le deuxieme objet detruit ne pourra pas détruire sont attributs de type ptr!
 *
 * 	Toute classe possedant un attribut de type ptr devrait
 *
 * 		- soit interdire toute copie (ni cc, ni surcharge =). Il suffit de les mettre private avec un corps vide!
 * 		- soit implementer explicitement (cc et surcharge =) pour effectuer des copies profondes des attributs de type ptr
 *
 *      et ceci de manière recursive sur les objets inclus dans l'element pointer par ptr!
 *
 * Constraints :
 *
 * 	Si T contient un prt, il est conseiller:
 *
 * 	- de surcharger T
 * 	- d'implementer un CC pour T
 *
 * 	dans le cas ou l'implementation ci-dessous n'a pas en private:
 *
 * 	 son consctructeur de copie
 * 	 sa surcharge de =
 **/
template<typename T>
class Array
    {

	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	/**
	 * Allocation of a tab of type T of size n
	 * Use the default constructeur of T
	 */
	Array(int n);

	virtual ~Array(void);

	/*--------------------------------------*\
	 |*		copie			*|
	 \*-------------------------------------*/

    private:

	/**
	 * constrcuteur copie en private pour empecher toute copie
	 */
	Array(const Array<T>& source);

	/**
	 * surcharge = en private pour eviter toute copie
	 */
	Array<T>& operator=(const Array<T>& source);

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

//	/**
//	 * i in [0,n[
//	 */
//	T operator[](int i);

	/*--------------------------------------*\
	 |*		Get			*|
	 \*-------------------------------------*/

	/**
	 * Use this to fill the array with data
	 */
	T* get()
	    {
	    return tab;
	    }

	int size()
	    {
	    return n;
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	T* tab;
	int n;
    };

// Implementaion should be in the same file!
#include "Array_Imp.h"



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
