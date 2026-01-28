	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
@feat.00 = 0
	.file	"bmb_program"
	.def	fibonacci;
	.scl	2;
	.type	32;
	.endef
	.text
	.globl	fibonacci                       # -- Begin function fibonacci
	.p2align	4
fibonacci:                              # @fibonacci
.seh_proc fibonacci
# %bb.0:                                # %entry
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	movl	%ecx, %esi
	cmpl	$1, %ecx
	jg	.LBB0_2
# %bb.1:                                # %then_0
	movslq	%esi, %rax
	.seh_startepilogue
	addq	$40, %rsp
	popq	%rdi
	popq	%rsi
	.seh_endepilogue
	retq
.LBB0_2:                                # %else_1
	leal	-1(%rsi), %ecx
	callq	fibonacci
	movq	%rax, %rdi
	addl	$-2, %esi
	movl	%esi, %ecx
	callq	fibonacci
	addq	%rdi, %rax
	.seh_startepilogue
	addq	$40, %rsp
	popq	%rdi
	popq	%rsi
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	bmb_user_main;
	.scl	2;
	.type	32;
	.endef
	.globl	bmb_user_main                   # -- Begin function bmb_user_main
	.p2align	4
bmb_user_main:                          # @bmb_user_main
.seh_proc bmb_user_main
# %bb.0:                                # %entry
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	movl	$35, %ecx
	callq	fibonacci
	movq	%rax, %rcx
	callq	bmb_println_i64
	xorl	%eax, %eax
	.seh_startepilogue
	addq	$40, %rsp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
