.global _start

.section .text
_start:
#your code here
	movb $0, result #result = 0 by default
	movq head, %rdi  # %rdi contains the adress of the first node
	cmpq $0, %rdi
	je strictly_increasing_HW1 #there is no "head", the list is strictly increasing trivially

test_strictly_increasing_HW1:

loop_strictly_increasing_HW1:
	movq (%rdi), %rbx  # %rbx contains the data of the current node
	movq 8(%rdi), %rcx # load the adress of the next node for the check
	test %rcx, %rcx 
	je strictly_increasing_HW1   #if we arrived to the end of the list
	movq (%rcx), %rcx  # %rcx contains the data of the next node
	cmp %rbx, %rcx     # current->next->data - current->data
	jle not_strictly_increasing_HW1 	   # current->next->data - current->data <= 0 
					   # => not strictly increasing
	movq 8(%rdi), %rdi  # advance to the next node	
	jmp loop_strictly_increasing_HW1	

not_strictly_increasing_HW1:
	mov $0, %r8  # Keeps track of the number of tries we did

test_increasing_HW1: 
	movq head, %rdi  # %rdi contains the adress of the first node
loop_increasing_HW1:
	movq (%rdi), %rbx  # %rbx contains the data of the current node
	movq 8(%rdi), %rcx # load the adress of the next node for the check
	test %rcx, %rcx    # if we arrived to the end of the list
	je increasing_or_semi_HW1
	movq (%rcx), %rcx  # %rcx contains the data of the next node
	cmp %rbx, %rcx     # current->next->data - current->data
	jl test_almost_increasing_HW1 	   # current->next->data - current->data < 0 
					   # => not increasing
	movq 8(%rdi), %rdi  # advance to the next node	
	jmp loop_increasing_HW1

test_almost_increasing_HW1:
	# currently %rdi contains the adress of the current element that causes 
	# current->next->data < current->data 
	# Strategy : 
	# Remove current
	# test_increasing, try #1
	# Remove next
	# test_increasing, try #2
	# if the list is still not increasing, then it is not semi increasing

	add $1, %r8  # Update %r8, compare to see if we are on the third try,
	cmp $3, %r8  # In which case the list is not semi increasing
	je return_HW1  #therefore it's neither of the cases
	cmp $2, %r8 # see if we are on second try
	je second_try_HW1
		
	# First try, Remove current, extreme cases if current is first/second
	cmp head, %rdi   #check if current is the first element of the list
	je remove_first_HW1
	movq head, %r11
	cmp 8(%r11), %rdi   #check if current is the second element of the list
	je remove_second_HW1
	movq 8(%rdi), %rdi # current = current->next
	#that way we cut out current
	jmp test_increasing_HW1

remove_first_HW1:
	movq 8(%rdi), %r9  # move first->next into temp register 
	movq %r9, head     #head = first->next
	#that way we cut out the first element
	# if the first element causes issue, it should be the only one 
	#in order for the list to be semi increasing
	movq $2, %r8  # don't let the program run if failed
	jmp test_increasing_HW1 

remove_second_HW1:  #same logic as above, but here we let it run the second try
	movq 8(%rdi), %r9  
	movq %r9, 8(%r11)
	jmp test_increasing_HW1

second_try_HW1:
	# second try, remove current->next

	movq 8(%rdi), %r9 #Move current->next into temp register
	movq 8(%r9), %r10 # Move current->next->next into temp register	
	movq %r10, 8(%rdi) # current->next = current->next->next
	# that way we cut out current->next
	jmp test_increasing_HW1

strictly_increasing_HW1:
	movb $3, result
	jmp return_HW1

increasing_or_semi_HW1:
	cmp $0, %r8  #if we got increasing on the first try
	je increasing_HW1  
	movb $1, result  # at this point, the list is semi increasing
	jmp return_HW1

increasing_HW1:
	movb $2, result
	jmp return_HW1
	
almost_increasing_HW1:
	movb $1, result
	jmp return_HW1

return_HW1:
