#include <stdio.h>

int poww(int a, int k)
{
	if (!k)
		return 1;
	int t = poww(a, k >> 1);
	return (t * t * (1 + (a - 1) * (k & 1)));
}

int main()
{
	int a, n;
	scanf("%i %i", &a, &n);
	printf("%i\n", poww(a, n));
	return 0;
}
