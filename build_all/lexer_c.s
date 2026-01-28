	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
@feat.00 = 0
	.file	"main.c"
	.def	main;
	.scl	2;
	.type	32;
	.endef
	.text
	.globl	main                            # -- Begin function main
	.p2align	4
main:                                   # @main
.seh_proc main
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	pushq	%rbx
	.seh_pushreg %rbx
	subq	$80, %rsp
	.seh_stackalloc 80
	.seh_endprologue
	leaq	.Lstr(%rip), %rcx
	callq	puts
	leaq	"??_C@_0BFC@DIEADGJB@fn?5fibonacci?$CIn?3?5i64?$CJ?5?9?$DO?5i64?5?$DN?6?5?5@"(%rip), %rsi
	leaq	32(%rsp), %rdx
	movq	%rsi, %rcx
	callq	count_tokens
	leaq	.Lstr.1(%rip), %rcx
	callq	puts
	movl	36(%rsp), %edx
	leaq	"??_C@_0BD@IAJDINBD@?5?5Identifiers?3?5?$CFd?6?$AA@"(%rip), %rcx
	callq	printf
	movl	40(%rsp), %edx
	leaq	"??_C@_0P@LLKBJJNG@?5?5Numbers?3?5?$CFd?6?$AA@"(%rip), %rcx
	callq	printf
	movl	48(%rsp), %edx
	leaq	"??_C@_0BA@MOHMKHOB@?5?5Keywords?3?5?$CFd?6?$AA@"(%rip), %rcx
	callq	printf
	movl	44(%rsp), %edx
	leaq	"??_C@_0P@KAMPHJHF@?5?5Strings?3?5?$CFd?6?$AA@"(%rip), %rcx
	callq	printf
	movl	52(%rsp), %edx
	leaq	"??_C@_0BB@DIBHJLMH@?5?5Operators?3?5?$CFd?6?$AA@"(%rip), %rcx
	callq	printf
	movl	56(%rsp), %edx
	leaq	"??_C@_0BD@CCMPHMFP@?5?5Punctuation?3?5?$CFd?6?$AA@"(%rip), %rcx
	callq	printf
	movl	60(%rsp), %edx
	leaq	"??_C@_0BA@KFFAIFLK@?5?5Comments?3?5?$CFd?6?$AA@"(%rip), %rcx
	callq	printf
	movl	$10, %ecx
	callq	putchar
	movb	$0, large_source(%rip)
	movl	$100, %ebx
	leaq	large_source(%rip), %rdi
	.p2align	4
.LBB0_1:                                # =>This Inner Loop Header: Depth=1
	movq	%rdi, %rcx
	callq	strlen
	leaq	(%rax,%rdi), %rcx
	movl	$338, %r8d                      # imm = 0x152
	movq	%rsi, %rdx
	callq	memcpy
	decl	%ebx
	jne	.LBB0_1
# %bb.2:
	leaq	large_source(%rip), %rcx
	leaq	32(%rsp), %rdx
	callq	count_tokens
	movdqu	36(%rsp), %xmm0
	pshufd	$238, %xmm0, %xmm1              # xmm1 = xmm0[2,3,2,3]
	paddd	%xmm0, %xmm1
	pshufd	$85, %xmm1, %xmm0               # xmm0 = xmm1[1,1,1,1]
	paddd	%xmm1, %xmm0
	movd	%xmm0, %eax
	addl	52(%rsp), %eax
	movl	56(%rsp), %esi
	addl	60(%rsp), %esi
	addl	%eax, %esi
	leaq	.Lstr.2(%rip), %rcx
	callq	puts
	leaq	"??_C@_0BE@IGPIKNDP@?5?5Total?5tokens?3?5?$CFd?6?$AA@"(%rip), %rcx
	movl	%esi, %edx
	callq	printf
	leaq	.Lstr.3(%rip), %rcx
	callq	puts
	xorl	%eax, %eax
	.seh_startepilogue
	addq	$80, %rsp
	popq	%rbx
	popq	%rdi
	popq	%rsi
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	printf;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,printf
	.globl	printf                          # -- Begin function printf
	.p2align	4
