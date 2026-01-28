	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
@feat.00 = 0
	.file	"json_parse_bmb.ll"
	.def	is_ws;
	.scl	2;
	.type	32;
	.endef
	.text
	.globl	is_ws                           # -- Begin function is_ws
	.p2align	4
is_ws:                                  # @is_ws
# %bb.0:                                # %alloca_entry
	cmpq	$32, %rcx
	sete	%dl
	leaq	-9(%rcx), %rax
	cmpq	$2, %rax
	setb	%r8b
	cmpq	$13, %rcx
	sete	%al
	orb	%dl, %al
	orb	%r8b, %al
	retq
                                        # -- End function
	.def	is_digit;
	.scl	2;
	.type	32;
	.endef
	.globl	is_digit                        # -- Begin function is_digit
	.p2align	4
is_digit:                               # @is_digit
# %bb.0:                                # %alloca_entry
	addq	$-48, %rcx
	cmpq	$10, %rcx
	setb	%al
	retq
                                        # -- End function
	.def	skip_ws;
	.scl	2;
	.type	32;
	.endef
	.globl	skip_ws                         # -- Begin function skip_ws
	.p2align	4
skip_ws:                                # @skip_ws
# %bb.0:                                # %alloca_entry
	movq	%rdx, %rax
	movq	8(%rcx), %rdx
	cmpq	%rdx, %rax
	jge	.LBB2_6
# %bb.1:                                # %bb_else_1.lr.ph
	movq	(%rcx), %rcx
	movabsq	$4294977024, %r8                # imm = 0x100002600
	.p2align	4
.LBB2_2:                                # %bb_else_1
                                        # =>This Inner Loop Header: Depth=1
	movzbl	(%rcx,%rax), %r9d
	cmpq	$32, %r9
	ja	.LBB2_6
# %bb.3:                                # %bb_else_1
                                        #   in Loop: Header=BB2_2 Depth=1
	btq	%r9, %r8
	jae	.LBB2_6
# %bb.4:                                # %bb_then_3
                                        #   in Loop: Header=BB2_2 Depth=1
	incq	%rax
	cmpq	%rax, %rdx
	jne	.LBB2_2
# %bb.5:
	movq	%rdx, %rax
.LBB2_6:                                # %bb_merge_2
	retq
                                        # -- End function
	.def	parse_number;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_number                    # -- Begin function parse_number
	.p2align	4
parse_number:                           # @parse_number
# %bb.0:                                # %alloca_entry
	movq	8(%rcx), %rax
	cmpq	%rax, %rdx
	jge	.LBB3_5
# %bb.1:                                # %bb_else_1.lr.ph
	movq	(%rcx), %rcx
	.p2align	4
.LBB3_2:                                # %bb_else_1
                                        # =>This Inner Loop Header: Depth=1
	movzbl	(%rcx,%rdx), %r9d
	leal	-48(%r9), %r10d
	cmpb	$9, %r10b
	ja	.LBB3_5
# %bb.3:                                # %bb_then_3
                                        #   in Loop: Header=BB3_2 Depth=1
	incq	%rdx
	leaq	(%r8,%r8,4), %r8
	leaq	(%r9,%r8,2), %r8
	addq	$-48, %r8
	cmpq	%rdx, %rax
	jne	.LBB3_2
# %bb.4:
	movq	%rax, %rdx
.LBB3_5:                                # %bb_merge_2
	imulq	$1000000, %rdx, %rax            # imm = 0xF4240
	addq	%r8, %rax
	retq
                                        # -- End function
	.def	find_close;
	.scl	2;
	.type	32;
	.endef
	.globl	find_close                      # -- Begin function find_close
	.p2align	4
find_close:                             # @find_close
# %bb.0:                                # %alloca_entry
	pushq	%rsi
	pushq	%rdi
	movq	%rdx, %rax
	movq	8(%rcx), %rdx
	cmpq	%rdx, %rax
	jge	.LBB4_5
# %bb.1:                                # %bb_else_1.lr.ph
	movq	(%rcx), %rcx
	movslq	56(%rsp), %r10
	movslq	%r9d, %r9
	movq	%r8, %r11
	.p2align	4
.LBB4_2:                                # %bb_else_1
                                        # =>This Inner Loop Header: Depth=1
	movzbl	(%rcx,%rax), %esi
	movq	%rsi, %rdi
	xorq	%r10, %rdi
	orq	%r11, %rdi
	je	.LBB4_5
# %bb.3:                                # %bb_else_4
                                        #   in Loop: Header=BB4_2 Depth=1
	leaq	1(%r11), %rdi
	decq	%r11
	cmpq	%r10, %rsi
	cmovneq	%r8, %r11
	cmpq	%r9, %rsi
	cmoveq	%rdi, %r11
	incq	%rax
	cmpq	%rax, %rdx
	jne	.LBB4_2
