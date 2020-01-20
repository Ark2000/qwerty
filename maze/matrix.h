#pragma once
#define MATRIX_DEBUG
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef int* Matrix;

typedef struct {
	int r;
	int c;
} vec2;

Matrix NewMatrix(int sz);

void DelMatrix(Matrix m);

int* MGet(Matrix m, int r, int c);

int MSize(Matrix m);

#ifdef MATRIX_DEBUG
#include <stdio.h>
void PrintM(Matrix m);
#endif