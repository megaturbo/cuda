#include <iostream>

using std::cout;
using std::endl;

#include "Histogram.h"

bool useHistogram(void);

bool useHistogram()
{
	const int SIZE_TAB = 256;	// hardcode op
	int repetition = 3;
	int tabSize = SIZE_TAB * repetition;
	int* tabResult;
	bool isTabRekt = true;

	Histogram histogram(tabSize);
	tabResult = histogram.run();

	cout << "Tab result:" << endl;
	for(int i=0; i < SIZE_TAB; i++)
	{
		isTabRekt &= (tabResult[i] == repetition);
		cout << tabResult[i] << ", ";
	}
	cout << endl;

	return isTabRekt;
}
