#include "path1.h"
#include "path1data.h"
#include "matrix.h"
#include "list.h"
#include <math.h>

int cicmp(const CellInfo* left, const CellInfo* right)
{
	return (left->mts + left->etg) - (right->mts + right->etg);
}

//Manhattan Distance
int estimate(vec2 start, vec2 goal)
{

	int dx = start.c - goal.c;
	int dy = start.r - goal.r;
	return abs(dx) + abs(dy);
}

void A_Star(Matrix m, vec2 start, vec2 goal, vec2* path, int* plen, int pcapacity)
{
	//only vertical and horizonal move are allowed.
	const int adj[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

	Matrix closed = NewMatrix(MSize(m));
	Matrix pre_r  = NewMatrix(MSize(m));
	Matrix pre_c  = NewMatrix(MSize(m));
	List   opened = NewList();

	Insert(opened, (CellInfo){start, 0, estimate(start, goal)}, cicmp);

	*plen = 0;
	while (!IsEmpty(opened)) {
		CellInfo cell = PopFront(opened);
		*MGet(closed, cell.pos.r, cell.pos.c) = 1;

		if (cell.etg == 0) {
			*plen = cell.mts;
			break;
		}

		for (int i = 0; i < 4; ++i) {
			int ar = cell.pos.r + adj[i][0];
			int ac = cell.pos.c + adj[i][1];
			vec2 adjc = {ar, ac};
			if (!*MGet(closed, ar, ac) && *MGet(m, ar, ac) != 0) {
				Insert(opened, (CellInfo){adjc, cell.mts + 1, estimate(adjc, goal)}, cicmp);
				*MGet(pre_r, ar, ac) = cell.pos.r;
				*MGet(pre_c, ar, ac) = cell.pos.c;
			}
		}
	}

	//there should be enough space.
	assert(*plen <= pcapacity);

	path[0] = goal;
	for (int i = 1; i < *plen; ++i) {
		int pr = *MGet(pre_r, path[i-1].r, path[i-1].c);
		int pc = *MGet(pre_c, path[i-1].r, path[i-1].c);
		vec2 prev = {pr, pc};
		path[i] = prev;
	}
	//reverse path to get correct order.
	for (int i = 0; i < *plen / 2; ++i) {
		vec2 tmp = path[i];
		path[i] = path[*plen - i - 1];
		path[*plen - i - 1] = tmp;
	}

	DelMatrix(closed);
	DelMatrix(pre_r);
	DelMatrix(pre_c);
	DelList(opened);
}

AStarDataPack CreateAStarDataPack(Matrix m, vec2 start, vec2 goal, vec2* path, int pcapacity)
{
	AStarDataPack data;

	data.m = m;
	data.start = start;
	data.goal = goal;
	data.path = path;
	data.pcapacity = pcapacity;

	data.plen = 0;

	data.status = -1;

	//Intermediate data
	data.closed = NewMatrix(MSize(m));
	data.pre_r = NewMatrix(MSize(m));
	data.pre_c = NewMatrix(MSize(m));
	data.opened = NewList();

	Insert(data.opened, (CellInfo){start, 0, estimate(start, goal)}, cicmp);

	return data;
}

//n means how many loops in one function call.
void A_Star_calc(AStarDataPack *data, int n)
{
	static const int adj[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

	if (data->status > 0) return;

	Matrix m = data->m;
	vec2 start = data->start;
	vec2 goal = data->goal;
	Matrix closed = data->closed;
	Matrix pre_r = data->pre_r;
	Matrix pre_c = data->pre_c;
	List opened = data->opened;

	for (int i = 0; i < n && !IsEmpty(opened); ++i) {

		CellInfo cell = PopFront(opened);
		*MGet(closed, cell.pos.r, cell.pos.c) = 1;

		if (cell.etg == 0) {
			data->status = 1;
			break;
		}

		for (int i = 0; i < 4; ++i) {
			int ar = cell.pos.r + adj[i][0];
			int ac = cell.pos.c + adj[i][1];
			vec2 adjc = {ar, ac};
			if (!*MGet(closed, ar, ac) && *MGet(m, ar, ac) != 0) {
				Insert(opened, (CellInfo){adjc, cell.mts + 1, estimate(adjc, goal)}, cicmp);
				*MGet(pre_r, ar, ac) = cell.pos.r;
				*MGet(pre_c, ar, ac) = cell.pos.c;
			}
		}
	}

	if (data->status == 1) {
		data->path[0] = goal;
		int pr = goal.r;
		int pc = goal.c;
		++data->plen;
		for (int i = 1; pr != start.r || pc != start.c; ++i) {
			pr = *MGet(pre_r, data->path[i-1].r, data->path[i-1].c);
			pc = *MGet(pre_c, data->path[i-1].r, data->path[i-1].c);
			vec2 prev = {pr, pc};
			++data->plen;
			assert(data->plen <= data->pcapacity);
			data->path[i] = prev;
		}

		for (int i = 0; i < data->plen / 2; ++i) {
			vec2 tmp = data->path[i];
			data->path[i] = data->path[data->plen - i - 1];
			data->path[data->plen - i - 1] = tmp;
		}
	} else
	if (IsEmpty(opened)) {
		//cannot find path
		data->status = 2;
	}

	if (data->status > 0) {
		DelMatrix(closed);
		DelMatrix(pre_r);
		DelMatrix(pre_c);
		DelList(opened);
	}
}

void A_Star_calc_8(AStarDataPack *data, int n)
{
	static const int adj[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

	if (data->status > 0) return;
	if (data->status < 0) {
		//initialization
		CellInfo cell = PopFront(data->opened);
		cell.etg *= 10;
		Insert(data->opened, cell, cicmp);
		data->status = 0;
	}

	Matrix m = data->m;
	vec2 start = data->start;
	vec2 goal = data->goal;
	Matrix closed = data->closed;
	Matrix pre_r = data->pre_r;
	Matrix pre_c = data->pre_c;
	List opened = data->opened;

	for (int i = 0; i < n && !IsEmpty(opened); ++i) {

		CellInfo cell = PopFront(opened);
		*MGet(closed, cell.pos.r, cell.pos.c) = 1;

		if (cell.etg == 0) {
			data->status = 1;
			break;
		}

		for (int i = 0; i < 8; ++i) {
			int ar = cell.pos.r + adj[i][0];
			int ac = cell.pos.c + adj[i][1];
			vec2 adjc = {ar, ac};

			if (
				((i < 4) || (i >= 4 && *MGet(m, ar - adj[i][0], ac) != 0 && *MGet(m, ar, ac - adj[i][1]) != 0)) &&
				!*MGet(closed, ar, ac) && *MGet(m, ar, ac) != 0
			) {
				int mts = i < 4 ? 10 : 14;
				Insert(opened, (CellInfo){adjc, cell.mts + mts, estimate(adjc, goal) * 10}, cicmp);
				*MGet(pre_r, ar, ac) = cell.pos.r;
				*MGet(pre_c, ar, ac) = cell.pos.c;
			}
		}
	}

	if (data->status == 1) {
		data->path[0] = goal;
		int pr = goal.r;
		int pc = goal.c;
		++data->plen;
		for (int i = 1; pr != start.r || pc != start.c; ++i) {
			pr = *MGet(pre_r, data->path[i-1].r, data->path[i-1].c);
			pc = *MGet(pre_c, data->path[i-1].r, data->path[i-1].c);
			vec2 prev = {pr, pc};
			++data->plen;
			assert(data->plen <= data->pcapacity);
			data->path[i] = prev;
		}

		for (int i = 0; i < data->plen / 2; ++i) {
			vec2 tmp = data->path[i];
			data->path[i] = data->path[data->plen - i - 1];
			data->path[data->plen - i - 1] = tmp;
		}
	} else
	if (IsEmpty(opened)) {
		//cannot find path
		data->status = 2;
	}

	if (data->status > 0) {
		DelMatrix(closed);
		DelMatrix(pre_r);
		DelMatrix(pre_c);
		DelList(opened);
	}
}