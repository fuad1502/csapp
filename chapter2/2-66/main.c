#include <stdio.h>
#include <limits.h>

void print_int_bits(int x)
{
	int w = sizeof(int) << 3;
	for(int i = w - 1; i >= 0; i--) {
		printf("%d", x >> i & 1);
	}
	printf("\n");
}

int leftmost_one(unsigned x)
{
	x = x | (x >> 16);
	x = x | (x >> 8);
	x = x | (x >> 4);
	x = x | (x >> 2);
	x = x | (x >> 1);
	return ((x + 1) >> 1) & x;
}

int main(void)
{
	for(int i = 0; i < 15; i++) {
		printf("Input:  ");
		print_int_bits(i);
		printf("Output: ");
		print_int_bits(leftmost_one(i));
	}
	return 0;
}
