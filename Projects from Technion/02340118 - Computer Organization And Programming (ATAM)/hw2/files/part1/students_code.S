.global get_element_from_matrix, inner_prod, matrix_multiplication

get_element_from_matrix:
	# Input parameters:
    # %rdi: matrix
    # %rsi: n, number of columns
    # %rdx: row
    # %rcx: col

    # Calculate the linear index corresponding to the 2D indices
    movq %rdx, %rax    # row
    imulq %rsi, %rax   # row * n
    addq %rcx, %rax    # row * n + col

    # Access the element in the matrix using the calculated index
    movl (%rdi, %rax, 4), %eax  # Assuming each element is a 4-byte integer
	ret

inner_prod:
    # Input parameters:
    # %rdi: mat_a
    # %rsi: mat_b
    # %rdx: row_a
    # %rcx: col_b
    # %r8:  max_col_a
    # %r9:  max_col_b
	
	/* Algorithm in C
	for (int col_a = 0, row_b = 0; col_a < max_col_a; col_a++, row_b++)
	{
		int elementA = get_element_from_matrix(mat_a, max_col_a, row_a, col_a);
		int elementB = get_element_from_matrix(mat_b, max_col_b, row_b, col_b);
		result += elementA * elementB;
	}
	*/
	
	#prologue
	push %rbp
	mov %rsp, %rbp
	
	#allocate stack frame for 11 local variables
	sub $100, %rsp
	
	#keep the parameters in stack, initialize
	mov %rdi, -8(%rbp) #matrix A
	mov %r8, -16(%rbp) #max_col_a
	mov %rdx, -24(%rbp) #row_a
	movq $0, -32(%rbp) #col_a = 0
	#the space at -40(%rbp) is for the element at matA[rowA][colA]
	mov %rsi, -48(%rbp) #matrix B
	mov %r9, -56(%rbp) #max_col_b
	movq $0, -64(%rbp) #row_b = 0
	mov %rcx, -72(%rbp) #col_b
	#the space at -80(%rbp) is for the element at matB[rowB][colB]
	#the space at -88(%rbp) is for the result
	movq $0, -88(%rbp)

loop:
	#Get element from matrix A into -40(%rbp), 
	# %rdi: matrix_a => -8(%rbp)
    # %rsi: max_col_a => -16(%rbp)
    # %rdx: row_a => -24(%rbp)  
    # %rcx: col_a => -32(%rbp)
	mov -8(%rbp), %rdi
	mov -16(%rbp), %rsi
	mov -24(%rbp), %rdx
	mov -32(%rbp), %rcx
	call get_element_from_matrix
	mov %rax, -40(%rbp)
	
	#Get element from matrix B into -80(%rbp)
	# %rdi: matrix_b => -48(%rbp)
    # %rsi: max_col_b => -56(%rbp)
    # %rdx: row_b => -64(%rbp)
    # %rcx: col_b => -72(%rbp)
	mov -48(%rbp), %rdi
	mov -56(%rbp), %rsi
	mov -64(%rbp), %rdx
	mov -72(%rbp), %rcx
	call get_element_from_matrix
	mov %rax, -80(%rbp)
	
	#Add elemA * elemB to the result
	mov -40(%rbp), %rcx
	imulq -80(%rbp), %rcx
	add %rcx, -88(%rbp)
	
	#increment col_a and row_b
	incq -32(%rbp) #col_a
	incq -64(%rbp) #row_b
	
	#check if end of loop : compare col_a to max_col_a
	cmp %r8, -32(%rbp)
	jl loop

#epilogue
end_inner_prod:
	movq -88(%rbp), %rax
	leave
	ret

matrix_multiplication:
    # Input parameters:
    # %rdi: mat_result
    # %rsi: mat_a
    # %rdx: mat_b
    # %rcx: max_row_a
    # %r8:  max_col_a
    # %r9:  max_row_b
	# 8(%rbp) max_col_b

/* Algorithm in C
	if (max_col_a != max_row_b) return false;
	if (max_col_a == 0 || max_col_b == 0 ||
		max_row_a == 0 || max_row_b == 0)
	row_result = max_row_a;
	col_result = max_col_b;	
	for (int row = 0; row < max_row_a; row++)
	{
		for (int col = 0; col < max_col_b; col++)
		{
			int element = inner_prod(mat_a, mat_b, row, col, max_col_a, max_col_b);
			set_element_in_matrix(mat_result, col_result, row, col);
		}
	}	
	return true;
*/
	#prologue
	push %rbp
	mov %rsp, %rbp
	
	# max_col_b is in 16(%rbp)
	
	#Allocate stack frame for local variables
	sub $100, %rsp
	
	#keep parameters in stack, initialize
	mov %rdi, -8(%rbp) #mat_result
	mov %rsi, -16(%rbp) #mat_a
	mov %rdx, -24(%rbp) #mat_b
	movq $0, -32(%rbp) #row_a = 0
	movq $0, -40(%rbp) #col_b = 0
	mov %r8, -48(%rbp) #max_col_a
	# the space at -56(%rbp) is for the result of inner_prod
	mov %rcx, -64(%rbp) #max_row_a
	mov %r9, -72(%rbp) #max_row_b

	#Verification of dimensions : max_col_a == max_row_b
	cmp %r8, %r9
	jne failure
	
	#%rcx, %r8, %r9, 16(%rbp) should not be negative or zero
	cmp $0, %rcx 
	jle failure
	cmp $0, %r8 
	jle failure	
	cmp $0, %r9
	jle failure	
	cmpq $0, 16(%rbp)
	jle failure
	
outer_loop:
	movq $0, -40(%rbp) #col_b = 0
	
inner_loop:

	#Get inner product of row_a * col_b into -56(%rbp)
	# parameters:
    # %rdi: mat_a => -16(%rbp)
    # %rsi: mat_b => -24(%rbp)
    # %rdx: row_a => -32(%rbp)
    # %rcx: col_b => -40(%rbp)
    # %r8:  max_col_a => -48(%rbp)
    # %r9:  max_col_b => 16(%rbp)
	movq -16(%rbp), %rdi
	movq -24(%rbp), %rsi
	movq -32(%rbp), %rdx
	movq -40(%rbp), %rcx
	movq -48(%rbp), %r8
	movq 16(%rbp), %r9
	call inner_prod
	
	#Set element result[row_a][col_b] to the value in %rax
	#parameters:
	# %rdi: mat_result => -8(%rbp)
	# %rsi: max_col => max_col_b => 16(%rbp)
	# %rdx: row_a => -32(%rbp)
	# %rcx: col_b => -40(%rbp)
	# %r8: value => %rax
	movq -8(%rbp), %rdi
	movq 16(%rbp), %rsi
	movq -32(%rbp), %rdx
	movq -40(%rbp), %rcx
	movq %rax, %r8
	call set_element_in_matrix
	
	#increment inner loop
	incq -40(%rbp) #col_b++
	movq 16(%rbp), %r9
	cmp  %r9, -40(%rbp) #col_b - max_col_b
	jl inner_loop #if col_b < max_col_b
	
	#increment outer loop
	incq -32(%rbp) #row_a++
	movq -64(%rbp), %r9
	cmp %r9, -32(%rbp)	#row_a - max_row_a
	jl outer_loop #if row_a < max_row_a
	
success: 
	mov $1, %rax
	jmp end_matrix_mult
	
failure: 
	mov $0, %rax
	
end_matrix_mult:
	#epilogue
	leave
	ret
	

