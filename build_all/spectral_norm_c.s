	.file	"main.c"
	.text
	.p2align 4
	.globl	A
	.def	A;	.scl	2;	.type	32;	.endef
	.seh_proc	A
A:
	.seh_endprologue
	movsd	.LC0(%rip), %xmm0
	pxor	%xmm1, %xmm1
	leal	(%rcx,%rdx), %eax
	leal	1(%rax), %edx
	imull	%eax, %edx
	movl	%edx, %eax
	shrl	$31, %eax
	addl	%edx, %eax
	sarl	%eax
	leal	1(%rax,%rcx), %eax
	cvtsi2sdl	%eax, %xmm1
	divsd	%xmm1, %xmm0
	ret
	.seh_endproc
	.p2align 4
	.globl	mult_Av
	.def	mult_Av;	.scl	2;	.type	32;	.endef
	.seh_proc	mult_Av
mult_Av:
	pushq	%rbx
	.seh_pushreg	%rbx
	.seh_endprologue
	movq	%rcx, %rbx
	testl	%r8d, %r8d
	jle	.L3
	movsd	.LC0(%rip), %xmm3
	movl	%r8d, %r11d
	xorl	%r10d, %r10d
	.p2align 4
	.p2align 3
.L6:
	movq	$0x000000000, (%rdx)
	movl	%r10d, %ecx
	movq	%rbx, %r9
	pxor	%xmm1, %xmm1
	.p2align 6
	.p2align 4
	.p2align 3
.L5:
	movl	%ecx, %eax
	addl	$1, %ecx
	pxor	%xmm2, %xmm2
	addq	$8, %r9
	imull	%ecx, %eax
	movapd	%xmm3, %xmm0
	sarl	%eax
	leal	1(%r10,%rax), %eax
	cvtsi2sdl	%eax, %xmm2
	divsd	%xmm2, %xmm0
	mulsd	-8(%r9), %xmm0
	addsd	%xmm0, %xmm1
	movsd	%xmm1, (%rdx)
	cmpl	%ecx, %r11d
	jne	.L5
	addl	$1, %r10d
	addq	$8, %rdx
	addl	$1, %r11d
	cmpl	%r10d, %r8d
	jne	.L6
.L3:
	popq	%rbx
	ret
	.seh_endproc
	.p2align 4
	.globl	mult_Atv
	.def	mult_Atv;	.scl	2;	.type	32;	.endef
	.seh_proc	mult_Atv
mult_Atv:
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	.seh_endprologue
	movq	%rcx, %rbx
	movl	%r8d, %esi
	testl	%r8d, %r8d
	jle	.L10
	movsd	.LC0(%rip), %xmm3
	xorl	%r10d, %r10d
	movslq	%r8d, %r8
	.p2align 4
	.p2align 3
.L13:
	movq	$0x000000000, (%rdx)
	xorl	%eax, %eax
	pxor	%xmm1, %xmm1
	leal	1(%r10), %r11d
	.p2align 6
	.p2align 4
	.p2align 3
.L12:
	leal	(%r11,%rax), %ecx
	leal	(%r10,%rax), %r9d
	pxor	%xmm2, %xmm2
	imull	%r9d, %ecx
	movapd	%xmm3, %xmm0
	sarl	%ecx
	leal	1(%rcx,%rax), %ecx
	cvtsi2sdl	%ecx, %xmm2
	divsd	%xmm2, %xmm0
	mulsd	(%rbx,%rax,8), %xmm0
	addq	$1, %rax
	addsd	%xmm0, %xmm1
	movsd	%xmm1, (%rdx)
	cmpq	%rax, %r8
	jne	.L12
	movl	%r11d, %r10d
	addq	$8, %rdx
	cmpl	%r11d, %esi
	jne	.L13
.L10:
	popq	%rbx
	popq	%rsi
	ret
	.seh_endproc
	.p2align 4
	.globl	mult_AtAv
	.def	mult_AtAv;	.scl	2;	.type	32;	.endef
	.seh_proc	mult_AtAv