# %bb.4:
	movq	%rdx, %rax
.LBB4_5:                                # %bb_merge_2
	popq	%rdi
	popq	%rsi
	retq
                                        # -- End function
	.def	count_array;
	.scl	2;
	.type	32;
	.endef
	.globl	count_array                     # -- Begin function count_array
	.p2align	4
count_array:                            # @count_array
# %bb.0:                                # %alloca_entry
	pushq	%rsi
	pushq	%rbx
	movq	8(%rcx), %r8
	cmpq	%r8, %rdx
	jge	.LBB5_6
# %bb.1:                                # %bb_else_1.lr.ph.i
	movq	(%rcx), %r9
	movabsq	$4294977024, %r10               # imm = 0x100002600
	xorl	%eax, %eax
	.p2align	4
.LBB5_2:                                # %bb_else_1.i
                                        # =>This Inner Loop Header: Depth=1
	movzbl	(%r9,%rdx), %r11d
	cmpq	$32, %r11
	ja	.LBB5_6
# %bb.3:                                # %bb_else_1.i
                                        #   in Loop: Header=BB5_2 Depth=1
	btq	%r11, %r10
	jae	.LBB5_6
# %bb.4:                                # %bb_then_3.i
                                        #   in Loop: Header=BB5_2 Depth=1
	incq	%rdx
	cmpq	%rdx, %r8
	jne	.LBB5_2
.LBB5_5:                                # %common.ret
	popq	%rbx
	popq	%rsi
	retq
.LBB5_6:                                # %skip_ws.exit
	cmpq	%r8, %rdx
	jge	.LBB5_14
# %bb.7:                                # %bb_else_1
	movq	(%rcx), %rcx
	cmpb	$91, (%rcx,%rdx)
	jne	.LBB5_14
# %bb.8:                                # %bb_then_3
	incq	%rdx
	cmpq	%r8, %rdx
	jge	.LBB5_15
# %bb.9:
	movabsq	$4294977024, %r10               # imm = 0x100002600
	xorl	%eax, %eax
	.p2align	4
.LBB5_10:                               # %bb_else_1.i11
                                        # =>This Inner Loop Header: Depth=1
	movzbl	(%rcx,%rdx), %r9d
	cmpq	$32, %r9
	ja	.LBB5_16
# %bb.11:                               # %bb_else_1.i11
                                        #   in Loop: Header=BB5_10 Depth=1
	btq	%r9, %r10
	jae	.LBB5_16
# %bb.12:                               # %bb_then_3.i15
                                        #   in Loop: Header=BB5_10 Depth=1
	incq	%rdx
	cmpq	%rdx, %r8
	jne	.LBB5_10
	jmp	.LBB5_5
.LBB5_14:
	xorl	%eax, %eax
	popq	%rbx
	popq	%rsi
	retq
.LBB5_15:                               # %bb_then_3.skip_ws.exit18_crit_edge
	movzbl	(%rcx,%rdx), %r9d
.LBB5_16:                               # %skip_ws.exit18
	xorl	%eax, %eax
	cmpq	%r8, %rdx
	jge	.LBB5_5
# %bb.17:                               # %skip_ws.exit18
	cmpb	$93, %r9b
	je	.LBB5_5
# %bb.18:                               # %bb_else_1.i23.preheader
	movl	$1, %r9d
	xorl	%r10d, %r10d
	movl	$1, %eax
	jmp	.LBB5_22
	.p2align	4
.LBB5_19:                               # %bb_then_6.i
                                        #   in Loop: Header=BB5_22 Depth=1
	incq	%r10
.LBB5_20:                               # %bb_loop_header_16.backedge.i
                                        #   in Loop: Header=BB5_22 Depth=1
	movl	$1, %eax
	incq	%rdx
	cmpq	%rdx, %r8
	je	.LBB5_5
.LBB5_22:                               # %bb_else_1.i23
                                        # =>This Inner Loop Header: Depth=1
	movzbl	(%rcx,%rdx), %r11d
	testq	%r10, %r10
	jne	.LBB5_24
# %bb.23:                               # %bb_else_1.i23
                                        #   in Loop: Header=BB5_22 Depth=1
	cmpb	$93, %r11b
	je	.LBB5_5
.LBB5_24:                               # %bb_else_4.i
                                        #   in Loop: Header=BB5_22 Depth=1
	movl	%r11d, %ebx
	andb	$-33, %bl
	cmpb	$91, %bl
	je	.LBB5_19
# %bb.25:                               # %bb_else_7.i
                                        #   in Loop: Header=BB5_22 Depth=1
	movzbl	%r11b, %r11d
	movl	%r11d, %esi
	orl	$32, %esi
	cmpl	$125, %esi
	jne	.LBB5_27
# %bb.26:                               # %bb_then_9.i
                                        #   in Loop: Header=BB5_22 Depth=1
	decq	%r10
	jmp	.LBB5_20
