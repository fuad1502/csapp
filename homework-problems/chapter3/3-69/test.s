test:
  mov     0x120(%rsi), %ecx // %ecx = *(bp + 288) = bp->last // Therefore a_struct a[CNT] is 284 bytes
  add     (%rsi), %ecx // %ecx = bp->last + bp->first // ecx is "int n"
  lea     (%rdi, %rdi, 4), %rax // %rax = 5 x i
  lea     (%rsi, %rax, 8), %rax // %rax = 40 x i + bp
  mov     0x8(%rax), %rdx // %rdx = *(bp + 40 x i + 8) = *(bp + 4 + 4 + 40*i) // *ap // a_struct is 40 bytes in size, 8 bytes in aligment
  movslq  %ecx, %rcx // %rcx = (long) n
  mov     %rcx, 0x10(%rax, %rdx, 8) // *(bp + 40 x i + 8 x *ap + 16) = *(ap + 8 + 8 x *ap) // *ap is ap->idx
  retq
