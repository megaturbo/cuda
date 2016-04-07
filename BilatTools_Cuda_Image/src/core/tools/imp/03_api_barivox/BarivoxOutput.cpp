#include <sstream>
#include <iostream>
#include <assert.h>

#include "BarivoxOutput.h"
#include "ResultWritter.h"
#include "Device.h"

using std::stringstream;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void maxFps(int* ptrTab, int n, int* ptrImax);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructor		*|
 \*-------------------------------------*/

BarivoxOutput::BarivoxOutput(int nDg, int nDb) :
	tabFpsDb(new int[nDb]), nDb(nDb), tabFpsDg(new int[nDg]), nDg(nDg), tabDg(new dim3[nDg]), tabDb(new dim3[nDb])
    {
    // rien
    }

BarivoxOutput::BarivoxOutput(const BarivoxOutput& source) :
	nDb(source.nDb), tabFpsDb(new int[source.nDb]), tabFpsDg(new int[source.nDg]), nDg(source.nDg), tabDg(new dim3[source.nDg]), tabDb(new dim3[source.nDb])
    {
    for (int i = 0; i < nDb; i++)
	{
	tabFpsDb[i] = source.tabFpsDb[i];
	tabDg[i] = source.tabDg[i];
	}

    for (int i = 0; i < nDb; i++)
	{
	tabFpsDg[i] = source.tabFpsDg[i];
	tabDg[i] = source.tabDg[i];
	}
    }

BarivoxOutput::~BarivoxOutput()
    {
    delete[] tabFpsDb;
    delete[] tabFpsDg;

    delete[] tabDg;
    delete[] tabDb;
    }

/*--------------------------------------*\
|*		Methodes		*|
 \*-------------------------------------*/

BarivoxOutput& BarivoxOutput::operator=(const BarivoxOutput& source)
    {
    if (nDb != source.nDb)
	{
	nDb = source.nDb;
	delete[] tabFpsDb;
	tabFpsDb = new int[nDb];
	}
    for (int i = 0; i < nDb; i++)
	{
	tabFpsDb[i] = source.tabFpsDb[i];
	tabDb[i] = source.tabDb[i];
	}

    if (nDg != source.nDg)
	{
	nDg = source.nDg;
	delete[] tabFpsDb;
	tabFpsDg = new int[nDg];
	}
    for (int i = 0; i < nDg; i++)
	{
	tabFpsDg[i] = source.tabFpsDg[i];
	tabDg[i] = source.tabDg[i];
	}

    return *this;
    }

string BarivoxOutput::toStringFpsDb() const
    {
    stringstream ss;

    for (int i = 0; i < nDb; i++)
	{
	ss << tabFpsDb[i] << "\t";
	}
    ss << std::endl;
    return ss.str();
    }

string BarivoxOutput::toStringFpsDg() const
    {
    stringstream ss;

    for (int i = 0; i < nDg; i++)
	{
	ss << tabFpsDg[i] << "\t";
	}
    ss << std::endl;
    return ss.str();
    }

string BarivoxOutput::toStringDg() const
    {
    stringstream ss;

    for (int i = 0; i < nDg; i++)
	{
	ss << tabDg[i].x << "\t";
	}
    ss << std::endl;
    return ss.str();
    }

string BarivoxOutput::toStringDb() const
    {
    stringstream ss;

    for (int i = 0; i < nDb; i++)
	{
	ss << tabDb[i].x << "\t";
	}
    ss << std::endl;
    return ss.str();
    }

void BarivoxOutput::save(string prefixe) const
    {
    string fileExtention = ".csv";

    // Fps db
	{
	string file = prefixe + "_fps_db" + fileExtention;
	if (!ResultWritter::save<int>(tabFpsDb, 1, nDb, file))
	    {
	    std::cerr << "Fail writting output file" << file << std::endl;
	    }
	}

    // Fps dg
	{
	string file = prefixe + "_fps_dg" + fileExtention;
	if (!ResultWritter::save<int>(tabFpsDg, 1, nDg, file))
	    {
	    std::cerr << "Fail writting output file" << file << std::endl;
	    }
	}

    //dg
	{
	int* tabData = new int[nDg];
	for (int i = 0; i < nDg; i++)
	    {
	    tabData[i] = Device::dim(tabDg[i]);
	    }

	string file = prefixe + "_dg" + fileExtention;
	if (!ResultWritter::save<int>(tabData, 1, nDg, file))
	    {
	    std::cerr << "Fail writting output file" << file << std::endl;
	    }
	delete[] tabData;
	}

    //db
	{
	int* tabData = new int[nDb];
	for (int i = 0; i < nDb; i++)
	    {
	    tabData[i] = Device::dim(tabDb[i]);
	    }

	string file = prefixe + "_db" + fileExtention;
	if (!ResultWritter::save<int>(tabData, 1, nDb, file))
	    {
	    std::cerr << "Fail writting output file" << file << std::endl;
	    }

	delete[] tabData;
	}
    }

