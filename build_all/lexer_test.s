	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
@feat.00 = 0
	.file	"lexer_test.ll"
	.def	printline;
	.scl	2;
	.type	32;
	.endef
	.text
	.globl	printline                       # -- Begin function printline
	.p2align	4
printline:                              # @printline
# %bb.0:                                # %alloca_entry
	subq	$40, %rsp
	callq	println_str
	xorl	%eax, %eax
	addq	$40, %rsp
	retq
                                        # -- End function
	.def	int_to_string;
	.scl	2;
	.type	32;
	.endef
	.globl	int_to_string                   # -- Begin function int_to_string
	.p2align	4
int_to_string:                          # @int_to_string
# %bb.0:                                # %alloca_entry
	pushq	%rsi
	pushq	%rdi
	subq	$40, %rsp
	testq	%rcx, %rcx
	js	.LBB1_1
# %bb.4:                                # %bb_else_1
	cmpq	$9, %rcx
	ja	.LBB1_7
# %bb.5:                                # %bb_then_3
	jne	.LBB1_2
# %bb.6:
	leaq	.L.str.2.bmb(%rip), %rax
	addq	$40, %rsp
	popq	%rdi
	popq	%rsi
	retq
.LBB1_1:                                # %bb_then_0
	negq	%rcx
	callq	int_to_string
	leaq	.L.str.0.bmb(%rip), %rcx
	movq	%rax, %rdx
	addq	$40, %rsp
	popq	%rdi
	popq	%rsi
	jmp	bmb_string_concat               # TAILCALL
.LBB1_7:                                # %bb_else_4
	movabsq	$-3689348814741910323, %rdx     # imm = 0xCCCCCCCCCCCCCCCD
	movq	%rcx, %rax
	mulq	%rdx
	movq	%rdx, %rsi
	shrq	$3, %rsi
	movq	%rcx, %rdi
	movq	%rsi, %rcx
	callq	int_to_string
	movq	%rdi, %rcx
	addq	%rsi, %rsi
	leaq	(%rsi,%rsi,4), %rdx
	subq	%rdx, %rcx
	cmpq	$8, %rcx
	ja	.LBB1_8
# %bb.9:                                # %switch.lookup13
	leaq	.Lswitch.table.digit_char(%rip), %rdx
	movq	(%rdx,%rcx,8), %rdx
	jmp	.LBB1_10
.LBB1_2:                                # %switch.lookup
	leaq	.Lswitch.table.digit_char(%rip), %rax
	movq	(%rax,%rcx,8), %rax
	addq	$40, %rsp
	popq	%rdi
	popq	%rsi
	retq
.LBB1_8:
	leaq	.L.str.2.bmb(%rip), %rdx
.LBB1_10:                               # %digit_char.exit11
	movq	%rax, %rcx
	addq	$40, %rsp
	popq	%rdi
	popq	%rsi
	jmp	bmb_string_concat               # TAILCALL
                                        # -- End function
	.def	digit_char;
	.scl	2;
	.type	32;
	.endef
	.globl	digit_char                      # -- Begin function digit_char
	.p2align	4
digit_char:                             # @digit_char
# %bb.0:                                # %alloca_entry
	cmpq	$8, %rcx
	ja	.LBB2_1
# %bb.2:                                # %switch.lookup
	leaq	.Lswitch.table.digit_char(%rip), %rax
	movq	(%rax,%rcx,8), %rax
	retq
.LBB2_1:
	leaq	.L.str.2.bmb(%rip), %rax
	retq
                                        # -- End function
	.def	tok_eof;
	.scl	2;
	.type	32;
	.endef
	.globl	tok_eof                         # -- Begin function tok_eof
	.p2align	4
tok_eof:                                # @tok_eof
# %bb.0:                                # %bb_entry
	xorl	%eax, %eax
	retq
                                        # -- End function
	.def	tok_ident;
	.scl	2;
	.type	32;
	.endef
	.globl	tok_ident                       # -- Begin function tok_ident
	.p2align	4
tok_ident:                              # @tok_ident
# %bb.0:                                # %bb_entry
	movl	$1, %eax
	retq
                                        # -- End function
	.def	tok_number;
	.scl	2;
	.type	32;
	.endef
	.globl	tok_number                      # -- Begin function tok_number
	.p2align	4
tok_number:                             # @tok_number
# %bb.0:                                # %bb_entry
	movl	$2, %eax
	retq
                                        # -- End function
	.def	tok_string;
	.scl	2;
	.type	32;
	.endef
	.globl	tok_string                      # -- Begin function tok_string
	.p2align	4
tok_string:                             # @tok_string
# %bb.0:                                # %bb_entry
	movl	$3, %eax
	retq
                                        # -- End function
	.def	tok_keyword;
	.scl	2;
	.type	32;
	.endef
	.globl	tok_keyword                     # -- Begin function tok_keyword
	.p2align	4
tok_keyword:                            # @tok_keyword
# %bb.0:                                # %bb_entry
	movl	$4, %eax
	retq
                                        # -- End function
	.def	tok_operator;
	.scl	2;
	.type	32;
	.endef
	.globl	tok_operator                    # -- Begin function tok_operator
	.p2align	4
tok_operator:                           # @tok_operator
# %bb.0:                                # %bb_entry
	movl	$5, %eax
	retq
                                        # -- End function
	.def	tok_punct;
	.scl	2;
	.type	32;
	.endef
	.globl	tok_punct                       # -- Begin function tok_punct
	.p2align	4
tok_punct:                              # @tok_punct
# %bb.0:                                # %bb_entry
	movl	$6, %eax
	retq
                                        # -- End function
	.def	tok_comment;
	.scl	2;
	.type	32;
	.endef
	.globl	tok_comment                     # -- Begin function tok_comment
	.p2align	4
tok_comment:                            # @tok_comment
# %bb.0:                                # %bb_entry
	movl	$7, %eax
	retq
                                        # -- End function
	.def	is_whitespace;
	.scl	2;
	.type	32;
	.endef
	.globl	is_whitespace                   # -- Begin function is_whitespace
	.p2align	4
is_whitespace:                          # @is_whitespace
# %bb.0:                                # %alloca_entry
	cmpq	$32, %rcx
	sete	%al
	leaq	-9(%rcx), %rdx
	cmpq	$2, %rdx
	setb	%dl
	cmpq	$13, %rcx
	sete	%cl
	orb	%al, %cl
	orb	%dl, %cl
	movzbl	%cl, %eax
	retq
                                        # -- End function
	.def	is_alpha;
	.scl	2;
	.type	32;
	.endef
	.globl	is_alpha                        # -- Begin function is_alpha
	.p2align	4
is_alpha:                               # @is_alpha
# %bb.0:                                # %alloca_entry
	andq	$-33, %rcx
	addq	$-65, %rcx
	xorl	%eax, %eax
	cmpq	$26, %rcx
	setb	%al
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
	xorl	%eax, %eax
	cmpq	$10, %rcx
	setb	%al
	retq
                                        # -- End function
	.def	is_alnum;
	.scl	2;
	.type	32;
	.endef
	.globl	is_alnum                        # -- Begin function is_alnum
	.p2align	4
is_alnum:                               # @is_alnum
# %bb.0:                                # %alloca_entry
	movq	%rcx, %rax
	andq	$-33, %rax
	addq	$-65, %rax
	cmpq	$26, %rax
	setb	%al
	addq	$-48, %rcx
	cmpq	$10, %rcx
	setb	%cl
	orb	%al, %cl
	movzbl	%cl, %eax
	retq
                                        # -- End function
	.def	is_operator_char;
	.scl	2;
	.type	32;
	.endef
	.globl	is_operator_char                # -- Begin function is_operator_char
	.p2align	4
