.global _tertium_syscall
.type _tertium_syscall,@function
_tertium_syscall:
	movq %rdi,%rax
	movq %rsi,%rdi
	movq %rdx,%rsi
	movq %rcx,%rdx
	movq %r8,%r10
	movq %r9,%r8
	movq 8(%rsp),%r9
	syscall
	cmpq $-4095,%rax
	jbe .L1
	negq %rax
	movq %rax,errno(%rip)
	movq $-1,%rax
.L1:
	retq
