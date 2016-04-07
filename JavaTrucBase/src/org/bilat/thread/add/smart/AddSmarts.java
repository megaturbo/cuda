
package org.bilat.thread.add.smart;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

import org.junit.Assert;

/**
 * Travaille sur n thread
 */
public class AddSmarts implements Runnable
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	/**
	 * tab1,tab2 : same size
	 */
	public AddSmarts(double[] tab1, double[] tab2, int nbThread)
		{
		Assert.assertTrue(tab1.length == tab2.length);

		this.tab1 = tab1;
		this.tab2 = tab2;
		this.nbThread = nbThread;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	@Override
	public void run()
		{
		int n = tab1.length;
		tabOutput = new double[n];

		//workVersion1(tabOutput);// Thread
		workVersion2(tabOutput, executoService); // poolThread (cf delta time in junit test! From 52s to 12s)
		}

	/*------------------------------*\
	|*				Get				*|
	\*------------------------------*/

	public double[] getTabOutput()
		{
		return this.tabOutput;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/**
	 * Thread
	 */
	private void workVersion1(double[] tabOutput)
		{
		Thread[] tabThread = new Thread[nbThread];
		for(int i = 1; i <= nbThread; i++)
			{
			tabThread[i - 1] = new Thread(new PortionTraiteurSmarts(tab1, tab2, tabOutput, nbThread, i));
			tabThread[i - 1].start();
			}

		join(tabThread);
		}

	/**
	 * Pool thread
	 */
	private void workVersion2(double[] tabOutput, ExecutorService executoService)
		{
		Future<?>[] tabFutue = new Future[nbThread];
		for(int i = 1; i <= nbThread; i++)
			{
			tabFutue[i - 1] = executoService.submit(new PortionTraiteurSmarts(tab1, tab2, tabOutput, nbThread, i));
			}

		join(tabFutue);
		}

	/*------------------------------*\
	|*			  Static			*|
	\*------------------------------*/

	private static void join(Thread[] tabThread)
		{
		try
			{
			for(int i = 1; i <= tabThread.length; i++)
				{
				tabThread[i - 1].join();
				}
			}
		catch (InterruptedException e)
			{
			e.printStackTrace();
			}
		}

	private static void join(Future<?>[] tabFutue)
		{
		try
			{
			for(int i = 1; i <= tabFutue.length; i++)
				{
				tabFutue[i - 1].get();
				}
			}
		catch (Exception e)
			{
			e.printStackTrace();
			}
		}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Inputs
	private double[] tab1;
	private double[] tab2;
	private int nbThread;

	// outputs
	private double[] tabOutput;

	/*------------------------------*\
	|*			  Static			*|
	\*------------------------------*/

	private static ExecutorService executoService = Executors.newCachedThreadPool();

	}
