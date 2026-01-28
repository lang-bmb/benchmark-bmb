	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
@feat.00 = 0
	.file	"brainfuck_bitpack.ll"
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
	.def	tape_size;
	.scl	2;
	.type	32;
	.endef
	.globl	tape_size                       # -- Begin function tape_size
	.p2align	4
tape_size:                              # @tape_size
# %bb.0:                                # %bb_entry
	movl	$30000, %eax                    # imm = 0x7530
	retq
                                        # -- End function
	.def	tape_new;
	.scl	2;
	.type	32;
	.endef
	.globl	tape_new                        # -- Begin function tape_new
	.p2align	4
tape_new:                               # @tape_new
# %bb.0:                                # %alloca_entry
	movl	$30000, %ecx                    # imm = 0x7530
	movl	$8, %edx
	jmp	calloc                          # TAILCALL
                                        # -- End function
	.def	tape_free;
	.scl	2;
	.type	32;
	.endef
	.globl	tape_free                       # -- Begin function tape_free
	.p2align	4
tape_free:                              # @tape_free
# %bb.0:                                # %alloca_entry
	subq	$40, %rsp
	callq	free
	xorl	%eax, %eax
	addq	$40, %rsp
	retq
                                        # -- End function
	.def	tape_get;
	.scl	2;
	.type	32;
	.endef
	.globl	tape_get                        # -- Begin function tape_get
	.p2align	4
tape_get:                               # @tape_get
# %bb.0:                                # %alloca_entry
	movq	(%rcx,%rdx,8), %rax
	retq
                                        # -- End function
	.def	tape_set;
	.scl	2;
	.type	32;
	.endef
	.globl	tape_set                        # -- Begin function tape_set
	.p2align	4
tape_set:                               # @tape_set
# %bb.0:                                # %alloca_entry
	movq	%r8, (%rcx,%rdx,8)
	xorl	%eax, %eax
	retq
                                        # -- End function
	.def	get_char;
	.scl	2;
	.type	32;
	.endef
	.globl	get_char                        # -- Begin function get_char
	.p2align	4
get_char:                               # @get_char
# %bb.0:                                # %alloca_entry
	cmpq	8(%rcx), %rdx
	jge	.LBB6_1
# %bb.3:                                # %bb_else_1
	movq	(%rcx), %rax
	movzbl	(%rax,%rdx), %eax
	retq
.LBB6_1:
	xorl	%eax, %eax
	retq
                                        # -- End function
	.def	mask32;
	.scl	2;
	.type	32;
	.endef
	.globl	mask32                          # -- Begin function mask32
	.p2align	4
mask32:                                 # @mask32
# %bb.0:                                # %bb_entry
	movl	$4294967295, %eax               # imm = 0xFFFFFFFF
	retq
                                        # -- End function
	.def	pack;
	.scl	2;
	.type	32;
	.endef
	.globl	pack                            # -- Begin function pack
	.p2align	4
pack:                                   # @pack
# %bb.0:                                # %alloca_entry
	shlq	$32, %rcx
	movl	%edx, %eax
	orq	%rcx, %rax
	retq
                                        # -- End function
	.def	unpack_ptr;
	.scl	2;
	.type	32;
	.endef
	.globl	unpack_ptr                      # -- Begin function unpack_ptr
	.p2align	4
unpack_ptr:                             # @unpack_ptr
# %bb.0:                                # %alloca_entry
	movq	%rcx, %rax
	sarq	$32, %rax
	retq
                                        # -- End function
	.def	unpack_pc;
	.scl	2;
	.type	32;
	.endef
	.globl	unpack_pc                       # -- Begin function unpack_pc
	.p2align	4
unpack_pc:                              # @unpack_pc
# %bb.0:                                # %alloca_entry
	movl	%ecx, %eax
	retq
                                        # -- End function
	.def	find_matching_close;
	.scl	2;
	.type	32;
	.endef
	.globl	find_matching_close             # -- Begin function find_matching_close
	.p2align	4
find_matching_close:                    # @find_matching_close
# %bb.0:                                # %alloca_entry
	movq	%rdx, %rax
	movq	8(%rcx), %rdx
	movl	$1, %r8d
	jmp	.LBB11_1
.LBB11_5:                               # %bb_then_6
                                        #   in Loop: Header=BB11_1 Depth=1
	decq	%r8
	.p2align	4
