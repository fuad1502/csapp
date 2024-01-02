#include <stdio.h>
#include <limits.h>

void printIntBits(int x)
{
	int w = sizeof(int) << 3;
	for(int i = w - 1; i >= 0; i--) {
		printf("%d", x >> i & 1);
	}
	printf("\n");
}

unsigned srl(unsigned x, int k)
{
	unsigned xsra = (int) x >> k;
	int w = sizeof(int) << 3;
	unsigned mask = (1 << (w - k)) - 1;
	return xsra & mask;
}

int sra(int x, int k)
{
	int xsrl = (unsigned) x >> k;
	int w = sizeof(int) << 3;
	int msb2 = xsrl & ((1 << (w - k - 1)));
	int mask = -msb2;
	return xsrl | mask;
}

int main(void)
{
	printf("UINT_MAX      :");
	printIntBits(UINT_MAX);
	printf("UINT_MAX >> 5 :");
	printIntBits(srl(UINT_MAX, 5));
	
	printf("-1            :");
	printIntBits(-1);
	printf("-1 >>> 5      :");
	printIntBits(sra(-1,5));

	printf("INT_MAX       :");
	printIntBits(INT_MAX);
	printf("INT_MAX >>> 5 :");
	printIntBits(sra(INT_MAX, 5));
}
