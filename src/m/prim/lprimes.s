	.file	"lprimes.c"
	.globl	N
	.data
	.align 8
	.type	N, @object
	.size	N, 8
N:
	.long	0
	.long	1128267776
	.globl	pt
	.align 32
	.type	pt, @object
	.size	pt, 200
pt:
	.long	2
	.long	3
	.long	5
	.long	7
	.long	11
	.long	13
	.long	17
	.long	19
	.long	23
	.long	29
	.long	31
	.long	37
	.long	41
	.long	43
	.long	47
	.long	53
	.long	59
	.long	61
	.long	67
	.long	71
	.long	73
	.long	79
	.long	83
	.long	89
	.long	97
	.long	101
	.long	103
	.long	107
	.long	109
	.long	113
	.long	127
	.long	131
	.long	137
	.long	139
	.long	149
	.long	151
	.long	157
	.long	163
	.long	167
	.long	173
	.long	179
	.long	181
	.long	191
	.long	193
	.long	197
	.long	199
	.long	211
	.long	223
	.long	227
	.long	229
	.globl	w
	.align 32
	.type	w, @object
	.size	w, 384
w:
	.long	0
	.long	1076101120
	.long	0
	.long	1073741824
	.long	0
	.long	1074790400
	.long	0
	.long	1073741824
	.long	0
	.long	1074790400
	.long	0
	.long	1075314688
	.long	0
	.long	1073741824
	.long	0
	.long	1075314688
	.long	0
	.long	1074790400
	.long	0
	.long	1073741824
	.long	0
	.long	1074790400
	.long	0
	.long	1075314688
	.long	0
	.long	1075314688
	.long	0
	.long	1073741824
	.long	0
	.long	1075314688
	.long	0
	.long	1074790400
	.long	0
	.long	1073741824
	.long	0
	.long	1075314688
	.long	0
	.long	1074790400
	.long	0
	.long	1075314688
	.long	0
	.long	1075838976
	.long	0
	.long	1074790400
	.long	0
	.long	1073741824
	.long	0
	.long	1074790400
	.long	0
	.long	1073741824
	.long	0
	.long	1074790400
	.long	0
	.long	1075838976
	.long	0
	.long	1075314688
	.long	0
	.long	1074790400
	.long	0
	.long	1075314688
	.long	0
	.long	1073741824
	.long	0
	.long	1074790400
	.long	0
	.long	1075314688
	.long	0
	.long	1073741824
	.long	0
	.long	1075314688
	.long	0
	.long	1075314688
	.long	0
	.long	1074790400
	.long	0
	.long	1073741824
	.long	0
	.long	1074790400
	.long	0
	.long	1075314688
	.long	0
	.long	1073741824
	.long	0
	.long	1075314688
	.long	0
	.long	1074790400
	.long	0
	.long	1073741824
	.long	0
	.long	1074790400
	.long	0
	.long	1073741824
	.long	0
	.long	1076101120
	.long	0
	.long	1073741824
	.comm	tbl,1000,32
	.globl	b
	.align 8
	.type	b, @object
	.size	b, 8
b:
	.byte	1
	.byte	2
	.byte	4
	.byte	8
	.byte	16
	.byte	32
	.byte	64
	.byte	-128
	.text
	.globl	mk
	.type	mk, @function
mk:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movsd	%xmm0, -24(%rbp)
	movq	%rdi, -32(%rbp)
	pxor	%xmm0, %xmm0
	cvtsi2sdq	-32(%rbp), %xmm0
	movsd	-24(%rbp), %xmm1
	divsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm0
	leaq	-16(%rbp), %rax
	movq	%rax, %rdi
	call	modf
	pxor	%xmm0, %xmm0
	cvtsi2sdq	-32(%rbp), %xmm0
	movsd	-16(%rbp), %xmm1
	mulsd	%xmm1, %xmm0
	subsd	-24(%rbp), %xmm0
	cvttsd2siq	%xmm0, %rax
	movq	%rax, -8(%rbp)
	cmpq	$0, -8(%rbp)
	jns	.L3
	movq	-32(%rbp), %rax
	addq	%rax, -8(%rbp)
	jmp	.L3