.LBB11_6:                               # %bb_merge_5
                                        #   in Loop: Header=BB11_1 Depth=1
	testq	%r8, %r8
	jle	.LBB11_7
.LBB11_1:                               # %bb_while_body_1
                                        # =>This Inner Loop Header: Depth=1
	movq	%rax, %r9
	incq	%rax
	cmpq	%rdx, %rax
	jge	.LBB11_6
# %bb.2:                                # %get_char.exit
                                        #   in Loop: Header=BB11_1 Depth=1
	movq	(%rcx), %r10
	movzbl	1(%r10,%r9), %r9d
	cmpl	$93, %r9d
	je	.LBB11_5
# %bb.3:                                # %get_char.exit
                                        #   in Loop: Header=BB11_1 Depth=1
	cmpl	$91, %r9d
	jne	.LBB11_6
# %bb.4:                                # %bb_then_3
                                        #   in Loop: Header=BB11_1 Depth=1
	incq	%r8
	jmp	.LBB11_6
.LBB11_7:                               # %bb_while_exit_2
	retq
                                        # -- End function
	.def	find_matching_open;
	.scl	2;
	.type	32;
	.endef
	.globl	find_matching_open              # -- Begin function find_matching_open
	.p2align	4
find_matching_open:                     # @find_matching_open
# %bb.0:                                # %alloca_entry
	movq	%rdx, %rax
	movq	8(%rcx), %rdx
	movl	$1, %r8d
	jmp	.LBB12_1
.LBB12_5:                               # %bb_then_6
                                        #   in Loop: Header=BB12_1 Depth=1
	decq	%r8
	.p2align	4
.LBB12_6:                               # %bb_merge_5
                                        #   in Loop: Header=BB12_1 Depth=1
	decq	%rax
	testq	%r8, %r8
	jle	.LBB12_7
.LBB12_1:                               # %bb_while_body_1
                                        # =>This Inner Loop Header: Depth=1
	cmpq	%rdx, %rax
	jg	.LBB12_6
# %bb.2:                                # %get_char.exit
                                        #   in Loop: Header=BB12_1 Depth=1
	movq	(%rcx), %r9
	movzbl	-1(%r9,%rax), %r9d
	cmpl	$91, %r9d
	je	.LBB12_5
# %bb.3:                                # %get_char.exit
                                        #   in Loop: Header=BB12_1 Depth=1
	cmpl	$93, %r9d
	jne	.LBB12_6
# %bb.4:                                # %bb_then_3
                                        #   in Loop: Header=BB12_1 Depth=1
	incq	%r8
	jmp	.LBB12_6
.LBB12_7:                               # %bb_while_exit_2
	retq
                                        # -- End function
	.def	do_right;
	.scl	2;
	.type	32;
	.endef
	.globl	do_right                        # -- Begin function do_right
	.p2align	4
do_right:                               # @do_right
# %bb.0:                                # %alloca_entry
	incq	%rcx
	xorl	%eax, %eax
	cmpq	%rdx, %rcx
	cmovlq	%rcx, %rax
	retq
                                        # -- End function
	.def	do_left;
	.scl	2;
	.type	32;
	.endef
	.globl	do_left                         # -- Begin function do_left
	.p2align	4
do_left:                                # @do_left
# %bb.0:                                # %alloca_entry
	testq	%rcx, %rcx
	cmovneq	%rcx, %rdx
	leaq	-1(%rdx), %rax
	retq
                                        # -- End function
	.def	do_inc;
	.scl	2;
	.type	32;
	.endef
	.globl	do_inc                          # -- Begin function do_inc
	.p2align	4
do_inc:                                 # @do_inc
# %bb.0:                                # %alloca_entry
	incl	%ecx
	movzbl	%cl, %eax
	retq
                                        # -- End function
	.def	do_dec;
	.scl	2;
	.type	32;
	.endef
	.globl	do_dec                          # -- Begin function do_dec
	.p2align	4
do_dec:                                 # @do_dec
# %bb.0:                                # %alloca_entry
	decl	%ecx
	movzbl	%cl, %eax
	retq
                                        # -- End function
	.def	exec_instr;
	.scl	2;
	.type	32;
	.endef
	.globl	exec_instr                      # -- Begin function exec_instr
	.p2align	4
exec_instr:                             # @exec_instr
# %bb.0:                                # %alloca_entry
	pushq	%rsi
	pushq	%rdi
	subq	$40, %rsp
	addq	$-43, %r9
	cmpq	$50, %r9
	ja	.LBB17_6