mult_AtAv:
	pushq	%r13
	.seh_pushreg	%r13
	movl	$8088, %eax
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	call	___chkstk_ms
	subq	%rax, %rsp
	.seh_stackalloc	8088
	movups	%xmm6, 8000(%rsp)
	.seh_savexmm	%xmm6, 8000
	movups	%xmm7, 8016(%rsp)
	.seh_savexmm	%xmm7, 8016
	movups	%xmm8, 8032(%rsp)
	.seh_savexmm	%xmm8, 8032
	movups	%xmm9, 8048(%rsp)
	.seh_savexmm	%xmm9, 8048
	movups	%xmm10, 8064(%rsp)
	.seh_savexmm	%xmm10, 8064
	.seh_endprologue
	movq	%rcx, %rbx
	movq	%rdx, %r10
	testl	%r8d, %r8d
	jle	.L17
	movl	%r8d, %ecx
	pcmpeqd	%xmm4, %xmm4
	leal	-1(%r8), %r11d
	movq	%rsp, %rsi
	shrl	$2, %ecx
	psrld	$31, %xmm4
	xorl	%edx, %edx
	movdqu	.LC2(%rip), %xmm8
	salq	$5, %rcx
	movddup	.LC0(%rip), %xmm5
	movsd	.LC0(%rip), %xmm7
	addq	%rbx, %rcx
	.p2align 4
	.p2align 3
.L24:
	cmpl	$2, %r11d
	jbe	.L31
	movl	$4, %eax
	movl	%r8d, %r9d
	movd	%eax, %xmm6
	andl	$-4, %r9d
	pshufd	$0, %xmm6, %xmm6
.L21:
	movd	%edx, %xmm3
	movdqa	%xmm8, %xmm1
	pxor	%xmm2, %xmm2
	movq	%rbx, %rax
	pshufd	$0, %xmm3, %xmm3
	.p2align 4
	.p2align 3
.L20:
	movdqa	%xmm3, %xmm10
	addq	$32, %rax
	paddd	%xmm1, %xmm10
	paddd	%xmm6, %xmm1
	movdqa	%xmm10, %xmm9
	paddd	%xmm4, %xmm9
	movdqa	%xmm9, %xmm0
	psrlq	$32, %xmm9
	pmuludq	%xmm10, %xmm0
	psrlq	$32, %xmm10
	pmuludq	%xmm10, %xmm9
	movapd	%xmm5, %xmm10
	pshufd	$8, %xmm0, %xmm0
	pshufd	$8, %xmm9, %xmm9
	punpckldq	%xmm9, %xmm0
	psrad	$1, %xmm0
	paddd	%xmm3, %xmm0
	paddd	%xmm4, %xmm0
	cvtdq2pd	%xmm0, %xmm9
	divpd	%xmm9, %xmm10
	movupd	-32(%rax), %xmm9
	pshufd	$238, %xmm0, %xmm0
	cvtdq2pd	%xmm0, %xmm0
	mulpd	%xmm9, %xmm10
	movapd	%xmm5, %xmm9
	divpd	%xmm0, %xmm9
	movupd	-16(%rax), %xmm0
	mulpd	%xmm0, %xmm9
	movapd	%xmm10, %xmm0
	unpckhpd	%xmm10, %xmm10
	addsd	%xmm2, %xmm0
	addsd	%xmm10, %xmm0
	addsd	%xmm9, %xmm0
	unpckhpd	%xmm9, %xmm9
	movapd	%xmm0, %xmm2
	addsd	%xmm9, %xmm2
	cmpq	%rax, %rcx
	jne	.L20
	cmpl	%r9d, %r8d
	je	.L38
