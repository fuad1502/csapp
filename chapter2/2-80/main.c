#include <stdio.h>
#include <math.h>
#include <limits.h>

int threefourths(int x)
{
  // handle negative x to round upward
  // ceil(3x/4) -> floor((3x + bias)/4) = floor(3*(x + bias/3)/4)
  // since for divide by 4, bias is equal to 3, bias/3 is 1
  int w = sizeof(w) << 3;
  int bias = 1;
  int bias_mask = 0 - (x >> (w-1));
  x = (x + (bias & bias_mask));
  // divide by 4, rounded toward zero
  int res = x >> 2;
  // multiply by 3
  res = res + (res << 1);
  // Add 1 if the truncated bits are 0b10 
  // Add 2 if the truncated bits are 0b11
  res = res + (((x >> 1) & 1) << (x & 1));
  return res;
}

int threefourths_reference(int x)
{
  double xf = (double) x;
  double resf = x * 3.0 / 4.0;
  if(resf > 0) {
    return (int) floor(resf);
  } else {
    return (int) ceil(resf);
  }
}

int main()
{
  for(int i = INT_MIN; i <= INT_MAX; i++) {
    int a = threefourths_reference(i);
    int b = threefourths(i);
    if(a != b) {
      printf("Wrong answer for x = %d\n", i);
      printf("Correct answer = %d\n", a);
      printf("Calculated answer = %d\n", b);
      return 0;
    }
    if(i == INT_MAX) break;
  }

  printf("All answers are correct!\n");

  return 0;
}