.L4:
	movq	-8(%rbp), %rax
	sarq	$3, %rax
	movq	-8(%rbp), %rdx
	sarq	$3, %rdx
	movzbl	tbl(%rdx), %ecx
	movq	-8(%rbp), %rdx
	andl	$7, %edx
	movzbl	b(%rdx), %edx
	orl	%ecx, %edx
	movb	%dl, tbl(%rax)
	movq	-32(%rbp), %rax
	addq	%rax, -8(%rbp)
.L3:
	movq	-8(%rbp), %rax
	cmpq	$7999, %rax
	jbe	.L4
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	mk, .-mk
	.section	.rodata
.LC3:
	.string	"%d\n"
.LC7:
	.string	"%.0f\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$80, %rsp
	movl	%edi, -52(%rbp)
	movq	%rsi, -64(%rbp)
	cmpl	$1, -52(%rbp)
	jg	.L6
	movl	$0, %edi
	call	exit
.L6:
	movq	-64(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atof
	movq	%xmm0, %rax
	movq	%rax, -32(%rbp)
	movsd	N(%rip), %xmm0
	movsd	%xmm0, -24(%rbp)
	cmpl	$2, -52(%rbp)
	jle	.L7
	movq	-64(%rbp), %rax
	addq	$16, %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	atof
	movq	%xmm0, %rax
	movq	%rax, -24(%rbp)
	movsd	-32(%rbp), %xmm0
	ucomisd	-24(%rbp), %xmm0
	jbe	.L47
	movl	$0, %edi
	call	exit
.L47:
	movsd	N(%rip), %xmm1
	movsd	-24(%rbp), %xmm0
	ucomisd	%xmm1, %xmm0
	jbe	.L7
	movl	$0, %edi
	call	exit
.L7:
	pxor	%xmm0, %xmm0
	ucomisd	-32(%rbp), %xmm0
	ja	.L11
	movsd	N(%rip), %xmm1
	movsd	-32(%rbp), %xmm0
	ucomisd	%xmm1, %xmm0
	jbe	.L48
.L11:
	movl	$0, %edi
	call	exit
.L48:
	pxor	%xmm0, %xmm0
	ucomisd	-32(%rbp), %xmm0
	jp	.L14
	pxor	%xmm0, %xmm0
	ucomisd	-32(%rbp), %xmm0
	jne	.L14
	movsd	.LC1(%rip), %xmm0
	movsd	%xmm0, -32(%rbp)
.L14:
	movsd	.LC2(%rip), %xmm0
	ucomisd	-32(%rbp), %xmm0
	jbe	.L16
	movl	$0, -4(%rbp)
	jmp	.L18
.L25:
	movl	-4(%rbp), %eax
	cltq
	movl	pt(,%rax,4), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sd	%eax, %xmm0
	movsd	-32(%rbp), %xmm1
	ucomisd	%xmm0, %xmm1
	ja	.L51
	movl	-4(%rbp), %eax
	cltq
	movl	pt(,%rax,4), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sd	%eax, %xmm0
	ucomisd	-24(%rbp), %xmm0
	jbe	.L49
	movl	$0, %edi
	call	exit
.L49:
	movl	-4(%rbp), %eax
	cltq
	movl	pt(,%rax,4), %eax
	movl	%eax, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	movsd	N(%rip), %xmm1
	movsd	-24(%rbp), %xmm0
	ucomisd	%xmm1, %xmm0
	jb	.L21
	movl	$0, %edi
	call	exit
.L51:
	nop
.L21:
	addl	$1, -4(%rbp)
.L18:
	movl	-4(%rbp), %eax
	cmpl	$49, %eax
	jbe	.L25
	movsd	.LC2(%rip), %xmm0
	movsd	%xmm0, -32(%rbp)
.L16:
	movsd	-32(%rbp), %xmm0
	movsd	.LC4(%rip), %xmm1
	divsd	%xmm1, %xmm0
	leaq	-48(%rbp), %rax
	movq	%rax, %rdi
	call	modf
	movsd	-48(%rbp), %xmm0
	addsd	%xmm0, %xmm0
	movsd	.LC1(%rip), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -32(%rbp)
.L38:
	movl	$0, -4(%rbp)
	jmp	.L26
.L27:
	movl	-4(%rbp), %eax
	cltq
	movb	$0, tbl(%rax)
	addl	$1, -4(%rbp)
.L26:
	movl	-4(%rbp), %eax
	cmpl	$999, %eax
	jbe	.L27
	movsd	-32(%rbp), %xmm1
	movsd	.LC5(%rip), %xmm0
	addsd	%xmm1, %xmm0
	call	sqrt
	movq	%xmm0, %rax
	movq	%rax, -40(%rbp)
	movq	-32(%rbp), %rax
	movl	$3, %edi
	movq	%rax, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	call	mk
	movq	-32(%rbp), %rax
	movl	$5, %edi
	movq	%rax, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	call	mk
	movq	-32(%rbp), %rax
	movl	$7, %edi
	movq	%rax, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	call	mk
	movl	$0, -4(%rbp)
	movsd	.LC6(%rip), %xmm0
	movsd	%xmm0, -16(%rbp)
	jmp	.L28
.L30:
	movsd	-16(%rbp), %xmm0
	cvttsd2siq	%xmm0, %rdx
	movq	-32(%rbp), %rax
	movq	%rdx, %rdi
	movq	%rax, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	call	mk
	movl	-4(%rbp), %eax
	cmpl	$47, %eax
	jbe	.L29
	movl	$0, -4(%rbp)
.L29:
	movl	-4(%rbp), %eax
	cltq
	movsd	w(,%rax,8), %xmm0
	movsd	-16(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
.L28:
	movsd	-40(%rbp), %xmm0
	ucomisd	-16(%rbp), %xmm0
	jnb	.L30
	movl	$0, -4(%rbp)
	jmp	.L31
.L37:
	movl	-4(%rbp), %eax
	sarl	$3, %eax
	cltq
	movzbl	tbl(%rax), %edx
	movl	-4(%rbp), %eax
	andl	$7, %eax
	cltq
	movzbl	b(%rax), %eax
	andl	%edx, %eax
	testb	%al, %al
	jne	.L52
	pxor	%xmm0, %xmm0
	cvtsi2sd	-4(%rbp), %xmm0
	addsd	-32(%rbp), %xmm0
	movsd	%xmm0, -48(%rbp)
	movsd	-48(%rbp), %xmm0
	ucomisd	-24(%rbp), %xmm0
	jbe	.L50
	movl	$0, %edi
	call	exit
.L50:
	movq	-48(%rbp), %rax
	movq	%rax, -72(%rbp)
	movsd	-72(%rbp), %xmm0
	movl	$.LC7, %edi
	movl	$1, %eax
	call	printf
	movsd	N(%rip), %xmm1
	movsd	-24(%rbp), %xmm0
	ucomisd	%xmm1, %xmm0
	jb	.L33
	movl	$0, %edi
	call	exit
.L52:
	nop
.L33:
	addl	$2, -4(%rbp)
.L31:
	movl	-4(%rbp), %eax
	cmpl	$7999, %eax
	jbe	.L37
	movsd	-32(%rbp), %xmm1
	movsd	.LC5(%rip), %xmm0
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -32(%rbp)
	jmp	.L38
	.cfi_endproc
.LFE3:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC1:
	.long	0
	.long	1072693248
	.align 8
.LC2:
	.long	0
	.long	1080868864
	.align 8
.LC4:
	.long	0
	.long	1073741824
	.align 8
.LC5:
	.long	0
	.long	1086275584
	.align 8
.LC6:
	.long	0
	.long	1076232192
	.ident	"GCC: (GNU) 6.2.1 20160830"
	.section	.note.GNU-stack,"",@progbits