printf:                                 # @printf
.seh_proc printf
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	pushq	%rbx
	.seh_pushreg %rbx
	subq	$48, %rsp
	.seh_stackalloc 48
	.seh_endprologue
	movq	%rcx, %rsi
	movq	%rdx, 88(%rsp)
	movq	%r8, 96(%rsp)
	movq	%r9, 104(%rsp)
	leaq	88(%rsp), %rbx
	movq	%rbx, 40(%rsp)
	movl	$1, %ecx
	callq	__acrt_iob_func
	movq	%rax, %rdi
	callq	__local_stdio_printf_options
	movq	(%rax), %rcx
	movq	%rbx, 32(%rsp)
	movq	%rdi, %rdx
	movq	%rsi, %r8
	xorl	%r9d, %r9d
	callq	__stdio_common_vfprintf
	nop
	.seh_startepilogue
	addq	$48, %rsp
	popq	%rbx
	popq	%rdi
	popq	%rsi
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	count_tokens;
	.scl	3;
	.type	32;
	.endef
	.text
	.p2align	4                               # -- Begin function count_tokens
count_tokens:                           # @count_tokens
.seh_proc count_tokens
# %bb.0:
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
	subq	$88, %rsp
	.seh_stackalloc 88
	.seh_endprologue
	movq	%rdx, %rsi
	movq	%rcx, %rdi
	callq	strlen
	movq	%rax, %rbx
	xorps	%xmm0, %xmm0
	movups	%xmm0, (%rsi)
	movups	%xmm0, 16(%rsi)
	movl	$0, 32(%rsi)
	leal	-1(%rax), %ebp
	xorl	%r14d, %r14d
.LBB2_1:                                # =>This Loop Header: Depth=1
                                        #     Child Loop BB2_2 Depth 2
                                        #     Child Loop BB2_59 Depth 2
                                        #     Child Loop BB2_18 Depth 2
                                        #     Child Loop BB2_21 Depth 2
                                        #     Child Loop BB2_10 Depth 2
	leaq	"??_C@_0M@BHPJPHLP@?$CL?9?$CK?1?$CF?$DN?$DM?$DO?$CB?$CG?$HM?$AA@"(%rip), %r15
	.p2align	4
.LBB2_2:                                #   Parent Loop BB2_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	cmpl	%ebx, %r14d
	jl	.LBB2_4
# %bb.3:                                #   in Loop: Header=BB2_2 Depth=2
	xorl	%ecx, %ecx
	callq	isspace
	testl	%eax, %eax
	jne	.LBB2_2
	jmp	.LBB2_72
.LBB2_4:                                #   in Loop: Header=BB2_2 Depth=2
	movslq	%r14d, %r12
	movsbl	(%rdi,%r12), %r13d
	movl	%r13d, %ecx
	callq	isspace
	testl	%eax, %eax
	je	.LBB2_6
# %bb.5:                                #   in Loop: Header=BB2_2 Depth=2
	incl	%r14d
	jmp	.LBB2_2
	.p2align	4
.LBB2_6:                                #   in Loop: Header=BB2_1 Depth=1
	movl	%ebp, 44(%rsp)                  # 4-byte Spill
	leaq	(%rdi,%r12), %rbp
	cmpb	$45, %r13b
	jne	.LBB2_14
# %bb.7:                                #   in Loop: Header=BB2_1 Depth=1
	leaq	1(%r12), %rax
	cmpl	%ebx, %eax
	jge	.LBB2_14
# %bb.8:                                #   in Loop: Header=BB2_1 Depth=1
	cmpb	$45, (%rdi,%rax)
	jne	.LBB2_14
# %bb.9:                                #   in Loop: Header=BB2_1 Depth=1
	movl	%r14d, %r15d
	.p2align	4
.LBB2_10:                               #   Parent Loop BB2_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movzbl	(%rbp), %eax
	testl	%eax, %eax
	je	.LBB2_54
# %bb.11:                               #   in Loop: Header=BB2_10 Depth=2
	cmpl	$10, %eax
	je	.LBB2_54
# %bb.12:                               #   in Loop: Header=BB2_10 Depth=2
	incl	%r15d
	incq	%rbp
	cmpl	%r15d, %ebx
	jne	.LBB2_10
# %bb.13:                               #   in Loop: Header=BB2_1 Depth=1
	movl	$7, %eax
	movl	%ebx, %r15d
	jmp	.LBB2_55
	.p2align	4