# %bb.1:                                # %alloca_entry
	movq	96(%rsp), %rax
	leaq	.LJTI17_0(%rip), %r10
	movslq	(%r10,%r9,4), %r9
	addq	%r10, %r9
	jmpq	*%r9
.LBB17_4:                               # %bb_then_6
	movl	(%rcx,%rdx,8), %eax
	incl	%eax
	jmp	.LBB17_5
.LBB17_2:                               # %bb_then_0
	movq	%rdx, %rax
	shlq	$32, %rax
	movabsq	$4294967296, %rcx               # imm = 0x100000000
	addq	%rax, %rcx
	xorl	%r9d, %r9d
	cmpq	$29999, %rdx                    # imm = 0x752F
	cmovlq	%rcx, %r9
	movl	%r8d, %eax
	orq	%r9, %rax
	addq	$40, %rsp
	popq	%rdi
	popq	%rsi
	retq
.LBB17_11:                              # %bb_then_18
	cmpq	$0, (%rcx,%rdx,8)
	jne	.LBB17_6
# %bb.12:                               # %bb_then_21
	movq	8(%rax), %rcx
	movl	$1, %r9d
	jmp	.LBB17_13
.LBB17_17:                              # %bb_then_6.i
                                        #   in Loop: Header=BB17_13 Depth=1
	decq	%r9
	.p2align	4
.LBB17_18:                              # %bb_merge_5.i
                                        #   in Loop: Header=BB17_13 Depth=1
	testq	%r9, %r9
	jle	.LBB17_6
.LBB17_13:                              # %bb_while_body_1.i
                                        # =>This Inner Loop Header: Depth=1
	movq	%r8, %r10
	incq	%r8
	cmpq	%rcx, %r8
	jge	.LBB17_18
# %bb.14:                               # %get_char.exit.i
                                        #   in Loop: Header=BB17_13 Depth=1
	movq	(%rax), %r11
	movzbl	1(%r11,%r10), %r10d
	cmpl	$93, %r10d
	je	.LBB17_17
# %bb.15:                               # %get_char.exit.i
                                        #   in Loop: Header=BB17_13 Depth=1
	cmpl	$91, %r10d
	jne	.LBB17_18
# %bb.16:                               # %bb_then_3.i
                                        #   in Loop: Header=BB17_13 Depth=1
	incq	%r9
	jmp	.LBB17_18
.LBB17_19:                              # %bb_then_24
	cmpq	$0, (%rcx,%rdx,8)
	je	.LBB17_6
# %bb.20:                               # %bb_then_27
	movq	8(%rax), %rcx
	movl	$1, %r9d
	jmp	.LBB17_21
.LBB17_25:                              # %bb_then_6.i63
                                        #   in Loop: Header=BB17_21 Depth=1
	decq	%r9
	.p2align	4
.LBB17_26:                              # %bb_merge_5.i65
                                        #   in Loop: Header=BB17_21 Depth=1
	decq	%r8
	testq	%r9, %r9
	jle	.LBB17_6
.LBB17_21:                              # %bb_while_body_1.i57
                                        # =>This Inner Loop Header: Depth=1
	cmpq	%rcx, %r8
	jg	.LBB17_26
# %bb.22:                               # %get_char.exit.i59
                                        #   in Loop: Header=BB17_21 Depth=1
	movq	(%rax), %r10
	movzbl	-1(%r10,%r8), %r10d
	cmpl	$91, %r10d
	je	.LBB17_25
# %bb.23:                               # %get_char.exit.i59
                                        #   in Loop: Header=BB17_21 Depth=1
	cmpl	$93, %r10d
	jne	.LBB17_26
# %bb.24:                               # %bb_then_3.i68
                                        #   in Loop: Header=BB17_21 Depth=1
	incq	%r9
	jmp	.LBB17_26
.LBB17_8:                               # %bb_then_9
	movl	(%rcx,%rdx,8), %eax
	decl	%eax
.LBB17_5:                               # %common.ret
	movzbl	%al, %eax
	movq	%rax, (%rcx,%rdx,8)
.LBB17_6:                               # %bb_then_15
	shlq	$32, %rdx
.LBB17_7:                               # %common.ret
	movl	%r8d, %eax
	orq	%rdx, %rax
	addq	$40, %rsp
	popq	%rdi
	popq	%rsi
	retq
