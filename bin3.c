#include <stdio.h>

int main()
{
		int n;
		scanf("%i", &n);
		printf("%i", (((n >> 31)) | !!n));
		return 0;
}