/*--------------------------------------*\
 |*		Set			*|
 \*-------------------------------------*/

void BarivoxOutput::setFpsDb(int s, int fps)
    {
    tabFpsDb[s] = fps;
    }

void BarivoxOutput::setFpsDg(int s, int fps)
    {
    tabFpsDg[s] = fps;
    }

void BarivoxOutput::setCroix(int2 croix)
    {
    this->croix = croix;
    }

void BarivoxOutput::setCroix(int dgInit, int dbMaxForDgInit)
    {
    int2 croix =
	{
	dgInit, dbMaxForDgInit
	};
    setCroix(croix);
    }

void BarivoxOutput::setGrid(dim3* tabDg, dim3* tabDb)
    {
    // dg
	{
	for (int i = 0; i < nDg; i++)
	    {
	    this->tabDg[i] = tabDg[i];
	    }
	}

    //db
	{
	for (int i = 0; i < nDb; i++)
	    {
	    this->tabDb[i] = tabDb[i];
	    }
	}
    }

/*--------------------------------------*\
 |*		print			*|
 \*-------------------------------------*/

void BarivoxOutput::print(ostream& stream, const string& titre) const
    {
    stream << titre << endl;

    int dgStart = croix.x;
    int dbMax = croix.y;

    stream << endl;
    stream << "Output Barivox croix = (dgStart,dbMax)=(" << dgStart << "," << dbMax << ")";
    stream << endl << endl;
    stream << "Output Barivox --> dg = " << dgStart << " (fixe)" << endl;
    stream << "Output Barivox --> \t\tdb  : " << toStringDb();
    stream << "Output Barivox --> \t\tfps : " << toStringFpsDb();
    stream << endl;
    stream << "Output Barivox  dg " << endl;
    stream << "Output Barivox   ^" << endl;
    stream << "Output Barivox   |  db = " << dbMax << " (fixe)" << endl;
    stream << "Output Barivox   |  \t\tdg  : " << toStringDg();
    stream << "Output Barivox   |  \t\tfps : " << toStringFpsDg();
    stream << "Output Barivox   |";
    stream << endl;
    stream << endl;
    stream << "Output Barivox";
    stream << endl;
    max(stream);
    stream << endl;
    }

/**
 * friend
 */
ostream& operator <<(ostream& stream, const BarivoxOutput& barivoxOutput)
    {
    barivoxOutput.print(stream);
    return stream;
    }

void BarivoxOutput::max(ostream& stream) const
    {
    int imaxDb = -1;
    int imaxDg = -1;

    maxFps(tabFpsDb, nDb, &imaxDb);
    maxFps(tabFpsDg, nDg, &imaxDg);

    int nbBlocks;
    int nbThreadByBlock;
    int fpsMax;

    // dg fixe
    if (tabFpsDb[imaxDb] > tabFpsDg[imaxDg])
	{
	nbBlocks = croix.x;
	nbThreadByBlock = Device::dim(tabDb[imaxDb]);

	fpsMax = tabFpsDb[imaxDb];
	}
    else //db fixe
	{
	nbThreadByBlock = croix.y;
	nbBlocks =  Device::dim(tabDg[imaxDg]);

	fpsMax = tabFpsDg[imaxDg];
	}

    int nbThreadTotal = nbBlocks * nbThreadByBlock;

    stream << "\tfps (max) = " << fpsMax << std::endl;
    stream << "\t"<<"#blocks=" << nbBlocks << "\t#ThreadsByBlock=" << nbThreadByBlock << "\t#Thread(Total)=" << nbThreadTotal << std::endl;
    }

void maxFps(int* ptrTab, int n, int* ptrImax)
    {
    int max = 0;
    *ptrImax = -1;

    for (int i = 0; i < n; i++)
	{
	if (ptrTab[i] > max)
	    {
	    *ptrImax = i;
	    max = ptrTab[i];
	    }
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