.LBB2_14:                               #   in Loop: Header=BB2_1 Depth=1
	movl	%r13d, %ecx
	callq	isalpha
	cmpb	$95, %r13b
	je	.LBB2_20
# %bb.15:                               #   in Loop: Header=BB2_1 Depth=1
	testl	%eax, %eax
	jne	.LBB2_20
# %bb.16:                               #   in Loop: Header=BB2_1 Depth=1
	leal	-48(%r13), %eax
	cmpl	$9, %eax
	ja	.LBB2_45
# %bb.17:                               #   in Loop: Header=BB2_1 Depth=1
	leaq	1(%rdi), %rax
	addq	%rax, %r12
	movl	%r14d, %r15d
	movl	44(%rsp), %ebp                  # 4-byte Reload
	.p2align	4
.LBB2_18:                               #   Parent Loop BB2_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	$2, %eax
	cmpl	%r15d, %ebp
	je	.LBB2_53
# %bb.19:                               #   in Loop: Header=BB2_18 Depth=2
	movsbl	(%r12), %ecx
	cmpl	$46, %ecx
	setne	%dl
	addl	$-48, %ecx
	cmpl	$10, %ecx
	setae	%cl
	incq	%r12
	incl	%r15d
	testb	%cl, %dl
	je	.LBB2_18
	jmp	.LBB2_71
.LBB2_20:                               #   in Loop: Header=BB2_1 Depth=1
	movl	$28262, %r12d                   # imm = 0x6E66
	movl	%r14d, %r15d
	.p2align	4
.LBB2_21:                               #   Parent Loop BB2_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	cmpl	%ebx, %r15d
	jl	.LBB2_23
# %bb.22:                               #   in Loop: Header=BB2_21 Depth=2
	xorl	%ecx, %ecx
	callq	isalnum
	testl	%eax, %eax
	jne	.LBB2_21
	jmp	.LBB2_26
.LBB2_23:                               #   in Loop: Header=BB2_21 Depth=2
	movslq	%r15d, %rax
	movsbl	(%rdi,%rax), %r13d
	movl	%r13d, %ecx
	callq	isalnum
	cmpl	$95, %r13d
	je	.LBB2_25
# %bb.24:                               #   in Loop: Header=BB2_21 Depth=2
	testl	%eax, %eax
	je	.LBB2_26
.LBB2_25:                               #   in Loop: Header=BB2_21 Depth=2
	incl	%r15d
	jmp	.LBB2_21
.LBB2_26:                               #   in Loop: Header=BB2_1 Depth=1
	movl	%r15d, %eax
	subl	%r14d, %eax
	cmpl	$32, %eax
	jl	.LBB2_28
# %bb.27:                               #   in Loop: Header=BB2_1 Depth=1
	movl	$1, %eax
	jmp	.LBB2_55
.LBB2_28:                               #   in Loop: Header=BB2_1 Depth=1
	movslq	%eax, %r13
	leaq	48(%rsp), %rcx
	movq	%rbp, %rdx
	movq	%r13, %r8
	callq	strncpy
	movb	$0, 48(%rsp,%r13)
	movl	48(%rsp), %eax
	xorl	%r12d, %eax
	movzbl	50(%rsp), %ecx
	orw	%ax, %cx
	je	.LBB2_52
# %bb.29:                               #   in Loop: Header=BB2_1 Depth=1
	movl	48(%rsp), %eax
	cmpl	$7628140, %eax                  # imm = 0x74656C
	je	.LBB2_52
# %bb.30:                               #   in Loop: Header=BB2_1 Depth=1
	movl	48(%rsp), %ecx
	movl	$26217, %edx                    # imm = 0x6669
	xorl	%edx, %ecx
	movzbl	50(%rsp), %edx
	orw	%cx, %dx
	je	.LBB2_52
# %bb.31:                               #   in Loop: Header=BB2_1 Depth=1
	movl	48(%rsp), %ecx
	movl	$1702063205, %edx               # imm = 0x65736C65
	xorl	%edx, %ecx
	movzbl	52(%rsp), %edx
	orl	%ecx, %edx
	je	.LBB2_52
