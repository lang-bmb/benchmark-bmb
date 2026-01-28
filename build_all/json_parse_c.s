	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
@feat.00 = 0
	.file	"main.c"
	.def	skip_ws;
	.scl	2;
	.type	32;
	.endef
	.text
	.globl	skip_ws                         # -- Begin function skip_ws
	.p2align	4
skip_ws:                                # @skip_ws
.seh_proc skip_ws
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	movl	%edx, %esi
	movslq	%edx, %rdx
	movzbl	(%rcx,%rdx), %eax
	testb	%al, %al
	je	.LBB0_4
# %bb.1:
	leaq	(%rdx,%rcx), %rdi
	incq	%rdi
	.p2align	4
.LBB0_2:                                # =>This Inner Loop Header: Depth=1
	movsbl	%al, %ecx
	callq	isspace
	testl	%eax, %eax
	je	.LBB0_4
# %bb.3:                                #   in Loop: Header=BB0_2 Depth=1
	incl	%esi
	movzbl	(%rdi), %eax
	incq	%rdi
	testb	%al, %al
	jne	.LBB0_2
.LBB0_4:
	movl	%esi, %eax
	.seh_startepilogue
	addq	$40, %rsp
	popq	%rdi
	popq	%rsi
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	parse_number;
	.scl	2;
	.type	32;
	.endef
	.globl	parse_number                    # -- Begin function parse_number
	.p2align	4
parse_number:                           # @parse_number
# %bb.0:
	movl	$0, (%r8)
	movslq	%edx, %r11
	movzbl	(%rcx,%r11), %edx
	xorl	%eax, %eax
	cmpb	$45, %dl
	sete	%al
	addl	%r11d, %eax
	movslq	%eax, %r9
	movsbl	(%rcx,%r9), %r9d
	addl	$-48, %r9d
	xorl	%r10d, %r10d
	cmpl	$9, %r9d
	ja	.LBB1_3
# %bb.1:
	xorl	%eax, %eax
	cmpb	$45, %dl
	sete	%al
	leaq	(%rax,%r11), %r10
                                        # kill: def $eax killed $eax killed $rax
	addl	%r11d, %eax
	addq	%r10, %rcx
	incq	%rcx
	xorl	%r10d, %r10d
	.p2align	4
.LBB1_2:                                # =>This Inner Loop Header: Depth=1
	leal	(%r10,%r10,4), %r10d
	leal	(%r9,%r10,2), %r10d
	movl	%r10d, (%r8)
	movsbl	(%rcx), %r9d
	addl	$-48, %r9d
	incl	%eax
	incq	%rcx
	cmpl	$10, %r9d
	jb	.LBB1_2
.LBB1_3:
	cmpb	$45, %dl
	jne	.LBB1_5
# %bb.4:
	negl	%r10d
	movl	%r10d, (%r8)
.LBB1_5:
	retq
                                        # -- End function
	.def	find_close;
	.scl	2;
	.type	32;
	.endef
	.globl	find_close                      # -- Begin function find_close
	.p2align	4
find_close:                             # @find_close
.seh_proc find_close
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	.seh_endprologue
	movl	%edx, %eax
	movslq	%edx, %rdx
	movzbl	(%rcx,%rdx), %r10d
	testb	%r10b, %r10b
	je	.LBB2_5
# %bb.1:
	addq	%rdx, %rcx
	incq	%rcx
	xorl	%edx, %edx
	jmp	.LBB2_2
	.p2align	4
.LBB2_4:                                #   in Loop: Header=BB2_2 Depth=1
	xorl	%r11d, %r11d
	cmpb	%r9b, %r10b
	sete	%r11b
	xorl	%esi, %esi
	cmpb	%r8b, %r10b
	sete	%sil
	addl	%esi, %edx
	subl	%r11d, %edx
	incl	%eax
	movzbl	(%rcx), %r10d
	incq	%rcx
	testb	%r10b, %r10b
	je	.LBB2_5
.LBB2_2:                                # =>This Inner Loop Header: Depth=1
	cmpb	%r9b, %r10b
	jne	.LBB2_4
# %bb.3:                                #   in Loop: Header=BB2_2 Depth=1
	testl	%edx, %edx
	jne	.LBB2_4
.LBB2_5:
	.seh_startepilogue
	popq	%rsi
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	count_array;
	.scl	2;
	.type	32;
	.endef
	.globl	count_array                     # -- Begin function count_array
	.p2align	4
