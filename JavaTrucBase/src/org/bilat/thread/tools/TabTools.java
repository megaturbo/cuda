
package org.bilat.thread.tools;

public class TabTools
	{

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	public static void print(String titre, double[] tab)
		{
		System.out.println(titre + " (1x" + tab.length + ")");
		for(int i = 1; i <= tab.length; i++)
			{
			System.out.println(tab[i - 1]);
			}
		System.out.println("\n");
		}

	public static boolean isEgale(double[] tab1, double[] tab2)
		{
		if (tab1.length == tab2.length)
			{
			for(int i = 1; i <= tab1.length; i++)
				{
				if (tab1[i - 1] != tab2[i - 1]) { return false; }
				}

			return true;
			}
		else
			{
			return false;
			}
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	}