# %bb.32:                               #   in Loop: Header=BB2_1 Depth=1
	movl	48(%rsp), %ecx
	movl	$1818847351, %edx               # imm = 0x6C696877
	xorl	%edx, %ecx
	movzwl	52(%rsp), %edx
	xorl	$101, %edx
	orl	%ecx, %edx
	je	.LBB2_52
# %bb.33:                               #   in Loop: Header=BB2_1 Depth=1
	cmpl	$7499622, %eax                  # imm = 0x726F66
	je	.LBB2_52
# %bb.34:                               #   in Loop: Header=BB2_1 Depth=1
	movl	48(%rsp), %eax
	movl	$1970562418, %ecx               # imm = 0x75746572
	xorl	%ecx, %eax
	movl	51(%rsp), %ecx
	movl	$7238261, %edx                  # imm = 0x6E7275
	xorl	%edx, %ecx
	orl	%eax, %ecx
	je	.LBB2_52
# %bb.35:                               #   in Loop: Header=BB2_1 Depth=1
	movl	48(%rsp), %eax
	movl	$1702195828, %ecx               # imm = 0x65757274
	xorl	%ecx, %eax
	movzbl	52(%rsp), %ecx
	orl	%eax, %ecx
	je	.LBB2_52
# %bb.36:                               #   in Loop: Header=BB2_1 Depth=1
	movl	48(%rsp), %eax
	movl	$1936482662, %ecx               # imm = 0x736C6166
	xorl	%ecx, %eax
	movzwl	52(%rsp), %ecx
	xorl	$101, %ecx
	orl	%eax, %ecx
	je	.LBB2_52
# %bb.37:                               #   in Loop: Header=BB2_1 Depth=1
	movl	48(%rsp), %eax
	movl	$1819047278, %ecx               # imm = 0x6C6C756E
	xorl	%ecx, %eax
	movzbl	52(%rsp), %ecx
	orl	%eax, %ecx
	je	.LBB2_52
# %bb.38:                               #   in Loop: Header=BB2_1 Depth=1
	movl	48(%rsp), %eax
	movl	$1970435187, %ecx               # imm = 0x75727473
	xorl	%ecx, %eax
	movl	51(%rsp), %ecx
	movl	$7627637, %edx                  # imm = 0x746375
	xorl	%edx, %ecx
	orl	%eax, %ecx
	je	.LBB2_52
# %bb.39:                               #   in Loop: Header=BB2_1 Depth=1
	movl	48(%rsp), %eax
	movl	$1836412517, %ecx               # imm = 0x6D756E65
	xorl	%ecx, %eax
	movzbl	52(%rsp), %ecx
	orl	%eax, %ecx
	je	.LBB2_52
# %bb.40:                               #   in Loop: Header=BB2_1 Depth=1
	movl	48(%rsp), %eax
	bswapl	%eax
	movl	$1835103331, %ecx               # imm = 0x6D617463
	cmpl	$1835103331, %eax               # imm = 0x6D617463
	jne	.LBB2_42
# %bb.41:                               #   in Loop: Header=BB2_1 Depth=1
	movzwl	52(%rsp), %eax
	rolw	$8, %ax
	movzwl	%ax, %eax
	movl	$26624, %ecx                    # imm = 0x6800
	xorl	%edx, %edx
	cmpl	$26624, %eax                    # imm = 0x6800
	je	.LBB2_43
.LBB2_42:                               #   in Loop: Header=BB2_1 Depth=1
	xorl	%edx, %edx
	cmpl	%ecx, %eax
	setae	%dl
	leal	-1(,%rdx,2), %edx
.LBB2_43:                               #   in Loop: Header=BB2_1 Depth=1
	movl	$1, %eax
	testl	%edx, %edx
	movl	44(%rsp), %ebp                  # 4-byte Reload
	jne	.LBB2_71
# %bb.44:                               #   in Loop: Header=BB2_1 Depth=1
	movl	$4, %eax
	jmp	.LBB2_71
.LBB2_45:                               #   in Loop: Header=BB2_1 Depth=1
	movzbl	%r13b, %eax
	cmpb	$62, %al
	movl	44(%rsp), %ebp                  # 4-byte Reload
	ja	.LBB2_63
