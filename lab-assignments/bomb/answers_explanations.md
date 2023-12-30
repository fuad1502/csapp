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

# Phase 5

Here is the stack organization of *phase_5* function:

| address     | data            |
|------------ | --------------- |
| %rsp + 0x20 | return address  |
| %rsp + 0x18 | canary          |
| %rsp + 0x10 | \_\_\_\_\_\_0\_ |
| %rsp        |                 |

The string input characters, truncated to its last 4 bits, is used to index the string at address 0x4024b0, which contains: "maduiersnfotvbyl". The indexed characters are put into %rsp + 0x10. The resulting string are compared with the string at address 0x40245e, which contains "flyers".

In the string at address 0x4024b0, the indeces for "flyers" are: 0x9, 0xf, 0xe, 0x5, 0x6, 0x7.

The ASCII characters that have the previous hex digit as it's last four bits are (among others): i, o, n, e, f, g

Therefore, the answer is: "ionefg".

# Phase 6

Below is the analysis of *func6*:

## Part 1

```
0x4010f4 <phase_6>      push   %r14
0x4010f6 <phase_6+2>    push   %r13
0x4010f8 <phase_6+4>    push   %r12
0x4010fa <phase_6+6>    push   %rbp
0x4010fb <phase_6+7>    push   %rbx
0x4010fc <phase_6+8>    sub    $0x50,%rsp
```

First, callee saved registers are pushed to the stack, and the stack are prepared for local storage:

Here is the stack organization after the above code:

| address     | data            |
|------------ | --------------- |
| %rsp + 0x50 | callee saved    |
| %rsp + 0x48 |                 |
| %rsp + 0x40 |                 |
| %rsp + 0x38 |                 |
| %rsp + 0x30 |                 |
| %rsp + 0x28 |                 |
| %rsp + 0x20 |                 |
| %rsp + 0x18 |                 |
| %rsp + 0x10 |                 |
| %rsp + 0x08 |                 |
| %rsp        |                 |

## Part 2

```
0x401100 <phase_6+12>   mov    %rsp,%r13
0x401103 <phase_6+15>   mov    %rsp,%rsi
0x401106 <phase_6+18>   call   0x40145c <read_six_numbers>
0x40110b <phase_6+23>   mov    %rsp,%r14
0x40110e <phase_6+26>   mov    $0x0,%r12d
```

Next, *read_six_numbers* function is called to parse the input string into six numbers, stored in %rsp.

Here is the stack organization after running the above code:

| address     | data            |
|------------ | --------------- |
| %rsp + 0x50 | callee saved    |
| %rsp + 0x48 |                 |
| %rsp + 0x40 |                 |
| %rsp + 0x38 |                 |
| %rsp + 0x30 |                 |
| %rsp + 0x28 |                 |
| %rsp + 0x20 |                 |
| %rsp + 0x18 |                 |
| %rsp + 0x10 | x x             |
| %rsp + 0x08 | x x             |
| %rsp        | x x             |

Here is the register states:

```
%r12 = 0
%r13 = %r14 = %rsp
```

## Part 3
```
LOOP:
    0x401114 <phase_6+32>   mov    %r13,%rbp
    0x401117 <phase_6+35>   mov    0x0(%r13),%eax 
    0x40111b <phase_6+39>   sub    $0x1,%eax
        IF_1:
            0x40111e <phase_6+42>   cmp    $0x5,%eax
            0x401121 <phase_6+45>   jbe    0x401128 <#>
            0x401123 <phase_6+47>   call   0x40143a <explode_bomb>
    #:
    0x401128 <phase_6+52>   add    $0x1,%r12d
    IF_2:
        0x40112c <phase_6+56>   cmp    $0x6,%r12d
        0x401130 <phase_6+60>   je     0x401153 <END>
    FOR_LOOP:
        INIT:
            0x401132 <phase_6+62>   mov    %r12d,%ebx
        DO:
            0x401135 <phase_6+65>   movslq %ebx,%rax
            0x401138 <phase_6+68>   mov    (%rsp,%rax,4),%eax
            IF_2:
                0x40113b <phase_6+71>   cmp    %eax,0x0(%rbp)
                0x40113e <phase_6+74>   jne    0x401145 <UPDATE>
                0x401140 <phase_6+76>   call   0x40143a <explode_bomb>
        UPDATE:
            0x401145 <phase_6+81>   add    $0x1,%ebx
        WHILE:
            0x401148 <phase_6+84>   cmp    $0x5,%ebx
            0x40114b <phase_6+87>   jle    0x401135 <DO>
    0x40114d <phase_6+89>   add    $0x4,%r13
    0x401151 <phase_6+93>   jmp    0x401114 <LOOP>
END:
```

