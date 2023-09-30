#include <stdio.h>
#include <limits.h>

int int_shifts_are_arithmetic()
{
	int shift_val = -1 >> 1;
	return (shift_val >> ((sizeof(int) << 3) - 1)) & 1;
}

int main(void)
{
	if(int_shifts_are_arithmetic() == 1) {
		printf("Shifts are arithmetic\n");
	} else {
		printf("Shifts are not arithmetic\n");
	}
	return 0;
}
