#pragma once

#include <mutex>
#include <iostream>
#include <assert.h>
#include <thread>

using std::mutex;
using std::cout;
using std::endl;

using std::this_thread::get_id;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class SingletonStd
    {
    private:

	SingletonStd()
	    {
	    cout << "[SingletonStd] ::create" << endl;

	    SingletonStd::compteur++;
	    assert(SingletonStd::compteur == 1);
	    }

    public:

	static SingletonStd* getInstance()
	    {
	    mutexInstance.lock();
	    if (instance == NULL)
		{
		instance = new SingletonStd();
		}
	    mutexInstance.unlock();
	    return instance;
	    }

	void print_tid()
	    {
	    cout << get_id() << endl;
	    ;
	    }

    private:

	static int compteur;

	static mutex mutexInstance;

	static SingletonStd* instance;

    };

mutex SingletonStd::mutexInstance;

SingletonStd* SingletonStd::instance = NULL;

int SingletonStd::compteur = 0;



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
