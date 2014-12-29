#ifndef STACK_FUNC_H_INCLUDED
#define STACK_FUNC_H_INCLUDED

#include "Num_func.h"

typedef struct stack_node
{
	number *value;
	struct stack_node *next;
} stack_node;

//deletes all elements from stack
void stack_delete(stack_node **head);

//clears all elements from stack
void stack_clear(stack_node **head);

//returns size of stack
int stack_size(stack_node **head);

//returns first element and deletes it from stack
void stack_pop(stack_node **head, number **num);

//adds new element to stack
void stack_push(stack_node **head, number **data);

void stack_print (stack_node **stack_head, number **value);

#endif // STACK_FUNC_H_INCLUDED