is_operator_char:                       # @is_operator_char
# %bb.0:                                # %alloca_entry
	movq	%rcx, %rax
	andq	$-2, %rax
	cmpq	$42, %rax
	sete	%al
	movq	%rcx, %rdx
	andq	$-3, %rdx
	cmpq	$45, %rdx
	sete	%dl
	orb	%al, %dl
	cmpq	$37, %rcx
	sete	%al
	leaq	-60(%rcx), %r8
	cmpq	$3, %r8
	setb	%r8b
	orb	%al, %r8b
	orb	%dl, %r8b
	cmpq	$33, %rcx
	sete	%al
	cmpq	$38, %rcx
	sete	%dl
	orb	%al, %dl
	cmpq	$124, %rcx
	sete	%al
	orb	%dl, %al
	orb	%r8b, %al
	movzbl	%al, %eax
	andl	$1, %eax
	retq
                                        # -- End function
	.def	is_punct_char;
	.scl	2;
	.type	32;
	.endef
	.globl	is_punct_char                   # -- Begin function is_punct_char
	.p2align	4
is_punct_char:                          # @is_punct_char
# %bb.0:                                # %alloca_entry
	movq	%rcx, %rax
	andq	$-2, %rax
	cmpq	$40, %rax
	sete	%dl
	cmpq	$123, %rcx
	sete	%r8b
	cmpq	$125, %rcx
	sete	%r9b
	orb	%r8b, %r9b
	orb	%dl, %r9b
	cmpq	$91, %rcx
	sete	%dl
	cmpq	$93, %rcx
	sete	%r8b
	orb	%dl, %r8b
	cmpq	$58, %rax
	sete	%al
	orb	%r8b, %al
	orb	%r9b, %al
	andq	$-3, %rcx
	cmpq	$44, %rcx
	sete	%cl
	orb	%al, %cl
	movzbl	%cl, %eax
	andl	$1, %eax
	retq
                                        # -- End function
	.def	peek;
	.scl	2;
	.type	32;
	.endef
	.globl	peek                            # -- Begin function peek
	.p2align	4
peek:                                   # @peek
# %bb.0:                                # %alloca_entry
	cmpq	8(%rcx), %rdx
	jge	.LBB17_1
# %bb.3:                                # %bb_else_1
	movq	(%rcx), %rax
	movzbl	(%rax,%rdx), %eax
	retq
.LBB17_1:
	xorl	%eax, %eax
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
	jge	.LBB18_6
# %bb.1:                                # %peek.exit.lr.ph
	movq	(%rcx), %rcx
	movabsq	$4294977024, %r8                # imm = 0x100002600
	.p2align	4
.LBB18_2:                               # %peek.exit
                                        # =>This Inner Loop Header: Depth=1
	movzbl	(%rcx,%rax), %r9d
	cmpq	$32, %r9
	ja	.LBB18_6
# %bb.3:                                # %peek.exit
                                        #   in Loop: Header=BB18_2 Depth=1
	btq	%r9, %r8
	jae	.LBB18_6
# %bb.4:                                # %bb_then_3
                                        #   in Loop: Header=BB18_2 Depth=1
	incq	%rax
	cmpq	%rax, %rdx
	jne	.LBB18_2
# %bb.5:
	movq	%rdx, %rax
.LBB18_6:                               # %bb_merge_2
	retq
                                        # -- End function
	.def	is_keyword_at;
	.scl	2;
	.type	32;
	.endef
	.globl	is_keyword_at                   # -- Begin function is_keyword_at
	.p2align	4
is_keyword_at:                          # @is_keyword_at
# %bb.0:                                # %alloca_entry
	pushq	%rbx
	movq	8(%rcx), %r9
	cmpq	%r9, %rdx
	jge	.LBB19_1
# %bb.2:                                # %bb_else_1.i95
	movq	(%rcx), %rax
	cmpb	$102, (%rax,%rdx)
	sete	%r11b
	leaq	1(%rdx), %r10
	cmpq	%r9, %r10
	jl	.LBB19_4
	jmp	.LBB19_6
.LBB19_1:
	xorl	%r11d, %r11d
	leaq	1(%rdx), %r10
	cmpq	%r9, %r10
	jge	.LBB19_6
.LBB19_4:                               # %peek.exit90
	movq	(%rcx), %rax
	cmpb	$110, (%rax,%r10)
	sete	%bl
	cmpq	$2, %r8
	jne	.LBB19_6
# %bb.5:                                # %peek.exit90
	movl	$1, %eax
	andb	%bl, %r11b
	je	.LBB19_6
.LBB19_25:                              # %bb_merge_2
	popq	%rbx
	retq
.LBB19_6:                               # %bb_else_1
	cmpq	%r9, %rdx
	jge	.LBB19_7
# %bb.8:                                # %bb_else_1.i75
	movq	(%rcx), %rax
	cmpb	$108, (%rax,%rdx)
	sete	%al
	cmpq	%r9, %r10
	jl	.LBB19_10
	jmp	.LBB19_12
.LBB19_7:
	xorl	%eax, %eax
	cmpq	%r9, %r10
	jge	.LBB19_12
.LBB19_10:                              # %peek.exit70
	cmpq	$3, %r8
	setne	%r11b
	xorb	$1, %al
	orb	%r11b, %al
	jne	.LBB19_12
# %bb.11:                               # %peek.exit70
	movq	(%rcx), %r11
	movl	$1, %eax
	cmpb	$101, (%r11,%r10)
	je	.LBB19_25
.LBB19_12:                              # %bb_else_4
	cmpq	%r9, %rdx
	jge	.LBB19_13
# %bb.14:                               # %bb_else_1.i55
	movq	(%rcx), %rax
	cmpb	$105, (%rax,%rdx)
	sete	%r11b
	cmpq	%r9, %r10
	jl	.LBB19_16
	jmp	.LBB19_18
.LBB19_13:
	xorl	%r11d, %r11d
	cmpq	%r9, %r10
	jge	.LBB19_18
.LBB19_16:                              # %peek.exit50
	movq	(%rcx), %rax
	cmpb	$102, (%rax,%r10)
	sete	%r10b
	cmpq	$2, %r8
	jne	.LBB19_18
# %bb.17:                               # %peek.exit50
	movl	$1, %eax
	andb	%r10b, %r11b
	jne	.LBB19_25
.LBB19_18:                              # %bb_else_7
	cmpq	%r9, %rdx
	jge	.LBB19_19
# %bb.20:                               # %peek.exit40
	cmpq	$4, %r8
	sete	%r9b
	movq	(%rcx), %rax
	movzbl	(%rax,%rdx), %ecx
	cmpb	$101, %cl
	sete	%dl
	movl	$1, %eax
	testb	%dl, %r9b
	jne	.LBB19_25
# %bb.21:                               # %peek.exit30
	cmpq	$5, %r8
	sete	%dl
	cmpb	$119, %cl
	sete	%r9b
	testb	%r9b, %dl
	jne	.LBB19_25
# %bb.22:                               # %peek.exit20
	cmpq	$4, %r8
	sete	%dl
	cmpq	$6, %r8
	sete	%r10b
	cmpb	$114, %cl
	sete	%r11b
	cmpb	$116, %cl
	sete	%r9b
	testb	%r11b, %r10b
	jne	.LBB19_25
