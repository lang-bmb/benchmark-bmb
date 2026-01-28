	.file	"main.c"
	.text
	.p2align 4
	.globl	fibonacci
	.def	fibonacci;	.scl	2;	.type	32;	.endef
	.seh_proc	fibonacci
fibonacci:
	pushq	%r15
	.seh_pushreg	%r15
	pushq	%r14
	.seh_pushreg	%r14
	pushq	%r13
	.seh_pushreg	%r13
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
	subq	$168, %rsp
	.seh_stackalloc	168
	.seh_endprologue
	movslq	%ecx, %rbx
	cmpl	$1, %ecx
	jle	.L1
	leal	-1(%rcx), %eax
	movl	%ecx, %edi
	movl	%ecx, %ebx
	andl	$-2, %eax
	subl	%eax, %edi
	movl	%edi, %esi
	xorl	%edi, %edi
.L5:
	cmpl	%esi, %ebx
	je	.L42
	leal	-1(%rbx), %r15d
	leal	-2(%rbx), %eax
	movq	%rdi, 88(%rsp)
	xorl	%r12d, %r12d
	andl	$-2, %eax
	movl	%r15d, %r13d
	leal	-2(%rbx), %edi
	movl	%r15d, %ebx
	subl	%eax, %r13d
.L9:
	cmpl	%r13d, %ebx
	je	.L37
	leal	-1(%rbx), %eax
	leal	-2(%rbx), %edx
	movq	%r12, 96(%rsp)
	movl	%esi, %ebp
	andl	$-2, %edx
	movl	%eax, %ecx
	xorl	%r14d, %r14d
	movl	%r13d, %esi
	subl	%edx, %ecx
	leal	-2(%rbx), %r15d
	movl	%ecx, 124(%rsp)
.L13:
	cmpl	124(%rsp), %eax
	je	.L38
	leal	-1(%rax), %r8d
	subl	$2, %eax
	movl	%ebp, %ebx
	movl	%esi, %r13d
	movl	%eax, %ecx
	movl	%r8d, %edx
	movl	%eax, 108(%rsp)
	movq	%r14, %rsi
	andl	$-2, %ecx
	xorl	%ebp, %ebp
	movl	%edi, %r14d
	subl	%ecx, %edx
	movl	%edx, 128(%rsp)
.L17:
	cmpl	128(%rsp), %r8d
	je	.L39
	leal	-1(%r8), %r10d
	subl	$2, %r8d
	movq	%rbp, 112(%rsp)
	movq	%rsi, %rdx
	movl	%r8d, %eax
	movl	%r10d, %edi
	movl	%r8d, 120(%rsp)
	movl	%ebx, %r11d
	andl	$-2, %eax
	xorl	%r12d, %r12d
	movl	%r13d, %r9d
	movl	%r15d, %r8d
	subl	%eax, %edi
	movl	%r14d, %ebx
	movl	%edi, %esi
.L21:
	cmpl	%esi, %r10d
	je	.L40
	leal	-2(%r10), %edi
	leal	-1(%r10), %eax
	xorl	%r14d, %r14d
	movl	%edi, %ecx
	movl	%eax, %r13d
	leal	-4(%r10), %ebp
	andl	$-2, %ecx
	subl	%ecx, %r13d
.L25:
	cmpl	%r13d, %eax
	je	.L24
	leal	-2(%rax), %r15d
	leal	-3(%rax), %r10d
	subl	$5, %eax
	movl	%r11d, 48(%rsp)
	movl	%r15d, %ecx
	movl	%r9d, 52(%rsp)
	movl	%r8d, %r11d
	movq	%r12, %r9
	andl	$-2, %ecx
	movq	%rdx, 40(%rsp)
	movq	%r14, %r12
	movl	%ebp, %r8d
	subl	%ecx, %r10d
	movl	%ebp, %ecx
	movl	%ebx, 56(%rsp)
	andl	$-2, %ecx
	movl	%r10d, 80(%rsp)
	xorl	%r10d, %r10d
	subl	%ecx, %eax
	movl	%eax, 60(%rsp)
	cmpl	%r8d, 80(%rsp)
	je	.L44
.L26:
	leal	-2(%r8), %edx
	movq	%r10, 72(%rsp)
	leal	1(%r8), %eax
	movl	%r8d, %r14d
	movl	%edx, 84(%rsp)
	movq	%r9, 64(%rsp)
	xorl	%r9d, %r9d
.L33:
	cmpl	$1, %r14d
	je	.L41
	movl	%edx, %ebx
	leal	-2(%rax), %r10d
	subl	$4, %eax
	andl	$-2, %ebx
	movl	%r10d, %ecx
	subl	%ebx, %eax
	xorl	%ebx, %ebx
	movl	%eax, 104(%rsp)
