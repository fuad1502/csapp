#include <limits.h>
#include <math.h>
#include <stdio.h>

typedef unsigned float_bits;

void print_float_bits(float_bits f)
{
	for(int i = 31; i >= 0; i--) {
		printf("%d", f >> i & 1);
    if(i == 31 || i == 23) {
      printf(" | ");
    }
	}
	printf("\n");
}

float_bits float_half(float_bits f)
{
  unsigned sign = f >> 31;
  unsigned exp = f >> 23 & 0xFF;
  unsigned frac = f & 0x7FFFFF;

  if(exp == 0xFF) {
    return f;
  } else if(exp == 0x00) {
    // Denormalized
    int last_bit = frac & 1;
    frac = frac >> 1;
    // Round to even
    if(last_bit == 1) {
      frac = frac + (frac & 1);
    }
  } else {
    // Normalized
    if(exp == 1) {
      // Convert to denormalized
      exp = 0;
      int last_bit = frac & 1;
      frac = frac >> 1;
      frac += 1 << 22;
      // Round to even
      if(last_bit == 1) {
        frac = frac + (frac & 1);
      }
    } else {
      exp--;
    }
  }

  return (sign << 31) + (exp << 23) + frac;
}

typedef union {
  unsigned u;
  float f;
} uf;

int main()
{
  for(unsigned i = 0; i <= UINT_MAX; i++) {
    uf input, ref, test;
    input.u = i;
    ref.f = input.f * 0.5;
    test.u = float_half(i);
    if(!isnan(input.f) && ref.u != test.u) {
      printf("Wrong answer!\n");
      printf("input = %f, reference = %f, test = %f\n", input.f, ref.f, test.f);
      printf("input     : "); print_float_bits(i);
      printf("reference : "); print_float_bits(ref.u);
      printf("test      : "); print_float_bits(test.u);
      return 0;
    }
    if(i == UINT_MAX) break;
  }

  printf("All answers are correct!\n");
  return 0;
}