.LBB5_27:                               # %bb_else_10.i
                                        #   in Loop: Header=BB5_22 Depth=1
	incq	%rax
	cmpl	$44, %r11d
	cmovneq	%r9, %rax
	testq	%r10, %r10
	cmovneq	%r9, %rax
	xorl	%r10d, %r10d
	incq	%rdx
	cmpq	%rdx, %r8
	jne	.LBB5_22
	jmp	.LBB5_5
                                        # -- End function
	.def	count_elements;
	.scl	2;
	.type	32;
	.endef
	.globl	count_elements                  # -- Begin function count_elements
	.p2align	4
count_elements:                         # @count_elements
# %bb.0:                                # %alloca_entry
	pushq	%rsi
	pushq	%rdi
	pushq	%rbx
	movq	8(%rcx), %r10
	cmpq	%r10, %rdx
	jge	.LBB6_1
# %bb.2:                                # %bb_else_1.lr.ph
	movq	(%rcx), %rcx
	movq	%r9, %rax
	movq	%r8, %r11
	jmp	.LBB6_3
	.p2align	4
.LBB6_5:                                # %bb_then_6
                                        #   in Loop: Header=BB6_3 Depth=1
	incq	%r11
.LBB6_6:                                # %bb_loop_header_16.backedge
                                        #   in Loop: Header=BB6_3 Depth=1
	movq	%r9, %rax
	incq	%rdx
	cmpq	%rdx, %r10
	je	.LBB6_8
.LBB6_3:                                # %bb_else_1
                                        # =>This Inner Loop Header: Depth=1
	movzbl	(%rcx,%rdx), %esi
	cmpl	$93, %esi
	sete	%bl
	testq	%r11, %r11
	sete	%dil
	testb	%bl, %dil
	jne	.LBB6_8
# %bb.4:                                # %bb_else_4
                                        #   in Loop: Header=BB6_3 Depth=1
	movl	%esi, %ebx
	andb	$-33, %bl
	cmpb	$91, %bl
	je	.LBB6_5
# %bb.9:                                # %bb_else_7
                                        #   in Loop: Header=BB6_3 Depth=1
	movl	%esi, %edi
	orl	$32, %edi
	cmpl	$125, %edi
	jne	.LBB6_11
# %bb.10:                               # %bb_then_9
                                        #   in Loop: Header=BB6_3 Depth=1
	decq	%r11
	jmp	.LBB6_6
.LBB6_11:                               # %bb_else_10
                                        #   in Loop: Header=BB6_3 Depth=1
	incq	%rax
	cmpl	$44, %esi
	cmovneq	%r9, %rax
	testq	%r11, %r11
	cmovneq	%r9, %rax
	movq	%r8, %r11
	incq	%rdx
	cmpq	%rdx, %r10
	jne	.LBB6_3
.LBB6_8:                                # %bb_merge_2
	popq	%rbx
	popq	%rdi
	popq	%rsi
	retq
.LBB6_1:
	movq	%r9, %rax
	popq	%rbx
	popq	%rdi
	popq	%rsi
	retq
                                        # -- End function
	.def	validate_json;
	.scl	2;
	.type	32;
	.endef
	.globl	validate_json                   # -- Begin function validate_json
	.p2align	4
validate_json:                          # @validate_json
# %bb.0:                                # %alloca_entry
	pushq	%rbx
	movq	8(%rcx), %rax
	cmpq	%rax, %rdx
	jge	.LBB7_6
# %bb.1:                                # %bb_else_1.lr.ph.i
	movq	(%rcx), %r8
	movabsq	$4294977024, %r9                # imm = 0x100002600
	.p2align	4
.LBB7_2:                                # %bb_else_1.i
                                        # =>This Inner Loop Header: Depth=1
	movzbl	(%r8,%rdx), %r10d
	cmpq	$32, %r10
	ja	.LBB7_6
# %bb.3:                                # %bb_else_1.i
                                        #   in Loop: Header=BB7_2 Depth=1
	btq	%r10, %r9
	jae	.LBB7_6
# %bb.4:                                # %bb_then_3.i
                                        #   in Loop: Header=BB7_2 Depth=1
	incq	%rdx
	cmpq	%rdx, %rax
	jne	.LBB7_2
	jmp	.LBB7_5
.LBB7_6:                                # %skip_ws.exit
	cmpq	%rax, %rdx
	jge	.LBB7_5
# %bb.7:                                # %bb_else_1
	movq	(%rcx), %rcx
	movzbl	(%rcx,%rdx), %r8d
	cmpl	$34, %r8d
	je	.LBB7_20
# %bb.8:                                # %bb_else_1
	cmpl	$91, %r8d
	je	.LBB7_15
# %bb.9:                                # %bb_else_1
	cmpl	$123, %r8d
	jne	.LBB7_27
