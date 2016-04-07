#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "Device.h"
#include "cudaTools.h"

#include "VagueProvider.h"
#include "DamierProvider.h"
#include "VagueGrayProvider.h"
#include "DamierRGBAFloatProvider.h"
#include "DamierHSBAFloatProvider.h"
#include "DamierHueFloatProvider.h"
#include "EventProvider.h"
#include "OverlayProvider.h"
#include "DomaineProvider.h"

#include "MyGLUTWindow.h"
#include "MyDisplayableProvider.h"

#include "Settings_GPU.h"
#include "Viewer_GPU.h"
using namespace gpu;

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainImage(Settings& settings);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainImage(Settings& settings)
    {
    cout << "\n[Image] mode" << endl;

    GLUTImageViewers::init(settings.getArgc(), settings.getArgv()); //only once

    // ImageOption : (boolean,boolean) : (isSelection ,isAnimation)
    ImageOption zoomable(true);
    ImageOption nozoomable(false);

    Viewer<VagueProvider> vague(nozoomable, 25, 25); // imageOption px py
    Viewer<DamierProvider> damier(zoomable, 50, 50); // imageOption px py

    Viewer<EventProvider> event(nozoomable, 75, 75); // imageOption px py
    Viewer<OverlayProvider> overlay(nozoomable, 100, 100); // imageOption px py
    Viewer<DomaineProvider> domaine(nozoomable, 125, 125); // imageOption px py

    Viewer<VagueGrayProvider> vagueGray(nozoomable, 150, 150); // imageOption px py
    Viewer<DamierRGBAFloatProvider> damierRGBAFloat(nozoomable, 175, 175); // imageOption px py
    Viewer<DamierHSBAFloatProvider> damierHSBAfloat(nozoomable, 200, 200); // imageOption px py
    Viewer<DamierHueFloatProvider> damierHUEfloat(nozoomable, 225, 225); // imageOption px py

    // Custom (Advanced)
     Displayable_A* ptrMyDisplayable = MyDisplayableProvider::createGL();
     MyGLUTWindow myGlutWindow(ptrMyDisplayable, "OpenGL : Custom Displayable", 600, 600, 250, 250); // scene OpenGL // (w,h,px,py)


    // Common
    GLUTImageViewers::runALL(); // Bloquant, Tant qu'une fenetre est ouverte

    cout << "\n[Image] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

