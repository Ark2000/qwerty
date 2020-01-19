#include "matrix.h"
#include <time.h>

typedef struct
{
	int r;
	int c;
} vec2;

Matrix PrimTree(int sz)
{
	srand(time(0));
	const int adj[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

	Matrix m = NewMatrix(sz);
	vec2* cand = (vec2*)malloc(sizeof(vec2) * sz * sz);
	int clen = 0;

	*MGet(m, 1, 1) = 1;
	cand[clen++] = (vec2){1, 2};
	cand[clen++] = (vec2){2, 1};

	while (clen > 0) {
		int id = rand() % clen;
		vec2 b = cand[id];
		cand[id] = cand[--clen];

		*MGet(m, b.r, b.c) = 1;
		
		for (int i = 0; i < 4; ++i) {
			int br = b.r + adj[i][0];
			int bc = b.c + adj[i][1];
			if (br > 0 && bc > 0 && br < sz - 1 && bc < sz - 1 && *MGet(m, br, bc) == 0) {
				cand[clen++] = (vec2){br, bc};
			}
		}
		for (int j = 0; j < clen;) {
			int cc, cr;
			for (int i = 0; i < 4; ++i) {
				cr = cand[j].r + adj[i][0];
				cc = cand[j].c + adj[i][1];
				if (*MGet(m, cr, cc) != 0) {
					cr = adj[i][0];
					cc = adj[i][1];
					break;
				}
			}
			int adj2[5][2] = {{-cr, -cc}, {cc, cr}, {-cc, -cr}, {cc-cr, cr-cc}, {-cc-cr, -cr-cc}};
			int flag = 0;
			for (int i = 0; i < 5; ++i) {
				int pr = cand[j].r + adj2[i][0];
				int pc = cand[j].c + adj2[i][1];
				if (*MGet(m, pr, pc) != 0) {
					flag = 1;
					break;
				}
			}
			if (flag) {
				cand[j] = cand[--clen];
			} else {
				++j;
			}
		}
	}
	return m;
}