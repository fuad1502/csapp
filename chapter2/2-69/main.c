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
void print_int_hex(int x)
{
	int w = sizeof(int) << 3;
	printf("0x");
	for(int i = (w >> 2) - 1; i >= 0; i--) {
		printf("%x", x >> (i << 2) & 0xF);
	}
	printf("\n");
}

unsigned rotate_left(unsigned x, int n)
{
	int w = sizeof(int) << 3;
	unsigned moved_bits = x & ~(UINT_MAX >> n);
	return (x << n) + (moved_bits >> (w - n)); 
}

int main(void)
{
	printf("Input    : ");
	print_int_hex(0x12345678);
	printf("Rotate 4 : ");
	print_int_hex(rotate_left(0x12345678,4));
	printf("Rotate 20: ");
	print_int_hex(rotate_left(0x12345678,20));
	printf("Rotate 0 : ");
	print_int_hex(rotate_left(0x12345678,0));
	return 0;
}
