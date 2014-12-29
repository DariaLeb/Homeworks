#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Num_func.h"

int max (int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}

int min (int x, int y)
{
    if (x < y)
        return x;
    else
        return y;
}

number* Num_init()
{
    number *p = (number*) malloc(sizeof(number));
    if (p == NULL)
        return 1;
    p -> sign = 1;
    p -> head = NULL;
    return p;
}

void Num_clear(number **num)
{
    List_delList(&(*num) -> head);
    (*num) -> sign = 1;
    return;
}

void Num_del(number **num)
{
    Num_clear(num);
    free(*num);
    return;
}


void Num_delZeroes(number **num)
{
	while(((*num) -> head) -> n == 0)
	{
		List_remove(&(*num) -> head, 0);
		if ((*num) -> head == NULL)
		{
			List_add(&(*num) -> head, 0);
			break;
		}
	}
	return;
}

void Num_print(number **num)
{
	List *p = &(*num) -> head;
	while (p != NULL)
	{
		printf("%i", p -> n);
		p = p -> next;
	}
	printf("\n");
	return;
}

void Num_reverse(number **num)
{
	List *result = NULL;
	List *p = (*num)->head;
	int sign = (*num)->sign;

	while(p != NULL)
	{
		List_add(&result, p -> n);
		p = p -> next;
	}
	Num_clear(num);
	(*num)->head = result;
	(*num)->sign = sign;
	return;
}

int Num_read(number **num, char first_digit)
{
	char digit;

	digit = first_digit;
	if (digit == '-')
		(*num)->sign = -1;
	else if (digit < '0' || digit > '9')
	{
		while((int)digit != 10)
			scanf("%c", &digit);
		return 1;
	}
	else
		List_add(&(*num)->head, (int)digit - (int)('0'));
	while (1)
	{
		digit = getchar();
		if (digit < ('0') || digit > ('9'))
		{
			if ((int)digit == 10 || digit == ' ' || (int)digit == EOF)
				break;
			else
			{
				while((int)digit != 10)
					scanf("%c", &digit);
				return 1;
			}
		}
		List_add(&(*num)->head, (int)digit - (int)('0'));
	}
	return 0;
}

int Num_sum(number **num1, number **num2, number **num_sum)
{
	List *p1 = (*num1) -> head, *p2 = (*num2) -> head;
	int a = 0, i;
	while ((p1 != NULL) || (p2 != NULL))
	{
	    i = 0;
		if (p1 != NULL)
        {
			i += p1 -> n;
			p1 = p1 -> next;
        }
		if (p2 != NULL)
        {
			i += p2 -> n;
			p2 = p2 -> next;
        }
		i += a;
		if (List_add(&(*num_sum) -> head, i % 10) == 1)
		{
			Num_del(num_sum);
			return 1;
		};
		a = max(i / 10, 0);
	}
	if (a != 0)
		if (List_add(&(*num_sum) -> head, a) == 1)
		{
			Num_del(num_sum);
			return 1;
		}
	Num_delZeroes(num_sum);
	if ((((*num_sum) -> head) -> n == 0) && List_size(&(*num_sum) -> head) == 1)
		(*num_sum) -> sign = 0;
	return 0;
}

void Num_dif(number **num1, number **num2, number **result)
{
	List *p = NULL;
	List *p1 = (*num1) -> head;
	List *p2 = (*num2) -> head;
	number *tempRes = Num_init();
	int a = 0, less = 0, first = 1, digit = 0;

	(*result) -> sign = 1;
	while(p1 != NULL || p2 != NULL)
	{
		if (p1 == NULL && a)
			less = 1;
		if (p1 != NULL)
		{
			a += p1 -> n;
			p1 = p1 -> next;
		}
		if (p2 != NULL)
		{
			a -= p2 -> n;
			p2 = p2 -> next;
		}

		if (a < 0)
		{
			List_add(&tempRes->head, a + 10);
			a = -1;
		}
		else
		{
			List_add(&tempRes->head, a);
			a = 0;
		}
	}
	Num_reverse(&tempRes);
	if (a)
		less = 1;
	if (less)
	{
		a = 0;
		p = tempRes->head;
		while(p != NULL)
		{
			digit = 9 - (int)*(&p -> n) + a;
			if (first)
			{
				digit++;
				if (digit == 10)
				{
					digit = 0;
					a = 1;
				}
				else
					a = 0;
				List_add(&(*result) -> head, digit);
				first = 0;
			}
			else
			{
				if (digit == 10)
				{
					digit = 0;
					a = 1;
				}
				else
					a = 0;
				List_add(&(*result) -> head, digit);
			}
			p = p -> next;
		}
		(*result) -> sign = -1;
	}
	else
	{
		p = tempRes->head;
		while(p != NULL)
		{
			digit = (int)*(&p -> n);
			List_add(&(*result) -> head, digit);
			p = p -> next;
		}
	}
	Num_delZeroes(result);
	if ((((*result) -> head) -> n == 0) && List_size(&(*result) -> head) == 1)
		(*result) -> sign = 0;
	Num_del(&tempRes);
	return;
}

