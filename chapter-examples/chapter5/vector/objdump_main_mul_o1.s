00000000000014cc <get_vec_element>:
    14cc:	f3 0f 1e fa          	endbr64
    14d0:	b8 00 00 00 00       	mov    $0x0,%eax
    14d5:	48 85 f6             	test   %rsi,%rsi
    14d8:	78 17                	js     14f1 <get_vec_element+0x25>
    14da:	48 39 37             	cmp    %rsi,(%rdi)
    14dd:	7e 12                	jle    14f1 <get_vec_element+0x25>
    14df:	48 8b 47 08          	mov    0x8(%rdi),%rax
    14e3:	f2 0f 10 04 f0       	movsd  (%rax,%rsi,8),%xmm0
    14e8:	f2 0f 11 02          	movsd  %xmm0,(%rdx)
    14ec:	b8 01 00 00 00       	mov    $0x1,%eax
    14f1:	c3                   	ret

00000000000014f2 <set_vec_element>:
    14f2:	f3 0f 1e fa          	endbr64
    14f6:	b8 00 00 00 00       	mov    $0x0,%eax
    14fb:	48 85 f6             	test   %rsi,%rsi
    14fe:	78 13                	js     1513 <set_vec_element+0x21>
    1500:	48 39 37             	cmp    %rsi,(%rdi)
    1503:	7e 0e                	jle    1513 <set_vec_element+0x21>
    1505:	48 8b 47 08          	mov    0x8(%rdi),%rax
    1509:	f2 0f 11 04 f0       	movsd  %xmm0,(%rax,%rsi,8)
    150e:	b8 01 00 00 00       	mov    $0x1,%eax
    1513:	c3                   	ret

0000000000001514 <vec_length>:
    1514:	f3 0f 1e fa          	endbr64
    1518:	48 8b 07             	mov    (%rdi),%rax
    151b:	c3                   	ret

000000000000151c <combine1>:
...
    1554:	4c 89 ea             	mov    %r13,%rdx
    1557:	48 89 de             	mov    %rbx,%rsi
    155a:	4c 89 e7             	mov    %r12,%rdi
    155d:	e8 6a ff ff ff       	call   14cc <get_vec_element>
    1562:	f2 0f 10 45 00       	movsd  0x0(%rbp),%xmm0
    1567:	f2 0f 59 04 24       	mulsd  (%rsp),%xmm0
    156c:	f2 0f 11 45 00       	movsd  %xmm0,0x0(%rbp)
    1571:	48 83 c3 01          	add    $0x1,%rbx
    1575:	4c 89 e7             	mov    %r12,%rdi
    1578:	e8 97 ff ff ff       	call   1514 <vec_length>
    157d:	48 39 d8             	cmp    %rbx,%rax
    1580:	7f d2                	jg     1554 <combine1+0x38>
...

00000000000015a2 <combine2>:
...
    15e7:	4c 89 f2             	mov    %r14,%rdx
    15ea:	48 89 de             	mov    %rbx,%rsi
    15ed:	4c 89 ef             	mov    %r13,%rdi
    15f0:	e8 d7 fe ff ff       	call   14cc <get_vec_element>
    15f5:	f2 0f 10 45 00       	movsd  0x0(%rbp),%xmm0
    15fa:	f2 0f 59 04 24       	mulsd  (%rsp),%xmm0
    15ff:	f2 0f 11 45 00       	movsd  %xmm0,0x0(%rbp)
    1604:	48 83 c3 01          	add    $0x1,%rbx
    1608:	49 39 dc             	cmp    %rbx,%r12
    160b:	75 da                	jne    15e7 <combine2+0x45>
...

000000000000162f <combine3>:
...
    1658:	48 8b 4d 08          	mov    0x8(%rbp),%rcx
    165c:	f2 0f 10 03          	movsd  (%rbx),%xmm0
    1660:	f2 0f 59 04 d1       	mulsd  (%rcx,%rdx,8),%xmm0
    1665:	f2 0f 11 03          	movsd  %xmm0,(%rbx)
    1669:	48 83 c2 01          	add    $0x1,%rdx
    166d:	48 39 d0             	cmp    %rdx,%rax
    1670:	75 e6                	jne    1658 <combine3+0x29>
...

...
0000000000001679 <combine4>:
    16ad:	f2 0f 59 02          	mulsd  (%rdx),%xmm0
    16b1:	48 83 c2 08          	add    $0x8,%rdx
    16b5:	48 39 c2             	cmp    %rax,%rdx
    16b8:	75 f3                	jne    16ad <combine4+0x34>
...
