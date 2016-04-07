
package org.bilat.thread.add.smart;

import org.junit.Assert;

/**
 * <pre>
 * Avantage :
 * 		(A1) Généraliser à nThread
 * 		(A2) Approche Cuda compatibe!
 * </pre>
 */
public class PortionTraiteurSmarts implements Runnable
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	/**
	 * <pre>
	 * Hyp 1 : tabInput1,tabInput2,tabOutput de lenth n
	 * Hyp 2 : tabResult already instancié
	 * </pre>
	 */
	public PortionTraiteurSmarts(double[] tabInput1, double[] tabInput2, double[] tabOutput, int nbThread, int threadIndex)
		{
		Assert.assertTrue(tabInput1.length == tabInput2.length);
		Assert.assertTrue(tabInput2.length == tabOutput.length);

		this.tabInput1 = tabInput1;
		this.tabInput2 = tabInput2;
		this.tabOutput = tabOutput;

		this.threadIndex = threadIndex;
		this.nbThread = nbThread;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	/**
	 * Si nbThread=1, le code ci-dessous est focntionnel
	 *
	 *  	int n = tabInput1.length;
	 *		int i = 1;
	 *		while(i <= n)
	 *			{
	 *			tabOutput[i - 1] = tabInput1[i - 1] + tabInput2[i - 1];
	 *			i += 1;
	 *			}
	 *
	 * Il s'agit d'une boucle for(int i=1;i<=n;i++) ecrite en while
	 * Comme nbThread!=1, il faut généraliser!
	 *
	 * Exemple (E1) :
	 * 		Supposons nbThread=3, et n = 9
	 * 		On partitionne notre tableau comme suit:
	 *
	 *     		 1 2 3 4 5 6 7 8 9
	 * 			 a b c a b c a b c
	 *
	 * 		Le thread 1 : doit parcouris tous les : a (il y en a 3)
	 * 		Le thread 2 : doit parcouris tous les : b (il y en a 3)
	 * 		Le thread 3 : doit parcouris tous les : c (il y en a 3)
	 *
	 *     		 1 2 3 4 5 6 7 8 9
	 * 			 a     a     a 		(Thread 1 : parcours 1 4 7 : delta =3 : start=1=indexThread)
	 *		 	  b     b     b  	(Thread 2 : parcours 2 5 8 : delta =3 : start=2=indexThread)
	 *         	   c     c     c	(Thread 3 : parcours 3 6 9 : delta =3 : start=3=indexThread)
	 *
	 * 		Pour passer de a1 à a4, if faut incrémenter l'indice de 3=nbThread.
	 * 		Idem pour b et c
	 *
	 * Exemple (E2) :
	 * 		Supposons nbThread=3, et n = 10
	 * 		On partitionne notre tableau comme suit:
	 *
	 *      	1 2 3 4 5 6 7 8 9 10
	 * 			a b c a b c a b c a
	 *
	 * 		Le thread 1 : doit parcouris tous les : a (il y en a 4!)
	 * 		Le thread 2 : doit parcouris tous les : b (il y en a 3)
	 * 		Le thread 3 : doit parcouris tous les : c (il y en a 3)
	 *
	 *      1 2 3 4 5 6 7 8 9 10
	 * 		a     a     a 	  a  	(Thread 1 : parcours 1 4 7 10 : delta =3 : start=1=indexThread))
	 *		  b     b     b  		(Thread 2 : parcours 2 5 8    : delta =3 : start=2=indexThread))
	 *          c     c     c		(Thread 3 : parcours 3 6 9    : delta =3 : start=3=indexThread))
	 */
	@Override
	public void run() // call once by every thread!!
		{
		int n = tabInput1.length;
		int tid = threadIndex;

		while(tid <= n)
			{
			tabOutput[tid - 1] = tabInput1[tid - 1] + tabInput2[tid - 1];
			tid += nbThread;
			}
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// input
	private double[] tabInput1;
	private double[] tabInput2;
	private int threadIndex;
	private int nbThread;

	// input/ouputs
	private double[] tabOutput;

	}
