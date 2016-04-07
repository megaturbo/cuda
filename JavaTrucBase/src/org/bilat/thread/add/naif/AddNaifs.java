
package org.bilat.thread.add.naif;

import org.junit.Assert;

/**
 * <pre>
 * Travaille sur 2 thread
 * Difficile à généraliser sur nThread
 * </pre>
 */
public class AddNaifs implements Runnable
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	/**
	 * tab1,tab2 : same size
	 */
	public AddNaifs(double[] tab1, double[] tab2)
		{
		Assert.assertTrue(tab1.length == tab2.length);

		this.tab1 = tab1;
		this.tab2 = tab2;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	@Override
	public void run()
		{
		int n = tab1.length;
		tabOutput = new double[n];

		int midle = n / 2;

		PortionTraiteurNaifs portionTraiteur1 = new PortionTraiteurNaifs(tab1, tab2, tabOutput, 1, midle);
		PortionTraiteurNaifs portionTraiteur2 = new PortionTraiteurNaifs(tab1, tab2, tabOutput, midle + 1, n);

		Thread thread1 = new Thread(portionTraiteur1);
		Thread thread2 = new Thread(portionTraiteur2);

		thread1.start();
		thread2.start();

		join(thread1, thread2);
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

	private void join(Thread thread1, Thread thread2)
		{
		try
			{
			thread1.join();
			thread2.join();
			}
		catch (InterruptedException e)
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

	// outputs
	private double[] tabOutput;

	}
