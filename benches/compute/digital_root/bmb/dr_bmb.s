	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
@feat.00 = 0
	.file	"dr_bmb.ll"
	.def	sum_digital_roots;
	.scl	2;
	.type	32;
	.endef
	.text
	.globl	sum_digital_roots               # -- Begin function sum_digital_roots
	.p2align	4
sum_digital_roots:                      # @sum_digital_roots
# %bb.0:                                # %alloca_entry
	pushq	%rsi
	pushq	%rdi
	testq	%rcx, %rcx
	jle	.LBB0_1
# %bb.2:                                # %bb_while_cond_0.i.preheader.preheader
	movl	$1, %r10d
	xorl	%r8d, %r8d
	movabsq	$-3689348814741910323, %r11     # imm = 0xCCCCCCCCCCCCCCCD
	jmp	.LBB0_3
	.p2align	4
.LBB0_7:                                # %digital_root.exit
                                        #   in Loop: Header=BB0_3 Depth=1
	addq	%rax, %r8
	cmpq	%rcx, %r10
	leaq	1(%r10), %r10
	je	.LBB0_8
.LBB0_3:                                # %bb_while_cond_0.i.preheader
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_6 Depth 2
	movq	%r10, %rax
	cmpq	$10, %r10
	jb	.LBB0_7
# %bb.4:                                # %bb_while_body_1.i.i.preheader
                                        #   in Loop: Header=BB0_3 Depth=1
	xorl	%esi, %esi
	movq	%r10, %r9
	.p2align	4
.LBB0_6:                                # %bb_while_body_1.i.i
                                        #   Parent Loop BB0_3 Depth=1
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
	cmpq	$10, %r9
	movq	%rdx, %r9
	jae	.LBB0_6
# %bb.5:                                # %bb_while_cond_0.i.loopexit
                                        #   in Loop: Header=BB0_6 Depth=2
	movl	$0, %esi
	movq	%rax, %r9
	cmpq	$10, %rax
	jae	.LBB0_6
	jmp	.LBB0_7
.LBB0_1:
	xorl	%r8d, %r8d
.LBB0_8:                                # %bb_while_exit_2
	movq	%r8, %rax
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
# %bb.0:                                # %alloca_entry
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
	pushq	%rbp
	.seh_pushreg %rbp
	pushq	%rbx
	.seh_pushreg %rbx
	subq	$56, %rsp
	.seh_stackalloc 56
	.seh_endprologue
	movl	$1, %r8d
	xorl	%esi, %esi
	movabsq	$-3689348814741910323, %r10     # imm = 0xCCCCCCCCCCCCCCCD
	jmp	.LBB1_1
	.p2align	4
.LBB1_5:                                # %digital_root.exit.i
                                        #   in Loop: Header=BB1_1 Depth=1
	addq	%rax, %rsi
	cmpq	$100000, %r8                    # imm = 0x186A0
	leaq	1(%r8), %r8
	je	.LBB1_6
.LBB1_1:                                # %bb_while_cond_0.i.preheader.i
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_4 Depth 2
	movq	%r8, %rax
	cmpq	$10, %r8
	jb	.LBB1_5
# %bb.2:                                # %bb_while_body_1.i.i.i.preheader
                                        #   in Loop: Header=BB1_1 Depth=1
	xorl	%r11d, %r11d
	movq	%r8, %rcx
	.p2align	4
.LBB1_4:                                # %bb_while_body_1.i.i.i
                                        #   Parent Loop BB1_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%rcx, %rax
	mulq	%r10
	shrq	$3, %rdx
	leaq	(%rdx,%rdx), %rax
	leaq	(%rax,%rax,4), %rax
	movq	%rcx, %r9
	subq	%rax, %r9
	movq	%r11, %rax
	addq	%r9, %rax
	movq	%rax, %r11
	cmpq	$10, %rcx
	movq	%rdx, %rcx
	jae	.LBB1_4
# %bb.3:                                # %bb_while_cond_0.i.loopexit.i
                                        #   in Loop: Header=BB1_4 Depth=2
	movl	$0, %r11d
	movq	%rax, %rcx
	cmpq	$10, %rax
	jae	.LBB1_4
	jmp	.LBB1_5
