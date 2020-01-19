#include "matrix.h"
#include "time.h"
Matrix DrunkWalk(int sz)
{
	srand(time(0));

	Matrix m = NewMatrix(sz);

	const int nit = (int)(sz * sz * 1.20);
	const int ran = 83;

	const int startx = rand() % (sz - 2) + 1;
	const int starty = sz - 2;

	int px = startx; int py = starty;
	int dx = 0; int dy = 0;

	for (int i = 0; i < nit; ++i) {
		*MGet(m, py, px) = 1;

		if (rand() % 100 > ran) {
			switch (rand() % 4) {
				case 0: dx = 1; dy = 0; break;
				case 1: dx = -1; dy = 0; break;
				case 2: dy = 1; dx = 0; break;
				case 3: dy = -1; dx = 0; break;
			}
		}

		if (px + dx <= 0) {
			dx = 1;
		} else
		if (px + dx >= sz - 1) {
			dx = -1;
		} else
		if (py + dy <= 0) {
			dy = 1;
		} else
		if (py + dy >= sz - 1) {
			dy = -1;
		}
		px += dx; py += dy;
	}
	return m;
}