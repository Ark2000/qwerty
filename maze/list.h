#pragma once
#include <stdlib.h>
#include <assert.h>

//////////////////////////////////
///////////////config/////////////
//typedef int ELEM;
#include "path1.h"
typedef CellInfo ELEM;
//////////////////////////////////

typedef int (*CMP)(const ELEM* left, const ELEM* right);

typedef struct Node *List;

List NewList(void);

int IsEmpty(List l);

ELEM PopFront(List l);

void Insert(List l, ELEM elem, CMP cmp);

void DelList(List l);