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
# %bb.0:                                # %entry
	pushq	%rsi
	pushq	%rdi
	subq	$40, %rsp
	xorl	%esi, %esi
	cmpl	$2, %ecx
	jl	.LBB0_3
# %bb.1:                                # %else_1.preheader
	movl	%ecx, %edi
	.p2align	4
.LBB0_2:                                # %else_1
                                        # =>This Inner Loop Header: Depth=1
	leal	-1(%rdi), %ecx
	callq	fibonacci
	leal	-2(%rdi), %ecx
	addq	%rax, %rsi
	cmpl	$4, %edi
	movl	%ecx, %edi
	jae	.LBB0_2
.LBB0_3:                                # %then_0
	movslq	%ecx, %rax
	addq	%rsi, %rax
	addq	$40, %rsp
	popq	%rdi
	popq	%rsi
	retq
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
