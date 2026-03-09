	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
@feat.00 = 0
	.file	"main.c"
	.def	digit_sum;
	.scl	2;
	.type	32;
	.endef
	.text
	.globl	digit_sum                       # -- Begin function digit_sum
	.p2align	4
digit_sum:                              # @digit_sum
# %bb.0:
	testq	%rcx, %rcx
	jle	.LBB0_1
# %bb.2:
	movq	%rcx, %r8
	xorl	%ecx, %ecx
	movabsq	$-3689348814741910323, %r9      # imm = 0xCCCCCCCCCCCCCCCD
	.p2align	4
.LBB0_3:                                # =>This Inner Loop Header: Depth=1
	movq	%r8, %rax
	mulq	%r9
	shrq	$3, %rdx
	leaq	(%rdx,%rdx), %rax
	leaq	(%rax,%rax,4), %rax
	movq	%r8, %r10
	subq	%rax, %r10
	addq	%r10, %rcx
	cmpq	$9, %r8
	movq	%rdx, %r8
	ja	.LBB0_3
# %bb.4:
	movq	%rcx, %rax
	retq
.LBB0_1:
	xorl	%ecx, %ecx
	movq	%rcx, %rax
	retq
                                        # -- End function
	.def	digital_root;
	.scl	2;
	.type	32;
	.endef
	.globl	digital_root                    # -- Begin function digital_root
	.p2align	4
digital_root:                           # @digital_root
# %bb.0:
	cmpq	$10, %rcx
	jl	.LBB1_1
# %bb.2:
	xorl	%r9d, %r9d
	movabsq	$-3689348814741910323, %r8      # imm = 0xCCCCCCCCCCCCCCCD
	.p2align	4
.LBB1_3:                                # =>This Inner Loop Header: Depth=1
	movq	%rcx, %rax
	mulq	%r8
	shrq	$3, %rdx
	leaq	(%rdx,%rdx), %rax
	leaq	(%rax,%rax,4), %rax
	movq	%rcx, %r10
	subq	%rax, %r10
	movq	%r9, %rax
	addq	%r10, %rax
	movq	%rax, %r9
	cmpq	$9, %rcx
	movq	%rdx, %rcx
	ja	.LBB1_3
# %bb.4:                                #   in Loop: Header=BB1_3 Depth=1
	movl	$0, %r9d
	movq	%rax, %rcx
	cmpq	$9, %rax
	ja	.LBB1_3
# %bb.5:
	retq
.LBB1_1:
	movq	%rcx, %rax
	retq
                                        # -- End function
	.def	sum_digital_roots;
	.scl	2;
	.type	32;
	.endef
	.globl	sum_digital_roots               # -- Begin function sum_digital_roots
	.p2align	4
sum_digital_roots:                      # @sum_digital_roots
.seh_proc sum_digital_roots
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	.seh_endprologue
	testq	%rcx, %rcx
	jle	.LBB2_1
# %bb.3:
	movl	$1, %r10d
	xorl	%r8d, %r8d
	movabsq	$-3689348814741910323, %r11     # imm = 0xCCCCCCCCCCCCCCCD
	jmp	.LBB2_4
	.p2align	4
.LBB2_8:                                #   in Loop: Header=BB2_4 Depth=1
	addq	%rax, %r8
	cmpq	%rcx, %r10
	leaq	1(%r10), %r10
	je	.LBB2_2
.LBB2_4:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB2_6 Depth 2
	movq	%r10, %rax
	cmpq	$10, %r10
	jb	.LBB2_8
# %bb.5:                                #   in Loop: Header=BB2_4 Depth=1
	xorl	%esi, %esi
	movq	%r10, %r9
	.p2align	4
.LBB2_6:                                #   Parent Loop BB2_4 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%r9, %rax
	mulq	%r11
	shrq	$3, %rdx
	leaq	(%rdx,%rdx), %rax
	leaq	(%rax,%rax,4), %rax
	movq	%r9, %rdi
	subq	%rax, %rdi
	movq	%rsi, %rax
	addq	%rdi, %rax
	movq	%rax, %rsi
	cmpq	$9, %r9
	movq	%rdx, %r9
	ja	.LBB2_6
# %bb.7:                                #   in Loop: Header=BB2_6 Depth=2
	movl	$0, %esi
	movq	%rax, %r9
	cmpq	$9, %rax
	ja	.LBB2_6
	jmp	.LBB2_8
.LBB2_1:
	xorl	%r8d, %r8d
