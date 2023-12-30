#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char *argv[]) {
  srand(time(NULL));
  while (1) {
    int mem[6] = {0, 1, 2, 3, 4, 5};
    int memp[6] = {0x014c, 0x00a8, 0x039c, 0x02b3, 0x01dd, 0x01bb};
    int A[6];

    // Generate permutation of input
    int input[6] = {0, 1, 2, 3, 4, 5};
    for (int i = 0; i < 6; i++) {
      int j = rand() % 6;
      int tmp = input[i];
      input[i] = input[j];
      input[j] = tmp;
    }

    // Print input
    printf("input: ");
    for (int i = 0; i < 6; i++) {
      printf("%d ", input[i] + 1);
    }
    printf("\n");

    // Fill A (Part 5)
    for (int i = 0; i < 6; i++) {
      A[i] = mem[5 - input[i]];
    }

    // Modify mem (Part 6)
    for (int i = 1; i < 6; i++) {
      mem[A[i - 1]] = A[i];
    }
    mem[A[5]] = 0xffffffff;

    // Check A (Part 7)
    int ok = 1;
    int rb = A[0];
    for (int i = 5; i > 0; i--) {
      int ra = memp[mem[rb]];
      if (memp[rb] < ra) {
        printf("Boom!\n");
        ok = 0;
        break;
      }
      rb = mem[rb];
    }

    if (ok) {
      printf("Defused!\n");
      break;
    }
  }

  return 0;
}
