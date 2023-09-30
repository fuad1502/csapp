store_ele:
  leaq (%rsi, %rsi, 2), %rax // %rax = 3j
  leaq (%rsi, %rax, 4), %rax // %rax = 13j
  movq %rdi, %rsi // %rsi = i
  salq $6, %rsi // %rsi = 64i
  addq %rsi, %rdi // %rdi = 65i
  addq %rax, %rdi // $rdi = 65i + 13j
  addq %rdi, %rdx // %rdx = 65i + 13j + k 
  movq A(,%rdx,8), %rax // %rax = A[65i + 13j + k]
  movq %rax, (%rcx) // *dest = A[65i + 13j + k]
  movl $3640, %eax // return 3640
  ret