.LBB2_2:
	movq	%r8, %rax
	.seh_startepilogue
	popq	%rdi
	popq	%rsi
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	main;
	.scl	2;
	.type	32;
	.endef
	.globl	main                            # -- Begin function main
	.p2align	4
main:                                   # @main
.seh_proc main
# %bb.0:
	pushq	%rbp
	.seh_pushreg %rbp
	pushq	%r15
	.seh_pushreg %r15
	pushq	%r14
	.seh_pushreg %r14
	pushq	%r13
	.seh_pushreg %r13
	pushq	%r12
	.seh_pushreg %r12
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	pushq	%rbx
	.seh_pushreg %rbx
	subq	$56, %rsp
	.seh_stackalloc 56
	leaq	48(%rsp), %rbp
	.seh_setframe %rbp, 48
	.seh_endprologue
	movl	$1, %edi
	xorl	%esi, %esi
	callq	__main
	movabsq	$-3689348814741910323, %r9      # imm = 0xCCCCCCCCCCCCCCCD
	jmp	.LBB3_1
	.p2align	4
.LBB3_5:                                #   in Loop: Header=BB3_1 Depth=1
	addq	%rax, %rsi
	cmpq	$100000, %rdi                   # imm = 0x186A0
	leaq	1(%rdi), %rdi
	je	.LBB3_6
.LBB3_1:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB3_3 Depth 2
	movq	%rdi, %rax
	cmpq	$10, %rdi
	jb	.LBB3_5
# %bb.2:                                #   in Loop: Header=BB3_1 Depth=1
	xorl	%r8d, %r8d
	movq	%rdi, %rcx
	.p2align	4
.LBB3_3:                                #   Parent Loop BB3_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%rcx, %rax
	mulq	%r9
	shrq	$3, %rdx
	leaq	(%rdx,%rdx), %rax
	leaq	(%rax,%rax,4), %rax
	movq	%rcx, %r10
	subq	%rax, %r10
	movq	%r8, %rax
	addq	%r10, %rax
	movq	%rax, %r8
	cmpq	$9, %rcx
	movq	%rdx, %rcx
	ja	.LBB3_3
# %bb.4:                                #   in Loop: Header=BB3_3 Depth=2
	movl	$0, %r8d
	movq	%rax, %rcx
	cmpq	$9, %rax
	ja	.LBB3_3
	jmp	.LBB3_5
.LBB3_6:
	movl	$1, %r8d
	xorl	%edi, %edi
	jmp	.LBB3_7
	.p2align	4
.LBB3_11:                               #   in Loop: Header=BB3_7 Depth=1
	addq	%rax, %rdi
	cmpq	$100000, %r8                    # imm = 0x186A0
	leaq	1(%r8), %r8
	je	.LBB3_12
.LBB3_7:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB3_9 Depth 2
	movq	%r8, %rax
	cmpq	$10, %r8
	jb	.LBB3_11
# %bb.8:                                #   in Loop: Header=BB3_7 Depth=1
	xorl	%r11d, %r11d
	movq	%r8, %rcx
	.p2align	4
.LBB3_9:                                #   Parent Loop BB3_7 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%rcx, %rax
	mulq	%r9
	shrq	$3, %rdx
	leaq	(%rdx,%rdx), %rax
	leaq	(%rax,%rax,4), %rax
	movq	%rcx, %r10
	subq	%rax, %r10
	movq	%r11, %rax
	addq	%r10, %rax
	movq	%rax, %r11
	cmpq	$9, %rcx
	movq	%rdx, %rcx
	ja	.LBB3_9
# %bb.10:                               #   in Loop: Header=BB3_9 Depth=2
	movl	$0, %r11d
	movq	%rax, %rcx
	cmpq	$9, %rax
	ja	.LBB3_9
	jmp	.LBB3_11
.LBB3_12:
	movq	%rsi, -16(%rbp)                 # 8-byte Spill
	movl	$1, %r8d
	xorl	%r11d, %r11d
	jmp	.LBB3_13
	.p2align	4
.LBB3_17:                               #   in Loop: Header=BB3_13 Depth=1
	addq	%rax, %r11
	cmpq	$100000, %r8                    # imm = 0x186A0
	leaq	1(%r8), %r8
	je	.LBB3_18
.LBB3_13:                               # =>This Loop Header: Depth=1
                                        #     Child Loop BB3_15 Depth 2
	movq	%r8, %rax
	cmpq	$10, %r8
	jb	.LBB3_17
