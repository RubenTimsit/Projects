
.section .text
_start:

    leaq vertices(%rip), %rdi 
    movb $-1, circle
    movq $0, %rcx
    movq $0, %rdx	
    movq $0, %rax
    movq $0, %rbx 
    movq $-1, %r10        
    movq $-1, %r11	
    movq $-1, %r12	
    movq $-1, %r13        
    movq $-1, %r14        
    movq $-1, %r15	
    movq $-1, %r8	 
    movq $-1, %rsp        
    
    cmpq $0, (%rdi)      
    je .end_hw1 
    
.numberOfTsmatimesloop_HW1:
    addq $1, %rdx
    addq $1, %rax	
    movq (%rdi,%rax,8), %rsi
    cmpq $0, %rsi
    jne .numberOfTsmatimesloop_HW1

    xor %rax, %rax    
    cmpq $0, (%rdi)
    je  .goodStartOfCode_HW1
    movq (%rdi), %r10
    cmpq $0, 8(%rdi)
    je  .goodStartOfCode_HW1
    movq 8(%rdi), %r11
    cmpq $0, 16(%rdi)
    je  .goodStartOfCode_HW1
    movq 16(%rdi), %r12
    cmpq $0, 24(%rdi)
    je  .goodStartOfCode_HW1
    movq 24(%rdi), %r13
    cmpq $0, 32(%rdi)
    je  .goodStartOfCode_HW1
    movq 32(%rdi), %r14
    cmpq $0, 40(%rdi)
    je  .goodStartOfCode_HW1
    movq 40(%rdi), %r15
    cmpq $0, 48(%rdi)
    je  .goodStartOfCode_HW1
    movq 48(%rdi), %r8
    cmpq $0, 56(%rdi)
    je  .goodStartOfCode_HW1
    movq 56(%rdi), %rsp

    
.goodStartOfCode_HW1:

    movq (%rdi), %rsi
    
.loop_HW1:
    cmpq $0, (%rsi)
    je .keepAsConnected_HW1

.loopCheckNeighbors_HW1:
    movq (%rsi,%rbx,8), %r9  #next neighbors
    addq $1, %rbx  
    cmpq %r10, %r9
    je .loopAfter_HW1
    cmpq %r11, %r9
    je .loopAfter_HW1
    cmpq %r12, %r9
    je .loopAfter_HW1
    cmpq $0, %r9
    cmpq %r13, %r9
    je .loopAfter_HW1
    cmpq %r14, %r9
    je .loopAfter_HW1
    cmpq %r15, %r9
    je .loopAfter_HW1
    cmpq %r8, %r9
    je .loopAfter_HW1
    cmpq %rsp, %r9
    je .loopAfter_HW1

    cmpq $0, %r9
    je .keepAsConnected_HW1
    jmp .loopCheckNeighbors_HW1
   

.loopAfter_HW1:
    addq $1, %rax	#next tsmztim
    xor %rbx, %rbx
    movq (%rdi,%rax,8), %rsi
    cmpq $0, %rsi
    je .is_circle_hw1
    cmpq %r10, %rsi
    je .loop_HW1
    cmpq %r11, %rsi
    je .loop_HW1
    cmpq %r12, %rsi
    je .loop_HW1
    cmpq %r13, %rsi
    je .loop_HW1
    cmpq %r14, %rsi
    je .loop_HW1
    cmpq %r15, %rsi
    je .loop_HW1
    cmpq %r8, %rsi
    je .loop_HW1
    cmpq %rsp, %rsi
    je .loop_HW1

    jmp .loopAfter_HW1


.keepAsConnected_HW1:
    cmpq %r10, %rsi
    je .r10Connected_HW1
    cmpq %r11, %rsi
    je .r11Connected_HW1
    cmpq %r12, %rsi
    je .r12Connected_HW1
    cmpq %r13, %rsi
    je .r13Connected_HW1
    cmpq %r14, %rsi
    je .r14Connected_HW1
    cmpq %r15, %rsi
    je .r15Connected_HW1
    cmpq %r8, %rsi
    je .r8Connected_HW1
    cmpq %rsp, %rsi
    je .rspConnected_HW1


.r10Connected_HW1:
    movq $-1, %r10
    addq $1, %rcx	    
    cmpq %rdx, %rcx
    je .end_hw1
    xor %rax, %rax
    subq $1, %rax	#next tsmztim
    jmp .loopAfter_HW1

.r11Connected_HW1:
    movq $-1, %r11
    addq $1, %rcx	    
    cmpq %rdx, %rcx 
    je .end_hw1
    xor %rax, %rax
    subq $1, %rax	#next tsmztim
    jmp .loopAfter_HW1


.r12Connected_HW1:
    movq $-1, %r12
    addq $1, %rcx	    
    cmpq %rdx, %rcx 
    je .end_hw1
    xor %rax, %rax
    subq $1, %rax	#next tsmztim
    jmp .loopAfter_HW1

.r13Connected_HW1:
    movq $-1, %r13
    addq $1, %rcx	    
    cmpq %rdx, %rcx 
    je .end_hw1
    xor %rax, %rax
    subq $1, %rax	#next tsmztim
    jmp .loopAfter_HW1
    
.r14Connected_HW1:
    movq $-1, %r14
    addq $1, %rcx	    
    cmpq %rdx, %rcx 
    je .end_hw1
    xor %rax, %rax
    subq $1, %rax	#next tsmztim
    jmp .loopAfter_HW1    
    
.r15Connected_HW1:
    movq $-1, %r15
    addq $1, %rcx	    
    cmpq %rdx, %rcx 
    je .end_hw1
    xor %rax, %rax
    subq $1, %rax	#next tsmztim
    jmp .loopAfter_HW1

.r8Connected_HW1:
    movq $-1, %r8
    addq $1, %rcx	    
    cmpq %rdx, %rcx 
    je .end_hw1
    xor %rax, %rax
    subq $1, %rax	#next tsmztim
    jmp .loopAfter_HW1
    
.rspConnected_HW1:
    movq $-1, %rsp
    addq $1, %rcx	    
    cmpq %rdx, %rcx 
    je .end_hw1
    xor %rax, %rax
    subq $1, %rax	#next tsmztim
    jmp .loopAfter_HW1
    
.is_circle_hw1:
    movb $1, circle
    
    
.end_hw1:


        
            