.L19:
	leal	(%rdx,%r9), %ebp
	pxor	%xmm1, %xmm1
	movapd	%xmm7, %xmm0
	movslq	%r9d, %rdi
	leal	1(%rbp), %eax
	imull	%ebp, %eax
	sarl	%eax
	leal	1(%rdx,%rax), %eax
	cvtsi2sdl	%eax, %xmm1
	divsd	%xmm1, %xmm0
	leal	1(%r9), %eax
	mulsd	(%rbx,%rdi,8), %xmm0
	addsd	%xmm2, %xmm0
	cmpl	%eax, %r8d
	jle	.L23
	addl	%edx, %eax
	pxor	%xmm2, %xmm2
	movapd	%xmm7, %xmm1
	addl	$2, %r9d
	leal	1(%rax), %ebp
	imull	%ebp, %eax
	sarl	%eax
	leal	1(%rdx,%rax), %eax
	cvtsi2sdl	%eax, %xmm2
	divsd	%xmm2, %xmm1
	mulsd	8(%rbx,%rdi,8), %xmm1
	addsd	%xmm1, %xmm0
	cmpl	%r9d, %r8d
	jle	.L23
	addl	%edx, %r9d
	pxor	%xmm2, %xmm2
	movapd	%xmm7, %xmm1
	leal	1(%r9), %eax
	imull	%r9d, %eax
	sarl	%eax
	leal	1(%rdx,%rax), %eax
	cvtsi2sdl	%eax, %xmm2
	divsd	%xmm2, %xmm1
	mulsd	16(%rbx,%rdi,8), %xmm1
	addsd	%xmm1, %xmm0
.L23:
	addl	$1, %edx
	movsd	%xmm0, (%rsi)
	addq	$8, %rsi
	cmpl	%edx, %r8d
	jne	.L24
.L22:
	movl	%r8d, %eax
	pcmpeqd	%xmm3, %xmm3
	movslq	%edx, %rdi
	xorl	%ebx, %ebx
	shrl	$2, %eax
	movddup	.LC0(%rip), %xmm4
	movdqu	.LC2(%rip), %xmm8
	psrld	$31, %xmm3
	salq	$5, %rax
	movsd	.LC0(%rip), %xmm7
	leaq	(%rsp,%rax), %rcx
	.p2align 4
	.p2align 3
.L30:
	movl	%ebx, %esi
	cmpl	$2, %r11d
	jbe	.L32
	movl	$4, %eax
	movl	%r8d, %r9d
	movd	%eax, %xmm5
	andl	$-4, %r9d
	pshufd	$0, %xmm5, %xmm5
.L28:
	movd	%esi, %xmm6
	movdqa	%xmm8, %xmm2
	pxor	%xmm1, %xmm1
	movq	%rsp, %rax
	pshufd	$0, %xmm6, %xmm6
	.p2align 4
	.p2align 3
.L26:
	movdqa	%xmm2, %xmm10
	addq	$32, %rax
	paddd	%xmm6, %xmm10
	movdqa	%xmm10, %xmm9
	paddd	%xmm3, %xmm9
	movdqa	%xmm9, %xmm0
	psrlq	$32, %xmm9
	pmuludq	%xmm10, %xmm0
	psrlq	$32, %xmm10
	pmuludq	%xmm10, %xmm9
	pshufd	$8, %xmm0, %xmm0
	pshufd	$8, %xmm9, %xmm9
	punpckldq	%xmm9, %xmm0
	movapd	%xmm4, %xmm9
	psrad	$1, %xmm0
	paddd	%xmm2, %xmm0
	paddd	%xmm5, %xmm2
	paddd	%xmm3, %xmm0
	cvtdq2pd	%xmm0, %xmm10
	divpd	%xmm10, %xmm9
	pshufd	$238, %xmm0, %xmm0
	movapd	%xmm4, %xmm10
	cvtdq2pd	%xmm0, %xmm0
	divpd	%xmm0, %xmm10
	movupd	-16(%rax), %xmm0
	mulpd	-32(%rax), %xmm9
	addsd	%xmm9, %xmm1
	unpckhpd	%xmm9, %xmm9
	addsd	%xmm1, %xmm9
	mulpd	%xmm10, %xmm0
	movapd	%xmm0, %xmm1
	unpckhpd	%xmm0, %xmm0
	addsd	%xmm9, %xmm1
	addsd	%xmm0, %xmm1
	cmpq	%rax, %rcx
	jne	.L26
	cmpl	%r9d, %r8d
	je	.L39