# %bb.46:                               #   in Loop: Header=BB2_1 Depth=1
	movabsq	$8070450815715770368, %rcx      # imm = 0x7000004200000000
	btq	%rax, %rcx
	jae	.LBB2_56
.LBB2_47:                               #   in Loop: Header=BB2_1 Depth=1
	incq	%r12
	cmpl	%ebx, %r12d
	jge	.LBB2_64
# %bb.48:                               #   in Loop: Header=BB2_1 Depth=1
	movzbl	(%rdi,%r12), %eax
	cmpl	$38, %eax
	je	.LBB2_51
# %bb.49:                               #   in Loop: Header=BB2_1 Depth=1
	cmpl	$124, %eax
	je	.LBB2_51
# %bb.50:                               #   in Loop: Header=BB2_1 Depth=1
	cmpl	$61, %eax
	jne	.LBB2_64
.LBB2_51:                               #   in Loop: Header=BB2_1 Depth=1
	addl	$2, %r14d
	jmp	.LBB2_66
.LBB2_52:                               #   in Loop: Header=BB2_1 Depth=1
	movl	44(%rsp), %ebp                  # 4-byte Reload
	movl	$4, %eax
	jmp	.LBB2_71
.LBB2_53:                               #   in Loop: Header=BB2_1 Depth=1
	movl	%ebx, %r15d
	jmp	.LBB2_71
.LBB2_54:                               #   in Loop: Header=BB2_1 Depth=1
	movl	$7, %eax
.LBB2_55:                               #   in Loop: Header=BB2_1 Depth=1
	movl	44(%rsp), %ebp                  # 4-byte Reload
	jmp	.LBB2_71
.LBB2_56:                               #   in Loop: Header=BB2_1 Depth=1
	cmpq	$34, %rax
	jne	.LBB2_63
# %bb.57:                               #   in Loop: Header=BB2_1 Depth=1
	incl	%r14d
	movl	$3, %eax
	cmpl	%ebx, %r14d
	jge	.LBB2_70
# %bb.58:                               #   in Loop: Header=BB2_1 Depth=1
	movl	%r14d, %r15d
.LBB2_59:                               #   Parent Loop BB2_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movslq	%r15d, %rcx
	movzbl	(%rdi,%rcx), %ecx
	testl	%ecx, %ecx
	je	.LBB2_70
# %bb.60:                               #   in Loop: Header=BB2_59 Depth=2
	cmpl	$34, %ecx
	je	.LBB2_69
# %bb.61:                               #   in Loop: Header=BB2_59 Depth=2
	xorl	%edx, %edx
	cmpb	$92, %cl
	sete	%dl
	movl	%r15d, %r8d
	addl	%edx, %r8d
	xorl	%r15d, %r15d
	cmpl	%ebx, %r8d
	setl	%r15b
	addl	%r8d, %r15d
	cmpl	%ebx, %r8d
	cmovll	%r15d, %r14d
	cmpb	$92, %cl
	cmovel	%r15d, %r14d
	cmpl	%ebx, %r15d
	jl	.LBB2_59
	jmp	.LBB2_70
.LBB2_63:                               #   in Loop: Header=BB2_1 Depth=1
	cmpl	$124, %eax
	je	.LBB2_47
.LBB2_64:                               #   in Loop: Header=BB2_1 Depth=1
	movl	$12, %r8d
	movq	%r15, %rcx
	movl	%r13d, %edx
	callq	memchr
	testq	%rax, %rax
	je	.LBB2_67
# %bb.65:                               #   in Loop: Header=BB2_1 Depth=1
	incl	%r14d
.LBB2_66:                               #   in Loop: Header=BB2_1 Depth=1
	movl	$5, %eax
	jmp	.LBB2_70
.LBB2_67:                               #   in Loop: Header=BB2_1 Depth=1
	movl	$11, %r8d
	leaq	"??_C@_0L@LMDJFAEM@?$CI?$CJ?$HL?$HN?$FL?$FN?$DL?3?0?4?$AA@"(%rip), %rcx
	movl	%r13d, %edx
	callq	memchr
	xorl	%ecx, %ecx
	testq	%rax, %rax
	sete	%cl
	incl	%r14d
	leaq	6(,%rcx,2), %rax
.LBB2_70:                               #   in Loop: Header=BB2_1 Depth=1
	movl	%r14d, %r15d