.LBB1_6:                                # %bb_while_cond_0.i.preheader.i.1.preheader
	movq	%rsi, 48(%rsp)                  # 8-byte Spill
	movl	$1, %r8d
	xorl	%r11d, %r11d
	jmp	.LBB1_7
	.p2align	4
.LBB1_11:                               # %digital_root.exit.i.1
                                        #   in Loop: Header=BB1_7 Depth=1
	addq	%rax, %r11
	cmpq	$100000, %r8                    # imm = 0x186A0
	leaq	1(%r8), %r8
	je	.LBB1_12
.LBB1_7:                                # %bb_while_cond_0.i.preheader.i.1
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_9 Depth 2
	movq	%r8, %rax
	cmpq	$10, %r8
	jb	.LBB1_11
# %bb.8:                                # %bb_while_body_1.i.i.i.1.preheader
                                        #   in Loop: Header=BB1_7 Depth=1
	xorl	%esi, %esi
	movq	%r8, %rcx
	.p2align	4
.LBB1_9:                                # %bb_while_body_1.i.i.i.1
                                        #   Parent Loop BB1_7 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%rcx, %rax
	mulq	%r10
	shrq	$3, %rdx
	leaq	(%rdx,%rdx), %rax
	leaq	(%rax,%rax,4), %rax
	movq	%rcx, %r9
	subq	%rax, %r9
	movq	%rsi, %rax
	addq	%r9, %rax
	movq	%rax, %rsi
	cmpq	$9, %rcx
	movq	%rdx, %rcx
	ja	.LBB1_9
# %bb.10:                               # %bb_while_cond_0.i.loopexit.i.1
                                        #   in Loop: Header=BB1_9 Depth=2
	movl	$0, %esi
	movq	%rax, %rcx
	cmpq	$9, %rax
	ja	.LBB1_9
	jmp	.LBB1_11
.LBB1_12:                               # %bb_while_cond_0.i.preheader.i.2.preheader
	movl	$1, %r8d
	xorl	%esi, %esi
	jmp	.LBB1_13
	.p2align	4
.LBB1_17:                               # %digital_root.exit.i.2
                                        #   in Loop: Header=BB1_13 Depth=1
	addq	%rax, %rsi
	cmpq	$100000, %r8                    # imm = 0x186A0
	leaq	1(%r8), %r8
	je	.LBB1_18
.LBB1_13:                               # %bb_while_cond_0.i.preheader.i.2
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_15 Depth 2
	movq	%r8, %rax
	cmpq	$10, %r8
	jb	.LBB1_17
# %bb.14:                               # %bb_while_body_1.i.i.i.2.preheader
                                        #   in Loop: Header=BB1_13 Depth=1
	xorl	%edi, %edi
	movq	%r8, %rcx
	.p2align	4
.LBB1_15:                               # %bb_while_body_1.i.i.i.2
                                        #   Parent Loop BB1_13 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%rcx, %rax
	mulq	%r10
	shrq	$3, %rdx
	leaq	(%rdx,%rdx), %rax
	leaq	(%rax,%rax,4), %rax
	movq	%rcx, %r9
	subq	%rax, %r9
	movq	%rdi, %rax
	addq	%r9, %rax
	movq	%rax, %rdi
	cmpq	$9, %rcx
	movq	%rdx, %rcx
	ja	.LBB1_15
# %bb.16:                               # %bb_while_cond_0.i.loopexit.i.2
                                        #   in Loop: Header=BB1_15 Depth=2
	movl	$0, %edi
	movq	%rax, %rcx
	cmpq	$9, %rax
	ja	.LBB1_15
	jmp	.LBB1_17
.LBB1_18:                               # %bb_while_cond_0.i.preheader.i.3.preheader
	movl	$1, %r8d
	xorl	%edi, %edi
	jmp	.LBB1_19
	.p2align	4
.LBB1_23:                               # %digital_root.exit.i.3
                                        #   in Loop: Header=BB1_19 Depth=1
	addq	%rax, %rdi
	cmpq	$100000, %r8                    # imm = 0x186A0
	leaq	1(%r8), %r8
	je	.LBB1_24
