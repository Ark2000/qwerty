#include "matrix.h"

Matrix NewMatrix(int sz)
{
	assert(sz > 0);

	int* m = (int*)malloc(sizeof(int) * (sz * sz + 1));
	assert(m != NULL);

	m[0] = sz;
	memset(m + 1, 0, sz * sz * sizeof(int));
	return m;
}

void DelMatrix(Matrix m)
{
	free(m);
}

int* MGet(Matrix m, int r, int c)
{
#ifdef MATRIX_DEBUG
	assert(r >= 0 && r < m[0] && c >= 0 && c < m[0]);
#endif
	return m + r * m[0] + c + 1;
}

int MSize(Matrix m)
{
	return m[0];
}

#ifdef MATRIX_DEBUG
void PrintM(Matrix m)
{
	int sz = m[0];
	for (int i = 0; i < sz - 1; ++i) {
		for (int j = 0; j < sz; ++j) {
			printf("%3d ", *MGet(m, i, j));
		}
		putchar('\n');
	}
	for (int j = 0; j < sz; ++j) {
		printf("%3d ", *MGet(m, sz - 1, j));
	}
}
#endif