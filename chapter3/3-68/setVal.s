setVal:
  movslq 8(%rsi), %rax // %rax = (long) q->t, therefore *char array[B]* is 8 bytes long, which means B is "at most" 8.
  addq 32(%rsi), %rax // %rax = (long) q->t + q->u, therefore *short s[A]* is 32 - 4 (t) - 8 (array) = 20 bytes. Therefore A is "at most" 10.
  movq %rax, 184(%rdi) // p->y = q->t + q->u, therefore *int x[A][B]* is 184 bytes. Therefore A*B is "at most" 46.
  ret
