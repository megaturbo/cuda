#pragma once

#include <iostream>

#include "Grid.h"
#include "Device.h"
//#include "builtin_types.h"
#include "cudaTools.h"

#include "DomaineMath_GPU.h"

using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

namespace gpu
    {
    template<typename T>
    class Animable_I
	{

	    /*--------------------------------------*\
	|*		Constructor		*|
	     \*-------------------------------------*/
	public:

	    Animable_I(const Grid& grid, unsigned int w, unsigned int h, string title, const DomaineMath& domaineInit, bool isGridHeuristic = true) :
		    w(w), h(h), title(title), domaineInit(domaineInit), dg(grid.dg), db(grid.db), isGridHeuristic(isGridHeuristic)
		{
		this->t = 0;

		checkDim(grid);
		}

	    Animable_I(const Grid& grid, unsigned int w, unsigned int h, string title, bool isGridHeuristic = true) :
		    w(w), h(h), title(title), domaineInit(0, w, 0, h), dg(grid.dg), db(grid.db), isGridHeuristic(isGridHeuristic)
		{
		this->t = 0;

		checkDim(grid);
		}

	    virtual ~Animable_I()
		{
		// Nothing here
		}

	    /*--------------------------------------*\
	     |*		Methodes		*|
	     \*-------------------------------------*/

	public:

	    virtual void animationStep(void)=0;

	    virtual void process(T* ptrTabPixels, unsigned int w, unsigned int h, const DomaineMath& domaineMath)=0;

	    /*--------------------------------------*\
	 |*		Get			*|
	     \*-------------------------------------*/

	public:

	    inline float getAnimationPara() const
		{
		return t;
		}

	    inline string getTitle() const
		{
		return title;
		}

	    inline int getW() const
		{
		return w;
		}

	    inline int getH() const
		{
		return h;
		}

	    inline DomaineMath getDomaineMathInit() const
		{
		return domaineInit;
		}

	    inline dim3 getDg() const
		{
		return dg;
		}

	    inline dim3 getDb() const
		{
		return db;
		}

	    /*--------------------------------------*\
	 |*		Set			*|
	     \*-------------------------------------*/

	    void setGrid(const dim3& dg, const dim3& db)
		{
		this->dg = db;
		this->db = db;

		Device::gridAssert(dg, db);
		}

	    void setGrid(const Grid& grid)
		{
		this->dg = grid.dg;
		this->db = grid.db;

		Device::gridAssert(grid);
		}

	    void setGridHeuristic(bool isGridHeuristic)
		{
		this->isGridHeuristic = isGridHeuristic;
		}

	    /*--------------------------------------*\
	     |*		Methodes		*|
	     \*-------------------------------------*/

	private:

	    void checkDim(const dim3& dg, const dim3& db)
		{
		if (isGridHeuristic)
		    {
		    Device::gridHeuristic(dg, db);
		    }
		else
		    {
		    Device::gridAssert(dg, db);
		    }
		}

	    void checkDim(const Grid& grid)
		{
		checkDim(grid.dg, grid.db);
		}

	    /*--------------------------------------*\
	     |*		Attributs		*|
	     \*-------------------------------------*/

	protected:

	    // Inputs
	    const unsigned int w;
	    const unsigned int h;
	    const string title;
	    DomaineMath domaineInit;
	    bool isGridHeuristic;

	    //Tools
	    double t;
	    dim3 dg;
	    dim3 db;
	};

    typedef Animable_I<uchar4> Animable_I_uchar4;
    typedef Animable_I<uchar3> Animable_I_uchar3;
    typedef Animable_I<unsigned char> Animable_I_uchar;

    typedef Animable_I<float4> Animable_I_float4;
    typedef Animable_I<float3> Animable_I_float3;
    typedef Animable_I<float> Animable_I_float;

    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

