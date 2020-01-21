#include "matrix.h"
#include "path1data.h"

Matrix DrunkWalk(int sz, int seed);
Matrix PrimTree(int sz, int seed);
void DrawMatrix(Matrix m, int has_grid);
void DrawMatrixWithPath_1(Matrix map, int has_grid, vec2* path, int plen);
AStarDataPack CreateAStarDataPack(Matrix m, vec2 start, vec2 goal, vec2* path, int pcapacity);
void A_Star_calc(AStarDataPack *data, int n);
void A_Star_calc_8(AStarDataPack *data, int n);

int main(void)
{
	Matrix maze1 = DrunkWalk(64, 0);
//	PrintM(maze1);putchar('\n');
//	DrawMatrix(maze1, 1);


	Matrix maze2 = PrimTree(64, 0);
//	PrintM(maze2);putchar('\n');
//	DrawMatrix(maze2, 1);

	AStarDataPack pack1 = CreateAStarDataPack(maze1, (vec2){13, 13}, (vec2){62, 62}, (vec2*)malloc(sizeof(vec2) * 256), 256);
	AStarDataPack pack2 = CreateAStarDataPack(maze2, (vec2){1, 1}, (vec2){62, 62}, (vec2*)malloc(sizeof(vec2) * 256), 256);
	for (int i = 0 ; i < 10000; ++i) {
		A_Star_calc_8(&pack1, 32);
		A_Star_calc_8(&pack2, 32);
	}
	if (pack1.status == 1) DrawMatrixWithPath_1(maze1, 1, pack1.path, pack1.plen);
	if (pack2.status == 1) DrawMatrixWithPath_1(maze2, 1, pack2.path, pack2.plen);

	free(pack1.path);
	free(pack2.path);

	DelMatrix(maze2);
	DelMatrix(maze1);
	return 0;
}