# %bb.10:                               # %bb_then_3
	incq	%rdx
	cmpq	%rax, %rdx
	jge	.LBB7_5
# %bb.11:                               # %bb_else_1.i27.preheader
	xorl	%r8d, %r8d
	xorl	%r9d, %r9d
	.p2align	4
.LBB7_12:                               # %bb_else_1.i27
                                        # =>This Inner Loop Header: Depth=1
	movzbl	(%rcx,%rdx), %r10d
	cmpb	$125, %r10b
	sete	%r11b
	testq	%r9, %r9
	sete	%bl
	testb	%r11b, %bl
	jne	.LBB7_26
# %bb.13:                               # %bb_else_4.i
                                        #   in Loop: Header=BB7_12 Depth=1
	leaq	1(%r9), %r11
	decq	%r9
	cmpb	$125, %r10b
	cmovneq	%r8, %r9
	cmpb	$123, %r10b
	cmoveq	%r11, %r9
	incq	%rdx
	cmpq	%rdx, %rax
	jne	.LBB7_12
	jmp	.LBB7_19
.LBB7_15:                               # %bb_then_6
	incq	%rdx
	cmpq	%rax, %rdx
	jge	.LBB7_5
# %bb.16:                               # %bb_else_1.i38.preheader
	xorl	%r8d, %r8d
	xorl	%r9d, %r9d
	.p2align	4
.LBB7_17:                               # %bb_else_1.i38
                                        # =>This Inner Loop Header: Depth=1
	movzbl	(%rcx,%rdx), %r10d
	cmpb	$93, %r10b
	sete	%r11b
	testq	%r9, %r9
	sete	%bl
	testb	%r11b, %bl
	jne	.LBB7_26
# %bb.18:                               # %bb_else_4.i47
                                        #   in Loop: Header=BB7_17 Depth=1
	leaq	1(%r9), %r11
	decq	%r9
	cmpb	$93, %r10b
	cmovneq	%r8, %r9
	cmpb	$91, %r10b
	cmoveq	%r11, %r9
	incq	%rdx
	cmpq	%rdx, %rax
	jne	.LBB7_17
.LBB7_19:
	movq	%rax, %rdx
	cmpq	%rax, %rdx
	setl	%al
                                        # kill: def $al killed $al killed $eax
	popq	%rbx
	retq
.LBB7_20:                               # %bb_then_9
	incq	%rdx
	cmpq	%rax, %rdx
	jl	.LBB7_24
.LBB7_5:
	xorl	%eax, %eax
                                        # kill: def $al killed $al killed $eax
	popq	%rbx
	retq
	.p2align	4
.LBB7_22:                               # %bb_then_6.i
                                        #   in Loop: Header=BB7_24 Depth=1
	movl	$2, %r8d
.LBB7_23:                               # %bb_loop_header_10.backedge.i
                                        #   in Loop: Header=BB7_24 Depth=1
	addq	%r8, %rdx
	cmpq	%rax, %rdx
	jge	.LBB7_26
.LBB7_24:                               # %bb_else_1.i61
                                        # =>This Inner Loop Header: Depth=1
	movzbl	(%rcx,%rdx), %r9d
	cmpl	$92, %r9d
	je	.LBB7_22
# %bb.25:                               # %bb_else_1.i61
                                        #   in Loop: Header=BB7_24 Depth=1
	movl	$1, %r8d
	cmpl	$34, %r9d
	jne	.LBB7_23
.LBB7_26:                               # %find_close.exit.loopexit
	cmpq	%rax, %rdx
	setl	%al
                                        # kill: def $al killed $al killed $eax
	popq	%rbx
	retq
.LBB7_27:                               # %bb_else_10
	leal	-48(%r8), %eax
	cmpb	$10, %al
	setb	%al
	cmpb	$45, %r8b
	sete	%cl
	orb	%al, %cl
	movb	$1, %al
	je	.LBB7_31
# %bb.28:                               # %common.ret
                                        # kill: def $al killed $al killed $eax
	popq	%rbx
	retq
.LBB7_31:                               # %bb_else_13
	cmpb	$116, %r8b
	sete	%cl
	andb	$-9, %r8b
	cmpb	$102, %r8b
	sete	%al
	orb	%cl, %al
                                        # kill: def $al killed $al killed $eax
	popq	%rbx
	retq
                                        # -- End function
	.def	validate_object;
	.scl	2;
	.type	32;
	.endef
	.globl	validate_object                 # -- Begin function validate_object
	.p2align	4
validate_object:                        # @validate_object
# %bb.0:                                # %alloca_entry
	pushq	%rbx
	incq	%rdx
	movq	8(%rcx), %rax
	cmpq	%rax, %rdx
	jge	.LBB8_1
# %bb.2:                                # %bb_else_1.lr.ph.i
	movq	(%rcx), %rcx
	xorl	%r8d, %r8d
	xorl	%r9d, %r9d
	.p2align	4
