.global __asm_syscall
.hidden __asm_syscall
.type __asm_syscall,@function
__asm_syscall:
	movq %rdi,%rax
	movq %rsi,%rdi
	movq %rdx,%rsi
	movq %rcx,%rdx
	movq %r8,%r10
	movq %r9,%r8
	movq 8(%rsp),%r9
	syscall
ret