.L35:
	movl	%r10d, 156(%rsp)
	movl	%r11d, 152(%rsp)
	movl	%edx, 148(%rsp)
	movl	%r8d, 144(%rsp)
	movq	%r9, 136(%rsp)
	movl	%ecx, 132(%rsp)
	call	fibonacci
	movl	132(%rsp), %ecx
	movq	136(%rsp), %r9
	addq	%rax, %rbx
	movl	144(%rsp), %r8d
	movl	148(%rsp), %edx
	subl	$2, %ecx
	cmpl	%ecx, 104(%rsp)
	movl	152(%rsp), %r11d
	movl	156(%rsp), %r10d
	jne	.L35
	subl	$2, %r14d
	movl	%r10d, %eax
	movl	%edx, %r10d
	subl	$2, %edx
	andl	$-2, %r10d
	movl	%r14d, %ecx
	subl	%r10d, %ecx
	movslq	%ecx, %rcx
	addq	%rbx, %rcx
	addq	%rcx, %r9
	cmpl	$1, %eax
	jne	.L33
	.p2align 4
	.p2align 3
.L41:
	movq	72(%rsp), %r10
	leaq	1(%r9), %rax
	movq	64(%rsp), %r9
	addq	%rax, %r10
	movl	84(%rsp), %eax
	cmpl	%eax, 60(%rsp)
	je	.L28
	movl	%eax, %r8d
	cmpl	%r8d, 80(%rsp)
	jne	.L26
.L44:
	movq	%r12, %r14
	movl	%r11d, %r8d
	movq	%r9, %r12
	movq	40(%rsp), %rdx
	movl	52(%rsp), %r9d
	movl	48(%rsp), %r11d
	addq	$1, %r10
	movl	56(%rsp), %ebx
.L27:
	movl	%r15d, %eax
	addq	%r10, %r14
	subl	$2, %ebp
	cmpl	$1, %r15d
	jne	.L25
.L24:
	leaq	1(%r14), %rax
	movl	%edi, %r10d
	addq	%rax, %r12
	cmpl	$1, %edi
	jne	.L21
.L40:
	movq	112(%rsp), %rbp
	movl	%r8d, %r15d
	movl	120(%rsp), %r8d
	movl	%ebx, %r14d
	leaq	1(%r12), %rax
	movq	%rdx, %rsi
	movl	%r9d, %r13d
	movl	%r11d, %ebx
	addq	%rax, %rbp
	cmpl	$1, %r8d
	jne	.L17
.L39:
	movl	108(%rsp), %eax
	leaq	1(%rbp), %rcx
	movl	%r14d, %edi
	movq	%rsi, %r14
	movl	%ebx, %ebp
	movl	%r13d, %esi
	addq	%rcx, %r14
	cmpl	$1, %eax
	jne	.L13
.L38:
	movq	96(%rsp), %r12
	leaq	1(%r14), %rax
	movl	%esi, %r13d
	movl	%r15d, %ebx
	movl	%ebp, %esi
	addq	%rax, %r12
	cmpl	$1, %r15d
	jne	.L9
.L37:
	movl	%edi, %ebx
	movq	88(%rsp), %rdi
	leaq	1(%r12), %rax
	addq	%rax, %rdi
	cmpl	$1, %ebx
	jne	.L5
.L42:
	leaq	1(%rdi), %rbx
.L1:
	movq	%rbx, %rax
	addq	$168, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%rbp
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	ret
.L28:
	movslq	%r8d, %rax
	movq	%r12, %r14
	movl	%r11d, %r8d
	movq	%r9, %r12
	movq	40(%rsp), %rdx
	movl	52(%rsp), %r9d
	addq	%rax, %r10
	movl	48(%rsp), %r11d
	movl	56(%rsp), %ebx
	jmp	.L27
	.seh_endproc
	.section .rdata,"dr"
.LC0:
	.ascii "fibonacci(%d) = %lld\12\0"
	.section	.text.startup,"x"
	.p2align 4
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	movl	$34, %edi
	xorl	%ebp, %ebp
	call	__main
.L46:
	movl	%edi, %ebx
	xorl	%esi, %esi
.L47:
	leal	-1(%rbx), %ecx
	subl	$2, %ebx
	call	fibonacci
	addq	%rax, %rsi
	cmpl	$1, %ebx
	jg	.L47
	addq	%rsi, %rbp
	subl	$2, %edi
	jne	.L46
	leaq	1(%rbp), %r8
	movl	$35, %edx
	leaq	.LC0(%rip), %rcx
	call	printf
	xorl	%eax, %eax
	addq	$40, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev9, Built by MSYS2 project) 15.2.0"
	.def	printf;	.scl	2;	.type	32;	.endef