.LBB8_3:                                # %bb_else_1.i
                                        # =>This Inner Loop Header: Depth=1
	movzbl	(%rcx,%rdx), %r10d
	cmpb	$125, %r10b
	sete	%r11b
	testq	%r9, %r9
	sete	%bl
	testb	%r11b, %bl
	jne	.LBB8_6
# %bb.4:                                # %bb_else_4.i
                                        #   in Loop: Header=BB8_3 Depth=1
	leaq	1(%r9), %r11
	decq	%r9
	cmpb	$125, %r10b
	cmovneq	%r8, %r9
	cmpb	$123, %r10b
	cmoveq	%r11, %r9
	incq	%rdx
	cmpq	%rdx, %rax
	jne	.LBB8_3
# %bb.5:
	movq	%rax, %rdx
.LBB8_6:                                # %find_close.exit.loopexit
	cmpq	%rax, %rdx
	setl	%al
                                        # kill: def $al killed $al killed $eax
	popq	%rbx
	retq
.LBB8_1:
	xorl	%eax, %eax
                                        # kill: def $al killed $al killed $eax
	popq	%rbx
	retq
                                        # -- End function
	.def	validate_array;
	.scl	2;
	.type	32;
	.endef
	.globl	validate_array                  # -- Begin function validate_array
	.p2align	4
validate_array:                         # @validate_array
# %bb.0:                                # %alloca_entry
	pushq	%rbx
	incq	%rdx
	movq	8(%rcx), %rax
	cmpq	%rax, %rdx
	jge	.LBB9_1
# %bb.2:                                # %bb_else_1.lr.ph.i
	movq	(%rcx), %rcx
	xorl	%r8d, %r8d
	xorl	%r9d, %r9d
	.p2align	4
.LBB9_3:                                # %bb_else_1.i
                                        # =>This Inner Loop Header: Depth=1
	movzbl	(%rcx,%rdx), %r10d
	cmpb	$93, %r10b
	sete	%r11b
	testq	%r9, %r9
	sete	%bl
	testb	%r11b, %bl
	jne	.LBB9_6
# %bb.4:                                # %bb_else_4.i
                                        #   in Loop: Header=BB9_3 Depth=1
	leaq	1(%r9), %r11
	decq	%r9
	cmpb	$93, %r10b
	cmovneq	%r8, %r9
	cmpb	$91, %r10b
	cmoveq	%r11, %r9
	incq	%rdx
	cmpq	%rdx, %rax
	jne	.LBB9_3
# %bb.5:
	movq	%rax, %rdx
.LBB9_6:                                # %find_close.exit.loopexit
	cmpq	%rax, %rdx
	setl	%al
                                        # kill: def $al killed $al killed $eax
	popq	%rbx
	retq
.LBB9_1:
	xorl	%eax, %eax
                                        # kill: def $al killed $al killed $eax
	popq	%rbx
	retq
                                        # -- End function
	.def	validate_string;
	.scl	2;
	.type	32;
	.endef
	.globl	validate_string                 # -- Begin function validate_string
	.p2align	4
validate_string:                        # @validate_string
# %bb.0:                                # %alloca_entry
	incq	%rdx
	movq	8(%rcx), %rax
	cmpq	%rax, %rdx
	jge	.LBB10_1
# %bb.2:                                # %bb_else_1.lr.ph.i
	movq	(%rcx), %rcx
	jmp	.LBB10_3
	.p2align	4
.LBB10_5:                               # %bb_then_6.i
                                        #   in Loop: Header=BB10_3 Depth=1
	movl	$2, %r8d
.LBB10_6:                               # %bb_loop_header_10.backedge.i
                                        #   in Loop: Header=BB10_3 Depth=1
	addq	%r8, %rdx
	cmpq	%rax, %rdx
	jge	.LBB10_7
.LBB10_3:                               # %bb_else_1.i
                                        # =>This Inner Loop Header: Depth=1
	movzbl	(%rcx,%rdx), %r9d
	cmpl	$92, %r9d
	je	.LBB10_5
# %bb.4:                                # %bb_else_1.i
                                        #   in Loop: Header=BB10_3 Depth=1
	movl	$1, %r8d
	cmpl	$34, %r9d
	jne	.LBB10_6
.LBB10_7:                               # %find_string_end.exit.loopexit
	cmpq	%rax, %rdx
	setl	%al
                                        # kill: def $al killed $al killed $eax
	retq
.LBB10_1:
	xorl	%eax, %eax
                                        # kill: def $al killed $al killed $eax
	retq
                                        # -- End function
	.def	find_string_end;
	.scl	2;
	.type	32;
	.endef
	.globl	find_string_end                 # -- Begin function find_string_end
	.p2align	4
find_string_end:                        # @find_string_end
# %bb.0:                                # %alloca_entry
	movq	%rdx, %rax
	movq	8(%rcx), %rdx
	cmpq	%rdx, %rax
	jge	.LBB11_6