.L25:
	leal	(%r9,%rsi), %r13d
	pxor	%xmm2, %xmm2
	movapd	%xmm7, %xmm0
	movslq	%r9d, %r12
	leal	1(%r13), %eax
	leaq	0(,%r12,8), %rbp
	imull	%r13d, %eax
	sarl	%eax
	leal	1(%r9,%rax), %eax
	cvtsi2sdl	%eax, %xmm2
	divsd	%xmm2, %xmm0
	mulsd	(%rsp,%r12,8), %xmm0
	leal	1(%r9), %r12d
	addsd	%xmm1, %xmm0
	cmpl	%edx, %r12d
	jge	.L29
	leal	(%r12,%rsi), %r13d
	pxor	%xmm2, %xmm2
	movapd	%xmm7, %xmm1
	addl	$2, %r9d
	leal	1(%r13), %eax
	imull	%r13d, %eax
	sarl	%eax
	leal	1(%r12,%rax), %eax
	cvtsi2sdl	%eax, %xmm2
	divsd	%xmm2, %xmm1
	mulsd	8(%rsp,%rbp), %xmm1
	addsd	%xmm1, %xmm0
	cmpl	%edx, %r9d
	jge	.L29
	addl	%r9d, %esi
	pxor	%xmm2, %xmm2
	movapd	%xmm7, %xmm1
	leal	1(%rsi), %eax
	imull	%esi, %eax
	sarl	%eax
	leal	1(%r9,%rax), %eax
	cvtsi2sdl	%eax, %xmm2
	divsd	%xmm2, %xmm1
	mulsd	16(%rsp,%rbp), %xmm1
	addsd	%xmm1, %xmm0
.L29:
	movsd	%xmm0, (%r10,%rbx,8)
	addq	$1, %rbx
	cmpq	%rbx, %rdi
	jne	.L30
.L17:
	movups	8000(%rsp), %xmm6
	movups	8016(%rsp), %xmm7
	movups	8032(%rsp), %xmm8
	movups	8048(%rsp), %xmm9
	movups	8064(%rsp), %xmm10
	addq	$8088, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%rbp
	popq	%r12
	popq	%r13
	ret
	.p2align 4,,10
	.p2align 3
.L38:
	addl	$1, %edx
	movsd	%xmm2, (%rsi)
	addq	$8, %rsi
	cmpl	%edx, %r8d
	jne	.L21
	jmp	.L22
	.p2align 4,,10
	.p2align 3
.L39:
	movsd	%xmm1, (%r10,%rbx,8)
	addq	$1, %rbx
	cmpq	%rdi, %rbx
	je	.L17
	movl	%ebx, %esi
	jmp	.L28
	.p2align 4,,10
	.p2align 3
.L32:
	pxor	%xmm1, %xmm1
	xorl	%r9d, %r9d
	jmp	.L25
	.p2align 4,,10
	.p2align 3
.L31:
	pxor	%xmm2, %xmm2
	xorl	%r9d, %r9d
	jmp	.L19
	.seh_endproc
	.section .rdata,"dr"