.LBB1_19:                               # %bb_while_cond_0.i.preheader.i.3
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_21 Depth 2
	movq	%r8, %rax
	cmpq	$10, %r8
	jb	.LBB1_23
# %bb.20:                               # %bb_while_body_1.i.i.i.3.preheader
                                        #   in Loop: Header=BB1_19 Depth=1
	xorl	%ebx, %ebx
	movq	%r8, %rcx
	.p2align	4
.LBB1_21:                               # %bb_while_body_1.i.i.i.3
                                        #   Parent Loop BB1_19 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%rcx, %rax
	mulq	%r10
	shrq	$3, %rdx
	leaq	(%rdx,%rdx), %rax
	leaq	(%rax,%rax,4), %rax
	movq	%rcx, %r9
	subq	%rax, %r9
	movq	%rbx, %rax
	addq	%r9, %rax
	movq	%rax, %rbx
	cmpq	$9, %rcx
	movq	%rdx, %rcx
	ja	.LBB1_21
# %bb.22:                               # %bb_while_cond_0.i.loopexit.i.3
                                        #   in Loop: Header=BB1_21 Depth=2
	movl	$0, %ebx
	movq	%rax, %rcx
	cmpq	$9, %rax
	ja	.LBB1_21
	jmp	.LBB1_23
.LBB1_24:                               # %bb_while_cond_0.i.preheader.i.4.preheader
	movl	$1, %r8d
	xorl	%ebx, %ebx
	jmp	.LBB1_25
	.p2align	4
.LBB1_29:                               # %digital_root.exit.i.4
                                        #   in Loop: Header=BB1_25 Depth=1
	addq	%rax, %rbx
	cmpq	$100000, %r8                    # imm = 0x186A0
	leaq	1(%r8), %r8
	je	.LBB1_30
.LBB1_25:                               # %bb_while_cond_0.i.preheader.i.4
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_27 Depth 2
	movq	%r8, %rax
	cmpq	$10, %r8
	jb	.LBB1_29
# %bb.26:                               # %bb_while_body_1.i.i.i.4.preheader
                                        #   in Loop: Header=BB1_25 Depth=1
	xorl	%r14d, %r14d
	movq	%r8, %rcx
	.p2align	4
.LBB1_27:                               # %bb_while_body_1.i.i.i.4
                                        #   Parent Loop BB1_25 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%rcx, %rax
	mulq	%r10
	shrq	$3, %rdx
	leaq	(%rdx,%rdx), %rax
	leaq	(%rax,%rax,4), %rax
	movq	%rcx, %r9
	subq	%rax, %r9
	movq	%r14, %rax
	addq	%r9, %rax
	movq	%rax, %r14
	cmpq	$9, %rcx
	movq	%rdx, %rcx
	ja	.LBB1_27
# %bb.28:                               # %bb_while_cond_0.i.loopexit.i.4
                                        #   in Loop: Header=BB1_27 Depth=2
	movl	$0, %r14d
	movq	%rax, %rcx
	cmpq	$9, %rax
	ja	.LBB1_27
	jmp	.LBB1_29
.LBB1_30:                               # %bb_while_cond_0.i.preheader.i.5.preheader
	movl	$1, %r8d
	xorl	%r14d, %r14d
	jmp	.LBB1_31
	.p2align	4
.LBB1_35:                               # %digital_root.exit.i.5
                                        #   in Loop: Header=BB1_31 Depth=1
	addq	%rax, %r14
	cmpq	$100000, %r8                    # imm = 0x186A0
	leaq	1(%r8), %r8
	je	.LBB1_36
.LBB1_31:                               # %bb_while_cond_0.i.preheader.i.5
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_33 Depth 2
	movq	%r8, %rax
	cmpq	$10, %r8
	jb	.LBB1_35
# %bb.32:                               # %bb_while_body_1.i.i.i.5.preheader
                                        #   in Loop: Header=BB1_31 Depth=1
	xorl	%r15d, %r15d
	movq	%r8, %rcx
	.p2align	4
.LBB1_33:                               # %bb_while_body_1.i.i.i.5
                                        #   Parent Loop BB1_31 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%rcx, %rax
	mulq	%r10
	shrq	$3, %rdx
	leaq	(%rdx,%rdx), %rax
	leaq	(%rax,%rax,4), %rax
	movq	%rcx, %r9
	subq	%rax, %r9
	movq	%r15, %rax
	addq	%r9, %rax
	movq	%rax, %r15
	cmpq	$9, %rcx
	movq	%rdx, %rcx
	ja	.LBB1_33
