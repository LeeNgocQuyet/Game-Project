#ifndef _calculate__H
#define _calculate__H
#include <math.h>
#include <iostream>
using namespace std;
void calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy)
{
	int steps = max(abs(x1 - x2), abs(y1 - y2));

	if (steps == 0)
	{
		*dx = *dy = 0;
		return;
	}

	*dx = (x1 - x2);
	*dx /= steps;

	*dy = (y1 - y2);
	*dy /= steps;
}

double angle_degrees(int x1, int y1, int x2, int y2) {

  double adjacent = abs(x2 - x1);
  double opposite = abs(y2 - y1);
  double angle_radians = atan2(opposite, adjacent);

  double angle_degrees = angle_radians * 180.0 / M_PI;

  return angle_degrees;
}
#endif
