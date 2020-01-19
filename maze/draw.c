#include "Matrix.h"
#include "svpng.inc"
#include <time.h>
#include <malloc.h>

const int SZ = 16;


const int WHITE[3] = {255, 255, 255};
const int BLACK[3] = {16, 16, 16};
const int GREY[3] = {64, 64, 64};

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