#include <stdio.h>

int main()
{
	int n, x, t;
	scanf("%i %i", &x, &n);
	t = x >> (n - 1);
	printf("%i\n", !(t + !!t));
	return 0;
}
