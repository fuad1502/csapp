From analyzing the assembly code, we get the following:
1. B is at most 8, and at least (8 - 3)/1 = 5
2. A is at most 10, and at least (32 - 8 - 4 - 7)/2 = 7
3. A x B is at most 46, and at least (184 - 7)/4 = 45

The factor of 46 is 26 x 2, no A or B value satisfy all of the above conditions.
The factor of 45 is 3 x 3 x 5, which can be combined to either 9 x 5 or 15 x 3. Only 9 x 5 satisfy all the above conditions. Therefore A is 9 while B is 5.