# %bb.34:                               # %bb_while_cond_0.i.loopexit.i.5
                                        #   in Loop: Header=BB1_33 Depth=2
	movl	$0, %r15d
	movq	%rax, %rcx
	cmpq	$9, %rax
	ja	.LBB1_33
	jmp	.LBB1_35
.LBB1_36:                               # %bb_while_cond_0.i.preheader.i.6.preheader
	movl	$1, %r15d
	xorl	%ecx, %ecx
	jmp	.LBB1_37
	.p2align	4
.LBB1_41:                               # %digital_root.exit.i.6
                                        #   in Loop: Header=BB1_37 Depth=1
	addq	%rax, %rcx
	cmpq	$100000, %r15                   # imm = 0x186A0
	leaq	1(%r15), %r15
	je	.LBB1_42
.LBB1_37:                               # %bb_while_cond_0.i.preheader.i.6
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_39 Depth 2
	movq	%r15, %rax
	cmpq	$10, %r15
	jb	.LBB1_41
# %bb.38:                               # %bb_while_body_1.i.i.i.6.preheader
                                        #   in Loop: Header=BB1_37 Depth=1
	xorl	%r12d, %r12d
	movq	%r15, %r8
	.p2align	4
.LBB1_39:                               # %bb_while_body_1.i.i.i.6
                                        #   Parent Loop BB1_37 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%r8, %rax
	mulq	%r10
	shrq	$3, %rdx
	leaq	(%rdx,%rdx), %rax
	leaq	(%rax,%rax,4), %rax
	movq	%r8, %r9
	subq	%rax, %r9
	movq	%r12, %rax
	addq	%r9, %rax
	movq	%rax, %r12
	cmpq	$9, %r8
	movq	%rdx, %r8
	ja	.LBB1_39
# %bb.40:                               # %bb_while_cond_0.i.loopexit.i.6
                                        #   in Loop: Header=BB1_39 Depth=2
	movl	$0, %r12d
	movq	%rax, %r8
	cmpq	$9, %rax
	ja	.LBB1_39
	jmp	.LBB1_41
.LBB1_42:                               # %bb_while_cond_0.i.preheader.i.7.preheader
	movl	$1, %r12d
	xorl	%r15d, %r15d
	jmp	.LBB1_43
	.p2align	4
.LBB1_47:                               # %digital_root.exit.i.7
                                        #   in Loop: Header=BB1_43 Depth=1
	addq	%rax, %r15
	cmpq	$100000, %r12                   # imm = 0x186A0
	leaq	1(%r12), %r12
	je	.LBB1_48
.LBB1_43:                               # %bb_while_cond_0.i.preheader.i.7
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_45 Depth 2
	movq	%r12, %rax
	cmpq	$10, %r12
	jb	.LBB1_47
# %bb.44:                               # %bb_while_body_1.i.i.i.7.preheader
                                        #   in Loop: Header=BB1_43 Depth=1
	xorl	%r13d, %r13d
	movq	%r12, %r8
	.p2align	4
.LBB1_45:                               # %bb_while_body_1.i.i.i.7
                                        #   Parent Loop BB1_43 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%r8, %rax
	mulq	%r10
	shrq	$3, %rdx
	leaq	(%rdx,%rdx), %rax
	leaq	(%rax,%rax,4), %rax
	movq	%r8, %r9
	subq	%rax, %r9
	movq	%r13, %rax
	addq	%r9, %rax
	movq	%rax, %r13
	cmpq	$9, %r8
	movq	%rdx, %r8
	ja	.LBB1_45
# %bb.46:                               # %bb_while_cond_0.i.loopexit.i.7
                                        #   in Loop: Header=BB1_45 Depth=2
	movl	$0, %r13d
	movq	%rax, %r8
	cmpq	$9, %rax
	ja	.LBB1_45
	jmp	.LBB1_47