.LBB17_9:                               # %bb_then_12
	movq	(%rcx,%rdx,8), %rcx
	movq	%rdx, %rsi
	movq	%r8, %rdi
	callq	chr
	movq	%rax, %rcx
	callq	print_str
	shlq	$32, %rsi
	movl	%edi, %eax
	orq	%rsi, %rax
	addq	$40, %rsp
	popq	%rdi
	popq	%rsi
	retq
.LBB17_3:                               # %bb_then_3
	movq	%rdx, %rax
	shlq	$32, %rax
	movabsq	$-4294967296, %rcx              # imm = 0xFFFFFFFF00000000
	addq	%rax, %rcx
	testq	%rdx, %rdx
	movabsq	$128844723912704, %rdx          # imm = 0x752F00000000
	cmovneq	%rcx, %rdx
	jmp	.LBB17_7
	.section	.rdata,"dr"
	.p2align	2, 0x0
.LJTI17_0:
	.long	.LBB17_4-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_8-.LJTI17_0
	.long	.LBB17_9-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_3-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_2-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_11-.LJTI17_0
	.long	.LBB17_6-.LJTI17_0
	.long	.LBB17_19-.LJTI17_0
                                        # -- End function
	.def	interpret;
	.scl	2;
	.type	32;
	.endef
	.text
	.globl	interpret                       # -- Begin function interpret
	.p2align	4
interpret:                              # @interpret
# %bb.0:                                # %alloca_entry
	pushq	%rsi
	pushq	%rdi
	pushq	%rbx
	subq	$48, %rsp
	movq	%rcx, %rsi
	movl	$30000, %ecx                    # imm = 0x7530
	movl	$8, %edx
	callq	calloc
	movq	%rax, %rdi
	movq	8(%rsi), %rbx
	testq	%rbx, %rbx
	jle	.LBB18_6
# %bb.1:                                # %bb_while_body_1.preheader
	xorl	%edx, %edx
	xorl	%r8d, %r8d
	jmp	.LBB18_2
	.p2align	4
.LBB18_4:                               # %bb_else_1.i
                                        #   in Loop: Header=BB18_2 Depth=1
	movq	(%rsi), %rax
	movzbl	(%rax,%r8), %r9d
.LBB18_5:                               # %get_char.exit
                                        #   in Loop: Header=BB18_2 Depth=1
	movq	%rsi, 32(%rsp)
	movq	%rdi, %rcx
	callq	exec_instr
	movl	%eax, %r8d
	movq	%rax, %rdx
	sarq	$32, %rdx
	incq	%r8
	cmpq	%rbx, %r8
	jae	.LBB18_6
.LBB18_2:                               # %bb_while_body_1
                                        # =>This Inner Loop Header: Depth=1
	cmpq	8(%rsi), %r8
	jl	.LBB18_4
# %bb.3:                                #   in Loop: Header=BB18_2 Depth=1
	xorl	%r9d, %r9d
	jmp	.LBB18_5
.LBB18_6:                               # %bb_while_exit_2
	movq	%rdi, %rcx
	callq	free
	xorl	%eax, %eax
	addq	$48, %rsp
	popq	%rbx
	popq	%rdi
	popq	%rsi
	retq
                                        # -- End function
	.def	hello_world;
	.scl	2;
	.type	32;
	.endef
	.globl	hello_world                     # -- Begin function hello_world
	.p2align	4
hello_world:                            # @hello_world
# %bb.0:                                # %alloca_entry
	leaq	.L.str.0.bmb(%rip), %rax
	retq
                                        # -- End function
	.def	nested_loops;
	.scl	2;
	.type	32;
	.endef
	.globl	nested_loops                    # -- Begin function nested_loops
	.p2align	4
nested_loops:                           # @nested_loops
# %bb.0:                                # %alloca_entry
	leaq	.L.str.1.bmb(%rip), %rax
	retq
                                        # -- End function
	.def	add_test;
	.scl	2;
	.type	32;
	.endef
	.globl	add_test                        # -- Begin function add_test
	.p2align	4
add_test:                               # @add_test
# %bb.0:                                # %bb_entry
	leaq	.L.str.2.bmb(%rip), %rax
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
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	pushq	%rbx
	.seh_pushreg %rbx
	subq	$48, %rsp
	.seh_stackalloc 48
	.seh_endprologue
	leaq	.L.str.3.bmb(%rip), %rcx
	callq	println_str
	leaq	.L.str.4.bmb(%rip), %rcx
	callq	print_str
	movl	$30000, %ecx                    # imm = 0x7530
	movl	$8, %edx
	callq	calloc
	movq	%rax, %rsi
	movq	.L.str.0.bmb+8(%rip), %rdi
	testq	%rdi, %rdi
	jle	.LBB22_6
