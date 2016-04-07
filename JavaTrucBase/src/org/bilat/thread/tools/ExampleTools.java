
package org.bilat.thread.tools;

public class ExampleTools
	{

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	/**
	 * tabTheorique = tab1 +tab2
	 */
	public static double[] tabTheorique(int n)
		{
		double[] tab = new double[n];
		for(int i = 1; i <= n; i++)
			{
			tab[i - 1] = (i - 1) * i;
			}
		return tab;
		}

	public static double[] tab1(int n)
		{
		double[] tab = new double[n];
		for(int i = 1; i <= n; i++)
			{
			tab[i - 1] = i * i;
			}
		return tab;
		}

	public static double[] tab2(int n)
		{
		double[] tab = new double[n];
		for(int i = 1; i <= n; i++)
			{
			tab[i - 1] = -i;
			}
		return tab;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	}
