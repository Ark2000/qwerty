#include "list.h"

struct Node {
	ELEM data;
	struct Node* next;
};
typedef List PNode;

List NewList(void)
{
	PNode node = (PNode)malloc(sizeof(struct Node));
	assert(node != NULL);
	node->next = NULL;
	return node;
}

int IsEmpty(List l)
{
	return l->next == NULL;
}

ELEM PopFront(List l)
{
	if (IsEmpty(l)) {
		return l->data;
	} else {
		ELEM data = l->next->data;
		PNode tmp = l->next->next;
		free(l->next);
		l->next = tmp;
		return data;
	}
}

void Insert(List l, ELEM elem, CMP cmp)
{
	PNode newnode = (PNode)malloc(sizeof(struct Node));
	assert(newnode != NULL);
	newnode->data = elem;

	PNode p = l;
	for (; p->next != NULL; p = p->next) {
		if (cmp(&elem, &(p->next->data)) <= 0) {
			break;
		}
	}
	PNode tmp = p->next;
	p->next = newnode;
	newnode->next = tmp;
}

void DelList(List l)
{
	PNode p = l;
	while (p) {
		PNode tmp = p->next;
		free(p);
		p = tmp;
	}
}

/*
int intcmp(const ELEM* left, const ELEM* right)
{
	return *left - *right;
}
#include <stdio.h>
int main(void)
{
	List l = NewList();

	Insert(l, 3, intcmp);
	Insert(l, 1, intcmp);
	Insert(l, 2, intcmp);
	Insert(l, 7, intcmp);
	Insert(l, 3, intcmp);
	Insert(l, 0, intcmp);
	Insert(l, 4, intcmp);
	Insert(l, 4, intcmp);

	while (!IsEmpty(l)) {
		int num = PopFront(l);
		printf("%d ", num);
	}

	DelList(l);

	return 0;
}
*/