#include <stdio.h>

void print_int_bits(int x)
{
	int w = sizeof(int) << 3;
	for(int i = w - 1; i >= 0; i--) {
		printf("%d", x >> i & 1);
	}
	printf("\n");
}

int odd_ones(unsigned x)
{
	unsigned temp = x;
	temp = (temp >> 16) ^ temp;
	temp = (temp >>  8) ^ temp;
	temp = (temp >>  4) ^ temp;
	temp = (temp >>  2) ^ temp;
	temp = (temp >>  1) ^ temp;
	return temp & 1;
}

int main(void) {
	for(int i = 0; i < 15; i++) {
		printf("Input: ");
		print_int_bits(i);	
		printf("Odd? %d\n", odd_ones(i));
	}
	return 0;
}

