#include <stdio.h>
#include <stdlib.h>
#include "List_func.h"

int main()
{
    List *list = NULL;
	char c;
	int i;
	while ((c = getchar()) != 'q')
		switch (c)
		{
			case 'a':
			{
				scanf("%i", &i);
				if (List_add(&list, i) == 1)
					printf("Error\n");
				break;
			}
			case 'r':
			{
				scanf("%i", &i);
				if (List_remove(&list, i) == 1)
					printf("Not found =(\n");
				break;
			}
			case 'p':
			{
				List_print(&list);
				break;
			}
		}
	List_delList(&list);
	return 0;
}
