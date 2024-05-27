	.global _start
	.section .text
	_start:
	#your code here
		movb character, %al
		cmpb $97, %al         #%al - 97
		jl .not_a_lower_letter_HW1   # %al - 97 < 0 => %al < 97 => %al is not a letter
		# we know %al >= 97
		cmpb $122, %al
		jle .case_lower_letter_HW1  # %al - 122 <= 0 => %al <= 122 

	.not_a_lower_letter_HW1:
		cmpb $48, %al     #0
		je .case_0_HW1
		cmpb $50, %al     #2
		je .case_2_HW1
		cmpb $54, %al     #6
		je .case_6_HW1
		cmpb $49, %al    #1
		je .case_1_3_4_5_HW1
		cmpb $51, %al    #3
		je .case_1_3_4_5_HW1
		cmpb $52, %al    #4
		je .case_1_3_4_5_HW1
		cmpb $53, %al    #5
		je .case_1_3_4_5_HW1
		cmpb $55, %al    #7
		je .case_7_9_HW1
		cmpb $57, %al    #9
		je .case_7_9_HW1
		cmpb $56, %al    #8
		je .case_8_HW1
		cmpb $'`', %al
		je .case_special_1_HW1
		cmpb $'-', %al
		je .case_special_2_HW1
		cmpb $'=', %al
		je .case_equal_HW1
		cmpb $'[', %al
		je .case_brackets_slash_HW1
		cmpb $']', %al
		je .case_brackets_slash_HW1
		cmpb $'\\', %al
		je .case_brackets_slash_HW1
		cmpb $';', %al
		je .case_special_6_HW1
		cmpb $39, %al
		je .case_special_7_HW1
		cmpb $',', %al
		je .case_special_9_10_11_HW1
		cmpb $'.', %al
		je .case_special_9_10_11_HW1
		cmpb $'/', %al
		je .case_special_9_10_11_HW1

# Check if the character is in the right part of the table

		cmpb $62, %al  #%al - 62 < 0
		jl .not_within_62_64_HW1
		cmpb $90, %al    #al - 90 <= 0
		jle .case_right_part_HW1
		
	.not_within_62_64_HW1:
		cmpb $58, %al
		je .return_HW1
		cmpb $60, %al
		je .return_HW1
		cmpb $94, %al
		je .return_HW1
		cmpb $95, %al
		je .return_HW1

		cmpb $33, %al
		jl .not_within_33_48_HW1
		cmpb $38, %al 
		jle .case_right_part_HW1

	.not_within_33_48_HW1:

		cmpb $40, %al
		jl .not_within_40_43_HW1
		cmpb $43, %al 
		jle .case_right_part_HW1

	.not_within_40_43_HW1:

		cmpb $123, %al
		jl .not_in_keyboard_HW1
		cmpb $126, %al 
		jle .case_right_part_HW1
		
	.case_right_part_HW1:  #Do nothing
		jmp .return_HW1

# If the character is not in the keyboard
	.not_in_keyboard_HW1:
		movb $0xff, %al
		jmp .return_HW1
		
	.case_lower_letter_HW1:  # a - z
		subb $32, %al  # A - Z
		jmp .return_HW1
		
	.case_0_HW1:       # 0
		subb $7, %al   # ) 
		jmp .return_HW1

	.case_1_3_4_5_HW1: # 1 3 4 5
		subb $16, %al  # ! # $ %
		jmp .return_HW1

	.case_2_HW1:       # 2
		addb $14, %al  # @
		jmp .return_HW1
		
	.case_6_HW1:       # 6
		addb $40, %al  # ^
		jmp .return_HW1
		
	.case_7_9_HW1:     # 7 9
		subb $17, %al  # & (
		jmp .return_HW1
		
	.case_8_HW1:       # 8 
		subb $14, %al  # *
		jmp .return_HW1
		
	.case_special_1_HW1:  # `
		addb $30, %al     # ~
		jmp .return_HW1
		
	.case_special_2_HW1: # -
		addb $50, %al    # _
		jmp .return_HW1	
		
	.case_equal_HW1:     # =
		subb $18, %al    # +
		jmp .return_HW1	
		
	.case_brackets_slash_HW1: # [ ] \
		addb $32, %al         # { } |
		jmp .return_HW1
		
	.case_special_6_HW1:      # ;
		subb $1, %al          # : 
		jmp .return_HW1
		
	.case_special_7_HW1:      # '
		subb $5, %al         # "
		jmp .return_HW1	
		
	.case_special_9_10_11_HW1: # , . /
		addb $16, %al          # < > ?
		jmp .return_HW1	
			
	.return_HW1:
		movb %al, shifted