void Num_mult(number **num1, number **num2, number **result)
{
	List *p = NULL;
	List *p1Mult = (*num1)->head;
	List *p2Mult = (*num2)->head;
	number *p1Sum = Num_init();
	number *p2Sum = Num_init();
	number *tempResSum = Num_init();
	int digit = 0, less = 0, a = 0, i = 0, counter = 0;
	if (List_size(&(*num1)->head) < List_size(&(*num2)->head))
	{
		p1Mult = (*num2)->head;
		p2Mult = (*num1)->head;
		less = 1;
	}

	while(p2Mult != NULL)
	{
		digit = p2Mult -> n;
		if (!less)
			p1Mult = (*num1) -> head;
		else
			p1Mult = (*num2) -> head;
		a = 0;
		List_delList(&p1Sum -> head);

		while(p1Mult != NULL)
		{
			a += digit * p1Mult -> n;
			List_add(&p1Sum -> head, a % 10);
			a /= 10;
			p1Mult = p1Mult->next;
		}
		if (a)
			List_add(&p1Sum -> head, a);
		Num_reverse(&p1Sum);
		for (i = 0; i < counter; ++i)
			List_add(&p1Sum -> head, 0);

		List_delList(&tempResSum -> head);
		Num_sum(&p1Sum, &p2Sum, &tempResSum);
		List_delList(&p2Sum->head);

		p = tempResSum -> head;
		while(p != NULL)
		{
			digit = (int)*(&p -> n);
			List_add(&p2Sum -> head, digit);
			p = p->next;
		}
		counter++;
		p2Mult = p2Mult->next;
	}
	p = p2Sum->head;
	while(p != NULL)
	{
		digit = (int)*(&p -> n);
		List_add(&(*result) -> head, digit);
		p = p->next;
	}
	Num_delZeroes(result);
	if ((((*result) -> head) -> n == 0) && List_size(&(*result) -> head) == 1)
		(*result) -> sign = 0;
	Num_del(&p1Sum);
	Num_del(&p2Sum);
	Num_del(&tempResSum);
	return;
}

void Num_divide(number **num1, number **num2, number **result)
{
	List *p = NULL;
	List *p1 = NULL;
	number *temp1Div = *num1;
	number *temp1Sub = Num_init();
	number *temp2Sub = *num2;
	number *tempResSub = Num_init();
	int digit = 0, tempDigit = 0, less = 0, a = 0, mod0 = 0;

	Num_reverse(&temp1Div);
	p1 = temp1Div -> head;
	while(p1 != NULL)
	{
		a = 0;
		digit = (int)p1 -> n;
		List_add(&temp1Sub -> head, digit);
		while(1)
		{
			Num_clear(&tempResSub);
			Num_dif(&temp1Sub, &temp2Sub, &tempResSub);
			if (tempResSub -> sign < 0)
				break;
			Num_clear(&temp1Sub);
			p = tempResSub -> head;
			while(p != NULL)
			{
				tempDigit = (int)*(&p -> n);
				List_add(&temp1Sub -> head, tempDigit);
				p = p -> next;
			}
			a++;
		}
		p1 = p1 -> next;
		List_add(&(*result) -> head, a);
	}
	if (List_size(&temp1Sub -> head) == 1 && temp1Sub -> head -> n == 0)
		mod0 = 1;
	if ((*num1) -> sign == -1 && !mod0)
	{
		Num_clear(&temp1Sub);
		p = (*result) -> head;
		while(p != NULL)
		{
			tempDigit = (int)*(&p -> n);
			List_add(&temp1Sub -> head, tempDigit);
			p = p -> next;
		}
		temp2Sub = Num_init();
		List_add(&temp2Sub -> head, 1);
		Num_clear(result);
		Num_sum(&temp1Sub, &temp2Sub, result);
	}
	Num_reverse(&(*result));
	Num_delZeroes(result);
	if ((((*result) -> head) -> n == 0) && List_size(&(*result) -> head) == 1)
			(*result) -> sign = 0;
	Num_del(&temp1Sub);
	Num_del(&tempResSub);
	return;
}