.LC6:
	.ascii "%.9f\12\0"
	.section	.text.startup,"x"
	.p2align 4
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rsi
	.seh_pushreg	%rsi
	movl	$24104, %eax
	pushq	%rbx
	.seh_pushreg	%rbx
	call	___chkstk_ms
	subq	%rax, %rsp
	.seh_stackalloc	24104
	movups	%xmm6, 24032(%rsp)
	.seh_savexmm	%xmm6, 24032
	movups	%xmm7, 24048(%rsp)
	.seh_savexmm	%xmm7, 24048
	movups	%xmm8, 24064(%rsp)
	.seh_savexmm	%xmm8, 24064
	movups	%xmm9, 24080(%rsp)
	.seh_savexmm	%xmm9, 24080
	.seh_endprologue
	call	__main
	leaq	32(%rsp), %r8
	movddup	.LC0(%rip), %xmm1
	leaq	8032(%rsp), %rdx
	movq	%r8, %rax
	.p2align 4
	.p2align 4
	.p2align 3
.L41:
	movups	%xmm1, (%rax)
	addq	$32, %rax
	movups	%xmm1, -16(%rax)
	cmpq	%rax, %rdx
	jne	.L41
	pcmpeqd	%xmm2, %xmm2
	movl	$4, %eax
	movdqu	.LC2(%rip), %xmm4
	movl	$10, %ebx
	movd	%eax, %xmm3
	psrld	$31, %xmm2
	leaq	8000(%rdx), %rcx
	pshufd	$0, %xmm3, %xmm3
	.p2align 4
	.p2align 3
.L42:
	leaq	16032(%rsp), %r10
	xorl	%r9d, %r9d
	.p2align 4
	.p2align 3
.L44:
	movd	%r9d, %xmm7
	movq	%r8, %rax
	movdqa	%xmm4, %xmm6
	pxor	%xmm8, %xmm8
	pshufd	$0, %xmm7, %xmm7
	.p2align 4
	.p2align 3
.L43:
	movdqa	%xmm6, %xmm9
	addq	$32, %rax
	paddd	%xmm3, %xmm6
	paddd	%xmm7, %xmm9
	movdqa	%xmm9, %xmm5
	paddd	%xmm2, %xmm5
	movdqa	%xmm5, %xmm0
	psrlq	$32, %xmm5
	pmuludq	%xmm9, %xmm0
	psrlq	$32, %xmm9
	pmuludq	%xmm9, %xmm5
	pshufd	$8, %xmm0, %xmm0
	pshufd	$8, %xmm5, %xmm5
	punpckldq	%xmm5, %xmm0
	movapd	%xmm1, %xmm5
	psrad	$1, %xmm0
	paddd	%xmm7, %xmm0
	paddd	%xmm2, %xmm0
	cvtdq2pd	%xmm0, %xmm9
	divpd	%xmm9, %xmm5
	pshufd	$238, %xmm0, %xmm0
	movapd	%xmm1, %xmm9
	cvtdq2pd	%xmm0, %xmm0
	divpd	%xmm0, %xmm9
	movupd	-16(%rax), %xmm0
	mulpd	-32(%rax), %xmm5
	addsd	%xmm5, %xmm8
	unpckhpd	%xmm5, %xmm5
	addsd	%xmm8, %xmm5
	mulpd	%xmm9, %xmm0
	movapd	%xmm0, %xmm8
	unpckhpd	%xmm0, %xmm0
	addsd	%xmm5, %xmm8
	addsd	%xmm0, %xmm8
	cmpq	%rax, %rdx
	jne	.L43
	addl	$1, %r9d
	movsd	%xmm8, (%r10)
	addq	$8, %r10
	cmpl	$1000, %r9d
	jne	.L44
	movq	%rdx, %r10
	movq	%rdx, %r11
	xorl	%r9d, %r9d
	.p2align 4
	.p2align 3
.L46:
	movd	%r9d, %xmm7
	movdqa	%xmm4, %xmm6
	pxor	%xmm8, %xmm8
	leaq	16032(%rsp), %rax
	pshufd	$0, %xmm7, %xmm7
	.p2align 4
	.p2align 3
