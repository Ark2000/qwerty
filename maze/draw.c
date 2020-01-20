#include "Matrix.h"
#include "svpng.inc"
#include <time.h>
#include <malloc.h>

const int SZ = 16;


const int WHITE[3] = {255, 255, 255};
const int BLACK[3] = {16, 16, 16};
const int GREY[3] = {64, 64, 64};
const int RED[3] = {255, 0, 0};

static void Plot(unsigned char* p, const int* color)
{
	*p++ = (unsigned char)color[0];
	*p++ = (unsigned char)color[1];
	*p++ = (unsigned char)color[2];
}

void DrawMatrix(Matrix m, int has_grid)
{
	char name[64];
	itoa((int)time(NULL), name, 10);
	char randnum[4];
	itoa(rand() % 1000, randnum, 10);
	strcat(name, randnum);
	strcat(name, ".png");

	FILE *fp = fopen(name, "wb");

	unsigned char *rgb, *p;
	int sz = MSize(m) * SZ;
	rgb = (unsigned char*)malloc(sizeof(unsigned char) * sz * sz * 3);
	p = rgb;
	for (int y = 0; y < sz; ++y) {
		for (int x = 0; x < sz; ++x) {
			//draw grid
			if (has_grid) {
				if (y % SZ == 0 || x % SZ == 0) {
					Plot(p, BLACK); p += 3;
					continue;
				}
			}
			int num = *MGet(m, y / SZ, x / SZ);
			switch (num) {
			case 0:
				Plot(p, GREY); break;
			default:
				Plot(p, WHITE); break;
			}
			p += 3;
		}
	}
	svpng(fp, sz, sz, rgb, 0);
	fclose(fp);
}

void DrawMatrixWithPath_1(Matrix map, int has_grid, vec2* path, int plen)
{
	Matrix m = NewMatrix(MSize(map));
	for (int i = 1; i <= MSize(map) * MSize(map); ++i) {
		m[i] = map[i];
	}
	for (int i = 0; i < plen; ++i) {
		*MGet(m, path[i].r, path[i].c) = 2;
	}

	char name[64];
	itoa((int)time(NULL), name, 10);
	char randnum[4];
	itoa(rand() % 1000, randnum, 10);
	strcat(name, randnum);
	strcat(name, ".png");

	FILE *fp = fopen(name, "wb");

	unsigned char *rgb, *p;
	int sz = MSize(m) * SZ;
	rgb = (unsigned char*)malloc(sizeof(unsigned char) * sz * sz * 3);
	p = rgb;
	for (int y = 0; y < sz; ++y) {
		for (int x = 0; x < sz; ++x) {
			//draw grid
			if (has_grid) {
				if (y % SZ == 0 || x % SZ == 0) {
					Plot(p, BLACK); p += 3;
					continue;
				}
			}
			int num = *MGet(m, y / SZ, x / SZ);
			switch (num) {
			case 0:
				Plot(p, GREY); break;
			case 2:
				Plot(p, RED); break;
			default:
				Plot(p, WHITE); break;
			}
			p += 3;
		}
	}
	svpng(fp, sz, sz, rgb, 0);
	fclose(fp);
	DelMatrix(m);
}