# %bb.1:                                # %bb_while_body_1.i.preheader
	xorl	%edx, %edx
	leaq	.L.str.0.bmb(%rip), %rbx
	xorl	%r8d, %r8d
	jmp	.LBB22_2
	.p2align	4
.LBB22_4:                               # %bb_else_1.i.i
                                        #   in Loop: Header=BB22_2 Depth=1
	movq	.L.str.0.bmb(%rip), %rax
	movzbl	(%rax,%r8), %r9d
.LBB22_5:                               # %get_char.exit.i
                                        #   in Loop: Header=BB22_2 Depth=1
	movq	%rbx, 32(%rsp)
	movq	%rsi, %rcx
	callq	exec_instr
	movl	%eax, %r8d
	movq	%rax, %rdx
	sarq	$32, %rdx
	incq	%r8
	cmpq	%rdi, %r8
	jae	.LBB22_6
.LBB22_2:                               # %bb_while_body_1.i
                                        # =>This Inner Loop Header: Depth=1
	cmpq	.L.str.0.bmb+8(%rip), %r8
	jl	.LBB22_4
# %bb.3:                                #   in Loop: Header=BB22_2 Depth=1
	xorl	%r9d, %r9d
	jmp	.LBB22_5
.LBB22_6:                               # %interpret.exit
	movq	%rsi, %rcx
	callq	free
	leaq	.L.str.5.bmb(%rip), %rcx
	callq	println_str
	leaq	.L.str.6.bmb(%rip), %rcx
	callq	print_str
	movl	$30000, %ecx                    # imm = 0x7530
	movl	$8, %edx
	callq	calloc
	movq	%rax, %rsi
	movq	.L.str.1.bmb+8(%rip), %rdi
	testq	%rdi, %rdi
	jle	.LBB22_12
# %bb.7:                                # %bb_while_body_1.i9.preheader
	xorl	%edx, %edx
	leaq	.L.str.1.bmb(%rip), %rbx
	xorl	%r8d, %r8d
	jmp	.LBB22_8
	.p2align	4
.LBB22_10:                              # %bb_else_1.i.i21
                                        #   in Loop: Header=BB22_8 Depth=1
	movq	.L.str.1.bmb(%rip), %rax
	movzbl	(%rax,%r8), %r9d
.LBB22_11:                              # %get_char.exit.i14
                                        #   in Loop: Header=BB22_8 Depth=1
	movq	%rbx, 32(%rsp)
	movq	%rsi, %rcx
	callq	exec_instr
	movl	%eax, %r8d
	movq	%rax, %rdx
	sarq	$32, %rdx
	incq	%r8
	cmpq	%rdi, %r8
	jae	.LBB22_12
.LBB22_8:                               # %bb_while_body_1.i9
                                        # =>This Inner Loop Header: Depth=1
	cmpq	.L.str.1.bmb+8(%rip), %r8
	jl	.LBB22_10
# %bb.9:                                #   in Loop: Header=BB22_8 Depth=1
	xorl	%r9d, %r9d
	jmp	.LBB22_11
.LBB22_12:                              # %interpret.exit26
	movq	%rsi, %rcx
	callq	free
	leaq	.L.str.5.bmb(%rip), %rcx
	callq	println_str
	leaq	.L.str.7.bmb(%rip), %rcx
	callq	print_str
	movl	$30000, %ecx                    # imm = 0x7530
	movl	$8, %edx
	callq	calloc
	movq	%rax, %rsi
	movq	.L.str.2.bmb+8(%rip), %rdi
	testq	%rdi, %rdi
	jle	.LBB22_18
# %bb.13:                               # %bb_while_body_1.i31.preheader
	xorl	%edx, %edx
	leaq	.L.str.2.bmb(%rip), %rbx
	xorl	%r8d, %r8d
	jmp	.LBB22_14
	.p2align	4
.LBB22_16:                              # %bb_else_1.i.i43
                                        #   in Loop: Header=BB22_14 Depth=1
	movq	.L.str.2.bmb(%rip), %rax
	movzbl	(%rax,%r8), %r9d