count_array:                            # @count_array
.seh_proc count_array
# %bb.0:
	pushq	%r14
	.seh_pushreg %r14
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	pushq	%rbx
	.seh_pushreg %rbx
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	movl	%edx, %esi
	movq	%rcx, %rdi
	movslq	%edx, %rcx
	movzbl	(%rdi,%rcx), %eax
	testb	%al, %al
	je	.LBB3_4
# %bb.1:
	leaq	(%rcx,%rdi), %rbx
	incq	%rbx
	.p2align	4
.LBB3_2:                                # =>This Inner Loop Header: Depth=1
	movsbl	%al, %ecx
	callq	isspace
	testl	%eax, %eax
	je	.LBB3_4
# %bb.3:                                #   in Loop: Header=BB3_2 Depth=1
	incl	%esi
	movzbl	(%rbx), %eax
	incq	%rbx
	testb	%al, %al
	jne	.LBB3_2
.LBB3_4:
	movslq	%esi, %rbx
	xorl	%esi, %esi
	cmpb	$91, (%rdi,%rbx)
	jne	.LBB3_20
# %bb.5:
	movzbl	1(%rdi,%rbx), %eax
	incq	%rbx
	testb	%al, %al
	je	.LBB3_9
# %bb.6:
	leaq	(%rbx,%rdi), %r14
	incq	%r14
	.p2align	4
.LBB3_7:                                # =>This Inner Loop Header: Depth=1
	movsbl	%al, %ecx
	callq	isspace
	testl	%eax, %eax
	je	.LBB3_9
# %bb.8:                                #   in Loop: Header=BB3_7 Depth=1
	incl	%ebx
	movzbl	(%r14), %eax
	incq	%r14
	testb	%al, %al
	jne	.LBB3_7
.LBB3_9:
	movslq	%ebx, %rcx
	movzbl	(%rdi,%rcx), %eax
	testl	%eax, %eax
	je	.LBB3_19
# %bb.10:
	cmpl	$93, %eax
	je	.LBB3_20
# %bb.11:
	addq	%rdi, %rcx
	incq	%rcx
	movl	$1, %esi
	xorl	%edx, %edx
	jmp	.LBB3_12
	.p2align	4
.LBB3_18:                               #   in Loop: Header=BB3_12 Depth=1
	cmpb	$44, %al
	sete	%al
	testl	%edx, %edx
	sete	%r8b
	andb	%al, %r8b
	movzbl	%r8b, %eax
	addl	%eax, %esi
	movzbl	(%rcx), %eax
	incq	%rcx
	testb	%al, %al
	je	.LBB3_20
.LBB3_12:                               # =>This Inner Loop Header: Depth=1
	cmpb	$93, %al
	jne	.LBB3_14
# %bb.13:                               #   in Loop: Header=BB3_12 Depth=1
	testl	%edx, %edx
	je	.LBB3_20
.LBB3_14:                               #   in Loop: Header=BB3_12 Depth=1
	movzbl	%al, %r8d
	orl	$32, %r8d
	cmpl	$123, %r8d
	jne	.LBB3_16
# %bb.15:                               #   in Loop: Header=BB3_12 Depth=1
	incl	%edx
.LBB3_16:                               #   in Loop: Header=BB3_12 Depth=1
	cmpl	$125, %r8d
	jne	.LBB3_18
# %bb.17:                               #   in Loop: Header=BB3_12 Depth=1
	decl	%edx
	jmp	.LBB3_18
.LBB3_19:
	movl	$1, %esi
.LBB3_20:
	movl	%esi, %eax
	.seh_startepilogue
	addq	$40, %rsp
	popq	%rbx
	popq	%rdi
	popq	%rsi
	popq	%r14
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	validate_object;
	.scl	2;
	.type	32;
	.endef
	.globl	validate_object                 # -- Begin function validate_object
	.p2align	4
validate_object:                        # @validate_object
.seh_proc validate_object
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	subq	$32, %rsp
	.seh_stackalloc 32
	.seh_endprologue
	movslq	%edx, %rax
	movzbl	1(%rcx,%rax), %r8d
	testb	%r8b, %r8b
	je	.LBB4_1
# %bb.2:
	xorl	%edx, %edx
	jmp	.LBB4_3
	.p2align	4