# %bb.23:                               # %peek.exit20
	andb	%r9b, %dl
	jne	.LBB19_25
# %bb.24:                               # %bb_else_1.i
	cmpq	$5, %r8
	sete	%al
	cmpb	$102, %cl
	sete	%cl
	andb	%al, %cl
	movzbl	%cl, %eax
	popq	%rbx
	retq
.LBB19_19:
	xorl	%eax, %eax
	popq	%rbx
	retq
                                        # -- End function
	.def	skip_ident;
	.scl	2;
	.type	32;
	.endef
	.globl	skip_ident                      # -- Begin function skip_ident
	.p2align	4
skip_ident:                             # @skip_ident
# %bb.0:                                # %alloca_entry
	movq	%rdx, %rax
	movq	8(%rcx), %rdx
	cmpq	%rdx, %rax
	jge	.LBB20_7
# %bb.1:                                # %peek.exit.lr.ph
	movq	(%rcx), %rcx
	jmp	.LBB20_2
	.p2align	4
.LBB20_5:                               # %bb_then_3
                                        #   in Loop: Header=BB20_2 Depth=1
	incq	%rax
	cmpq	%rax, %rdx
	je	.LBB20_6
.LBB20_2:                               # %peek.exit
                                        # =>This Inner Loop Header: Depth=1
	movzbl	(%rcx,%rax), %r8d
	cmpb	$95, %r8b
	je	.LBB20_5
# %bb.3:                                # %peek.exit
                                        #   in Loop: Header=BB20_2 Depth=1
	leal	-48(%r8), %r9d
	cmpb	$10, %r9b
	jb	.LBB20_5
# %bb.4:                                # %peek.exit
                                        #   in Loop: Header=BB20_2 Depth=1
	andb	$-33, %r8b
	addb	$-65, %r8b
	cmpb	$25, %r8b
	jbe	.LBB20_5
.LBB20_7:                               # %bb_merge_2
	retq
.LBB20_6:
	movq	%rdx, %rax
	retq
                                        # -- End function
	.def	skip_number;
	.scl	2;
	.type	32;
	.endef
	.globl	skip_number                     # -- Begin function skip_number
	.p2align	4
skip_number:                            # @skip_number
# %bb.0:                                # %alloca_entry
	movq	%rdx, %rax
	movq	8(%rcx), %rdx
	cmpq	%rdx, %rax
	jge	.LBB21_5
# %bb.1:                                # %peek.exit.lr.ph
	movq	(%rcx), %rcx
	.p2align	4
.LBB21_2:                               # %peek.exit
                                        # =>This Inner Loop Header: Depth=1
	movzbl	(%rcx,%rax), %r8d
	leal	-48(%r8), %r9d
	cmpb	$10, %r9b
	setae	%r9b
	cmpb	$46, %r8b
	setne	%r8b
	testb	%r9b, %r8b
	jne	.LBB21_5
# %bb.3:                                # %bb_then_3
                                        #   in Loop: Header=BB21_2 Depth=1
	incq	%rax
	cmpq	%rax, %rdx
	jne	.LBB21_2
# %bb.4:
	movq	%rdx, %rax
.LBB21_5:                               # %bb_merge_2
	retq
                                        # -- End function
	.def	skip_string;
	.scl	2;
	.type	32;
	.endef
	.globl	skip_string                     # -- Begin function skip_string
	.p2align	4
skip_string:                            # @skip_string
# %bb.0:                                # %alloca_entry
	movq	%rdx, %rax
	movq	8(%rcx), %rdx
	cmpq	%rdx, %rax
	jge	.LBB22_5
# %bb.1:                                # %peek.exit10.lr.ph
	movq	(%rcx), %rcx
	.p2align	4
.LBB22_2:                               # %peek.exit10
                                        # =>This Inner Loop Header: Depth=1
	movzbl	(%rcx,%rax), %r8d
	cmpb	$34, %r8b
	je	.LBB22_3
# %bb.4:                                # %peek.exit
                                        #   in Loop: Header=BB22_2 Depth=1
	xorl	%r9d, %r9d
	cmpb	$92, %r8b
	sete	%r9b
	addq	%r9, %rax
	incq	%rax
	cmpq	%rdx, %rax
	jl	.LBB22_2
.LBB22_5:                               # %bb_merge_2
	retq
.LBB22_3:                               # %bb_then_3
	incq	%rax
	retq
                                        # -- End function
	.def	skip_comment;
	.scl	2;
	.type	32;
	.endef
	.globl	skip_comment                    # -- Begin function skip_comment
	.p2align	4
skip_comment:                           # @skip_comment
# %bb.0:                                # %alloca_entry
	movq	%rdx, %rax
	movq	8(%rcx), %rdx
	cmpq	%rdx, %rax
	jge	.LBB23_5
# %bb.1:                                # %peek.exit.lr.ph
	movq	(%rcx), %rcx
	.p2align	4
.LBB23_2:                               # %peek.exit
                                        # =>This Inner Loop Header: Depth=1
	cmpb	$10, (%rcx,%rax)
	je	.LBB23_5
# %bb.3:                                # %bb_else_4
                                        #   in Loop: Header=BB23_2 Depth=1
	incq	%rax
	cmpq	%rax, %rdx
	jne	.LBB23_2
# %bb.4:
	movq	%rdx, %rax
.LBB23_5:                               # %bb_merge_2
	retq
                                        # -- End function
	.def	next_token;
	.scl	2;
	.type	32;
	.endef
	.globl	next_token                      # -- Begin function next_token
	.p2align	4
next_token:                             # @next_token
# %bb.0:                                # %alloca_entry
	pushq	%rsi
	subq	$32, %rsp
	movq	8(%rcx), %rax
	cmpq	%rax, %rdx
	jge	.LBB24_6
# %bb.1:                                # %peek.exit.lr.ph.i
	movq	(%rcx), %r8
	movabsq	$4294977024, %r9                # imm = 0x100002600
	.p2align	4
.LBB24_2:                               # %peek.exit.i
                                        # =>This Inner Loop Header: Depth=1
	movzbl	(%r8,%rdx), %r10d
	cmpq	$32, %r10
	ja	.LBB24_6
# %bb.3:                                # %peek.exit.i
                                        #   in Loop: Header=BB24_2 Depth=1
	btq	%r10, %r9
	jae	.LBB24_6
# %bb.4:                                # %bb_then_3.i
                                        #   in Loop: Header=BB24_2 Depth=1
	incq	%rdx
	cmpq	%rdx, %rax
	jne	.LBB24_2
# %bb.5:                                # %bb_merge_2
	addq	$32, %rsp
	popq	%rsi
	retq
.LBB24_6:                               # %skip_ws.exit
	cmpq	%rax, %rdx
	jge	.LBB24_15
# %bb.7:                                # %peek.exit53
	movq	(%rcx), %r9
	movzbl	(%r9,%rdx), %ecx
	leaq	1(%rdx), %r8
	cmpq	%rax, %r8
	jge	.LBB24_16
# %bb.8:                                # %peek.exit43
	movzbl	(%r9,%r8), %r11d
	cmpl	$45, %ecx
	jne	.LBB24_20
# %bb.9:                                # %peek.exit43
	cmpb	$45, %r11b
	jne	.LBB24_20
# %bb.10:                               # %bb_then_3
	addq	$2, %rdx
	cmpq	%rax, %rdx
	jge	.LBB24_14
	.p2align	4