Here is the rough translation to C:

```
int *rsp = {x, x, x, x, x, x};
int *r13 = rsp;
int *r14 = rsp;
int r12 = 0;
while(true) {
    int* bp = r13;
    int ra = r13[0];
    ra -= 1;
    if (ra > 5) {
        explode_bomb();
    }
    r12 += 1;
    if (r12 == 6) {
        break;
    }
    for (int rb = r12; rb <= 5; rb++) {
       int ra = rb;
       int ra = rsp[ra];
       if (ra == bp[0]) {
           explode_bomb();
       }
    }
    r13 += 1;
}
```

This function basically ensures that the 6 numbers are all different and are all smaller than or equal to 6 and larger than 0. Therefore, the numbers that satisfies this is any permutation of 1,2,3,4,5,6.

## Part 4

```
0x401153 <phase_6+95>   lea    0x18(%rsp),%rsi
0x401158 <phase_6+100>  mov    %r14,%rax
0x40115b <phase_6+103>  mov    $0x7,%ecx
LOOP:
    DO:
        0x401160 <phase_6+108>  mov    %ecx,%edx
        0x401162 <phase_6+110>  sub    (%rax),%edx
        0x401164 <phase_6+112>  mov    %edx,(%rax)
        0x401166 <phase_6+114>  add    $0x4,%rax
    WHILE:
        0x40116a <phase_6+118>  cmp    %rsi,%rax
        0x40116d <phase_6+121>  jne    0x401160 <DO>
END:
```

Here is the rough translation to C:

```
int* rsi = rsp[6];
int* ra = rsp;
int rc = 7;
do {
    int rd = rc;
    int rd -= ra[0];
    ra[0] = rd;
    ra += 1;
} while (rsi != ra);
```

This function basically transforms the *x* values stored in the stack array to 7 - *x*.

Here is the stack organization after running the above code:

| address     | data            |
|------------ | --------------- |
| %rsp + 0x50 | callee saved    |
| %rsp + 0x48 |                 |
| %rsp + 0x40 |                 |
| %rsp + 0x38 |                 |
| %rsp + 0x30 |                 |
| %rsp + 0x28 |                 |
| %rsp + 0x20 |                 |
| %rsp + 0x18 |                 |
| %rsp + 0x10 | 7-x 7-x         |
| %rsp + 0x08 | 7-x 7-x         |
| %rsp        | 7-x 7-x         |

## Part 5

```
0x40116f <phase_6+123>  mov    $0x0,%esi

LOOP_1:
    0x401174 <phase_6+128>  jmp    0x401197 <UPDATE_2>
    LOOP_3:
        DO:
            0x401176 <phase_6+130>  mov    0x8(%rdx),%rdx
            0x40117a <phase_6+134>  add    $0x1,%eax
        WHILE:
            0x40117d <phase_6+137>  cmp    %ecx,%eax
            0x40117f <phase_6+139>  jne    0x401176 <LOOP_3>
    END_3:
    0x401181 <phase_6+141>  jmp    0x401188 <BODY_2_1>
    LOOP_2:
        BODY_2_0:
            0x401183 <phase_6+143>  mov    $0x6032d0,%edx
        BODY_2_1:
            0x401188 <phase_6+148>  mov    %rdx,0x20(%rsp,%rsi,2)
            0x40118d <phase_6+153>  add    $0x4,%rsi
            IF:
                0x401191 <phase_6+157>  cmp    $0x18,%rsi
                0x401195 <phase_6+161>  je     0x4011ab <END_1>
        UPDATE_2:
            0x401197 <phase_6+163>  mov    (%rsp,%rsi,1),%ecx
        TEST_2:
            0x40119a <phase_6+166>  cmp    $0x1,%ecx
            0x40119d <phase_6+169>  jle    0x401183 <BODY_2_0>
    END_3:
    0x40119f <phase_6+171>  mov    $0x1,%eax
    0x4011a4 <phase_6+176>  mov    $0x6032d0,%edx
    0x4011a9 <phase_6+181>  jmp    0x401176 <phase_6+130>
END_1:
```