.LBB4_5:                                #   in Loop: Header=BB4_3 Depth=1
	xorl	%r9d, %r9d
	cmpb	$125, %r8b
	sete	%r9b
	xorl	%r10d, %r10d
	cmpb	$123, %r8b
	sete	%r10b
	addl	%r10d, %edx
	subl	%r9d, %edx
	movzbl	2(%rcx,%rax), %r8d
	incq	%rax
	testb	%r8b, %r8b
	je	.LBB4_6
.LBB4_3:                                # =>This Inner Loop Header: Depth=1
	cmpb	$125, %r8b
	jne	.LBB4_5
# %bb.4:                                #   in Loop: Header=BB4_3 Depth=1
	testl	%edx, %edx
	jne	.LBB4_5
.LBB4_6:
	incl	%eax
	jmp	.LBB4_7
.LBB4_1:
	incq	%rax
.LBB4_7:
	movslq	%eax, %rsi
	callq	strlen
	xorl	%ecx, %ecx
	cmpq	%rsi, %rax
	seta	%cl
	movl	%ecx, %eax
	.seh_startepilogue
	addq	$32, %rsp
	popq	%rsi
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	validate_array;
	.scl	2;
	.type	32;
	.endef
	.globl	validate_array                  # -- Begin function validate_array
	.p2align	4
validate_array:                         # @validate_array
.seh_proc validate_array
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	subq	$32, %rsp
	.seh_stackalloc 32
	.seh_endprologue
	movslq	%edx, %rax
	movzbl	1(%rcx,%rax), %r8d
	testb	%r8b, %r8b
	je	.LBB5_1
# %bb.2:
	xorl	%edx, %edx
	jmp	.LBB5_3
	.p2align	4
.LBB5_5:                                #   in Loop: Header=BB5_3 Depth=1
	xorl	%r9d, %r9d
	cmpb	$93, %r8b
	sete	%r9b
	xorl	%r10d, %r10d
	cmpb	$91, %r8b
	sete	%r10b
	addl	%r10d, %edx
	subl	%r9d, %edx
	movzbl	2(%rcx,%rax), %r8d
	incq	%rax
	testb	%r8b, %r8b
	je	.LBB5_6
.LBB5_3:                                # =>This Inner Loop Header: Depth=1
	cmpb	$93, %r8b
	jne	.LBB5_5
# %bb.4:                                #   in Loop: Header=BB5_3 Depth=1
	testl	%edx, %edx
	jne	.LBB5_5
.LBB5_6:
	incl	%eax
	jmp	.LBB5_7
.LBB5_1:
	incq	%rax
.LBB5_7:
	movslq	%eax, %rsi
	callq	strlen
	xorl	%ecx, %ecx
	cmpq	%rsi, %rax
	seta	%cl
	movl	%ecx, %eax
	.seh_startepilogue
	addq	$32, %rsp
	popq	%rsi
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	find_string_end;
	.scl	2;
	.type	32;
	.endef
	.globl	find_string_end                 # -- Begin function find_string_end
	.p2align	4
find_string_end:                        # @find_string_end
# %bb.0:
	movl	%edx, %eax
	jmp	.LBB6_1
	.p2align	4
.LBB6_5:                                #   in Loop: Header=BB6_1 Depth=1
	incl	%eax
.LBB6_6:                                #   in Loop: Header=BB6_1 Depth=1
	incl	%eax
.LBB6_1:                                # =>This Inner Loop Header: Depth=1
	movslq	%eax, %rdx
	movzbl	(%rcx,%rdx), %edx
	cmpl	$92, %edx
	je	.LBB6_5
# %bb.2:                                #   in Loop: Header=BB6_1 Depth=1
	testl	%edx, %edx
	je	.LBB6_4
# %bb.3:                                #   in Loop: Header=BB6_1 Depth=1
	cmpl	$34, %edx
	jne	.LBB6_6
.LBB6_4:
	retq
                                        # -- End function
	.def	validate_string;
	.scl	2;
	.type	32;
	.endef
	.globl	validate_string                 # -- Begin function validate_string
	.p2align	4
validate_string:                        # @validate_string
.seh_proc validate_string
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	subq	$32, %rsp
	.seh_stackalloc 32
	.seh_endprologue
	jmp	.LBB7_1
	.p2align	4
