0000000000001219 <poly>:
...
    1237:	66 0f 28 d1          	movapd %xmm1,%xmm2
    123b:	f2 0f 59 10          	mulsd  (%rax),%xmm2
    123f:	f2 0f 58 c2          	addsd  %xmm2,%xmm0
    1243:	f2 0f 59 cb          	mulsd  %xmm3,%xmm1
    1247:	48 83 c0 08          	add    $0x8,%rax
    124b:	48 39 d0             	cmp    %rdx,%rax
    124e:	75 e7                	jne    1237 <poly+0x1e>
    1250:	c3                   	ret

0000000000001251 <polyh>:
...
    1264:	f2 0f 59 c1          	mulsd  %xmm1,%xmm0
    1268:	f2 0f 58 04 f7       	addsd  (%rdi,%rsi,8),%xmm0
    126d:	48 83 ee 01          	sub    $0x1,%rsi
    1271:	48 83 fe ff          	cmp    $0xffffffffffffffff,%rsi
    1275:	75 ed                	jne    1264 <polyh+0x13>
    1277:	c3                   	ret
