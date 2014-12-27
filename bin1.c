#include <stdio.h>

int main()
{
	int s[64];
	int a, b, len = 0, i;
	scanf("%i", &a);
	b = a;
	while (a > 0)
	{
		//b = (a >> 1) << 1;
		s[++len] = a & 1;
		a = a >> 1;
	}
	for (i = len; i > 0; i--)
		printf("%i", s[i]);
	printf("\n");
	return 0;
}