.LBB7_5:                                #   in Loop: Header=BB7_1 Depth=1
	addl	$2, %edx
.LBB7_1:                                # =>This Inner Loop Header: Depth=1
	movslq	%edx, %rsi
	movzbl	1(%rcx,%rsi), %eax
	cmpl	$92, %eax
	je	.LBB7_5
# %bb.2:                                #   in Loop: Header=BB7_1 Depth=1
	incq	%rsi
	testl	%eax, %eax
	je	.LBB7_4
# %bb.3:                                #   in Loop: Header=BB7_1 Depth=1
	movl	%esi, %edx
	cmpl	$34, %eax
	jne	.LBB7_1
.LBB7_4:
	callq	strlen
	xorl	%ecx, %ecx
	cmpq	%rsi, %rax
	seta	%cl
	movl	%ecx, %eax
	.seh_startepilogue
	addq	$32, %rsp
	popq	%rsi
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.def	validate_json;
	.scl	2;
	.type	32;
	.endef
	.globl	validate_json                   # -- Begin function validate_json
	.p2align	4
validate_json:                          # @validate_json
.seh_proc validate_json
# %bb.0:
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	pushq	%rbx
	.seh_pushreg %rbx
	subq	$32, %rsp
	.seh_stackalloc 32
	.seh_endprologue
	movl	%edx, %edi
	movq	%rcx, %rsi
	movslq	%edx, %rcx
	movzbl	(%rsi,%rcx), %eax
	testb	%al, %al
	je	.LBB8_4
# %bb.1:
	leaq	(%rcx,%rsi), %rbx
	incq	%rbx
	.p2align	4
.LBB8_2:                                # =>This Inner Loop Header: Depth=1
	movsbl	%al, %ecx
	callq	isspace
	testl	%eax, %eax
	je	.LBB8_4
# %bb.3:                                #   in Loop: Header=BB8_2 Depth=1
	incl	%edi
	movzbl	(%rbx), %eax
	incq	%rbx
	testb	%al, %al
	jne	.LBB8_2
.LBB8_4:
	movslq	%edi, %rax
	movzbl	(%rsi,%rax), %ecx
	cmpl	$90, %ecx
	jg	.LBB8_12
# %bb.5:
	testl	%ecx, %ecx
	je	.LBB8_22
# %bb.6:
	cmpl	$34, %ecx
	je	.LBB8_8
	jmp	.LBB8_19
	.p2align	4
.LBB8_7:                                #   in Loop: Header=BB8_8 Depth=1
	addl	$2, %edi
.LBB8_8:                                # =>This Inner Loop Header: Depth=1
	movslq	%edi, %rbx
	movzbl	1(%rsi,%rbx), %eax
	cmpl	$92, %eax
	je	.LBB8_7
# %bb.9:                                #   in Loop: Header=BB8_8 Depth=1
	incq	%rbx
	testl	%eax, %eax
	je	.LBB8_11
# %bb.10:                               #   in Loop: Header=BB8_8 Depth=1
	movl	%ebx, %edi
	cmpl	$34, %eax
	jne	.LBB8_8
.LBB8_11:
	movq	%rsi, %rcx
	callq	strlen
	cmpq	%rbx, %rax
	jmp	.LBB8_29
.LBB8_12:
	cmpl	$91, %ecx
	je	.LBB8_23
# %bb.13:
	cmpl	$123, %ecx
	jne	.LBB8_19
# %bb.14:
	movzbl	1(%rsi,%rax), %r8d
	incq	%rax
	testb	%r8b, %r8b
	je	.LBB8_28
# %bb.15:
	leaq	(%rax,%rsi), %rcx
	incq	%rcx
	xorl	%edx, %edx
	jmp	.LBB8_17
	.p2align	4
.LBB8_16:                               #   in Loop: Header=BB8_17 Depth=1
	xorl	%r9d, %r9d
	cmpb	$125, %r8b
	sete	%r9b
	xorl	%r10d, %r10d
	cmpb	$123, %r8b
	sete	%r10b
	addl	%r10d, %edx
	subl	%r9d, %edx
	incl	%eax
	movzbl	(%rcx), %r8d
	incq	%rcx
	testb	%r8b, %r8b
	je	.LBB8_28
.LBB8_17:                               # =>This Inner Loop Header: Depth=1
	cmpb	$125, %r8b
	jne	.LBB8_16
