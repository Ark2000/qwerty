#include "matrix.h"
#include "path1data.h"

Matrix DrunkWalk(int sz, int seed);
Matrix PrimTree(int sz, int seed);
void DrawMatrix(Matrix m, int has_grid);
void DrawMatrixWithPath_1(Matrix map, int has_grid, vec2* path, int plen);
AStarDataPack CreateAStarDataPack(Matrix m, vec2 start, vec2 goal, vec2* path, int pcapacity);
void A_Star_calc(AStarDataPack *data, int n);

int main(void)
{
	Matrix maze1 = DrunkWalk(128, 0);
//	PrintM(maze1);putchar('\n');
	DrawMatrix(maze1, 1);
	DelMatrix(maze1);


	Matrix maze2 = PrimTree(128, 0);
//	PrintM(maze2);putchar('\n');
	DrawMatrix(maze2, 1);

	AStarDataPack pack = CreateAStarDataPack(maze2, (vec2){1, 1}, (vec2){126, 126}, (vec2*)malloc(sizeof(vec2) * 512), 512);
	while (pack.status == 0) A_Star_calc(&pack, 32);
	if (pack.status == 1) DrawMatrixWithPath_1(maze2, 1, pack.path, pack.plen);
	else if (pack.status == 2);//no path found
	free(pack.path);

	DelMatrix(maze2);

	return 0;
}