Here is the rough translation to C:

```
int rsi = 0;
while (true) {
    for (int rc = rsp[0]; rc <= 1; rc = rsp[rsi]) {
        long rd = 0x6032d0;
        X:
        long *t = &rsp[8];
        t[rsi] = rd;
        rsi += 1;
        if (rsi == 6)
            break OUT;
    }
    int ra = 1;
    long rd = 0x6032d0;
    do {
        rd = *((long *)rd + 8);
        ra += 1;
    } while(ra != rc);
    goto X:
}
OUT:
```

The code is very convoluted. What is clear is that this code fill in the stack from $rsp + 0x20 to the top with values grabbed from 0x6032d8 + i * 8.

Observing the result for different input string (remember that only permutations of (1, 2, 3, 4, 5, 6) are valid input strings), is that the input string determine the mapping of values stored in address 0x6032d8... to the values stored in the stack.

The values stored in the memory is as follows:

| address    | data       |
|----------- | ---------- |
| 0x6032d0   |            |
| 0x6032d8   | 0x6032e0   |
| 0x6032e0   |            |
| 0x6032e8   | 0x6032f0   |
| 0x6032f0   |            |
| 0x6032f8   | 0x603300   |
| 0x603300   |            |
| 0x603308   | 0x603310   |
| 0x603310   |            |
| 0x603318   | 0x603320   |
| 0x603320   |            |
| 0x603328   | 0x0        |

With input string = "1 2 3 4 5 6", the resulting stack organization is as follows:

| address     | data            |
|------------ | --------------- |
| %rsp + 0x50 | callee saved    |
| %rsp + 0x48 | 0x6032d0        |
| %rsp + 0x40 | 0x6032e0        |
| %rsp + 0x38 | 0x6032f0        |
| %rsp + 0x30 | 0x603300        |
| %rsp + 0x28 | 0x603310        |
| %rsp + 0x20 | 0x603320        |
| %rsp + 0x18 |                 |
| %rsp + 0x10 | 7-x 7-x         |
| %rsp + 0x08 | 7-x 7-x         |
| %rsp        | 7-x 7-x         |

Note that the order is reversed, which is expected because of the operation in part 4.

From here on now, let's refer to *%rsp + 0x20* as the *A* array, and the memory location starting at address 0x6032d8 up to 0x603328, in 0x10 increments, as the *mem* array.

One last thing, we will refer to the memory location starting at address 0x6032d0 up to 0x603320 as the *memp* (*p*revious quad of *mem* arrays) array.

## Part 6

```
0x4011ab <phase_6+183>  mov    0x20(%rsp),%rbx         
0x4011b0 <phase_6+188>  lea    0x28(%rsp),%rax
0x4011b5 <phase_6+193>  lea    0x50(%rsp),%rsi
0x4011ba <phase_6+198>  mov    %rbx,%rcx
LOOP:
    0x4011bd <phase_6+201>  mov    (%rax),%rdx
    0x4011c0 <phase_6+204>  mov    %rdx,0x8(%rcx)
    0x4011c4 <phase_6+208>  add    $0x8,%rax
        IF:
            0x4011c8 <phase_6+212>  cmp    %rsi,%rax
            0x4011cb <phase_6+215>  je     0x4011d2 <END>
    0x4011cd <phase_6+217>  mov    %rdx,%rcx
    0x4011d0 <phase_6+220>  jmp    0x4011bd <LOOP>
END:
0x4011d2 <phase_6+222>  movq   $0x0,0x8(%rdx)
```