.LBB24_11:                              # %peek.exit.i62
                                        # =>This Inner Loop Header: Depth=1
	cmpb	$10, (%r9,%rdx)
	je	.LBB24_14
# %bb.12:                               # %bb_else_4.i
                                        #   in Loop: Header=BB24_11 Depth=1
	incq	%rdx
	cmpq	%rdx, %rax
	jne	.LBB24_11
# %bb.13:
	movq	%rax, %rdx
.LBB24_14:                              # %skip_comment.exit
	addq	$7000000, %rdx                  # imm = 0x6ACFC0
.LBB24_15:
	movq	%rdx, %rax
	addq	$32, %rsp
	popq	%rsi
	retq
.LBB24_16:                              # %bb_else_4.thread
	xorl	%r11d, %r11d
	movl	$1, %r10d
	cmpq	$95, %rcx
	je	.LBB24_34
# %bb.17:                               # %bb_else_4.thread
	movl	%ecx, %esi
	andl	$-33, %esi
	addq	$-65, %rsi
	cmpl	$26, %esi
	jb	.LBB24_34
# %bb.18:                               # %bb_else_7.thread
	leal	-58(%rcx), %r10d
	cmpb	$-10, %r10b
	jae	.LBB24_33
# %bb.19:                               # %bb_else_13.thread
	cmpl	$34, %ecx
	je	.LBB24_70
	jmp	.LBB24_38
.LBB24_20:                              # %bb_else_4
	cmpq	$95, %rcx
	je	.LBB24_27
# %bb.21:                               # %bb_else_4
	movl	%ecx, %r10d
	andl	$-33, %r10d
	addq	$-65, %r10
	cmpl	$25, %r10d
	jbe	.LBB24_27
# %bb.22:                               # %bb_else_7
	leal	-58(%rcx), %r10d
	cmpb	$-10, %r10b
	jae	.LBB24_30
# %bb.23:                               # %bb_else_13
	cmpl	$34, %ecx
	jne	.LBB24_38
.LBB24_24:                              # %peek.exit10.i
                                        # =>This Inner Loop Header: Depth=1
	movzbl	(%r9,%r8), %ecx
	cmpb	$34, %cl
	je	.LBB24_69
# %bb.25:                               # %peek.exit.i103
                                        #   in Loop: Header=BB24_24 Depth=1
	xorl	%edx, %edx
	cmpb	$92, %cl
	sete	%dl
	addq	%rdx, %r8
	incq	%r8
	cmpq	%rax, %r8
	jl	.LBB24_24
	jmp	.LBB24_70
	.p2align	4
.LBB24_26:                              # %bb_then_3.i73
                                        #   in Loop: Header=BB24_27 Depth=1
	incq	%r8
	cmpq	%r8, %rax
	je	.LBB24_46
.LBB24_27:                              # %peek.exit.i71
                                        # =>This Inner Loop Header: Depth=1
	movzbl	(%r9,%r8), %r10d
	cmpb	$95, %r10b
	je	.LBB24_26
# %bb.28:                               # %peek.exit.i71
                                        #   in Loop: Header=BB24_27 Depth=1
	leal	-48(%r10), %esi
	cmpb	$10, %sil
	jb	.LBB24_26
# %bb.29:                               # %peek.exit.i71
                                        #   in Loop: Header=BB24_27 Depth=1
	andb	$-33, %r10b
	addb	$-65, %r10b
	cmpb	$25, %r10b
	jbe	.LBB24_26
	jmp	.LBB24_47
	.p2align	4
.LBB24_30:                              # %peek.exit.i87
                                        # =>This Inner Loop Header: Depth=1
	movzbl	(%r9,%r8), %ecx
	leal	-48(%rcx), %edx
	cmpb	$10, %dl
	setae	%dl
	cmpb	$46, %cl
	setne	%cl
	testb	%dl, %cl
	jne	.LBB24_33
# %bb.31:                               # %bb_then_3.i93
                                        #   in Loop: Header=BB24_30 Depth=1
	incq	%r8
	cmpq	%r8, %rax
	jne	.LBB24_30
# %bb.32:
	movq	%rax, %r8
.LBB24_33:                              # %skip_number.exit
	addq	$2000000, %r8                   # imm = 0x1E8480
	movq	%r8, %rax
	addq	$32, %rsp
	popq	%rsi
	retq
.LBB24_34:
	xorl	%edx, %edx
.LBB24_35:                              # %peek.exit20.i
	xorq	$6, %r10
	movq	%rcx, %rax
	xorq	$114, %rax
	cmpq	$116, %rcx
	sete	%r9b
	orq	%r10, %rax
	movl	$4000000, %eax                  # imm = 0x3D0900
	je	.LBB24_60
# %bb.36:                               # %peek.exit20.i
	andb	%r9b, %dl
	jne	.LBB24_60
# %bb.37:                               # %is_keyword_at.exit
	cmpl	$102, %ecx
	movl	$1000000, %ecx                  # imm = 0xF4240
	cmovneq	%rcx, %rax
	testb	%r11b, %r11b
	cmoveq	%rcx, %rax
	jmp	.LBB24_60
.LBB24_38:                              # %bb_else_16
	movl	%ecx, %r10d
	andl	$-2, %r10d
	cmpq	$124, %rcx
	je	.LBB24_61
# %bb.39:                               # %bb_else_16
	cmpb	$38, %cl
	je	.LBB24_61
# %bb.40:                               # %bb_else_16
	cmpb	$33, %cl
	je	.LBB24_61
# %bb.41:                               # %bb_else_16
	leal	-60(%rcx), %r11d
	cmpb	$3, %r11b
	jb	.LBB24_61
# %bb.42:                               # %bb_else_16
	cmpb	$37, %cl
	je	.LBB24_61
# %bb.43:                               # %bb_else_16
	cmpl	$42, %r10d
	je	.LBB24_61
# %bb.44:                               # %bb_else_16
	movl	%ecx, %r11d
	andl	$-3, %r11d
	cmpl	$45, %r11d
	je	.LBB24_61
# %bb.45:                               # %bb_else_19
	movq	%rdx, %rsi
	callq	is_punct_char
	movq	%rax, %rcx
	leaq	6000001(%rsi), %rax
	testq	%rcx, %rcx
	cmoveq	%rsi, %rax
	addq	$32, %rsp
	popq	%rsi
	retq
.LBB24_46:
	movq	%rax, %r8
.LBB24_47:                              # %peek.exit100.i
	movq	%r8, %r10
	subq	%rdx, %r10
	movl	$4000000, %eax                  # imm = 0x3D0900
	cmpq	$2, %r10
	jne	.LBB24_50
# %bb.48:                               # %peek.exit100.i
	cmpb	$102, %cl
	jne	.LBB24_50
# %bb.49:                               # %peek.exit100.i
	cmpb	$110, %r11b
	je	.LBB24_60
.LBB24_50:                              # %peek.exit70.i
	cmpq	$3, %r10
	jne	.LBB24_53
# %bb.51:                               # %peek.exit70.i
	cmpb	$108, %cl
	jne	.LBB24_53
# %bb.52:                               # %peek.exit70.i
	cmpb	$101, %r11b
	je	.LBB24_60
.LBB24_53:                              # %peek.exit50.i
	cmpq	$2, %r10
	jne	.LBB24_56
# %bb.54:                               # %peek.exit50.i
	cmpb	$105, %cl
	jne	.LBB24_56
