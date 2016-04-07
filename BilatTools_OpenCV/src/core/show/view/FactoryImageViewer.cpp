#include "FactoryImageViewer.h"

#include "CVViewerMatBGR.h"
#include "CVViewerUcharBGR.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

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



/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/


ImageViewer_I* FactoryImageViewer::create( Capture_I* ptrCapture, string ID_WINDOW)
    {
    CVViewerUcharBGR* ptrViewer=new CVViewerUcharBGR(ptrCapture, ID_WINDOW);

    return ptrViewer;
    }

ImageViewer_I* FactoryImageViewer::create(CaptureMat_I* ptrCapture, string ID_WINDOW)
    {
    CVViewerMatBGR* ptrViewer=new CVViewerMatBGR(ptrCapture, ID_WINDOW);
   // CVViewerUcharBGR* ptrViewer=new CVViewerUcharBGR(ptrCapture, ID_WINDOW);

     return ptrViewer;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