.LBB2_71:                               #   in Loop: Header=BB2_1 Depth=1
	incl	(%rsi,%rax,4)
	movl	%r15d, %r14d
	jmp	.LBB2_1
.LBB2_69:                               #   in Loop: Header=BB2_1 Depth=1
	incl	%r15d
	jmp	.LBB2_71
.LBB2_72:
	.seh_startepilogue
	addq	$88, %rsp
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
	.def	__local_stdio_printf_options;
	.scl	2;
	.type	32;
	.endef
	.section	.text,"xr",discard,__local_stdio_printf_options
	.globl	__local_stdio_printf_options    # -- Begin function __local_stdio_printf_options
	.p2align	4
__local_stdio_printf_options:           # @__local_stdio_printf_options
# %bb.0:
	leaq	__local_stdio_printf_options._OptionsStorage(%rip), %rax
	retq
                                        # -- End function
	.section	.rdata,"dr",discard,"??_C@_0BD@IAJDINBD@?5?5Identifiers?3?5?$CFd?6?$AA@"
	.globl	"??_C@_0BD@IAJDINBD@?5?5Identifiers?3?5?$CFd?6?$AA@" # @"??_C@_0BD@IAJDINBD@?5?5Identifiers?3?5?$CFd?6?$AA@"
"??_C@_0BD@IAJDINBD@?5?5Identifiers?3?5?$CFd?6?$AA@":
	.asciz	"  Identifiers: %d\n"

	.section	.rdata,"dr",discard,"??_C@_0P@LLKBJJNG@?5?5Numbers?3?5?$CFd?6?$AA@"
	.globl	"??_C@_0P@LLKBJJNG@?5?5Numbers?3?5?$CFd?6?$AA@" # @"??_C@_0P@LLKBJJNG@?5?5Numbers?3?5?$CFd?6?$AA@"
"??_C@_0P@LLKBJJNG@?5?5Numbers?3?5?$CFd?6?$AA@":
	.asciz	"  Numbers: %d\n"

	.section	.rdata,"dr",discard,"??_C@_0BA@MOHMKHOB@?5?5Keywords?3?5?$CFd?6?$AA@"
	.globl	"??_C@_0BA@MOHMKHOB@?5?5Keywords?3?5?$CFd?6?$AA@" # @"??_C@_0BA@MOHMKHOB@?5?5Keywords?3?5?$CFd?6?$AA@"
"??_C@_0BA@MOHMKHOB@?5?5Keywords?3?5?$CFd?6?$AA@":
	.asciz	"  Keywords: %d\n"

	.section	.rdata,"dr",discard,"??_C@_0P@KAMPHJHF@?5?5Strings?3?5?$CFd?6?$AA@"
	.globl	"??_C@_0P@KAMPHJHF@?5?5Strings?3?5?$CFd?6?$AA@" # @"??_C@_0P@KAMPHJHF@?5?5Strings?3?5?$CFd?6?$AA@"
"??_C@_0P@KAMPHJHF@?5?5Strings?3?5?$CFd?6?$AA@":
	.asciz	"  Strings: %d\n"

	.section	.rdata,"dr",discard,"??_C@_0BB@DIBHJLMH@?5?5Operators?3?5?$CFd?6?$AA@"
	.globl	"??_C@_0BB@DIBHJLMH@?5?5Operators?3?5?$CFd?6?$AA@" # @"??_C@_0BB@DIBHJLMH@?5?5Operators?3?5?$CFd?6?$AA@"
"??_C@_0BB@DIBHJLMH@?5?5Operators?3?5?$CFd?6?$AA@":
	.asciz	"  Operators: %d\n"

	.section	.rdata,"dr",discard,"??_C@_0BD@CCMPHMFP@?5?5Punctuation?3?5?$CFd?6?$AA@"
	.globl	"??_C@_0BD@CCMPHMFP@?5?5Punctuation?3?5?$CFd?6?$AA@" # @"??_C@_0BD@CCMPHMFP@?5?5Punctuation?3?5?$CFd?6?$AA@"