# %bb.55:                               # %peek.exit50.i
	cmpb	$102, %r11b
	je	.LBB24_60
.LBB24_56:                              # %peek.exit40.i
	cmpq	$4, %r10
	sete	%dl
	jne	.LBB24_58
# %bb.57:                               # %peek.exit40.i
	cmpb	$101, %cl
	je	.LBB24_60
.LBB24_58:                              # %peek.exit30.i
	cmpq	$5, %r10
	sete	%r11b
	jne	.LBB24_35
# %bb.59:                               # %peek.exit30.i
	cmpb	$119, %cl
	jne	.LBB24_35
.LBB24_60:                              # %is_keyword_at.exit.thread
	addq	%rax, %r8
	movq	%r8, %rax
	addq	$32, %rsp
	popq	%rsi
	retq
.LBB24_61:                              # %bb_then_18
	cmpq	%rax, %r8
	jge	.LBB24_64
# %bb.62:                               # %peek.exit
	cmpq	$33, %rcx
	setne	%r11b
	movzbl	(%r9,%r8), %r8d
	movzbl	%r8b, %eax
	cmpl	$60, %r10d
	setne	%r9b
	cmpq	$62, %rcx
	setne	%r10b
	andb	%r9b, %r10b
	testb	%r10b, %r11b
	jne	.LBB24_65
# %bb.63:                               # %peek.exit
	cmpb	$61, %r8b
	je	.LBB24_68
	jmp	.LBB24_65
.LBB24_64:
	xorl	%eax, %eax
.LBB24_65:                              # %bb_else_22
	movq	%rcx, %r8
	xorq	$124, %r8
	xorq	$38, %rcx
	movq	%rax, %r9
	xorq	$38, %r9
	xorq	$124, %rax
	orq	%r8, %rax
	sete	%al
	orq	%rcx, %r9
	je	.LBB24_68
# %bb.66:                               # %bb_else_22
	testb	%al, %al
	jne	.LBB24_68
# %bb.67:                               # %bb_else_25
	addq	$5000001, %rdx                  # imm = 0x4C4B41
	movq	%rdx, %rax
	addq	$32, %rsp
	popq	%rsi
	retq
.LBB24_68:                              # %bb_then_21
	addq	$5000002, %rdx                  # imm = 0x4C4B42
	movq	%rdx, %rax
	addq	$32, %rsp
	popq	%rsi
	retq
.LBB24_69:                              # %bb_then_3.i106
	incq	%r8
.LBB24_70:                              # %skip_string.exit
	addq	$3000000, %r8                   # imm = 0x2DC6C0
	movq	%r8, %rax
	addq	$32, %rsp
	popq	%rsi
	retq
                                        # -- End function
	.def	count_tokens_loop;
	.scl	2;
	.type	32;
	.endef
	.globl	count_tokens_loop               # -- Begin function count_tokens_loop
	.p2align	4
count_tokens_loop:                      # @count_tokens_loop
# %bb.0:                                # %alloca_entry
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rsi
	pushq	%rdi
	pushq	%rbx
	subq	$32, %rsp
	movq	%r9, %rsi
	movq	%r8, %rdi
	movq	%rcx, %rbx
	movq	152(%rsp), %r14
	movq	144(%rsp), %r15
	movq	136(%rsp), %r12
	callq	next_token
	movq	%rax, %rcx
	addq	$999999, %rax                   # imm = 0xF423F
	cmpq	$1999999, %rax                  # imm = 0x1E847F
	jb	.LBB25_3
# %bb.1:
	movabsq	$4835703278458516699, %r13      # imm = 0x431BDE82D7B634DB
	.p2align	4
.LBB25_2:                               # %bb_else_1
                                        # =>This Inner Loop Header: Depth=1
	movq	%rcx, %rax
	imulq	%r13
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$18, %rdx
	addq	%rax, %rdx
	imulq	$1000000, %rdx, %rax            # imm = 0xF4240
	movq	%rcx, %rdx
	subq	%rax, %rdx
	leaq	-1000000(%rcx), %rax
	cmpq	$1000000, %rax                  # imm = 0xF4240
	adcq	$0, %rdi
	leaq	-2000000(%rcx), %rax
	cmpq	$1000000, %rax                  # imm = 0xF4240
	adcq	$0, %rsi
	leaq	-4000000(%rcx), %rax
	cmpq	$1000000, %rax                  # imm = 0xF4240
	adcq	$0, %r12
	leaq	-5000000(%rcx), %rax
	cmpq	$1000000, %rax                  # imm = 0xF4240
	adcq	$0, %r15
	addq	$-6000000, %rcx                 # imm = 0xFFA47280
	cmpq	$1000000, %rcx                  # imm = 0xF4240
	adcq	$0, %r14
	movq	%rbx, %rcx
	callq	next_token
	movq	%rax, %rcx
	addq	$999999, %rax                   # imm = 0xF423F
	cmpq	$1999999, %rax                  # imm = 0x1E847F
	jae	.LBB25_2
.LBB25_3:                               # %bb_then_0
	imulq	$10000000, %rdi, %rax           # imm = 0x989680
	imulq	$100000, %rsi, %rcx             # imm = 0x186A0
	addq	%rax, %rcx
	imulq	$1000, %r12, %rax               # imm = 0x3E8
	addq	%rcx, %rax
	leaq	(%r15,%r15,4), %rcx
	leaq	(%rax,%rcx,2), %rax
	addq	%r14, %rax
	addq	$32, %rsp
	popq	%rbx
	popq	%rdi
	popq	%rsi
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	retq
                                        # -- End function
	.def	count_tokens;
	.scl	2;
	.type	32;
	.endef
	.globl	count_tokens                    # -- Begin function count_tokens
	.p2align	4
count_tokens:                           # @count_tokens
# %bb.0:                                # %alloca_entry
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rsi
	pushq	%rdi
	pushq	%rbx
	subq	$32, %rsp
	movq	%rcx, %rsi
	xorl	%edi, %edi
	xorl	%edx, %edx
	callq	next_token
	movq	%rax, %rcx
	addq	$999999, %rax                   # imm = 0xF423F
	cmpq	$1999999, %rax                  # imm = 0x1E847F
	jb	.LBB26_4
# %bb.1:                                # %bb_else_1.i.preheader
	xorl	%ebx, %ebx
	movabsq	$4835703278458516699, %r15      # imm = 0x431BDE82D7B634DB
	xorl	%edi, %edi
	xorl	%r14d, %r14d
	xorl	%r12d, %r12d
	xorl	%r13d, %r13d
	.p2align	4
.LBB26_2:                               # %bb_else_1.i
                                        # =>This Inner Loop Header: Depth=1
	movq	%rcx, %rax
	imulq	%r15
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$18, %rdx
	addq	%rax, %rdx
	imulq	$1000000, %rdx, %rax            # imm = 0xF4240
	movq	%rcx, %rdx
	subq	%rax, %rdx
	leaq	-1000000(%rcx), %rax
	cmpq	$1000000, %rax                  # imm = 0xF4240
	adcq	$0, %r13
	leaq	-2000000(%rcx), %rax
	cmpq	$1000000, %rax                  # imm = 0xF4240
	adcq	$0, %r12
	leaq	-4000000(%rcx), %rax
	cmpq	$1000000, %rax                  # imm = 0xF4240
	adcq	$0, %r14
	leaq	-5000000(%rcx), %rax
	cmpq	$1000000, %rax                  # imm = 0xF4240
	adcq	$0, %rdi
	addq	$-6000000, %rcx                 # imm = 0xFFA47280
	cmpq	$1000000, %rcx                  # imm = 0xF4240
	adcq	$0, %rbx
	movq	%rsi, %rcx
	callq	next_token
	movq	%rax, %rcx
	addq	$999999, %rax                   # imm = 0xF423F
	cmpq	$1999998, %rax                  # imm = 0x1E847E
	ja	.LBB26_2
