#include <stdio.h>

int main()
{
	float f, t = 0.5, m = 1;
	int i;
	scanf("%f", &f);
	union {
		float f;
		struct {
			unsigned int mant : 23;
			unsigned int ex : 8;
			int sign : 1;
		} bitField;
	} fragm;
	fragm.f = f;
	for(i = 22; i >= 0; i--)
	{
		m += !!((fragm.bitField.mant >> i) & 1) * t;
		t = t / 2;
	}
	printf("Sign = %d\nExponent = %d\nFraction = %f\n", fragm.bitField.sign, fragm.bitField.ex - 127, m);
}
