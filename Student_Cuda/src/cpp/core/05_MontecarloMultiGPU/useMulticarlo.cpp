#include <iostream>
#include <limits.h>
#include "MathTools.h"

using std::cout;
using std::endl;

#include "host/Multicarlo.h"

bool useMulticarlo(void);

bool useMulticarlo()
{
	float a = -1.0f;
	float b = 1.0f;
	float M = 1.0f;
	int nbFlechettes = INT_MAX / 10;

	Multicarlo multicarlo(a, b, M, nbFlechettes);
	multicarlo.run();
	float pi = multicarlo.getPi();
	cout << "Pi = " << pi << endl;

	return MathTools::isEquals(pi, PI_FLOAT, 0.01f);
}