.LBB22_17:                              # %get_char.exit.i36
                                        #   in Loop: Header=BB22_14 Depth=1
	movq	%rbx, 32(%rsp)
	movq	%rsi, %rcx
	callq	exec_instr
	movl	%eax, %r8d
	movq	%rax, %rdx
	sarq	$32, %rdx
	incq	%r8
	cmpq	%rdi, %r8
	jae	.LBB22_18
.LBB22_14:                              # %bb_while_body_1.i31
                                        # =>This Inner Loop Header: Depth=1
	cmpq	.L.str.2.bmb+8(%rip), %r8
	jl	.LBB22_16
# %bb.15:                               #   in Loop: Header=BB22_14 Depth=1
	xorl	%r9d, %r9d
	jmp	.LBB22_17
.LBB22_18:                              # %interpret.exit48
	movq	%rsi, %rcx
	callq	free
	leaq	.L.str.5.bmb(%rip), %rcx
	callq	println_str
	leaq	.L.str.8.bmb(%rip), %rcx
	callq	println_str
	xorl	%eax, %eax
	.seh_startepilogue
	addq	$48, %rsp
	popq	%rbx
	popq	%rdi
	popq	%rsi
	.seh_endepilogue
	retq
	.seh_endproc
                                        # -- End function
	.section	.rdata,"dr"
	.p2align	4, 0x0                          # @.str.3
.L.str.3:
	.asciz	"Brainfuck Interpreter Benchmark"

	.data
	.p2align	4, 0x0                          # @.str.3.bmb
.L.str.3.bmb:
	.quad	.L.str.3
	.quad	31                              # 0x1f
	.quad	31                              # 0x1f

	.section	.rdata,"dr"
	.p2align	4, 0x0                          # @.str.1
.L.str.1:
	.asciz	"++++++++++[>++++++++++[>++++++++++[>+<-]<-]<-]>>>[-]++++++++[>+++++++++++<-]>.[-]++++++++++."

	.data
	.p2align	4, 0x0                          # @.str.1.bmb
.L.str.1.bmb:
	.quad	.L.str.1
	.quad	92                              # 0x5c
	.quad	92                              # 0x5c

	.section	.rdata,"dr"
	.p2align	4, 0x0                          # @.str.2
.L.str.2:
	.asciz	"++++++++[>++++++++<-]>."

	.data
	.p2align	4, 0x0                          # @.str.2.bmb
.L.str.2.bmb:
	.quad	.L.str.2
	.quad	23                              # 0x17
	.quad	23                              # 0x17

	.section	.rdata,"dr"
	.p2align	4, 0x0                          # @.str.7
.L.str.7:
	.asciz	"Add test (8*8=@): "

	.data
	.p2align	4, 0x0                          # @.str.7.bmb
.L.str.7.bmb:
	.quad	.L.str.7
	.quad	18                              # 0x12
	.quad	18                              # 0x12

	.section	.rdata,"dr"
.L.str.5:                               # @.str.5
	.zero	1

	.data
	.p2align	4, 0x0                          # @.str.5.bmb
.L.str.5.bmb:
	.quad	.L.str.5
	.quad	0                               # 0x0
	.quad	0                               # 0x0

	.section	.rdata,"dr"
	.p2align	4, 0x0                          # @.str.0
.L.str.0:
	.asciz	"++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++."

	.data
	.p2align	4, 0x0                          # @.str.0.bmb
.L.str.0.bmb:
	.quad	.L.str.0
	.quad	106                             # 0x6a
	.quad	106                             # 0x6a

	.section	.rdata,"dr"
.L.str.4:                               # @.str.4
	.asciz	"Hello World: "

	.data
	.p2align	4, 0x0                          # @.str.4.bmb
.L.str.4.bmb:
	.quad	.L.str.4
	.quad	13                              # 0xd
	.quad	13                              # 0xd

	.section	.rdata,"dr"
	.p2align	4, 0x0                          # @.str.6
.L.str.6:
	.asciz	"Nested loops (1000 iterations): "

	.data
	.p2align	4, 0x0                          # @.str.6.bmb
.L.str.6.bmb:
	.quad	.L.str.6
	.quad	32                              # 0x20
	.quad	32                              # 0x20

	.section	.rdata,"dr"
.L.str.8:                               # @.str.8
	.asciz	"Done."

	.data
	.p2align	4, 0x0                          # @.str.8.bmb
.L.str.8.bmb:
	.quad	.L.str.8
	.quad	5                               # 0x5
	.quad	5                               # 0x5

	.addrsig
