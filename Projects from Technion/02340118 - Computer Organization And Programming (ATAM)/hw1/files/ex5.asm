.section .text
_start:
#your code here
	mov $0, %rcx   #i = 0
	movb $0, legal
	movl $0, integer

while_not_space_HW1:
	movzb command(,%rcx,1), %rax #load character value into rax
	cmp $0, %rax     #compare with end of string, not legal if equal
	je not_legal_HW1
	cmp $32, %rax   #Compare with space, jump to end if equal
	je found_space_HW1
	inc %rcx
	jmp while_not_space_HW1   #not a space

found_space_HW1:
	inc %rcx
	movzb command(,%rcx,1), %rax 
	cmp $36, %rax  #compare with $, not legal if not equal
	jne not_legal_HW1

	#Keep the index of the $ to keep track of it
	mov %rcx, %r12

	inc %rcx

	#the first digit after the $ should always be a number between 0 and 9
	movzb command(,%rcx,1), %rax  #contains the next value after $
	cmp $48, %rax   #%rax - 48 < 0
	jl not_legal_HW1      #if it's lower than 0 
	cmp $57, %rax   #%rax - 57 > 0
	jg not_legal_HW1      #if greater than 9

	cmp $48, %rax   #compare to see if hexa/octa/binary or decimal
	je hexa_or_octa_or_binary_HW1


# register pour mult
# r8 : 1
# r9 : basis 
# r10 : basis x basis 
	
decimal_HW1:              #rax already contains the value after $
	mov $1, %r8
	mov $10, %r9
	mov $100, %r10
	jmp pre_calculation_HW1

hexa_or_octa_or_binary_HW1:   #the value after $ is 0

	#Keep the index of the 0 to keep track of it
	mov %rcx, %r12

	inc %rcx
	movzb command(,%rcx,1), %rax  #contains the value after the first 0
	cmp $44, %rax # if it's a comma, then it's just mov $0,
	je legal_HW1
	cmp $98, %rax  #if the value is 'b' then we are binary
	je binary_HW1
	cmp $120, %rax   #if the value is 'x' then the number is hexa
	je hexa_HW1
	
	#Otherwise the number is octa

octa_HW1:
				#rcx is the index of the first value after 0
	inc %rcx   
	mov $1, %r8
	mov $8, %r9
	mov $64, %r10
	jmp pre_calculation_HW1

binary_HW1:

	#Keep the index of the 'b' to keep track of it
	mov %rcx, %r12

	inc %rcx
	mov $1, %r8
	mov $2, %r9
	mov $4, %r10
	jmp pre_calculation_HW1

hexa_HW1: 

	#Keep the index of the 'x' to keep track of it
	mov %rcx, %r12

	inc %rcx   
	mov $1, %r8
	mov $16, %r9
	mov $256, %r10
	jmp pre_calculation_HW1

pre_calculation_HW1:
	mov $0, %rdx  #int result = 0
	mov $1, %r11 # keep which step we are

while_not_comma_HW1:
	movzb command(,%rcx,1), %rax #load character value into rax
	cmp $0, %rax     #compare with end of string, not legal if equal
	je not_legal_HW1
	cmp $44, %rax   #Compare with comma, jump to end if equal
	je found_comma_HW1
	inc %rcx
	jmp while_not_comma_HW1   #not a comma

found_comma_HW1:
	#now %rcx is the index of the comma.
	#we have to calculate the number in reverse : 
	# first digit 
	# second digit x base (if there is)
	# third digit x base (if there is)

	dec %rcx #rcx is now the units number


calculation_HW1:

	movzb command(,%rcx,1), %rax   #contains the value of the previous char of the operand

	cmp $16, %r9
	je hexa_num_HW1
	cmp $8, %r9
	je octa_num_HW1
	cmp $2, %r9
	je binary_num_HW1

decimal_num_HW1:

	#compare with $, if equal then we arrived to a $ and have to check
	# with %r12 if the $ is the same as before	

	cmp $36, %rax   
	jne not_dollar_HW1
	cmp %rcx, %r12
	je legal_HW1

not_dollar_HW1:
	cmp $48, %rax # %rax - 48
	jl not_legal_HW1	
	cmp $57, %rax # %rax - 57
	jg not_legal_HW1
	sub $48, %rax  #now rax contains the real number and not the character
	jmp choose_calculation_HW1  

binary_num_HW1:

	#compare with 'b', if equal then we arrived to a $ and have to check
	# with %r12 if the 'b' is the same as before

	cmp $98, %rax
	jne not_b_HW1
	cmp %rcx, %r12
	je legal_HW1

not_b_HW1:
	cmp $48, %rax # %rax - 48
	jl not_legal_HW1
	cmp $49, %rax  #we already know rax >= 0, we just need to check that rax <= 1
	jg not_legal_HW1
	sub $48, %rax
	jmp choose_calculation_HW1
	
octa_num_HW1:

	#compare with 0, if equal then we arrived to a $ and have to check
	# with %r12 if the 0 is the same as before

	cmp $48, %rax   
	jne not_zero_HW1
	cmp %rcx, %r12
	je legal_HW1

not_zero_HW1:
	cmp $48, %rax # %rax - 48
	jl not_legal_HW1
	cmp $55, %rax    #if the number is greater than 7 then its not legal
	jg not_legal_HW1
	sub $48, %rax #now rax contains the real number and not the character
	jmp choose_calculation_HW1	
	
hexa_num_HW1:

	#compare with 'x', if equal then we arrived to a $ and have to check
	# with %r12 if the 'x' is the same as before

	cmp $120, %rax
	jne not_x_HW1
	cmp %rcx, %r12
	je legal_HW1

not_x_HW1:
	cmp $48, %rax       #check if 48 < char < 57, if greater than 57, then it could be a letter
	jl not_legal_HW1
	cmp $57, %rax
	jg letter_or_not_legal_HW1
	sub $48, %rax
	jmp choose_calculation_HW1
	
letter_or_not_legal_HW1:
	cmp $65, %rax
	jl not_legal_HW1
	cmp $70, %rax
	jg not_legal_HW1
	sub $55, %rax

choose_calculation_HW1:
	cmp $1, %r11  #if we finished the first step, we have tocalculate the first digit x 1
	je calculate_units_HW1
	cmp $2, %r11 #if we finished the second step, we have to calculate the second digit x base
	je calculate_decimals_HW1
	cmp $3, %r11 #if we finished the second step, we have to calculate the third digit x base x base
	je calculate_hundreds_HW1

calculate_units_HW1:	#number x r8 = 1, add %rax to result

	add %rax, %rdx
	dec %rcx
	inc %r11
	jmp calculation_HW1

calculate_decimals_HW1:

	imul %r9, %rax
	add %rax, %rdx
	dec %rcx
	inc %r11
	jmp calculation_HW1

calculate_hundreds_HW1:

	imul %r10, %rax
	add %rax, %rdx
	dec %rcx
	inc %r11
	jmp calculation_HW1

legal_HW1:
	movl %edx, integer
	movb $1, legal
	jmp return_HW1

not_legal_HW1:
	movl $0, integer
	movb $0, legal

return_HW1:
	movb legal, %sil
	