"??_C@_0BD@CCMPHMFP@?5?5Punctuation?3?5?$CFd?6?$AA@":
	.asciz	"  Punctuation: %d\n"

	.section	.rdata,"dr",discard,"??_C@_0BA@KFFAIFLK@?5?5Comments?3?5?$CFd?6?$AA@"
	.globl	"??_C@_0BA@KFFAIFLK@?5?5Comments?3?5?$CFd?6?$AA@" # @"??_C@_0BA@KFFAIFLK@?5?5Comments?3?5?$CFd?6?$AA@"
"??_C@_0BA@KFFAIFLK@?5?5Comments?3?5?$CFd?6?$AA@":
	.asciz	"  Comments: %d\n"

	.lcomm	large_source,100000,16          # @large_source
	.section	.rdata,"dr",discard,"??_C@_0BE@IGPIKNDP@?5?5Total?5tokens?3?5?$CFd?6?$AA@"
	.globl	"??_C@_0BE@IGPIKNDP@?5?5Total?5tokens?3?5?$CFd?6?$AA@" # @"??_C@_0BE@IGPIKNDP@?5?5Total?5tokens?3?5?$CFd?6?$AA@"
"??_C@_0BE@IGPIKNDP@?5?5Total?5tokens?3?5?$CFd?6?$AA@":
	.asciz	"  Total tokens: %d\n"

	.lcomm	__local_stdio_printf_options._OptionsStorage,8,8 # @__local_stdio_printf_options._OptionsStorage
	.section	.rdata,"dr",discard,"??_C@_0M@BHPJPHLP@?$CL?9?$CK?1?$CF?$DN?$DM?$DO?$CB?$CG?$HM?$AA@"
	.globl	"??_C@_0M@BHPJPHLP@?$CL?9?$CK?1?$CF?$DN?$DM?$DO?$CB?$CG?$HM?$AA@" # @"??_C@_0M@BHPJPHLP@?$CL?9?$CK?1?$CF?$DN?$DM?$DO?$CB?$CG?$HM?$AA@"
"??_C@_0M@BHPJPHLP@?$CL?9?$CK?1?$CF?$DN?$DM?$DO?$CB?$CG?$HM?$AA@":
	.asciz	"+-*/%=<>!&|"

	.section	.rdata,"dr",discard,"??_C@_0L@LMDJFAEM@?$CI?$CJ?$HL?$HN?$FL?$FN?$DL?3?0?4?$AA@"
	.globl	"??_C@_0L@LMDJFAEM@?$CI?$CJ?$HL?$HN?$FL?$FN?$DL?3?0?4?$AA@" # @"??_C@_0L@LMDJFAEM@?$CI?$CJ?$HL?$HN?$FL?$FN?$DL?3?0?4?$AA@"
"??_C@_0L@LMDJFAEM@?$CI?$CJ?$HL?$HN?$FL?$FN?$DL?3?0?4?$AA@":
	.asciz	"(){}[];:,."

	.section	.rdata,"dr",discard,"??_C@_02LHJKNHFG@fn?$AA@"
	.globl	"??_C@_02LHJKNHFG@fn?$AA@"      # @"??_C@_02LHJKNHFG@fn?$AA@"
"??_C@_02LHJKNHFG@fn?$AA@":
	.asciz	"fn"

	.section	.rdata,"dr",discard,"??_C@_02HEBPBKGD@if?$AA@"
	.globl	"??_C@_02HEBPBKGD@if?$AA@"      # @"??_C@_02HEBPBKGD@if?$AA@"
"??_C@_02HEBPBKGD@if?$AA@":
	.asciz	"if"

	.section	.rdata,"dr",discard,"??_C@_04FHMCPBIP@else?$AA@"
	.globl	"??_C@_04FHMCPBIP@else?$AA@"    # @"??_C@_04FHMCPBIP@else?$AA@"
"??_C@_04FHMCPBIP@else?$AA@":
	.asciz	"else"

	.section	.rdata,"dr",discard,"??_C@_05OODBEKIG@while?$AA@"
	.globl	"??_C@_05OODBEKIG@while?$AA@"   # @"??_C@_05OODBEKIG@while?$AA@"
"??_C@_05OODBEKIG@while?$AA@":
	.asciz	"while"

	.section	.rdata,"dr",discard,"??_C@_06LNOFJDNM@return?$AA@"
	.globl	"??_C@_06LNOFJDNM@return?$AA@"  # @"??_C@_06LNOFJDNM@return?$AA@"