The rough translation to C is as follows:

```
long rb = A[0];
long *ra = &A[1];
long *rsi = &A[6];
long rc = rb;
int i = 0;
while (true) {
    long rd = A[1 + i];
    long *t = (long *) rc;
    t[1] = rd;
    i += 1;
    if (i == 5) {
        break;
    }
    rc = rd;
}
long *t = (long *) A[5];
t[1] = 0;
```

Wrote in a better way:

```
for (int i = 1; i < 6; i++) {
    ((long *) A[i-1])[1] = A[i]; // mem[A[i - 1]] = A[i]
}
```

So, in the case of input string = "1 2 3 4 5 6", the address 0x603320 + 0x8 should now contain the value 0x603310, up to the address 0x6032e0 + 0x8 which should now contain 0x6032d0. And lastly, at 0x6032d0 + 0x8 should now contain 0.

## Part 7

```
LOOP:
    INIT:
        0x4011da <phase_6+230>  mov    $0x5,%ebp
    BODY:
        0x4011df <phase_6+235>  mov    0x8(%rbx),%rax
        0x4011e3 <phase_6+239>  mov    (%rax),%eax
            IF:
                0x4011e5 <phase_6+241>  cmp    %eax,(%rbx)
                0x4011e7 <phase_6+243>  jge    0x4011ee <#>
                0x4011e9 <phase_6+245>  call   0x40143a <explode_bomb>
        #:
        0x4011ee <phase_6+250>  mov    0x8(%rbx),%rbx
    UPDATE:
        0x4011f2 <phase_6+254>  sub    $0x1,%ebp
    TEST:
        0x4011f5 <phase_6+257>  jne    0x4011df <LOOP>
END:
```

The rough translation to C is as follows:

```
int i = 0;
int rb = A[0];
for (int bp = 5; bp > 0; bp--) {
    long ra = *((long *) rb + 1); // mem[rb]
    ra = *((long *) ra); // memp[mem[rb]]
    if (*((long *) rb) < ra) { // memp[rb] < mem[mem[rb]]
        explode_bomb();
    }
    rb = *((long *) rb + 1); // rb = mem[rb]
}
```

This part is a very convoluted check. Moreover, it turns out that the values stored in 0x603d0 and so on are important. Let's complete the previous memory organization:

| address    | data       |
|----------- | ---------- |
| 0x6032d0   | 0x014c     |
| 0x6032d8   | 0x6032e0   |
| 0x6032e0   | 0x00a8     |
| 0x6032e8   | 0x6032f0   |
| 0x6032f0   | 0x039c     |
| 0x6032f8   | 0x603300   |
| 0x603300   | 0x02b3     |
| 0x603308   | 0x603310   |
| 0x603310   | 0x01dd     |
| 0x603318   | 0x603320   |
| 0x603320   | 0x01bb     |
| 0x603328   | 0x0        |

And here lies the tricky part, how do we ensure that this convoluted check will pass, what should the input permutation be?

We could try to solve this recurrance check, but a way easier method would be to write a clone of this code and simulate for all permutation of "1 2 3 4 5 6" until we pass the check. See [phase_6.c](phase_6.c).

Upon running the simulation, an input string that satisfies the check is: "4 3 2 1 6 5"

And at last, the function stack in unwound:

```
0x4011f7 <phase_6+259>  add    $0x50,%rsp
0x4011fb <phase_6+263>  pop    %rbx
0x4011fc <phase_6+264>  pop    %rbp
0x4011fd <phase_6+265>  pop    %r12
0x4011ff <phase_6+267>  pop    %r13
0x401201 <phase_6+269>  pop    %r14
0x401203 <phase_6+271>  ret
```

So the solution to this phase is: "4 3 2 1 6 5".
