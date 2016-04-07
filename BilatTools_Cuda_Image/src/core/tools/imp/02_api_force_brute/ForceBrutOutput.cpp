#include <sstream>

#include "ForceBrutOutput.h"
#include "ResultWritter.h"


using std::stringstream;
using std::cout;
using std::cerr;
using std::endl;

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
 |*		Public			*|
 \*-------------------------------------*/

ForceBrutOutput::ForceBrutOutput(GridMaillage& gridMaillage) :
	gridMaillage(gridMaillage), tabFps(new int[gridMaillage.size()])
    {
    // Rien
    }

ForceBrutOutput::ForceBrutOutput(const ForceBrutOutput& source) :
	gridMaillage(source.gridMaillage), tabFps(new int[source.gridMaillage.size()])
    {
    for (int i = 0; i < gridMaillage.size(); i++)
	{
	tabFps[i] = source.tabFps[i];
	}
    }

ForceBrutOutput::~ForceBrutOutput()
    {
    delete[] tabFps;
    }

ForceBrutOutput& ForceBrutOutput::operator=(const ForceBrutOutput& source)
    {
    gridMaillage = source.gridMaillage;

    for (int i = 0; i < gridMaillage.size(); i++)
	{
	tabFps[i] = source.tabFps[i];
	}

    return *this;
    }

void ForceBrutOutput::setFps(int s, int fps)
    {
    tabFps[s] = fps;
    }

void ForceBrutOutput::setFps(int i, int j, int fps)
    {
    int s = i * gridMaillage.getM() + j;
    tabFps[s] = fps;
    }

string ForceBrutOutput::toStringFps() const
    {
    stringstream ss;
    const int N = gridMaillage.getN();
    const int M = gridMaillage.getM();

    for (int i = 0; i < N; i++)
	{
	for (int j = 0; j < M; j++)
	    {
	    int s = i * M + j;
	    ss << tabFps[s] << "\t";
	    }

	ss << std::endl;
	}

    return ss.str();
    }

string ForceBrutOutput::toStringThreadByBlock() const
    {
    stringstream ss;
    const int N = gridMaillage.getN();
    const int M = gridMaillage.getM();
    Grid* tabGrid = gridMaillage.getTabGrid();

    for (int i = 0; i < N; i++)
	{
	for (int j = 0; j < M; j++)
	    {
	    int s = i * M + j;
	    ss << tabGrid[s].threadByBlock() << "\t";
	    }

	ss << std::endl;
	}

    return ss.str();
    }

string ForceBrutOutput::toStringThreadTotal() const
    {
    stringstream ss;
    const int N = gridMaillage.getN();
    const int M = gridMaillage.getM();
    Grid* tabGrid = gridMaillage.getTabGrid();

    for (int i = 0; i < N; i++)
	{
	for (int j = 0; j < M; j++)
	    {
	    int s = i * M + j;
	    ss << tabGrid[s].threadCounts() << "\t";
	    }

	ss << std::endl;
	}

    return ss.str();
    }

string ForceBrutOutput::toStringNbBlocks() const
    {
    stringstream ss;
    const int N = gridMaillage.getN();
    const int M = gridMaillage.getM();
    Grid* tabGrid = gridMaillage.getTabGrid();

    for (int i = 0; i < N; i++)
	{
	for (int j = 0; j < M; j++)
	    {
	    int s = i * M + j;
	    ss << tabGrid[s].blockCounts() << "\t";
	    }

	ss << std::endl;
	}

    return ss.str();
    }

vector<GridFps> ForceBrutOutput::getMax() const
    {
    const int N = gridMaillage.getN();
    const int M = gridMaillage.getM();

    int max = tabFps[0];
    for (int s = 0; s < N * M; s++)
	{
	int fps = tabFps[s];
	if (fps > max)
	    {
	    max = fps;
	    }
	}

    // Get all grid there fps egals max
	{
	vector<GridFps> vectorGridFps;
	for (int s = 0; s < N * M; s++)
	    {
	    int fps = tabFps[s];
	    if (fps == max)
		{
		GridFps gridFps;
		gridFps.fps = fps;
		gridFps.grid = gridMaillage.getTabGrid()[s];
		vectorGridFps.push_back(gridFps);
		}
	    }

	return vectorGridFps;
	}
    }


