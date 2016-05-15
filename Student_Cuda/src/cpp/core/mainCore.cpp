#include <iostream>
#include <stdlib.h>

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern bool useHello(void);
extern bool useAddVecteur(void);
extern bool useSlice(void);
extern bool useMontecarlo(void);
extern bool useHistogram(void);
extern bool useMulticarlo(void);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainCore();

/*--------------------------------------*\
 |*				Private					*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*				Public					*|
 \*-------------------------------------*/

int mainCore()
{
	bool isOk = true;
	isOk &= useHello();
//    isOk &=useAddVecteur();	Invalid argument at AddVector.cu @ 52
	isOk &= useSlice();
	isOk &= useMontecarlo();
	isOk &= useHistogram();
	isOk &= useMulticarlo();

	cout << "\nisOK = " << isOk << endl;
	cout << "\nEnd : mainCore" << endl;

	return isOk ? EXIT_SUCCESS : EXIT_FAILURE;
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

