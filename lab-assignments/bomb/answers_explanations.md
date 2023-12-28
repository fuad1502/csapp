# Phase 1
Calls *strings_not_equal(in, s)* which compares string *in* and string *s*. Where *in* is the string input and *s* is the value stored in address 0x402400 ("Border relations with Canada have never been better.")
Therefore, the answer is: "Border relations with Canada have never been better.".

# Phase 2
Calls *read_six_numbers*, which in turn calls *sscanf(buffer, format, ...)*, where *buffer* is the string input, and *format* is the formatting string stored in address 0x4025c3 ("%d %d %d %d %d %d"). The first number is first checked whether it's equal to 1 or not. Then, the following numbers are checked in a for loop, ensuring that each number is twice the previous number.
Therefore, the answer is: "1 2 4 8 16 32".

# Phase 3
Read two numbers with *sscanf* as before. The first number is first checked to ensure that it's value is less than or equal to 7. The first number is used as an index to the jump table at address 0x402470. Each arm of the jump table (switch statement) sets %eax to a certain value. If the index is 0, the jump table jumps to the first arm, which sets %eax to 0xcf (207). Then, the second number parsed from *sscanf* is compared with the value stored in %eax. There are multiple answers to this phase, depending on the index chosen. In my case, I use index 0.
Therefore, the answer is: "0 207".

# Phase 4
Read two numbers with *sscanf* as before. The first number is first checked to ensure that it's value is less than 8. Then *func4(di, si, dx)* is called with *di* equals to the first number, *si* equals to 0, and *dx* equals to 14.
Here is a translation of the arithmetic operation performed in func4:
```
int a = dx - si;
int c = a >> 31;
a = a + c;
a = a >> 1;
c = a + si * 1;
if (c <= di) 
  jump 1:
di = c - 1;
a = func4(di, si, dx);
a = a + a;
return a;
1:
a = 0;
if (c >= di)
  return a; // This line
di = c + 1;
a = func4(di, si, dx);
a = a + a + 1;
return a;
```
The function looks complicated, but it's actually pretty simple to get the right output. Phase 4 expects the *func4* to return 0. Therefore, what we want is to get to the line marked in the code snippet above. And if we go through the operations, we would get that *di* = 7 get us to the marked line.
Next, the code expects the second number to be 0.
Therfore, the answer is: "7 0"