# %bb.18:                               #   in Loop: Header=BB8_17 Depth=1
	testl	%edx, %edx
	jne	.LBB8_16
	jmp	.LBB8_28
.LBB8_19:
	movsbl	%cl, %eax
	leal	-48(%rax), %edx
	cmpl	$10, %edx
	setb	%dl
	cmpb	$45, %al
	sete	%al
	orb	%dl, %al
	movb	$1, %al
	jne	.LBB8_30
# %bb.20:
	addb	$-102, %cl
	cmpb	$14, %cl
	ja	.LBB8_22
# %bb.21:
	movl	$16641, %eax                    # imm = 0x4101
                                        # kill: def $cl killed $cl killed $ecx
	shrl	%cl, %eax
	jmp	.LBB8_30
.LBB8_22:
	xorl	%eax, %eax
	jmp	.LBB8_30
.LBB8_23:
	movzbl	1(%rsi,%rax), %r8d
	incq	%rax
	testb	%r8b, %r8b
	je	.LBB8_28
# %bb.24:
	leaq	(%rax,%rsi), %rcx
	incq	%rcx
	xorl	%edx, %edx
	jmp	.LBB8_26
	.p2align	4
.LBB8_25:                               #   in Loop: Header=BB8_26 Depth=1
	xorl	%r9d, %r9d
	cmpb	$93, %r8b
	sete	%r9b
	xorl	%r10d, %r10d
	cmpb	$91, %r8b
	sete	%r10b
	addl	%r10d, %edx
	subl	%r9d, %edx
	incl	%eax
	movzbl	(%rcx), %r8d
	incq	%rcx
	testb	%r8b, %r8b
	je	.LBB8_28
.LBB8_26:                               # =>This Inner Loop Header: Depth=1
	cmpb	$93, %r8b
	jne	.LBB8_25
# %bb.27:                               #   in Loop: Header=BB8_26 Depth=1
	testl	%edx, %edx
	jne	.LBB8_25
.LBB8_28:
	movslq	%eax, %rdi
	movq	%rsi, %rcx
	callq	strlen
	cmpq	%rdi, %rax
.LBB8_29:
	seta	%al
.LBB8_30:
	movzbl	%al, %eax
	andl	$1, %eax
	.seh_startepilogue
	addq	$32, %rsp
	popq	%rbx
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
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	subq	$40, %rsp
	.seh_stackalloc 40
	.seh_endprologue
	leaq	"??_C@_0BH@NABBNEHN@?$FL1?02?03?04?05?06?07?08?09?010?$FN?$AA@"(%rip), %rsi
	movq	%rsi, %rcx
	xorl	%edx, %edx
	callq	validate_json
	movl	%eax, %edi
	movq	%rsi, %rcx
	xorl	%edx, %edx
	callq	count_array
	addl	%edi, %eax
	imull	$10000, %eax, %edx              # imm = 0x2710
	leaq	"??_C@_04PEDNGLFL@?$CFld?6?$AA@"(%rip), %rcx
	callq	printf
	xorl	%eax, %eax
	.seh_startepilogue
	addq	$40, %rsp
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
	.section	.rdata,"dr",discard,"??_C@_0BH@NABBNEHN@?$FL1?02?03?04?05?06?07?08?09?010?$FN?$AA@"
	.globl	"??_C@_0BH@NABBNEHN@?$FL1?02?03?04?05?06?07?08?09?010?$FN?$AA@" # @"??_C@_0BH@NABBNEHN@?$FL1?02?03?04?05?06?07?08?09?010?$FN?$AA@"
"??_C@_0BH@NABBNEHN@?$FL1?02?03?04?05?06?07?08?09?010?$FN?$AA@":
	.asciz	"[1,2,3,4,5,6,7,8,9,10]"

	.section	.rdata,"dr",discard,"??_C@_04PEDNGLFL@?$CFld?6?$AA@"
	.globl	"??_C@_04PEDNGLFL@?$CFld?6?$AA@" # @"??_C@_04PEDNGLFL@?$CFld?6?$AA@"
"??_C@_04PEDNGLFL@?$CFld?6?$AA@":
	.asciz	"%ld\n"

	.lcomm	__local_stdio_printf_options._OptionsStorage,8,8 # @__local_stdio_printf_options._OptionsStorage
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
	.addrsig_sym __local_stdio_printf_options._OptionsStorage
