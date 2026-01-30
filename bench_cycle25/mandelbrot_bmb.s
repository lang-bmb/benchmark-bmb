	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
@feat.00 = 0
	.file	"bmb_program"
	.def	scale;
	.scl	2;
	.type	32;
	.endef
	.text
	.globl	scale                           # -- Begin function scale
	.p2align	4
scale:                                  # @scale
# %bb.0:                                # %entry
	movl	$10000, %eax                    # imm = 0x2710
	retq
                                        # -- End function
	.def	mul_fp;
	.scl	2;
	.type	32;
	.endef
	.globl	mul_fp                          # -- Begin function mul_fp
	.p2align	4
mul_fp:                                 # @mul_fp
# %bb.0:                                # %entry
	movq	%rcx, %rax
	imulq	%rdx, %rax
	movabsq	$3777893186295716171, %rcx      # imm = 0x346DC5D63886594B
	imulq	%rcx
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$11, %rdx
	addq	%rdx, %rax
	retq
                                        # -- End function
	.def	square_fp;
	.scl	2;
	.type	32;
	.endef
	.globl	square_fp                       # -- Begin function square_fp
	.p2align	4
square_fp:                              # @square_fp
# %bb.0:                                # %entry
	subq	$40, %rsp
	movq	%rcx, %rdx
	callq	mul_fp
	addq	$40, %rsp
	retq
                                        # -- End function
	.def	threshold;
	.scl	2;
	.type	32;
	.endef
	.globl	threshold                       # -- Begin function threshold
	.p2align	4
threshold:                              # @threshold
# %bb.0:                                # %entry
	movl	$400000000, %eax                # imm = 0x17D78400
	retq
                                        # -- End function
	.def	iterate;
	.scl	2;
	.type	32;
	.endef
	.globl	iterate                         # -- Begin function iterate
	.p2align	4
iterate:                                # @iterate
# %bb.0:                                # %entry
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rsi
	pushq	%rdi
	pushq	%rbx
	subq	$48, %rsp
	movq	152(%rsp), %rax
	movq	144(%rsp), %r15
	cmpq	%rax, %r15
	jge	.LBB4_4
# %bb.1:                                # %else_1
	movq	%r9, %rdi
	movq	%r8, %r14
	movq	%rcx, %rsi
	movq	%rdx, %r13
	movq	%rax, %r12
	movq	%r8, %rcx
	callq	square_fp
	movq	%rax, %rbx
	movq	%rdi, %rcx
	callq	square_fp
	leaq	(%rbx,%rax), %rcx
	cmpq	$400000000, %rcx                # imm = 0x17D78400
	jle	.LBB4_3
# %bb.2:
	movq	%r15, %rax
	jmp	.LBB4_4
.LBB4_3:                                # %else_4
	subq	%rax, %rbx
	addq	%rsi, %rbx
	movq	%r14, %rcx
	movq	%rdi, %rdx
	callq	mul_fp
	movq	%r13, %rdx
	leaq	(%r13,%rax,2), %r9
	incq	%r15
	movq	%r12, 40(%rsp)
	movq	%r15, 32(%rsp)
	movq	%rsi, %rcx
	movq	%rbx, %r8
	callq	iterate
.LBB4_4:                                # %merge_2
	addq	$48, %rsp
	popq	%rbx
	popq	%rdi
	popq	%rsi
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	retq
                                        # -- End function
	.def	mandelbrot_point;
	.scl	2;
	.type	32;
	.endef
	.globl	mandelbrot_point                # -- Begin function mandelbrot_point
	.p2align	4
mandelbrot_point:                       # @mandelbrot_point
# %bb.0:                                # %entry
	subq	$56, %rsp
	movq	%rdx, %r10
	movq	96(%rsp), %r11
	imulq	$40000, %rcx, %rax              # imm = 0x9C40
	cqto
	idivq	%r8
	leaq	-20000(%rax), %rcx
	imulq	$40000, %r10, %rax              # imm = 0x9C40
	cqto
	idivq	%r9
	leaq	-20000(%rax), %rdx
	movq	%r11, 40(%rsp)
	movq	$0, 32(%rsp)
	xorl	%r8d, %r8d
	xorl	%r9d, %r9d
	callq	iterate
	addq	$56, %rsp
	retq
                                        # -- End function
	.def	bmb_user_main;
	.scl	2;
	.type	32;
	.endef
	.globl	bmb_user_main                   # -- Begin function bmb_user_main
	.p2align	4
bmb_user_main:                          # @bmb_user_main
# %bb.0:                                # %entry
	subq	$72, %rsp
	movl	$0, 60(%rsp)
	movl	$0, 56(%rsp)
	movl	$0, 52(%rsp)
	movl	$0, 64(%rsp)
	movl	$0, 68(%rsp)
	jmp	.LBB6_1
	.p2align	4
.LBB6_7:                                # %while_exit_5
                                        #   in Loop: Header=BB6_1 Depth=1
	incl	56(%rsp)
.LBB6_1:                                # %while_cond_0
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB6_3 Depth 2
	cmpl	$1999, 56(%rsp)                 # imm = 0x7CF
	jg	.LBB6_8
# %bb.2:                                # %while_body_1
                                        #   in Loop: Header=BB6_1 Depth=1
	movl	$0, 52(%rsp)
	jmp	.LBB6_3
	.p2align	4
.LBB6_6:                                # %merge_8
                                        #   in Loop: Header=BB6_3 Depth=2
	movl	%ecx, 68(%rsp)
	addl	%ecx, 60(%rsp)
	incl	52(%rsp)
.LBB6_3:                                # %while_cond_3
                                        #   Parent Loop BB6_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	cmpl	$1999, 52(%rsp)                 # imm = 0x7CF
	jg	.LBB6_7
# %bb.4:                                # %while_body_4
                                        #   in Loop: Header=BB6_3 Depth=2
	movslq	52(%rsp), %rcx
	movslq	56(%rsp), %rdx
	movq	$100, 32(%rsp)
	movl	$2000, %r8d                     # imm = 0x7D0
	movl	$2000, %r9d                     # imm = 0x7D0
	callq	mandelbrot_point
	movl	%eax, 64(%rsp)
	movl	$1, %ecx
	cmpl	$100, %eax
	jl	.LBB6_6
# %bb.5:                                # %else_7
                                        #   in Loop: Header=BB6_3 Depth=2
	xorl	%ecx, %ecx
	jmp	.LBB6_6
.LBB6_8:                                # %while_exit_2
	movslq	60(%rsp), %rcx
	callq	bmb_println_i64
	xorl	%eax, %eax
	addq	$72, %rsp
	retq
                                        # -- End function
