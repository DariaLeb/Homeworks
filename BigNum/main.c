#include <stdio.h>
#include <stdlib.h>
#include "stack_func.h"

//processes the commands and calls the necessary functions
int calc_starts(stack_node **stack_head, number **value, number **num1, number **num2, number **result, char *trash)
{
	List *temp = NULL;
	List *tempRev = NULL;
	char operation = '\0', first_digit = '\0';
	int i = 0, ok = 0, digit = 0;

	while((first_digit = getchar()) != EOF)
	{
		//reading number
		Num_clear(value);
		operation = '\0';

		if (first_digit == '=')
		{
			scanf("%c", trash);
			if (stack_size(stack_head) < 1)
			{
				printf("Not enough arguments\n");
				return 1;
			}
			temp = (*stack_head) -> value -> head;
			while(temp != NULL)
			{
				digit = (int)*(&temp -> n);
				List_add(&tempRev, digit);
				temp = temp -> next;
			}
			if ((*stack_head) -> value -> sign == -1)
				printf("-");
			List_print(&tempRev);
			printf("\n");
		}

		else if (first_digit == '+' || first_digit == '*' || first_digit == '/')
		{
			scanf("%c", trash);
			operation = first_digit;
			if ((int)*trash != 10 && *trash != ' ')
				return 1;
		}

		else
		{
			Num_read(value, first_digit);

			if (List_size(&(*value) -> head) == 0)
			{
				if (first_digit == '-')
					operation = first_digit;
				else
					return 1;
			}

			else if ((*value) -> sign == 0xDEAD)
			{
				printf("Unknown command\n");
				return 1;
			}

			else
				stack_push(stack_head, value);
		}

		//executes necessary operation
		if (operation != '\0')
		{
			if (stack_size(stack_head) < 2)
			{
				printf("Not enough arguments\n");
				return 1;
			}
			Num_del(num1);
			Num_del(num2);
			Num_clear(result);

			stack_pop(stack_head, num1);
			stack_pop(stack_head, num2);

			//choice of appropriate command
			if (operation == '+' || operation == '-')
			{
				if ((*num1)->sign == (*num2)->sign)
				{
					if (operation == '+')
						Num_sum(num1, num2, result);
					else
						Num_dif(num1, num2, result);
				}
				else
				{
					if (operation == '-')
						Num_sum(num1, num2, result);
					else
						Num_dif(num1, num2, result);
				}
				(*result) -> sign *= (*num1) -> sign;
			}
			else
			{
				if (operation == '*')
					Num_mult(num1, num2, result);

				else if (operation == '/')
				{
					if (List_size(&(*num2) -> head) == 1 && (*num2) -> head -> n == 0)
					{
						printf("Division by zero\n");
						return 1;
					}
					Num_divide(num1, num2, result);
				}
				if ((*num1) -> sign != (*num2) -> sign)
					(*result) -> sign *= (-1);
				else (*result) -> sign = 1;
			}
			Num_reverse(result);
			stack_push(stack_head, result);
		}
	}

	printf("[");
	while (stack_size(stack_head) != 0)
	{
		Num_del(value);
		stack_pop(stack_head, value);
		if ((*value) -> sign == -1)
			printf("-");
		Num_reverse(value);
		List_print(&(*value)->head);
		if (stack_size(stack_head) != 0)
			printf("; ");
	}
	printf("]");

	*trash = '\12';
	return 0;
}

int main(void)
{
	stack_node *stack_head = NULL;
	number *value = Num_init();
	number *num1 = Num_init();
	number *num2 = Num_init();
	number *result = Num_init();
	char trash = '\12';
	int returnCode = 0;

	returnCode = calc_starts(&stack_head, &value, &num1, &num2, &result, &trash);

	//deleting all numbers
	Num_del(&value);
    Num_del(&num1);
	Num_del(&num2);
	Num_del(&result);
	stack_delete(&stack_head);
	return returnCode;
}