# %bb.14:                               #   in Loop: Header=BB3_13 Depth=1
	xorl	%esi, %esi
	movq	%r8, %rcx
	.p2align	4
.LBB3_15:                               #   Parent Loop BB3_13 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%rcx, %rax
	mulq	%r9
	shrq	$3, %rdx
	leaq	(%rdx,%rdx), %rax
	leaq	(%rax,%rax,4), %rax
	movq	%rcx, %r10
	subq	%rax, %r10
	movq	%rsi, %rax
	addq	%r10, %rax
	movq	%rax, %rsi
	cmpq	$9, %rcx
	movq	%rdx, %rcx
	ja	.LBB3_15
# %bb.16:                               #   in Loop: Header=BB3_15 Depth=2
	movl	$0, %esi
	movq	%rax, %rcx
	cmpq	$9, %rax
	ja	.LBB3_15
	jmp	.LBB3_17
.LBB3_18:
	movq	%rdi, -8(%rbp)                  # 8-byte Spill
	movl	$1, %r8d
	xorl	%edi, %edi
	jmp	.LBB3_19
	.p2align	4
.LBB3_23:                               #   in Loop: Header=BB3_19 Depth=1
	addq	%rax, %rdi
	cmpq	$100000, %r8                    # imm = 0x186A0
	leaq	1(%r8), %r8
	je	.LBB3_24
.LBB3_19:                               # =>This Loop Header: Depth=1
                                        #     Child Loop BB3_21 Depth 2
	movq	%r8, %rax
	cmpq	$10, %r8
	jb	.LBB3_23
# %bb.20:                               #   in Loop: Header=BB3_19 Depth=1
	xorl	%esi, %esi
	movq	%r8, %rcx
	.p2align	4
.LBB3_21:                               #   Parent Loop BB3_19 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%rcx, %rax
	mulq	%r9
	shrq	$3, %rdx
	leaq	(%rdx,%rdx), %rax
	leaq	(%rax,%rax,4), %rax
	movq	%rcx, %r10
	subq	%rax, %r10
	movq	%rsi, %rax
	addq	%r10, %rax
	movq	%rax, %rsi
	cmpq	$9, %rcx
	movq	%rdx, %rcx
	ja	.LBB3_21
# %bb.22:                               #   in Loop: Header=BB3_21 Depth=2
	movl	$0, %esi
	movq	%rax, %rcx
	cmpq	$9, %rax
	ja	.LBB3_21
	jmp	.LBB3_23
.LBB3_24:
	movl	$1, %r8d
	xorl	%ebx, %ebx
	jmp	.LBB3_25
	.p2align	4
.LBB3_29:                               #   in Loop: Header=BB3_25 Depth=1
	addq	%rax, %rbx
	cmpq	$100000, %r8                    # imm = 0x186A0
	leaq	1(%r8), %r8
	je	.LBB3_30
.LBB3_25:                               # =>This Loop Header: Depth=1
                                        #     Child Loop BB3_27 Depth 2
	movq	%r8, %rax
	cmpq	$10, %r8
	jb	.LBB3_29
# %bb.26:                               #   in Loop: Header=BB3_25 Depth=1
	xorl	%esi, %esi
	movq	%r8, %rcx
	.p2align	4
.LBB3_27:                               #   Parent Loop BB3_25 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%rcx, %rax
	mulq	%r9
	shrq	$3, %rdx
	leaq	(%rdx,%rdx), %rax
	leaq	(%rax,%rax,4), %rax
	movq	%rcx, %r10
	subq	%rax, %r10
	movq	%rsi, %rax
	addq	%r10, %rax
	movq	%rax, %rsi
	cmpq	$9, %rcx
	movq	%rdx, %rcx
	ja	.LBB3_27
# %bb.28:                               #   in Loop: Header=BB3_27 Depth=2
	movl	$0, %esi
	movq	%rax, %rcx
	cmpq	$9, %rax
	ja	.LBB3_27
	jmp	.LBB3_29
.LBB3_30:
	movl	$1, %r8d
	xorl	%r14d, %r14d
	jmp	.LBB3_31
	.p2align	4
.LBB3_35:                               #   in Loop: Header=BB3_31 Depth=1
	addq	%rax, %r14
	cmpq	$100000, %r8                    # imm = 0x186A0
	leaq	1(%r8), %r8
	je	.LBB3_36
.LBB3_31:                               # =>This Loop Header: Depth=1
                                        #     Child Loop BB3_33 Depth 2
	movq	%r8, %rax
	cmpq	$10, %r8
	jb	.LBB3_35
