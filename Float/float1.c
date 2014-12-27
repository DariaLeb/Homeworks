#include <stdio.h>

int main()
{
	float f, frac = 1, t = 0.5;
	int intf, sign, ex, i;
	scanf("%f", &f);
 	intf = *(int *)(&f);
	sign = !!(intf >> 31);
	ex = (intf >> 23) & 0xFF;
	for(i = 22; i >= 0; i--)
	{
		frac += !!((intf >> i) & 1) * t;
		t = t / 2;
	}
	printf("Sign = %c\nExponent = %d\nFraction = %f\n", sign ? '1' : '0', ex - 127, frac);
}
