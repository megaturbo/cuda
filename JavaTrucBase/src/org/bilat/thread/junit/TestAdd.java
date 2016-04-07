
package org.bilat.thread.junit;

import static org.junit.Assert.assertTrue;

import org.bilat.thread.use.UseAdds;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class TestAdd
	{

	/*------------------------------------------------------------------*\
	 |*							Constructeurs							*|
	 \*------------------------------------------------------------------*/

	@Before
	public void before()
		{
		// rien
		}

	@After
	public void after()
		{
		// rien
		}

	/*------------------------------------------------------------------*\
	 |*							Methodes Public							*|
	 \*-----------------------------------------------------------------*/

	@Test
	public void testAdd()
		{
		int nMax = 1000;
		int nbThreadMax=25;

		for(int nbThread = 1; nbThread <= nbThreadMax; nbThread++)
			{
			System.out.println("nbThread : "+nbThread);
			for(int i = 25; i <= nMax; i++)
				{
				assertTrue(UseAdds.isOk(i,nbThread));
				}
			}

		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	}
