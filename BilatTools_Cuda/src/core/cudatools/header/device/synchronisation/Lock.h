#pragma once
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * General :
 *
 * 	A Mutex will act like something of a traffic signal that governs access to some resources.
 * 	When a thread reads a 0 from the mutex,it interprets this valu as a "green lignt" indicating that no other thread is using the memory.
 * 	Therefore, the thread is free to lock the memory and make whatever changes it desires,free of interference from other threads.
 * 	To lock the memory location in nquestion, the thread writes a 1 to the mutex.
 * 	This will act as a "red light" for potentially competing threads.
 * 	The competing threads must then wait until the owner has written a 0 to the mutex beforfe they can attempt to modify the locked memory.
 *
 * Interet
 * 	On utilise un lock lorsque l'opération qui doit être synchroniser ne possède pas d'opérateur atomic (comme atomicADD, ...),
 * 	ou lorsqui'il s'agit de plusieurs opérations à synchroniser (joue alors le role de section critique)
 *
 * Note :
 *
 * 	Lock ne laisse aucune trace coté host, il s'instancie only coté device: Code moins invasif
 * 	LockMixte laisse une trace coté host. Code plus invasif
 *
 *
 * Use : (Device side only)
 *
 *
 *	// Global variable of .cu
 * 	__device__ int mutex=0;	// Attention à l'initialisation
 *
 *	// variable local inside a kernel (same .cu as variable mutex)
 * 	Lock lock=Lock(&mutex);
 *
 * 	lock.lock();
 * 	doSomething();
 * 	lock.unlock();
 *
 *
 * WARNING:  ----------> !!!!!!!!!!!! <--------------
 *
 *      Contrainte:
 *
 *      	Ce lock ne marche que si un seul thread d'un block l'utilise! (ce qui est dans le cas dans la reduction interblock, pour lequel is est concu!)
 *
 *      Exemple (bonne utilisation)
 *
 *      	if (tid==0) // capitale! (0 ou un autre id)
 *      		{
 *      		Lock lock=Lock(&mutex);
 *
 *      		lock.lock();
 *      		doSomething(); // souvent une operation atomique qui n'existe pas
 *      		lock.unlock();
 *      		}
 *
 *      Exemple (mauvaise utilisation)
 *
 *              __global__ void myKernel(...)
 *              	{
 *              	Lock lock=Lock(&mutex);
 *
 *              	lock.lock(); 	// (A)
 *      		doSomething(); 	// (B)
 *      		lock.unlock(); 	// (C)
 *              	}
 *
 *               Observation:
 *
 *               	Le programme freeze! (ou TimeOut atteind)
 *
 *               Explication (model cuda7)
 *
 *			Soit tid0 le thread qui prend le premier le lock.
 *			Il cree une thread divergence.
 *			En B il est mis en pause, et attend que les autres threads le rejoignent!
 *			En effet, tout les threads d'un meme warp doivent faire la meme chose en meme temps!
 *			Quand ce n'est pas possible, les threads qui divergent sont mis en pause provisoirement.
 *
 *			tid0 attent indefiniment les autres threads qui eux sont bloquer en (A) a cause du mutex.
 *
 *
 *		Plus globalement : thread divergence model
 *
 *			On considere le schema d'execution suivant:
 *
 *				x
 *				|
 *			      |   |
 *                            a	  b
 *                              |
 *                              y
 *
 *                       On suppose :
 *
 *                       	24 threads passent en droite dans a
 *                       	8  threads passent  à gauche dans b
 *
 *                       Model 1 (Faux):
 *
 *				Le warp est casser en deux des le debut en deux "sous-warp"
 *
 *					sous-warp a de 24 threads
 *					sous-warp b de 8  threads
 *
 *				le sous-warp b est executer au complet : x --> a --> y
 *				puis
 *				le sous-warp c est executer au complet : x --> b --> y
 *
 *				Observation : Dommage, x comme y aurait pu etre fait de maniere 32-parralel!
 *
 *			Model 2 (Juste)
 *
 *				Le warp execute x de maniere 32-parrelel!
 *				A la thread divergence,l e warp est casser deux "sous-warp"
 *
 *					sous-warp a de 24 threads
 *					sous-warp b de 8  threads
 *
 *				le sous-warp b execute a
 *				puis attend
 *				le sous-warp c execute b
 *				puis attend
 *
 *				Reunification, le warp au complet execute de maniere 32 parallels y
 *
 *				Observation : x comme y on ete fait de maniere 32 parallel!
 *
 * Link
 *
 * 	http://stackoverflow.com/questions/2021019/how-to-implement-a-critical-section-in-cuda
 * 	https://devtalk.nvidia.com/default/topic/512038/cuda-programming-and-performance/atomic-locks/1/
 *
 */
class Lock
    {

	/*--------------------------------------*\
	 |*		Constructor		*|
	 \*-------------------------------------*/

    public:

	/**
	 * Toutes les instance se partagent la meme adresse du mutex ptrDevMutexGM
	 */
	__device__
	Lock(int* ptrDevMutexGM)
	    {
	    this->ptrDevMutexGM = ptrDevMutexGM;
	    }

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void lock(void)
	    {
	    // Goal :
	    // 		if (*ptrDev_mutex==0) {*ptrDev_mutex==1}
	    // 		But must be thread safe!
	    //
	    // Solution:
	    // 		atomicCAS  = atomic Compare And Swap
	    // 		Prototype : 	c atomicCAS(ptr,a,b)
	    // 		Action :	compare ptr avec a, si egale affecte b à ptr, renvoie ptr

	    // Tant que ptrDev_mutex!=0 le thread cuda boucle sur while
	    // Des qu'il vaut 0, il met le mutex à 1 et lock se termine
	    while (atomicCAS(ptrDevMutexGM, 0, 1) != 0);
	    }

	__device__
	void unlock(void)
	    {
	    // Goal :
	    //		Put 1 in the mutex
	    //
	    // Solution 1:
	    //
	    //		*ptrDev_mutex=0;
	    //		Aucun thread en competition ici. L'affectation n'a pas besoin d'être atomique.
	    //		Solution satisfaisante.
	    //
	    // Solution 2 (prefered for symetric approach)
	    //
	    //		Une solution atomique

	    // Echange et renvoie la valeur originale
	    atomicExch(ptrDevMutexGM, 0);
	    }

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	int* ptrDevMutexGM;
    };



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
