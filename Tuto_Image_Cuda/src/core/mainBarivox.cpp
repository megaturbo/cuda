#include <iostream>
#include <stdlib.h>

#include "VagueProvider.h"
#include "DamierProvider.h"
#include "VagueGrayProvider.h"
#include "DamierRGBAFloatProvider.h"
#include "DamierHSBAFloatProvider.h"
#include "DamierHueFloatProvider.h"

#include "Barivox.h"

#include "Settings_GPU.h"
using namespace gpu;

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |* Declaration *|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainBarivox(Settings& settings);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void vague();
static void damier();
static void vagueGray();
static void damierRGBAFloat();
static void damierHSBAFloat();
static void damierHueFloat();

// Tools
template<typename T>
static void barivox(Provider_I<T>* ptrProvider, string titre);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainBarivox(Settings& settings)
    {
    cout << "\n[Barivox] mode" << endl;

    // Attention : Un a la fois seulement!

    vague();
//    damier();
//    vagueGray();
//    damierRGBAFloat();
//    damierHSBAFloat();
//    damierHueFloat();

    cout << "\n[Barivox] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void vague()
    {
    VagueProvider provider;
    barivox<uchar4>(&provider, "Vague_RGBA_uchar4");
    }

void damier()
    {
    DamierProvider provider;
    barivox<uchar4>(&provider, "Damier_RGBA_uchar4");
    }

void vagueGray()
    {
    VagueGrayProvider provider;
    barivox<uchar>(&provider, "Vague_GRAY_uchar");
    }

void damierRGBAFloat()
    {
    DamierRGBAFloatProvider provider;
    barivox<float4>(&provider, "Vague_RGBA_float4");
    }

void damierHSBAFloat()
    {
    DamierHSBAFloatProvider provider;
    barivox<float4>(&provider, "Vague_HSBA_float4");
    }

void damierHueFloat()
    {
    DamierHueFloatProvider provider;
    barivox<float>(&provider, "Vague_Hue_float");
    }

/*-----------------------------------*\
 |*		Tools	        	*|
 \*-----------------------------------*/

/**
 * Grid 1d Only
 */
template<typename T>
void barivox(Provider_I<T>* ptrProvider, string titre)
    {
    cout << "\n[Barivox] : " << titre << endl;

    // Define Grid
    int mp = Device::getMPCount();
    int coreMp = Device::getCoreCountMP();
    int nbThreadBlockMax = Device::getMaxThreadPerBlock();
    int warpSize = Device::getWarpSize();

    dim3 dgStart(mp*2, 1, 1);
    VariateurData variateurDg(mp, 8 * mp, mp); 				// (min,max,step)  Attention : A definir intelligement selon le GPU !
    VariateurData variateurDb(coreMp, nbThreadBlockMax, warpSize); 	// (min,max,step)  Attention : A definir intelligement selon le GPU !

    // Run
    const bool IS_ANIMATOR_VERBOSITY_ENABLE = false; //TODO CBI BarivoxOption
    const bool IS_BARIVOX_VERBOSITY_ENABLE = true;
    const int NB_ITERATION = 1000;

    Barivox<T> barivox(ptrProvider, dgStart, variateurDg, variateurDb, NB_ITERATION, IS_BARIVOX_VERBOSITY_ENABLE, IS_ANIMATOR_VERBOSITY_ENABLE);
    const BarivoxOutput output = barivox.run();

    // Print
	{
	cout<<output<<endl;
	}

    // Save
	{
	output.save("out/barivox/barivox_" + titre);
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