# %bb.1:                                # %bb_else_1.lr.ph
	movq	(%rcx), %rcx
	jmp	.LBB11_2
	.p2align	4
.LBB11_4:                               # %bb_then_6
                                        #   in Loop: Header=BB11_2 Depth=1
	movl	$2, %r8d
.LBB11_5:                               # %bb_loop_header_10.backedge
                                        #   in Loop: Header=BB11_2 Depth=1
	addq	%r8, %rax
	cmpq	%rdx, %rax
	jge	.LBB11_6
.LBB11_2:                               # %bb_else_1
                                        # =>This Inner Loop Header: Depth=1
	movzbl	(%rcx,%rax), %r9d
	cmpl	$92, %r9d
	je	.LBB11_4
# %bb.3:                                # %bb_else_1
                                        #   in Loop: Header=BB11_2 Depth=1
	movl	$1, %r8d
	cmpl	$34, %r9d
	jne	.LBB11_5
.LBB11_6:                               # %bb_merge_2
	retq
                                        # -- End function
	.def	run_benchmark;
	.scl	2;
	.type	32;
	.endef
	.globl	run_benchmark                   # -- Begin function run_benchmark
	.p2align	4
run_benchmark:                          # @run_benchmark
# %bb.0:                                # %alloca_entry
	pushq	%r14
	pushq	%rsi
	pushq	%rdi
	pushq	%rbp
	pushq	%rbx
	subq	$32, %rsp
	movq	%rdx, %rsi
	testl	%ecx, %ecx
	jle	.LBB12_29
# %bb.1:                                # %bb_else_1.lr.ph
	movl	%ecx, %edi
	leaq	.L.str.0.bmb(%rip), %rcx
	xorl	%edx, %edx
	callq	validate_json
	movzbl	%al, %eax
	andl	$1, %eax
	movq	.L.str.0.bmb+8(%rip), %rcx
	movq	.L.str.0.bmb(%rip), %rdx
	movabsq	$4294977024, %r8                # imm = 0x100002600
	movl	$1, %r9d
	.p2align	4
.LBB12_4:                               # %bb_else_1
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB12_5 Depth 2
                                        #     Child Loop BB12_12 Depth 2
                                        #     Child Loop BB12_23 Depth 2
	xorl	%r10d, %r10d
	testq	%rcx, %rcx
	jle	.LBB12_9
	.p2align	4
.LBB12_5:                               # %bb_else_1.i.i
                                        #   Parent Loop BB12_4 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movzbl	(%rdx,%r10), %r11d
	cmpq	$32, %r11
	ja	.LBB12_9
# %bb.6:                                # %bb_else_1.i.i
                                        #   in Loop: Header=BB12_5 Depth=2
	btq	%r11, %r8
	jae	.LBB12_9
# %bb.7:                                # %bb_then_3.i.i
                                        #   in Loop: Header=BB12_5 Depth=2
	incq	%r10
	cmpq	%r10, %rcx
	jne	.LBB12_5
	jmp	.LBB12_2
	.p2align	4
.LBB12_9:                               # %skip_ws.exit.i
                                        #   in Loop: Header=BB12_4 Depth=1
	cmpq	%rcx, %r10
	jge	.LBB12_2
# %bb.10:                               # %bb_else_1.i
                                        #   in Loop: Header=BB12_4 Depth=1
	cmpb	$91, (%rdx,%r10)
	jne	.LBB12_2
# %bb.11:                               # %bb_then_3.i
                                        #   in Loop: Header=BB12_4 Depth=1
	incq	%r10
	cmpq	%rcx, %r10
	jge	.LBB12_17
	.p2align	4
.LBB12_12:                              # %bb_else_1.i11.i
                                        #   Parent Loop BB12_4 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movzbl	(%rdx,%r10), %r11d
	cmpq	$32, %r11
	ja	.LBB12_18
# %bb.13:                               # %bb_else_1.i11.i
                                        #   in Loop: Header=BB12_12 Depth=2
	btq	%r11, %r8
	jae	.LBB12_18
# %bb.14:                               # %bb_then_3.i15.i
                                        #   in Loop: Header=BB12_12 Depth=2
	incq	%r10
	cmpq	%r10, %rcx
	jne	.LBB12_12
	jmp	.LBB12_2
.LBB12_17:                              # %bb_then_3.skip_ws.exit18_crit_edge.i
                                        #   in Loop: Header=BB12_4 Depth=1
	movzbl	(%rdx,%r10), %r11d
.LBB12_18:                              # %skip_ws.exit18.i
                                        #   in Loop: Header=BB12_4 Depth=1
	cmpq	%rcx, %r10
	setge	%bl
	cmpb	$93, %r11b
	sete	%r11b
	orb	%bl, %r11b
	je	.LBB12_20
	.p2align	4
