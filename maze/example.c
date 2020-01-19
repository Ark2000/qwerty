#include "matrix.h"

Matrix DrunkWalk(int sz);
Matrix PrimTree(int sz);
void DrawMatrix(Matrix m, int has_grid);

int main(void)
{
	Matrix maze1 = DrunkWalk(256);
//	PrintM(maze1);putchar('\n');
	DrawMatrix(maze1, 1);
	DelMatrix(maze1);


	Matrix maze2 = PrimTree(256);
//	PrintM(maze2);putchar('\n');
	DrawMatrix(maze2, 1);
	DelMatrix(maze2);

	return 0;
}