.LBB1_48:                               # %bb_while_cond_0.i.preheader.i.8.preheader
	movq	%r11, 40(%rsp)                  # 8-byte Spill
	movl	$1, %r13d
	xorl	%r12d, %r12d
	jmp	.LBB1_49
	.p2align	4
.LBB1_53:                               # %digital_root.exit.i.8
                                        #   in Loop: Header=BB1_49 Depth=1
	addq	%rax, %r12
	cmpq	$100000, %r13                   # imm = 0x186A0
	leaq	1(%r13), %r13
	je	.LBB1_54
.LBB1_49:                               # %bb_while_cond_0.i.preheader.i.8
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_51 Depth 2
	movq	%r13, %rax
	cmpq	$10, %r13
	jb	.LBB1_53
# %bb.50:                               # %bb_while_body_1.i.i.i.8.preheader
                                        #   in Loop: Header=BB1_49 Depth=1
	xorl	%ebp, %ebp
	movq	%r13, %r8
	.p2align	4
.LBB1_51:                               # %bb_while_body_1.i.i.i.8
                                        #   Parent Loop BB1_49 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%r8, %rax
	mulq	%r10
	shrq	$3, %rdx
	leaq	(%rdx,%rdx), %rax
	leaq	(%rax,%rax,4), %rax
	movq	%r8, %r9
	subq	%rax, %r9
	movq	%rbp, %rax
	addq	%r9, %rax
	movq	%rax, %rbp
	cmpq	$9, %r8
	movq	%rdx, %r8
	ja	.LBB1_51
# %bb.52:                               # %bb_while_cond_0.i.loopexit.i.8
                                        #   in Loop: Header=BB1_51 Depth=2
	movl	$0, %ebp
	movq	%rax, %r8
	cmpq	$9, %rax
	ja	.LBB1_51
	jmp	.LBB1_53
.LBB1_54:                               # %bb_while_cond_0.i.preheader.i.9.preheader
	movl	$1, %r11d
	xorl	%r13d, %r13d
	jmp	.LBB1_55
	.p2align	4
.LBB1_59:                               # %digital_root.exit.i.9
                                        #   in Loop: Header=BB1_55 Depth=1
	addq	%rax, %r13
	cmpq	$100000, %r11                   # imm = 0x186A0
	leaq	1(%r11), %r11
	je	.LBB1_60
.LBB1_55:                               # %bb_while_cond_0.i.preheader.i.9
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB1_57 Depth 2
	movq	%r11, %rax
	cmpq	$10, %r11
	jb	.LBB1_59
# %bb.56:                               # %bb_while_body_1.i.i.i.9.preheader
                                        #   in Loop: Header=BB1_55 Depth=1
	xorl	%r9d, %r9d
	movq	%r11, %rbp
	.p2align	4
.LBB1_57:                               # %bb_while_body_1.i.i.i.9
                                        #   Parent Loop BB1_55 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movq	%rbp, %rax
	mulq	%r10
	shrq	$3, %rdx
	leaq	(%rdx,%rdx), %rax
	leaq	(%rax,%rax,4), %rax
	movq	%rbp, %r8
	subq	%rax, %r8
	movq	%r9, %rax
	addq	%r8, %rax
	movq	%rax, %r9
	cmpq	$9, %rbp
	movq	%rdx, %rbp
	ja	.LBB1_57
# %bb.58:                               # %bb_while_cond_0.i.loopexit.i.9
                                        #   in Loop: Header=BB1_57 Depth=2
	movl	$0, %r9d
	movq	%rax, %rbp
	cmpq	$9, %rax
	ja	.LBB1_57
	jmp	.LBB1_59
.LBB1_60:                               # %sum_digital_roots.exit.9
	movq	40(%rsp), %rax                  # 8-byte Reload
	addq	48(%rsp), %rax                  # 8-byte Folded Reload
	addq	%rsi, %rax
	addq	%rbx, %rdi
	addq	%r14, %rdi
	addq	%rax, %rdi
	addq	%r15, %rcx
	addq	%r12, %rcx
	addq	%r13, %rcx
	addq	%rdi, %rcx
	callq	println
	xorl	%eax, %eax
	.seh_startepilogue
	addq	$56, %rsp
	popq	%rbx
	popq	%rbp
	popq	%rdi
	popq	%rsi
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.addrsig
