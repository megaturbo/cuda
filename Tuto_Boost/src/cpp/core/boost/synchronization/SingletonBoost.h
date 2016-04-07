#pragma once

#include <boost/thread.hpp>
#include <iostream>
#include <assert.h>

using boost::mutex;
using std::cout;
using std::endl;

using boost::this_thread::get_id;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class SingletonBoost
    {
    private:

	SingletonBoost()
	    {
	    cout<<"[SingletonBoost] :: create"<<endl;

	    SingletonBoost::compteur++;
	    assert(SingletonBoost::compteur==1);
	    }

    public:

	static SingletonBoost* getInstance()
	    {
	    mutexInstance.lock();
	    if (instance == NULL)
		{
		instance = new SingletonBoost();
		}
	    mutexInstance.unlock();
	    return instance;
	    }

	void print_tid()
	    {
	    cout<<get_id()<<endl;
	    }

    private:

	static int compteur;

	static mutex mutexInstance;

	static SingletonBoost* instance;

    };


mutex SingletonBoost::mutexInstance;

SingletonBoost* SingletonBoost::instance=NULL;

int SingletonBoost::compteur=0;



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