# %bb.3:                                # %count_tokens_loop.exit.loopexit
	imulq	$10000000, %r13, %rax           # imm = 0x989680
	imulq	$100000, %r12, %rcx             # imm = 0x186A0
	addq	%rax, %rcx
	imulq	$1000, %r14, %rax               # imm = 0x3E8
	addq	%rcx, %rax
	leaq	(%rdi,%rdi,4), %rcx
	leaq	(%rax,%rcx,2), %rdi
	addq	%rbx, %rdi
.LBB26_4:                               # %count_tokens_loop.exit
	movq	%rdi, %rax
	addq	$32, %rsp
	popq	%rbx
	popq	%rdi
	popq	%rsi
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	retq
                                        # -- End function
	.def	test_source;
	.scl	2;
	.type	32;
	.endef
	.globl	test_source                     # -- Begin function test_source
	.p2align	4
test_source:                            # @test_source
# %bb.0:                                # %alloca_entry
	leaq	.L.str.11.bmb(%rip), %rax
	retq
                                        # -- End function
	.def	gen_large;
	.scl	2;
	.type	32;
	.endef
	.globl	gen_large                       # -- Begin function gen_large
	.p2align	4
gen_large:                              # @gen_large
# %bb.0:                                # %alloca_entry
	pushq	%rsi
	pushq	%rdi
	subq	$40, %rsp
	movq	%rdx, %rax
	testl	%ecx, %ecx
	jle	.LBB28_3
# %bb.1:                                # %bb_else_1.preheader
	movl	%ecx, %edi
	incq	%rdi
	leaq	.L.str.11.bmb(%rip), %rsi
	.p2align	4
.LBB28_2:                               # %bb_else_1
                                        # =>This Inner Loop Header: Depth=1
	movq	%rax, %rcx
	movq	%rsi, %rdx
	callq	bmb_string_concat
	decq	%rdi
	cmpq	$1, %rdi
	ja	.LBB28_2
.LBB28_3:                               # %bb_merge_2
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
# %bb.0:                                # %alloca_entry
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rsi
	pushq	%rdi
	pushq	%rbp
	pushq	%rbx
	subq	$40, %rsp
	leaq	.L.str.12.bmb(%rip), %rcx
	callq	println_str
	leaq	.L.str.11.bmb(%rip), %rcx
	xorl	%esi, %esi
	xorl	%edx, %edx
	callq	next_token
	movq	%rax, %rcx
	addq	$999999, %rax                   # imm = 0xF423F
	movabsq	$4835703278458516699, %r12      # imm = 0x431BDE82D7B634DB
	cmpq	$1999999, %rax                  # imm = 0x1E847F
	jb	.LBB29_4
# %bb.1:                                # %bb_else_1.i.preheader
	xorl	%edi, %edi
	leaq	.L.str.11.bmb(%rip), %rsi
	xorl	%ebx, %ebx
	xorl	%r14d, %r14d
	xorl	%r15d, %r15d
	xorl	%r13d, %r13d
	.p2align	4
.LBB29_2:                               # %bb_else_1.i
                                        # =>This Inner Loop Header: Depth=1
	movq	%rcx, %rax
	imulq	%r12
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$18, %rdx
	addq	%rax, %rdx
	imulq	$1000000, %rdx, %rax            # imm = 0xF4240
	movq	%rcx, %rdx
	subq	%rax, %rdx
	leaq	-1000000(%rcx), %rax
	cmpq	$1000000, %rax                  # imm = 0xF4240
	adcq	$0, %r13
	leaq	-2000000(%rcx), %rax
	cmpq	$1000000, %rax                  # imm = 0xF4240
	adcq	$0, %r15
	leaq	-4000000(%rcx), %rax
	cmpq	$1000000, %rax                  # imm = 0xF4240
	adcq	$0, %r14
	leaq	-5000000(%rcx), %rax
	cmpq	$1000000, %rax                  # imm = 0xF4240
	adcq	$0, %rbx
	addq	$-6000000, %rcx                 # imm = 0xFFA47280
	cmpq	$1000000, %rcx                  # imm = 0xF4240
	adcq	$0, %rdi
	movq	%rsi, %rcx
	callq	next_token
	movq	%rax, %rcx
	addq	$999999, %rax                   # imm = 0xF423F
	cmpq	$1999998, %rax                  # imm = 0x1E847E
	ja	.LBB29_2
# %bb.3:                                # %count_tokens_loop.exit.loopexit
	imulq	$10000000, %r13, %rax           # imm = 0x989680
	imulq	$100000, %r15, %rcx             # imm = 0x186A0
	addq	%rax, %rcx
	imulq	$1000, %r14, %rax               # imm = 0x3E8
	addq	%rcx, %rax
	leaq	(%rbx,%rbx,4), %rcx
	leaq	(%rax,%rcx,2), %rsi
	addq	%rdi, %rsi
.LBB29_4:                               # %count_tokens_loop.exit
	movabsq	$-2972493582642298179, %rbp     # imm = 0xD6BF94D5E57A42BD
	movq	%rsi, %rax
	imulq	%rbp
	leaq	(%rdx,%rsi), %rbx
	movq	%rbx, %rax
	shrq	$63, %rax
	sarq	$23, %rbx
	addq	%rax, %rbx
	movabsq	$3022314549036572937, %rcx      # imm = 0x29F16B11C6D1E109
	movq	%rsi, %rax
	imulq	%rcx
	movq	%rdx, %rdi
	shrq	$63, %rdi
	sarq	$14, %rdx
	addq	%rdx, %rdi
	movabsq	$-6640827866535438581, %r13     # imm = 0xA3D70A3D70A3D70B
	movq	%rdi, %rax
	imulq	%r13
	addq	%rdi, %rdx
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$6, %rdx
	addq	%rax, %rdx
	imulq	$100, %rdx, %rax
	subq	%rax, %rdi
	movabsq	$2361183241434822607, %rcx      # imm = 0x20C49BA5E353F7CF
	movq	%rsi, %rax
	imulq	%rcx
	movq	%rdx, %r14
	shrq	$63, %r14
	sarq	$7, %rdx
	addq	%rdx, %r14
	movq	%r14, %rax
	imulq	%r13
	addq	%r14, %rdx
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$6, %rdx
	addq	%rax, %rdx
	imulq	$100, %rdx, %rax
	subq	%rax, %r14
	movabsq	$7378697629483820647, %rcx      # imm = 0x6666666666666667
	movq	%rsi, %rax
	imulq	%rcx
	movq	%rdx, %rcx
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$2, %rcx
	addq	%rax, %rcx
	movq	%rcx, %rax
	imulq	%r13
	addq	%rcx, %rdx
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$6, %rdx
	addq	%rax, %rdx
	imulq	$100, %rdx, %rax
	movq	%rcx, %r15
	subq	%rax, %r15
	addq	%rcx, %rcx
	leaq	(%rcx,%rcx,4), %rax
	subq	%rax, %rsi
	leaq	.L.str.13.bmb(%rip), %rcx
	callq	println_str
	movq	%rbx, %rcx
	callq	int_to_string
	leaq	.L.str.14.bmb(%rip), %rcx
	movq	%rax, %rdx
	callq	bmb_string_concat
	movq	%rax, %rcx
	callq	println_str
	movq	%rdi, %rcx
	callq	int_to_string
	leaq	.L.str.15.bmb(%rip), %rcx
	movq	%rax, %rdx
	callq	bmb_string_concat
	movq	%rax, %rcx
	callq	println_str
	movq	%r14, %rcx
	callq	int_to_string
	leaq	.L.str.16.bmb(%rip), %rcx
	movq	%rax, %rdx
	callq	bmb_string_concat
	movq	%rax, %rcx
	callq	println_str
	movq	%r15, %rcx
	callq	int_to_string
	leaq	.L.str.17.bmb(%rip), %rcx
	movq	%rax, %rdx
	callq	bmb_string_concat
	movq	%rax, %rcx
	callq	println_str
	movq	%rsi, %rcx
	callq	int_to_string
	leaq	.L.str.18.bmb(%rip), %rcx
	movq	%rax, %rdx
	callq	bmb_string_concat
	movq	%rax, %rcx
	callq	println_str
	leaq	.L.str.19.bmb(%rip), %rdi
	movq	%rdi, %rcx
	callq	println_str
	movl	$101, %ebx
	leaq	.L.str.11.bmb(%rip), %rsi
	.p2align	4
