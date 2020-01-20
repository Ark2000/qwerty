
#pragma once
#include "matrix.h"
#include "list.h"

//A* data package waiting to be operated.
typedef struct {
	Matrix m;
	vec2 start;
	vec2 goal;
	vec2* path;
	int pcapacity;
	int plen;
	
	int status;	//0 means calculating, otherwise calculated.

	List opened;
	Matrix closed;
	Matrix pre_r;
	Matrix pre_c;

} AStarDataPack;