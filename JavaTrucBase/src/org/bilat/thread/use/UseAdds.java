
package org.bilat.thread.use;

import org.bilat.thread.add.naif.AddNaifs;
import org.bilat.thread.add.smart.AddSmarts;
import org.bilat.thread.tools.ExampleTools;
import org.bilat.thread.tools.TabTools;

public class UseAdds
	{

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	public static void main(String[] args)
		{
		main();
		}

	public static void main()
		{
		int n=10;
		int nbThreadSmart = Runtime.getRuntime().availableProcessors() * 2;

		System.out.println("isOk : " + isOk(n,nbThreadSmart));
		}

	public static boolean isOk(int n,int nbThreadSmart)
		{
		double[] tab1 = ExampleTools.tab1(n);
		double[] tab2 = ExampleTools.tab2(n);
		double[] tabTheorique = ExampleTools.tabTheorique(n);

		double[] tabResultNaif = naif(tab1, tab2);
		double[] tabResultSmart = smart(tab1, tab2,nbThreadSmart);

//		TabTools.print("naif", tabResultNaif);
//		TabTools.print("smart", tabResultSmart);
//		TabTools.print("theorique", tabTheorique);

		return TabTools.isEgale(tabResultNaif, tabTheorique) && TabTools.isEgale(tabResultSmart, tabTheorique);
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/**
	 * 2 thread only, difficilement généralisable
	 */
	private static double[] naif(double[] tab1, double[] tab2)
		{
		AddNaifs add = new AddNaifs(tab1, tab2);
		add.run();
		return add.getTabOutput();
		}

	/**
	 * n thread, cuda compatible
	 */
	private static double[] smart(double[] tab1, double[] tab2,int nbThreadSmart)
		{
		AddSmarts add = new AddSmarts(tab1, tab2, nbThreadSmart);
		add.run();
		return add.getTabOutput();
		}

	}