.L45:
	movdqa	%xmm6, %xmm9
	addq	$32, %rax
	leaq	24032(%rsp), %rsi
	paddd	%xmm7, %xmm9
	movdqa	%xmm9, %xmm5
	paddd	%xmm2, %xmm5
	movdqa	%xmm5, %xmm0
	psrlq	$32, %xmm5
	pmuludq	%xmm9, %xmm0
	psrlq	$32, %xmm9
	pmuludq	%xmm9, %xmm5
	pshufd	$8, %xmm0, %xmm0
	pshufd	$8, %xmm5, %xmm5
	punpckldq	%xmm5, %xmm0
	movapd	%xmm1, %xmm5
	psrad	$1, %xmm0
	paddd	%xmm6, %xmm0
	paddd	%xmm3, %xmm6
	paddd	%xmm2, %xmm0
	cvtdq2pd	%xmm0, %xmm9
	divpd	%xmm9, %xmm5
	pshufd	$238, %xmm0, %xmm0
	movapd	%xmm1, %xmm9
	cvtdq2pd	%xmm0, %xmm0
	divpd	%xmm0, %xmm9
	movupd	-16(%rax), %xmm0
	mulpd	-32(%rax), %xmm5
	addsd	%xmm5, %xmm8
	unpckhpd	%xmm5, %xmm5
	addsd	%xmm8, %xmm5
	mulpd	%xmm9, %xmm0
	movapd	%xmm0, %xmm8
	unpckhpd	%xmm0, %xmm0
	addsd	%xmm5, %xmm8
	addsd	%xmm0, %xmm8
	cmpq	%rsi, %rax
	jne	.L45
	addl	$1, %r9d
	movsd	%xmm8, (%r11)
	addq	$8, %r11
	cmpl	$1000, %r9d
	jne	.L46
	leaq	16032(%rsp), %r11
	xorl	%r9d, %r9d
	.p2align 4
	.p2align 3
.L48:
	movd	%r9d, %xmm7
	movq	%rdx, %rax
	movdqa	%xmm4, %xmm6
	pxor	%xmm8, %xmm8
	pshufd	$0, %xmm7, %xmm7
	.p2align 4
	.p2align 3
.L47:
	movdqa	%xmm6, %xmm9
	addq	$32, %rax
	paddd	%xmm3, %xmm6
	paddd	%xmm7, %xmm9
	movdqa	%xmm9, %xmm5
	paddd	%xmm2, %xmm5
	movdqa	%xmm5, %xmm0
	psrlq	$32, %xmm5
	pmuludq	%xmm9, %xmm0
	psrlq	$32, %xmm9
	pmuludq	%xmm9, %xmm5
	pshufd	$8, %xmm0, %xmm0
	pshufd	$8, %xmm5, %xmm5
	punpckldq	%xmm5, %xmm0
	movapd	%xmm1, %xmm5
	psrad	$1, %xmm0
	paddd	%xmm7, %xmm0
	paddd	%xmm2, %xmm0
	cvtdq2pd	%xmm0, %xmm9
	divpd	%xmm9, %xmm5
	pshufd	$238, %xmm0, %xmm0
	movapd	%xmm1, %xmm9
	cvtdq2pd	%xmm0, %xmm0
	divpd	%xmm0, %xmm9
	movupd	-16(%rax), %xmm0
	mulpd	-32(%rax), %xmm5
	addsd	%xmm5, %xmm8
	unpckhpd	%xmm5, %xmm5
	addsd	%xmm8, %xmm5
	mulpd	%xmm9, %xmm0
	movapd	%xmm0, %xmm8
	unpckhpd	%xmm0, %xmm0
	addsd	%xmm5, %xmm8
	addsd	%xmm0, %xmm8
	cmpq	%rax, %rcx
	jne	.L47
	addl	$1, %r9d
	movsd	%xmm8, (%r11)
	addq	$8, %r11
	cmpl	$1000, %r9d
	jne	.L48
	movq	%r8, %r11
	xorl	%r9d, %r9d
	.p2align 4
	.p2align 3