//void ForceBrutOutput::save(string prefixe) const
//    {
//    const int N = gridMaillage.getN();
//    const int M = gridMaillage.getM();
//
//    string fileExtention=".csv";
//    string filenameFps=prefixe+"_fps"+fileExtention;
//
//    if(!ResultWritter::save<int>(tabFps,N,M,filenameFps))
//	{
//	std::cerr<<"[ForceBrutOutput] : Fail writting output file : "<<filenameFps<<std::endl;
//	}
//    }

void ForceBrutOutput::save(string prefixe) const
    {
    const int N = gridMaillage.getN();
    const int M = gridMaillage.getM();
    Grid* tabGrid = gridMaillage.getTabGrid();

    string fileExtention = ".csv";
    string filenameFps = prefixe + "_fps" + fileExtention;

    if (!ResultWritter::save<int>(tabFps, N, M, filenameFps))
	{
	std::cerr << "[ForceBrutOutput] : Fail writting output file" << filenameFps << std::endl;
	}

    // Write threadByBlock
	{
	int* tabData = new int[N * M];
	for (int i = 0; i < N * M; i++)
	    {
	    tabData[i] = tabGrid[i].threadByBlock();
	    }
	string filenameThreadByBlock = prefixe + "_db" + fileExtention;
	if (!ResultWritter::save<int>(tabData, N, M, filenameThreadByBlock))
	    {
	    std::cerr << "[ForceBrutOutput] : Fail writting output file" << filenameThreadByBlock << std::endl;
	    }
	delete[] tabData;
	}

    // Write ThreadTotal
//	{
//	int* tabData = new int[N * M];
//	for (int i = 0; i < N * M; i++)
//	    {
//	    tabData[i] = tabGrid[i].threadCounts();
//	    }
//	string filenameThreadTotal = prefixe + "_ThreadTotal" + fileExtention;
//	if (!ResultWritter::save<int>(tabData, N, M, filenameThreadTotal))
//	    {
//	    std::cerr << "[ForceBrutOutput] : Fail writting output file" << filenameThreadTotal << std::endl;
//	    }
//	delete[] tabData;
//	}

    // Write NbBlocks
	{
	int* tabData = new int[N * M];
	for (int i = 0; i < N * M; i++)
	    {
	    tabData[i] = tabGrid[i].blockCounts();
	    }
	string filenameNbBlocks = prefixe + "_dg" + fileExtention;
	if (!ResultWritter::save<int>(tabData, N, M, filenameNbBlocks))
	    {
	    std::cerr << "[ForceBrutOutput] : Fail writting output file" << filenameNbBlocks << std::endl;
	    }
	delete[] tabData;
	}
    }

/*--------------------------------------*\
 |*		print			*|
 \*-------------------------------------*/

void ForceBrutOutput::print(ostream& stream, const string& titre) const
    {
    vector<GridFps> tabMax = getMax();
    const GridMaillage* ptrGridMaillage = getGridMaillage();

    stream << titre << endl;

  //  stream << "Output brutforce (#Threads Total) = " << endl << toStringThreadTotal() << endl;
    stream << "Output brutforce (#Blocks) = " << endl << toStringNbBlocks() << endl;
    stream << "Output brutforce (#Threads ByBlock) = " << endl << toStringThreadByBlock() << endl;
  //  stream << "Output brutforce (grid)" << (*ptrGridMaillage) << endl;
    stream << "Output brutforce (fps) = " << endl << toStringFps() << endl;
    stream << "Output brutforce (max) = " << endl << toString(tabMax) << endl;
    }

/**
 * friend
 */
ostream& operator <<(ostream& stream, const ForceBrutOutput& forceBrutOutput)
    {
    forceBrutOutput.print(stream);
    return stream;
    }

/*----------------------------------------------------------------------*\
 |*			Static 						*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

string ForceBrutOutput::toString(vector<GridFps> vectorGridFps)
    {
    stringstream ss;

    ss << "  fps (max) = " << vectorGridFps[0].fps << std::endl;
    ss << "  #Grid = " << vectorGridFps.size() << std::endl;
    for (int s = 0; s < vectorGridFps.size(); s++)
	{
	GridFps gridFps = vectorGridFps[s];

	int nbThreadTotal = gridFps.grid.threadCounts();
	int nbBlocks = gridFps.grid.blockCounts();
	int nbThreadByBlock = gridFps.grid.threadByBlock();

	ss << "    " << gridFps.grid << "\t#blocks=" << nbBlocks << "\t#ThreadsByBlock=" << nbThreadByBlock << "\t#Thread(Total)=" << nbThreadTotal
		<< std::endl;
	}

    return ss.str();
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