.LBB12_2:                               #   in Loop: Header=BB12_4 Depth=1
	xorl	%r11d, %r11d
.LBB12_3:                               # %count_array.exit
                                        #   in Loop: Header=BB12_4 Depth=1
	addq	%rax, %rsi
	addq	%r11, %rsi
	decq	%rdi
	jg	.LBB12_4
	jmp	.LBB12_29
.LBB12_20:                              # %bb_else_1.i23.i.preheader
                                        #   in Loop: Header=BB12_4 Depth=1
	movl	$1, %r11d
	xorl	%ebx, %ebx
	jmp	.LBB12_23
	.p2align	4
.LBB12_21:                              # %bb_then_6.i.i
                                        #   in Loop: Header=BB12_23 Depth=2
	incq	%rbx
	movl	$1, %r11d
	incq	%r10
	cmpq	%r10, %rcx
	je	.LBB12_3
.LBB12_23:                              # %bb_else_1.i23.i
                                        #   Parent Loop BB12_4 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movzbl	(%rdx,%r10), %ebp
	testq	%rbx, %rbx
	jne	.LBB12_25
# %bb.24:                               # %bb_else_1.i23.i
                                        #   in Loop: Header=BB12_23 Depth=2
	cmpb	$93, %bpl
	je	.LBB12_3
.LBB12_25:                              # %bb_else_4.i.i
                                        #   in Loop: Header=BB12_23 Depth=2
	movl	%ebp, %r14d
	andb	$-33, %r14b
	cmpb	$91, %r14b
	je	.LBB12_21
# %bb.26:                               # %bb_else_7.i.i
                                        #   in Loop: Header=BB12_23 Depth=2
	movzbl	%bpl, %ebp
	movl	%ebp, %r14d
	orl	$32, %r14d
	cmpl	$125, %r14d
	jne	.LBB12_28
# %bb.27:                               # %bb_then_9.i.i
                                        #   in Loop: Header=BB12_23 Depth=2
	decq	%rbx
	movl	$1, %r11d
	incq	%r10
	cmpq	%r10, %rcx
	jne	.LBB12_23
	jmp	.LBB12_3
.LBB12_28:                              # %bb_else_10.i.i
                                        #   in Loop: Header=BB12_23 Depth=2
	incq	%r11
	cmpl	$44, %ebp
	cmovneq	%r9, %r11
	testq	%rbx, %rbx
	cmovneq	%r9, %r11
	xorl	%ebx, %ebx
	incq	%r10
	cmpq	%r10, %rcx
	jne	.LBB12_23
	jmp	.LBB12_3
.LBB12_29:                              # %bb_merge_2
	movq	%rsi, %rax
	addq	$32, %rsp
	popq	%rbx
	popq	%rbp
	popq	%rdi
	popq	%rsi
	popq	%r14
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
	pushq	%r14
	.seh_pushreg %r14
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	pushq	%rbp
	.seh_pushreg %rbp
	pushq	%rbx
	.seh_pushreg %rbx
	subq	$32, %rsp
	.seh_stackalloc 32
	.seh_endprologue
	leaq	.L.str.0.bmb(%rip), %rcx
	xorl	%esi, %esi
	xorl	%edx, %edx
	callq	validate_json
	movzbl	%al, %eax
	andl	$1, %eax
	movq	.L.str.0.bmb+8(%rip), %rcx
	movl	$10000, %edx                    # imm = 0x2710
	movq	.L.str.0.bmb(%rip), %r8
	movabsq	$4294977024, %r9                # imm = 0x100002600
	movl	$1, %r10d
	.p2align	4
.LBB13_3:                               # %bb_else_1.i
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB13_4 Depth 2
                                        #     Child Loop BB13_11 Depth 2
                                        #     Child Loop BB13_22 Depth 2
	xorl	%r11d, %r11d
	testq	%rcx, %rcx
	jle	.LBB13_8
	.p2align	4
.LBB13_4:                               # %bb_else_1.i.i.i
                                        #   Parent Loop BB13_3 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movzbl	(%r8,%r11), %edi
	cmpq	$32, %rdi
	ja	.LBB13_8
# %bb.5:                                # %bb_else_1.i.i.i
                                        #   in Loop: Header=BB13_4 Depth=2
	btq	%rdi, %r9
	jae	.LBB13_8
# %bb.6:                                # %bb_then_3.i.i.i
                                        #   in Loop: Header=BB13_4 Depth=2
	incq	%r11
	cmpq	%r11, %rcx
	jne	.LBB13_4
	jmp	.LBB13_1
	.p2align	4
.LBB13_8:                               # %skip_ws.exit.i.i
                                        #   in Loop: Header=BB13_3 Depth=1
	cmpq	%rcx, %r11
	jge	.LBB13_1