.L50:
	movd	%r9d, %xmm7
	movdqa	%xmm4, %xmm6
	pxor	%xmm8, %xmm8
	leaq	16032(%rsp), %rax
	pshufd	$0, %xmm7, %xmm7
	.p2align 4
	.p2align 3
.L49:
	movdqa	%xmm6, %xmm9
	addq	$32, %rax
	leaq	24032(%rsp), %rsi
	paddd	%xmm7, %xmm9
	movdqa	%xmm9, %xmm5
	paddd	%xmm2, %xmm5
	movdqa	%xmm5, %xmm0
	psrlq	$32, %xmm5
	pmuludq	%xmm9, %xmm0
	psrlq	$32, %xmm9
	pmuludq	%xmm9, %xmm5
	pshufd	$8, %xmm0, %xmm0
	pshufd	$8, %xmm5, %xmm5
	punpckldq	%xmm5, %xmm0
	movapd	%xmm1, %xmm5
	psrad	$1, %xmm0
	paddd	%xmm6, %xmm0
	paddd	%xmm3, %xmm6
	paddd	%xmm2, %xmm0
	cvtdq2pd	%xmm0, %xmm9
	divpd	%xmm9, %xmm5
	pshufd	$238, %xmm0, %xmm0
	movapd	%xmm1, %xmm9
	cvtdq2pd	%xmm0, %xmm0
	divpd	%xmm0, %xmm9
	movupd	-16(%rax), %xmm0
	mulpd	-32(%rax), %xmm5
	addsd	%xmm5, %xmm8
	unpckhpd	%xmm5, %xmm5
	addsd	%xmm8, %xmm5
	mulpd	%xmm9, %xmm0
	movapd	%xmm0, %xmm8
	unpckhpd	%xmm0, %xmm0
	addsd	%xmm5, %xmm8
	addsd	%xmm0, %xmm8
	cmpq	%rsi, %rax
	jne	.L49
	addl	$1, %r9d
	movsd	%xmm8, (%r11)
	addq	$8, %r11
	cmpl	$1000, %r9d
	jne	.L50
	subl	$1, %ebx
	jne	.L42
	pxor	%xmm3, %xmm3
	movapd	%xmm3, %xmm2
	.p2align 6
	.p2align 4
	.p2align 3
.L51:
	movupd	(%r10), %xmm0
	movupd	(%r8), %xmm1
	addq	$16, %r8
	addq	$16, %r10
	mulpd	%xmm0, %xmm1
	mulpd	%xmm0, %xmm0
	addsd	%xmm1, %xmm2
	unpckhpd	%xmm1, %xmm1
	addsd	%xmm0, %xmm3
	unpckhpd	%xmm0, %xmm0
	addsd	%xmm1, %xmm2
	addsd	%xmm0, %xmm3
	cmpq	%r8, %rdx
	jne	.L51
	divsd	%xmm3, %xmm2
	pxor	%xmm1, %xmm1
	ucomisd	%xmm2, %xmm1
	movapd	%xmm2, %xmm0
	ja	.L68
	movapd	%xmm2, %xmm1
	sqrtsd	%xmm1, %xmm1
.L54:
	movq	%xmm1, %rdx
	leaq	.LC6(%rip), %rcx
	call	printf
	nop
	movups	24032(%rsp), %xmm6
	movups	24048(%rsp), %xmm7
	xorl	%eax, %eax
	movups	24064(%rsp), %xmm8
	movups	24080(%rsp), %xmm9
	addq	$24104, %rsp
	popq	%rbx
	popq	%rsi
	ret
.L68:
	call	sqrt
	movapd	%xmm0, %xmm1
	jmp	.L54
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC0:
	.long	0
	.long	1072693248
	.align 16
.LC2:
	.long	0
	.long	1
	.long	2
	.long	3
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev9, Built by MSYS2 project) 15.2.0"
	.def	printf;	.scl	2;	.type	32;	.endef
	.def	sqrt;	.scl	2;	.type	32;	.endef