# %bb.32:                               #   in Loop: Header=BB3_31 Depth=1
	xorl	%esi, %esi
	movq	%r8, %rcx
	.p2align	4
.LBB3_33:                               #   Parent Loop BB3_31 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%rcx, %rax
	mulq	%r9
	shrq	$3, %rdx
	leaq	(%rdx,%rdx), %rax
	leaq	(%rax,%rax,4), %rax
	movq	%rcx, %r10
	subq	%rax, %r10
	movq	%rsi, %rax
	addq	%r10, %rax
	movq	%rax, %rsi
	cmpq	$9, %rcx
	movq	%rdx, %rcx
	ja	.LBB3_33
# %bb.34:                               #   in Loop: Header=BB3_33 Depth=2
	movl	$0, %esi
	movq	%rax, %rcx
	cmpq	$9, %rax
	ja	.LBB3_33
	jmp	.LBB3_35
.LBB3_36:
	movl	$1, %r8d
	xorl	%r15d, %r15d
	jmp	.LBB3_37
	.p2align	4
.LBB3_41:                               #   in Loop: Header=BB3_37 Depth=1
	addq	%rax, %r15
	cmpq	$100000, %r8                    # imm = 0x186A0
	leaq	1(%r8), %r8
	je	.LBB3_42
.LBB3_37:                               # =>This Loop Header: Depth=1
                                        #     Child Loop BB3_39 Depth 2
	movq	%r8, %rax
	cmpq	$10, %r8
	jb	.LBB3_41
# %bb.38:                               #   in Loop: Header=BB3_37 Depth=1
	xorl	%esi, %esi
	movq	%r8, %rcx
	.p2align	4
.LBB3_39:                               #   Parent Loop BB3_37 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%rcx, %rax
	mulq	%r9
	shrq	$3, %rdx
	leaq	(%rdx,%rdx), %rax
	leaq	(%rax,%rax,4), %rax
	movq	%rcx, %r10
	subq	%rax, %r10
	movq	%rsi, %rax
	addq	%r10, %rax
	movq	%rax, %rsi
	cmpq	$9, %rcx
	movq	%rdx, %rcx
	ja	.LBB3_39
# %bb.40:                               #   in Loop: Header=BB3_39 Depth=2
	movl	$0, %esi
	movq	%rax, %rcx
	cmpq	$9, %rax
	ja	.LBB3_39
	jmp	.LBB3_41
.LBB3_42:
	movl	$1, %r8d
	xorl	%r12d, %r12d
	jmp	.LBB3_43
	.p2align	4
.LBB3_47:                               #   in Loop: Header=BB3_43 Depth=1
	addq	%rax, %r12
	cmpq	$100000, %r8                    # imm = 0x186A0
	leaq	1(%r8), %r8
	je	.LBB3_48
.LBB3_43:                               # =>This Loop Header: Depth=1
                                        #     Child Loop BB3_45 Depth 2
	movq	%r8, %rax
	cmpq	$10, %r8
	jb	.LBB3_47
# %bb.44:                               #   in Loop: Header=BB3_43 Depth=1
	xorl	%esi, %esi
	movq	%r8, %rcx
	.p2align	4
.LBB3_45:                               #   Parent Loop BB3_43 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%rcx, %rax
	mulq	%r9
	shrq	$3, %rdx
	leaq	(%rdx,%rdx), %rax
	leaq	(%rax,%rax,4), %rax
	movq	%rcx, %r10
	subq	%rax, %r10
	movq	%rsi, %rax
	addq	%r10, %rax
	movq	%rax, %rsi
	cmpq	$9, %rcx
	movq	%rdx, %rcx
	ja	.LBB3_45
# %bb.46:                               #   in Loop: Header=BB3_45 Depth=2
	movl	$0, %esi
	movq	%rax, %rcx
	cmpq	$9, %rax
	ja	.LBB3_45
	jmp	.LBB3_47
.LBB3_48:
	movq	%r11, (%rbp)                    # 8-byte Spill
	movl	$1, %r8d
	xorl	%r13d, %r13d
	jmp	.LBB3_49
	.p2align	4
.LBB3_53:                               #   in Loop: Header=BB3_49 Depth=1
	addq	%rax, %r13
	cmpq	$100000, %r8                    # imm = 0x186A0
	leaq	1(%r8), %r8
	je	.LBB3_54