.LBB29_5:                               # %bb_else_1.i22
                                        # =>This Inner Loop Header: Depth=1
	movq	%rdi, %rcx
	movq	%rsi, %rdx
	callq	bmb_string_concat
	movq	%rax, %rdi
	decq	%rbx
	cmpq	$1, %rbx
	ja	.LBB29_5
# %bb.6:                                # %gen_large.exit
	xorl	%esi, %esi
	movq	%rdi, %rcx
	xorl	%edx, %edx
	callq	next_token
	movq	%rax, %rcx
	addq	$999999, %rax                   # imm = 0xF423F
	cmpq	$1999999, %rax                  # imm = 0x1E847F
	jb	.LBB29_10
# %bb.7:                                # %bb_else_1.i28.preheader
	xorl	%ebx, %ebx
	xorl	%esi, %esi
	xorl	%r14d, %r14d
	xorl	%r15d, %r15d
	xorl	%ebp, %ebp
	.p2align	4
.LBB29_8:                               # %bb_else_1.i28
                                        # =>This Inner Loop Header: Depth=1
	movq	%rcx, %rax
	imulq	%r12
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$18, %rdx
	addq	%rax, %rdx
	imulq	$1000000, %rdx, %rax            # imm = 0xF4240
	movq	%rcx, %rdx
	subq	%rax, %rdx
	leaq	-1000000(%rcx), %rax
	cmpq	$1000000, %rax                  # imm = 0xF4240
	adcq	$0, %rbp
	leaq	-2000000(%rcx), %rax
	cmpq	$1000000, %rax                  # imm = 0xF4240
	adcq	$0, %r15
	leaq	-4000000(%rcx), %rax
	cmpq	$1000000, %rax                  # imm = 0xF4240
	adcq	$0, %r14
	leaq	-5000000(%rcx), %rax
	cmpq	$1000000, %rax                  # imm = 0xF4240
	adcq	$0, %rsi
	addq	$-6000000, %rcx                 # imm = 0xFFA47280
	cmpq	$1000000, %rcx                  # imm = 0xF4240
	adcq	$0, %rbx
	movq	%rdi, %rcx
	callq	next_token
	movq	%rax, %rcx
	addq	$999999, %rax                   # imm = 0xF423F
	cmpq	$1999998, %rax                  # imm = 0x1E847E
	ja	.LBB29_8
# %bb.9:                                # %count_tokens_loop.exit72.loopexit
	imulq	$10000000, %rbp, %rax           # imm = 0x989680
	imulq	$100000, %r15, %rcx             # imm = 0x186A0
	addq	%rax, %rcx
	imulq	$1000, %r14, %rax               # imm = 0x3E8
	addq	%rcx, %rax
	leaq	(%rsi,%rsi,4), %rcx
	leaq	(%rax,%rcx,2), %rsi
	addq	%rbx, %rsi
	movabsq	$-2972493582642298179, %rbp     # imm = 0xD6BF94D5E57A42BD
.LBB29_10:                              # %count_tokens_loop.exit72
	movq	%rsi, %rax
	imulq	%rbp
	leaq	(%rdx,%rsi), %r10
	movq	%r10, %rax
	shrq	$63, %rax
	sarq	$23, %r10
	addq	%rax, %r10
	movq	%rsi, %rax
	movabsq	$3022314549036572937, %rcx      # imm = 0x29F16B11C6D1E109
	imulq	%rcx
	movq	%rdx, %rcx
	shrq	$63, %rcx
	sarq	$14, %rdx
	addq	%rdx, %rcx
	movq	%rcx, %rax
	imulq	%r13
	addq	%rcx, %rdx
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$6, %rdx
	addq	%rax, %rdx
	imulq	$100, %rdx, %r9
	movq	%rsi, %rax
	movabsq	$2361183241434822607, %rdx      # imm = 0x20C49BA5E353F7CF
	imulq	%rdx
	movq	%rdx, %r8
	shrq	$63, %r8
	sarq	$7, %rdx
	addq	%rdx, %r8
	movq	%r8, %rax
	imulq	%r13
	subq	%r9, %rcx
	addq	%r8, %rdx
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$6, %rdx
	addq	%rax, %rdx
	imulq	$100, %rdx, %rax
	subq	%rax, %r8
	movq	%rsi, %rax
	movabsq	$7378697629483820647, %rdx      # imm = 0x6666666666666667
	imulq	%rdx
	movq	%rdx, %r9
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$2, %r9
	addq	%rax, %r9
	movq	%r9, %rax
	imulq	%r13
	addq	%r9, %rdx
	movq	%rdx, %rax
	shrq	$63, %rax
	sarq	$6, %rdx
	addq	%rax, %rdx
	imulq	$100, %rdx, %rax
	movq	%r9, %rdx
	subq	%rax, %rdx
	addq	%r8, %rdx
	addq	%r9, %r9
	leaq	(%r9,%r9,4), %rax
	subq	%rax, %rsi
	addq	%r10, %rsi
	addq	%rcx, %rsi
	addq	%rdx, %rsi
	leaq	.L.str.20.bmb(%rip), %rcx
	callq	println_str
	movq	%rsi, %rcx
	callq	int_to_string
	leaq	.L.str.21.bmb(%rip), %rcx
	movq	%rax, %rdx
	callq	bmb_string_concat
	movq	%rax, %rcx
	callq	println_str
	leaq	.L.str.22.bmb(%rip), %rcx
	callq	println_str
	xorl	%eax, %eax
	addq	$40, %rsp
	popq	%rbx
	popq	%rbp
	popq	%rdi
	popq	%rsi
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
	retq
                                        # -- End function
	.section	.rdata,"dr"
.L.str.19:                              # @.str.19
	.zero	1

	.data
	.p2align	4, 0x0                          # @.str.19.bmb
.L.str.19.bmb:
	.quad	.L.str.19
	.quad	0                               # 0x0
	.quad	0                               # 0x0

	.section	.rdata,"dr"
.L.str.12:                              # @.str.12
	.asciz	"Lexer Benchmark"

	.data
	.p2align	4, 0x0                          # @.str.12.bmb
