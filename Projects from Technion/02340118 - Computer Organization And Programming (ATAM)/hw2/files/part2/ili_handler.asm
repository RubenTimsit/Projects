.globl my_ili_handler

.text
.align 4, 0x90

my_ili_handler:

    pushq %rax
	pushq %rdi
    pushq %rbx
	pushq %rsi
	pushq %rdx
	pushq %rcx
	pushq %r8
	pushq %r9
	pushq %r10
	pushq %r11

  xorq %rbx, %rbx
  xorq %rax, %rax
  xorq %rdi, %rdi

  movq 80(%rsp), %rax 
  movw (%rax), %ax 
  
  cmpb $0x0F, %al
  jnz one_bit_HW3
  shr $8, %rax
  addq $1, %rbx
  
one_bit_HW3:
  addq $1, %rbx
  movzbq %al, %rdi

  call what_to_do

  cmpl $0, %eax
  jne good_return_HW3

call_previous_handler_HW3:

    popq %r11
	popq %r10
	popq %r9
	popq %r8
	popq %rcx
	popq %rdx
	popq %rsi
    popq %rbx
	popq %rdi
	popq %rax
  jmp *old_ili_handler
  iretq

good_return_HW3:
  addq %rbx, 80(%rsp)
	popq %r11
	popq %r10
	popq %r9
	popq %r8
	popq %rcx
	popq %rdx
	popq %rsi
    popq %rbx
	popq %rdi
	
    movq %rax, %rdi
    popq %rax

  iretq
