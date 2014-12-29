#ifndef NUM_FUNC_H_INCLUDED
#define NUM_FUNC_H_INCLUDED

#include "list_func.h"

typedef struct number
{
	int sign;
	List *head;
} number;

int max (int x, int y);
int min (int x, int y);

number* Num_init();
void Num_clear(number **num);
void Num_del(number **num);
void Num_delZeroes(number **num);
void Num_print(number **num);
void Num_reverse(number **num);
int Num_read(number **num, char first_digit);

int Num_sum(number **num1, number **num2, number **num_sum);
void Num_dif(number **num1, number **num2, number **result);
void Num_mult(number **num1, number **num2, number **result);
void Num_divide(number **num1, number **num2, number **result);

#endif //NUM_FUNC_H_INCLUDED
