00000000000014e0 <get_vec_element>:
    14e0:	f3 0f 1e fa          	endbr64
    14e4:	31 c0                	xor    %eax,%eax
    14e6:	48 85 f6             	test   %rsi,%rsi
    14e9:	78 17                	js     1502 <get_vec_element+0x22>
    14eb:	48 39 37             	cmp    %rsi,(%rdi)
    14ee:	7e 12                	jle    1502 <get_vec_element+0x22>
    14f0:	48 8b 47 08          	mov    0x8(%rdi),%rax
    14f4:	f2 0f 10 04 f0       	movsd  (%rax,%rsi,8),%xmm0
    14f9:	b8 01 00 00 00       	mov    $0x1,%eax
    14fe:	f2 0f 11 02          	movsd  %xmm0,(%rdx)
    1502:	c3                   	ret
    1503:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
    150a:	00 00 00 00 
    150e:	66 90                	xchg   %ax,%ax

0000000000001510 <set_vec_element>:
    1510:	f3 0f 1e fa          	endbr64
    1514:	31 c0                	xor    %eax,%eax
    1516:	48 85 f6             	test   %rsi,%rsi
    1519:	78 13                	js     152e <set_vec_element+0x1e>
    151b:	48 39 37             	cmp    %rsi,(%rdi)
    151e:	7e 0e                	jle    152e <set_vec_element+0x1e>
    1520:	48 8b 47 08          	mov    0x8(%rdi),%rax
    1524:	f2 0f 11 04 f0       	movsd  %xmm0,(%rax,%rsi,8)
    1529:	b8 01 00 00 00       	mov    $0x1,%eax
    152e:	c3                   	ret
    152f:	90                   	nop

0000000000001530 <vec_length>:
    1530:	f3 0f 1e fa          	endbr64
    1534:	48 8b 07             	mov    (%rdi),%rax
    1537:	c3                   	ret
    1538:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
    153f:	00 

0000000000001540 <combine1>:
...
    1578:	48 89 de             	mov    %rbx,%rsi
    157b:	4c 89 ea             	mov    %r13,%rdx
    157e:	4c 89 e7             	mov    %r12,%rdi
    1581:	48 83 c3 01          	add    $0x1,%rbx
    1585:	e8 56 ff ff ff       	call   14e0 <get_vec_element>
    158a:	f2 0f 10 45 00       	movsd  0x0(%rbp),%xmm0
    158f:	f2 0f 59 04 24       	mulsd  (%rsp),%xmm0
    1594:	f2 0f 11 45 00       	movsd  %xmm0,0x0(%rbp)
    1599:	4c 89 e7             	mov    %r12,%rdi
    159c:	e8 8f ff ff ff       	call   1530 <vec_length>
    15a1:	48 39 d8             	cmp    %rbx,%rax
    15a4:	7f d2                	jg     1578 <combine1+0x38>
...

00000000000015d0 <combine2>:
...
    1618:	48 89 de             	mov    %rbx,%rsi
    161b:	4c 89 f2             	mov    %r14,%rdx
    161e:	4c 89 ef             	mov    %r13,%rdi
    1621:	48 83 c3 01          	add    $0x1,%rbx
    1625:	e8 b6 fe ff ff       	call   14e0 <get_vec_element>
    162a:	f2 0f 10 45 00       	movsd  0x0(%rbp),%xmm0
    162f:	f2 0f 59 04 24       	mulsd  (%rsp),%xmm0
    1634:	f2 0f 11 45 00       	movsd  %xmm0,0x0(%rbp)
    1639:	49 39 dc             	cmp    %rbx,%r12
    163c:	75 da                	jne    1618 <combine2+0x48>
...

0000000000001660 <combine3>:
...
    1690:	f2 0f 59 02          	mulsd  (%rdx),%xmm0
    1694:	48 83 c2 08          	add    $0x8,%rdx
    1698:	f2 0f 11 03          	movsd  %xmm0,(%rbx)
    169c:	48 39 c2             	cmp    %rax,%rdx
    169f:	75 ef                	jne    1690 <combine3+0x30>
...

00000000000016b0 <combine4>:
...
    1700:	f2 0f 59 02          	mulsd  (%rdx),%xmm0
    1704:	48 83 c2 10          	add    $0x10,%rdx
    1708:	f2 0f 59 42 f8       	mulsd  -0x8(%rdx),%xmm0
    170d:	48 39 ca             	cmp    %rcx,%rdx
    1710:	75 ee                	jne    1700 <combine4+0x50>
...
