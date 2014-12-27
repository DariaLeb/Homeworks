#ifndef LIST_FUNC_H_INCLUDED
#define LIST_FUNC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct tagList List;
struct tagList
{
	int n;
	List * next;
};

int List_add(List **L, int x);

int List_del(List **L, int x);

void List_print(List **L);

void List_delList(List **L);

int List_reverse(List **L);

#endif // LIST_FUNC_H_INCLUDED
