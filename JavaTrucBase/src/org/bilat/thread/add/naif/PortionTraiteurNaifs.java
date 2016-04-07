
package org.bilat.thread.add.naif;

import org.junit.Assert;

public class PortionTraiteurNaifs implements Runnable
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	/**
	 * <pre>
	 * Hyp 1 : tabInput1,tabInput2,tabOutput de lenth n
	 * Hyp 2 : tabResult already instancié
	 * Hyp 3 : [iStart,iStop] in [1,n]
	 * </pre>
	 */
	public PortionTraiteurNaifs(double[] tabInput1, double[] tabInput2, double[] tabOutput, int iStart, int iStop)
		{
		Assert.assertTrue(tabInput1.length==tabInput2.length);
		Assert.assertTrue(tabInput2.length==tabOutput.length);

		this.tabInput1 = tabInput1;
		this.tabInput2 = tabInput2;
		this.tabOutput = tabOutput;
		this.iStart = iStart;
		this.iStop = iStop;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	@Override
	public void run()
		{
		for(int i = iStart; i <= iStop; i++)
			{
			tabOutput[i - 1] = tabInput1[i - 1]  + tabInput2[i - 1];
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
	private int iStart;
	private int iStop;

	// input/ouputs
	private double[] tabOutput;

	}