"??_C@_06LNOFJDNM@return?$AA@":
	.asciz	"return"

	.section	.rdata,"dr",discard,"??_C@_04LOAJBDKD@true?$AA@"
	.globl	"??_C@_04LOAJBDKD@true?$AA@"    # @"??_C@_04LOAJBDKD@true?$AA@"
"??_C@_04LOAJBDKD@true?$AA@":
	.asciz	"true"

	.section	.rdata,"dr",discard,"??_C@_05LAPONLG@false?$AA@"
	.globl	"??_C@_05LAPONLG@false?$AA@"    # @"??_C@_05LAPONLG@false?$AA@"
"??_C@_05LAPONLG@false?$AA@":
	.asciz	"false"

	.section	.rdata,"dr",discard,"??_C@_04MLLLIHIP@null?$AA@"
	.globl	"??_C@_04MLLLIHIP@null?$AA@"    # @"??_C@_04MLLLIHIP@null?$AA@"
"??_C@_04MLLLIHIP@null?$AA@":
	.asciz	"null"

	.section	.rdata,"dr",discard,"??_C@_06PBJBIPGK@struct?$AA@"
	.globl	"??_C@_06PBJBIPGK@struct?$AA@"  # @"??_C@_06PBJBIPGK@struct?$AA@"
"??_C@_06PBJBIPGK@struct?$AA@":
	.asciz	"struct"

	.section	.rdata,"dr",discard,"??_C@_04DBJPMPLO@enum?$AA@"
	.globl	"??_C@_04DBJPMPLO@enum?$AA@"    # @"??_C@_04DBJPMPLO@enum?$AA@"
"??_C@_04DBJPMPLO@enum?$AA@":
	.asciz	"enum"

	.section	.rdata,"dr",discard,"??_C@_05FNONLPDI@match?$AA@"
	.globl	"??_C@_05FNONLPDI@match?$AA@"   # @"??_C@_05FNONLPDI@match?$AA@"
"??_C@_05FNONLPDI@match?$AA@":
	.asciz	"match"

	.section	.rdata,"dr",discard,"??_C@_0BFC@DIEADGJB@fn?5fibonacci?$CIn?3?5i64?$CJ?5?9?$DO?5i64?5?$DN?6?5?5@"
	.globl	"??_C@_0BFC@DIEADGJB@fn?5fibonacci?$CIn?3?5i64?$CJ?5?9?$DO?5i64?5?$DN?6?5?5@" # @"??_C@_0BFC@DIEADGJB@fn?5fibonacci?$CIn?3?5i64?$CJ?5?9?$DO?5i64?5?$DN?6?5?5@"
"??_C@_0BFC@DIEADGJB@fn?5fibonacci?$CIn?3?5i64?$CJ?5?9?$DO?5i64?5?$DN?6?5?5@":
	.asciz	"fn fibonacci(n: i64) -> i64 =\n    if n <= 1 { n }\n    else { fibonacci(n - 1) + fibonacci(n - 2) };\n\nfn main() -> i64 = {\n    let result = fibonacci(35);\n    -- This is a comment\n    let x = 42;\n    let y = 3.14159;\n    let s = \"Hello, World!\";\n    if x > 10 && y < 100.0 {\n        return result;\n    } else {\n        return 0;\n    }\n};\n"

	.section	.rdata,"dr"
.Lstr:                                  # @str
	.asciz	"Lexer Benchmark"

.Lstr.1:                                # @str.1
	.asciz	"Small source:"

.Lstr.2:                                # @str.2
	.asciz	"Large source (100x):"

.Lstr.3:                                # @str.3
	.asciz	"\nDone."

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
	.short	22                              # Frontend version
	.short	1
	.short	0
	.short	0
	.short	22010                           # Backend version
	.short	0
	.short	0
	.short	0
	.asciz	"clang version 22.1.0-rc1 (https://github.com/llvm/llvm-project 8164f1a0c17b192e133817436bdb07598b7402a3)" # Null-terminated compiler version string
	.p2align	2, 0x0
.Ltmp5:
.Ltmp1:
	.p2align	2, 0x0
	.addrsig
	.addrsig_sym large_source
	.addrsig_sym __local_stdio_printf_options._OptionsStorage
