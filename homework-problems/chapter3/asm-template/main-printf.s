.LC0:
	.string	"Hello, world!\n"
.globl	main
main:
	pushq	%rbp
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	printf@PLT
	movl	$0, %eax
	popq	%rbp
	ret
