/*
	Task: "look inside a float number"
	Author: Darina Lebedeva, group 171
*/


#include <stdio.h>

int main()
{
	float f, a, b, fmant;
	int intf, mant, ex;
	char sign;
	scanf("%f %f", &a, &b);
	f = a / b;
	intf = *(int *)(&f);
 	sign = (intf & (1 << 0x1F)) ? '-' : '+';
	mant = intf & ((1 << 23) - 1);
	ex = ((intf >> 23) & 0xFF);

	if (!mant && !ex) {
		printf("%c0\n", sign);
		return;
	}

	if (!mant && !(ex ^ 0xFF)) {
		printf("%cInf\n", sign);
		return;
	}

	if (mant && !(ex ^ 0xFF)) {
		printf("NaN\n");
		return;
	}

	fmant = 1.0 + 1.0 * mant / (1 << 23);
	printf("Sign = %c\nExponent = %d\nFraction = %f\n", sign, ex - 127, fmant);
	return 0;
}