.LBB3_49:                               # =>This Loop Header: Depth=1
                                        #     Child Loop BB3_51 Depth 2
	movq	%r8, %rax
	cmpq	$10, %r8
	jb	.LBB3_53
# %bb.50:                               #   in Loop: Header=BB3_49 Depth=1
	xorl	%esi, %esi
	movq	%r8, %rcx
	.p2align	4
.LBB3_51:                               #   Parent Loop BB3_49 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%rcx, %rax
	mulq	%r9
	shrq	$3, %rdx
	leaq	(%rdx,%rdx), %rax
	leaq	(%rax,%rax,4), %rax
	movq	%rcx, %r10
	subq	%rax, %r10
	movq	%rsi, %rax
	addq	%r10, %rax
	movq	%rax, %rsi
	cmpq	$9, %rcx
	movq	%rdx, %rcx
	ja	.LBB3_51
# %bb.52:                               #   in Loop: Header=BB3_51 Depth=2
	movl	$0, %esi
	movq	%rax, %rcx
	cmpq	$9, %rax
	ja	.LBB3_51
	jmp	.LBB3_53
.LBB3_54:
	movl	$1, %r11d
	xorl	%r8d, %r8d
	jmp	.LBB3_55
	.p2align	4
.LBB3_59:                               #   in Loop: Header=BB3_55 Depth=1
	addq	%rax, %r8
	cmpq	$100000, %r11                   # imm = 0x186A0
	leaq	1(%r11), %r11
	je	.LBB3_60
.LBB3_55:                               # =>This Loop Header: Depth=1
                                        #     Child Loop BB3_57 Depth 2
	movq	%r11, %rax
	cmpq	$10, %r11
	jb	.LBB3_59
# %bb.56:                               #   in Loop: Header=BB3_55 Depth=1
	xorl	%r10d, %r10d
	movq	%r11, %rsi
	.p2align	4
.LBB3_57:                               #   Parent Loop BB3_55 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%rsi, %rax
	mulq	%r9
	shrq	$3, %rdx
	leaq	(%rdx,%rdx), %rax
	leaq	(%rax,%rax,4), %rax
	movq	%rsi, %rcx
	subq	%rax, %rcx
	movq	%r10, %rax
	addq	%rcx, %rax
	movq	%rax, %r10
	cmpq	$9, %rsi
	movq	%rdx, %rsi
	ja	.LBB3_57
# %bb.58:                               #   in Loop: Header=BB3_57 Depth=2
	movl	$0, %r10d
	movq	%rax, %rsi
	cmpq	$9, %rax
	ja	.LBB3_57
	jmp	.LBB3_59
.LBB3_60:
	movq	-8(%rbp), %rax                  # 8-byte Reload
	addq	-16(%rbp), %rax                 # 8-byte Folded Reload
	movq	(%rbp), %rcx                    # 8-byte Reload
	addq	%rax, %rcx
	addq	%rcx, %rdi
	addq	%rdi, %rbx
	addq	%rbx, %r14
	addq	%r14, %r15
	addq	%r15, %r12
	addq	%r12, %r13
	addq	%r13, %r8
	leaq	.L.str(%rip), %rcx
	movq	%r8, %rdx
	callq	printf
	xorl	%eax, %eax
	.seh_startepilogue
	addq	$56, %rsp
	popq	%rbx
	popq	%rdi
	popq	%rsi
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	popq	%rbp
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.section	.rdata,"dr"
.L.str:                                 # @.str
	.asciz	"%lld\n"

	.section	.debug$S,"dr"
	.p2align	2, 0x0
	.long	4                               # Debug section magic
	.long	241
	.long	.Ltmp1-.Ltmp0                   # Subsection size
.Ltmp0:
	.short	.Ltmp3-.Ltmp2                   # Record length
.Ltmp2:
	.short	4353                            # Record kind: S_OBJNAME
	.long	0                               # Signature
	.byte	0                               # Object name
	.p2align	2, 0x0
.Ltmp3:
	.short	.Ltmp5-.Ltmp4                   # Record length
.Ltmp4:
	.short	4412                            # Record kind: S_COMPILE3
	.long	0                               # Flags and language
	.short	208                             # CPUType
	.short	21                              # Frontend version
	.short	1
	.short	8
	.short	0
	.short	21018                           # Backend version
	.short	0
	.short	0
	.short	0
	.asciz	"clang version 21.1.8"          # Null-terminated compiler version string
	.p2align	2, 0x0
.Ltmp5:
.Ltmp1:
	.p2align	2, 0x0
	.addrsig
