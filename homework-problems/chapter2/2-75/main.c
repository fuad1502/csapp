#include <stdio.h>

void print_int_bits(int x)
{
	int w = sizeof(int) << 3;
	for(int i = w - 1; i >= 0; i--) {
		printf("%d", x >> i & 1);
	}
	printf("\n");
}

void print_half_int_bits(int x)
{
	int w = sizeof(int) << 3;
	for(int i = (w >> 1) - 1; i >= 0; i--) {
		printf("%d", x >> i & 1);
	}
	printf("\n");
}

int signed_high_product_reference(int x, int y)
{
  int w = sizeof(int) << 3;
  return ((unsigned) (x * y)) >> (w >> 1);
}

unsigned unsigned_high_product_reference(unsigned x, unsigned y)
{
  int w = sizeof(int) << 3;
  int mask = ((unsigned) -1) >> (w >> 1);
  x = x & mask;
  y = y & mask;
  return x * y >> (w >> 1);
}

unsigned unsigned_high_product(unsigned x, unsigned y)
{
  /*
   * for positive x and y, signed_high_product is the same as unsigned_high_product
   * If either x or y is negative, it's signed extended
   * The effect of sign extension needs to be removed
   * 
   * x' * y' = (x - 11..00..) * y = x * y - 11..00.. * y
   * So, unsigned_high_product(x, y) = signed_high_product(x, y) - y
   * 
   * Likewise, if both x and y is negative
   * x * y = (x - 11..00) * (y - 11..00) = x * y - 11..00.. * x - 11..00.. * y + 11..00.. * 11..00..
   * So, unsigned_high_product(x, y) = signed_high_product(x, y) + x + y
   */
  int w = sizeof(int) << 3;
  int mask = ((unsigned) -1) >> (w >> 1);
  int signed_high_product = signed_high_product_reference(x, y);
  // x = x & mask;
  // y = y & mask;
  int negative_x_mask = - ((x >> ((w >> 1) - 1)) & 1);
  int negative_y_mask = - ((y >> ((w >> 1) - 1)) & 1);
  return signed_high_product + (x & negative_y_mask) + (y & negative_x_mask);
}

#define N_TEST_CASES 3

int main()
{
  int test_cases[N_TEST_CASES] = {100, 54, 13};
  for(int i = 0; i < N_TEST_CASES; i++) {
    for(int j = i; j < N_TEST_CASES; j++) {
      for(int k = -1; k <= 1; k += 2) {
        for(int l = -1; l <= 1; l += 2) {
          int x = k * test_cases[i];
          int y = l * test_cases[j];
          printf("X: %d, Y: %d\n", x, y);
          printf("REFERENCE UNSIGNED_HIGH_PRODUCT: ");
          print_half_int_bits(unsigned_high_product_reference(x, y));
          printf("TEST UNSIGNED_HIGH_PRODUCT:      ");
          print_half_int_bits(unsigned_high_product(x, y));
        }
      }
    }
  }
  return 0;
}
