#pragma once

#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::ofstream;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class ResultWritter
    {

    public:

	/**
	 * Write the Matrice in the texte file filename.
	 *
	 * Sample :
	 *
	 * 	nxm = 10x5, separator= ';'
	 *
	 * 	12;15;78;0;6
	 * 	10;1;6;7;-5
	 * 	...
	 * 	1;2;3;4;5
	 *
	 * Constrain :
	 *
	 * 	T must implements operator<< !
	 */
	template<typename T>
	static bool save(T* ptrMatrice, unsigned int n, unsigned int m, string filename, string separator = ";");

    };

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

template<typename T>
bool ResultWritter::save(T* ptrMatrice, unsigned int n, unsigned int m, string filename, string separator)
    {
    ofstream filestream;
    filestream.open(filename.c_str());
    if (filestream.is_open())
	{
	for (int i = 0; i < n; i++)
	    {
	    for (int j = 0; j < m; j++)
		{
		int s = (i * m) + j; //Indice2D => Indice1D row-major
		filestream << ptrMatrice[s];
		// Pour ne pas ajouter le separateur en fin de ligne
		if (j < m-1)
		    {
		    filestream << separator;
		    }
		}
	    // Saut de ligne
	    filestream << "\n";
	    }

	filestream.close();
	return true;
	}
    return false;

    }



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