.L.str.12.bmb:
	.quad	.L.str.12
	.quad	15                              # 0xf
	.quad	15                              # 0xf

	.section	.rdata,"dr"
.L.str.2:                               # @.str.2
	.asciz	"9"

	.data
	.p2align	4, 0x0                          # @.str.2.bmb
.L.str.2.bmb:
	.quad	.L.str.2
	.quad	1                               # 0x1
	.quad	1                               # 0x1

	.section	.rdata,"dr"
.L.str.1:                               # @.str.1
	.asciz	"8"

	.data
	.p2align	4, 0x0                          # @.str.1.bmb
.L.str.1.bmb:
	.quad	.L.str.1
	.quad	1                               # 0x1
	.quad	1                               # 0x1

	.section	.rdata,"dr"
.L.str.5:                               # @.str.5
	.asciz	"5"

	.data
	.p2align	4, 0x0                          # @.str.5.bmb
.L.str.5.bmb:
	.quad	.L.str.5
	.quad	1                               # 0x1
	.quad	1                               # 0x1

	.section	.rdata,"dr"
.L.str.15:                              # @.str.15
	.asciz	"  Numbers: "

	.data
	.p2align	4, 0x0                          # @.str.15.bmb
.L.str.15.bmb:
	.quad	.L.str.15
	.quad	11                              # 0xb
	.quad	11                              # 0xb

	.section	.rdata,"dr"
	.p2align	4, 0x0                          # @.str.20
.L.str.20:
	.asciz	"Large source (100x):"

	.data
	.p2align	4, 0x0                          # @.str.20.bmb
.L.str.20.bmb:
	.quad	.L.str.20
	.quad	20                              # 0x14
	.quad	20                              # 0x14

	.section	.rdata,"dr"
.L.str.18:                              # @.str.18
	.asciz	"  Punctuation: "

	.data
	.p2align	4, 0x0                          # @.str.18.bmb
.L.str.18.bmb:
	.quad	.L.str.18
	.quad	15                              # 0xf
	.quad	15                              # 0xf

	.section	.rdata,"dr"
.L.str.0:                               # @.str.0
	.asciz	"-"

	.data
	.p2align	4, 0x0                          # @.str.0.bmb
.L.str.0.bmb:
	.quad	.L.str.0
	.quad	1                               # 0x1
	.quad	1                               # 0x1

	.section	.rdata,"dr"
.L.str.9:                               # @.str.9
	.asciz	"1"

	.data
	.p2align	4, 0x0                          # @.str.9.bmb
.L.str.9.bmb:
	.quad	.L.str.9
	.quad	1                               # 0x1
	.quad	1                               # 0x1

	.section	.rdata,"dr"
.L.str.3:                               # @.str.3
	.asciz	"7"

	.data
	.p2align	4, 0x0                          # @.str.3.bmb
.L.str.3.bmb:
	.quad	.L.str.3
	.quad	1                               # 0x1
	.quad	1                               # 0x1

	.section	.rdata,"dr"
.L.str.14:                              # @.str.14
	.asciz	"  Identifiers: "

	.data
	.p2align	4, 0x0                          # @.str.14.bmb
.L.str.14.bmb:
	.quad	.L.str.14
	.quad	15                              # 0xf
	.quad	15                              # 0xf

	.section	.rdata,"dr"
.L.str.6:                               # @.str.6
	.asciz	"4"

	.data
	.p2align	4, 0x0                          # @.str.6.bmb
.L.str.6.bmb:
	.quad	.L.str.6
	.quad	1                               # 0x1
	.quad	1                               # 0x1

	.section	.rdata,"dr"
.L.str.10:                              # @.str.10
	.asciz	"0"

	.data
	.p2align	4, 0x0                          # @.str.10.bmb
.L.str.10.bmb:
	.quad	.L.str.10
	.quad	1                               # 0x1
	.quad	1                               # 0x1

	.section	.rdata,"dr"
.L.str.16:                              # @.str.16
	.asciz	"  Keywords: "

	.data
	.p2align	4, 0x0                          # @.str.16.bmb
.L.str.16.bmb:
	.quad	.L.str.16
	.quad	12                              # 0xc
	.quad	12                              # 0xc

	.section	.rdata,"dr"
	.p2align	4, 0x0                          # @.str.11
.L.str.11:
	.asciz	"fn fibonacci(n: i64) -> i64 = if n <= 1 { n } else { fibonacci(n - 1) + fibonacci(n - 2) }; fn main() -> i64 = { let result = fibonacci(35); let x = 42; let y = 3.14159; if x > 10 { return result; } };"

	.data
	.p2align	4, 0x0                          # @.str.11.bmb
.L.str.11.bmb:
	.quad	.L.str.11
	.quad	201                             # 0xc9
	.quad	201                             # 0xc9

	.section	.rdata,"dr"
.L.str.7:                               # @.str.7
	.asciz	"3"

	.data
	.p2align	4, 0x0                          # @.str.7.bmb
.L.str.7.bmb:
	.quad	.L.str.7
	.quad	1                               # 0x1
	.quad	1                               # 0x1

	.section	.rdata,"dr"
.L.str.17:                              # @.str.17
	.asciz	"  Operators: "

	.data
	.p2align	4, 0x0                          # @.str.17.bmb
.L.str.17.bmb:
	.quad	.L.str.17
	.quad	13                              # 0xd
	.quad	13                              # 0xd

	.section	.rdata,"dr"
	.p2align	4, 0x0                          # @.str.21
.L.str.21:
	.asciz	"  Total tokens: "

	.data
	.p2align	4, 0x0                          # @.str.21.bmb
.L.str.21.bmb:
	.quad	.L.str.21
	.quad	16                              # 0x10
	.quad	16                              # 0x10

	.section	.rdata,"dr"
.L.str.22:                              # @.str.22
	.asciz	"Done."

	.data
	.p2align	4, 0x0                          # @.str.22.bmb
.L.str.22.bmb:
	.quad	.L.str.22
	.quad	5                               # 0x5
	.quad	5                               # 0x5

	.section	.rdata,"dr"
.L.str.8:                               # @.str.8
	.asciz	"2"

	.data
	.p2align	4, 0x0                          # @.str.8.bmb
.L.str.8.bmb:
	.quad	.L.str.8
	.quad	1                               # 0x1
	.quad	1                               # 0x1

	.section	.rdata,"dr"
.L.str.13:                              # @.str.13
	.asciz	"Small source:"

	.data
	.p2align	4, 0x0                          # @.str.13.bmb
.L.str.13.bmb:
	.quad	.L.str.13
	.quad	13                              # 0xd
	.quad	13                              # 0xd

	.section	.rdata,"dr"
.L.str.4:                               # @.str.4
	.asciz	"6"

	.data
	.p2align	4, 0x0                          # @.str.4.bmb
.L.str.4.bmb:
	.quad	.L.str.4
	.quad	1                               # 0x1
	.quad	1                               # 0x1

	.section	.rdata,"dr"
	.p2align	3, 0x0                          # @switch.table.digit_char
.Lswitch.table.digit_char:
	.quad	.L.str.10.bmb
	.quad	.L.str.9.bmb
	.quad	.L.str.8.bmb
	.quad	.L.str.7.bmb
	.quad	.L.str.6.bmb
	.quad	.L.str.5.bmb
	.quad	.L.str.4.bmb
	.quad	.L.str.3.bmb
	.quad	.L.str.1.bmb

	.addrsig
