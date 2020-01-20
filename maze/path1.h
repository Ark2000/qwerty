#pragma once
#include "matrix.h"

typedef struct {
	vec2 pos;	//cell position
	int mts;	//The shortest path to the start point
	int etg;	//The estimated path to the goal point
} CellInfo;