# %bb.9:                                # %bb_else_1.i.i
                                        #   in Loop: Header=BB13_3 Depth=1
	cmpb	$91, (%r8,%r11)
	jne	.LBB13_1
# %bb.10:                               # %bb_then_3.i.i
                                        #   in Loop: Header=BB13_3 Depth=1
	incq	%r11
	cmpq	%rcx, %r11
	jge	.LBB13_16
	.p2align	4
.LBB13_11:                              # %bb_else_1.i11.i.i
                                        #   Parent Loop BB13_3 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movzbl	(%r8,%r11), %edi
	cmpq	$32, %rdi
	ja	.LBB13_17
# %bb.12:                               # %bb_else_1.i11.i.i
                                        #   in Loop: Header=BB13_11 Depth=2
	btq	%rdi, %r9
	jae	.LBB13_17
# %bb.13:                               # %bb_then_3.i15.i.i
                                        #   in Loop: Header=BB13_11 Depth=2
	incq	%r11
	cmpq	%r11, %rcx
	jne	.LBB13_11
	jmp	.LBB13_1
.LBB13_16:                              # %bb_then_3.skip_ws.exit18_crit_edge.i.i
                                        #   in Loop: Header=BB13_3 Depth=1
	movzbl	(%r8,%r11), %edi
.LBB13_17:                              # %skip_ws.exit18.i.i
                                        #   in Loop: Header=BB13_3 Depth=1
	cmpq	%rcx, %r11
	setge	%bl
	cmpb	$93, %dil
	sete	%dil
	orb	%bl, %dil
	je	.LBB13_19
	.p2align	4
.LBB13_1:                               #   in Loop: Header=BB13_3 Depth=1
	xorl	%edi, %edi
.LBB13_2:                               # %count_array.exit.i
                                        #   in Loop: Header=BB13_3 Depth=1
	addq	%rax, %rsi
	addq	%rdi, %rsi
	subq	$1, %rdx
	ja	.LBB13_3
	jmp	.LBB13_28
.LBB13_19:                              # %bb_else_1.i23.i.i.preheader
                                        #   in Loop: Header=BB13_3 Depth=1
	movl	$1, %edi
	xorl	%ebx, %ebx
	jmp	.LBB13_22
	.p2align	4
.LBB13_20:                              # %bb_then_6.i.i.i
                                        #   in Loop: Header=BB13_22 Depth=2
	incq	%rbx
	movl	$1, %edi
	incq	%r11
	cmpq	%r11, %rcx
	je	.LBB13_2
.LBB13_22:                              # %bb_else_1.i23.i.i
                                        #   Parent Loop BB13_3 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movzbl	(%r8,%r11), %ebp
	testq	%rbx, %rbx
	jne	.LBB13_24
# %bb.23:                               # %bb_else_1.i23.i.i
                                        #   in Loop: Header=BB13_22 Depth=2
	cmpb	$93, %bpl
	je	.LBB13_2
.LBB13_24:                              # %bb_else_4.i.i.i
                                        #   in Loop: Header=BB13_22 Depth=2
	movl	%ebp, %r14d
	andb	$-33, %r14b
	cmpb	$91, %r14b
	je	.LBB13_20
# %bb.25:                               # %bb_else_7.i.i.i
                                        #   in Loop: Header=BB13_22 Depth=2
	movzbl	%bpl, %ebp
	movl	%ebp, %r14d
	orl	$32, %r14d
	cmpl	$125, %r14d
	jne	.LBB13_27
# %bb.26:                               # %bb_then_9.i.i.i
                                        #   in Loop: Header=BB13_22 Depth=2
	decq	%rbx
	movl	$1, %edi
	incq	%r11
	cmpq	%r11, %rcx
	jne	.LBB13_22
	jmp	.LBB13_2
.LBB13_27:                              # %bb_else_10.i.i.i
                                        #   in Loop: Header=BB13_22 Depth=2
	incq	%rdi
	cmpl	$44, %ebp
	cmovneq	%r10, %rdi
	testq	%rbx, %rbx
	cmovneq	%r10, %rdi
	xorl	%ebx, %ebx
	incq	%r11
	cmpq	%r11, %rcx
	jne	.LBB13_22
	jmp	.LBB13_2
.LBB13_28:                              # %run_benchmark.exit
	movq	%rsi, %rcx
	callq	println
	xorl	%eax, %eax
	.seh_startepilogue
	addq	$32, %rsp
	popq	%rbx
	popq	%rbp
	popq	%rdi
	popq	%rsi
	popq	%r14
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.section	.rdata,"dr"
	.p2align	4, 0x0                          # @.str.0
.L.str.0:
	.asciz	"[1,2,3,4,5,6,7,8,9,10]"

	.data
	.p2align	4, 0x0                          # @.str.0.bmb
.L.str.0.bmb:
	.quad	.L.str.0
	.quad	22                              # 0x16
	.quad	22                              # 0x16

	.addrsig
