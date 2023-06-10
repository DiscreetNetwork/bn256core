section .text
bits 64

; windows passes pointers and integers in rcx, rdx, r8, and r9
; rax, rcx, rdx, r8, r9, r10, r11 are volatile. we must store r12, r13, and r14 before use. We also shadow-store parameters, so the first 32 bytes above the fp are reserved.
;

global gfpneg
gfpneg:
	push r12
	push r13
	push r14
	push rsi
	push rdi

	mov r8,  qword [rel p2 +  0]
	mov r9,  qword [rel p2 +  8]
	mov r10, qword [rel p2 + 16]
	mov r11, qword [rel p2 + 24]

	mov rdi, rcx ; rcx stores return value 'c'
	mov rsi, rdx ; rdx stores parameter value 'a'
	
	sub r8,  qword [rsi +  0] ; ;r8 := r8 - [di] = pi - ai - carry
	sbb r9,  qword [rsi +  8]
	sbb r10, qword [rsi + 16]
	sbb r11, qword [rsi + 24]

	mov rax, 0
	
	;carry
	mov r12, r8
	mov r13, r9
	mov r14, r10
	mov rcx, r11
	mov rdx, rax
	sub r12, qword [rel p2 +  0]
	sbb r13, qword [rel p2 +  8]
	sbb r14, qword [rel p2 + 16]
	sbb rcx, qword [rel p2 + 24]
	sbb rdx, 0
	cmovge r8, r12
	cmovge r9, r13
	cmovge r10, r14
	cmovge r11, rcx

	;store result (r8:r11)
	mov qword [rdi +  0], r8
	mov qword [rdi +  8], r9
	mov qword [rdi + 16], r10
	mov qword [rdi + 24], r11
	
	pop rdi
	pop rsi
	pop r14
	pop r13
	pop r12
	ret

global gfpadd ; rcx = c, rdx = a, r8 = b
gfpadd:
	push r12
	push r13
	push r14
	push rsi
	push rdi
	push rbx

	mov rdi, rdx
	mov rsi, r8
	; do not disturb rcx

	; load rdi (a) into r8:r11
	mov r8,  qword [rdi +  0]
	mov r9,  qword [rdi +  8]
	mov r10, qword [rdi + 16]
	mov r11, qword [rdi + 24]

	; perform add
	mov r12, 0
	add r8,  [rsi +  0]
	adc r9,  [rsi +  8]
	adc r10, [rsi + 16]
	adc r11, [rsi + 24]
	adc r12, 0

	; clear registers that matter
	xor r13, r13
	xor r14, r14
	xor rdx, rdx
	xor rax, rax
	xor rbx, rbx

	; carry (R8,R9,R10,R11,R12, R13,R14,DX,AX,BX)
	mov r13, r8
	mov r14, r9
	mov rdx, r10
	mov rax, r11
	sub r13, [rel p2 +  0]
	sbb r14, [rel p2 +  8]
	sbb rdx, [rel p2 + 16]
	sbb rax, [rel p2 + 24]
	sbb rbx, 0
	cmovge r8,  r13
	cmovge r9,  r14
	cmovge r10, rdx
	cmovge r11, rax

	mov qword [rcx +  0], r8
	mov qword [rcx +  8], r9
	mov qword [rcx + 16], r10
	mov qword [rcx + 24], r11

	pop rbx
	pop rdi
	pop rsi
	pop r14
	pop r13
	pop r12
	ret

global gfpsub ; c = rcx, a = rdx, b = r8
gfpsub:
	push r12
	push r13
	push r14
	push rdi
	push rsi

	mov rdi, rdx
	mov rsi, r8

	; load di (a) into r8:r11
	mov r8,  [rdi +  0]
	mov r9,  [rdi +  8]
	mov r10, [rdi + 16]
	mov r11, [rdi + 24]

	mov r12, [rel p2 +  0]
	mov r13, [rel p2 +  8]
	mov r14, [rel p2 + 16]
	mov rdx, [rel p2 + 24]
	mov rax, 0

	sub r8,  [rsi +  0]
	sbb r9,  [rsi +  8]
	sbb r10, [rsi + 16]
	sbb r11, [rsi + 24]

	cmovge r12, rax
	cmovge r13, rax
	cmovge r14, rax
	cmovge rdx, rax

	add r8,  r12
	adc r9,  r13
	adc r10, r14
	adc r11, rdx

	mov qword [rcx +  0], r8
	mov qword [rcx +  8], r9
	mov qword [rcx + 16], r10
	mov qword [rcx + 24], r11

	pop rsi
	pop rdi
	pop r14
	pop r13
	pop r12
	ret

; MULXQ source2, dest1, dest2
; for us, it's:
; mulx destlo, desthi, source2

global mulbmi2 ; c = rcx, a = rdx, b = r8
mulbmi2:			; rsp-(8:32) = T[0:4], rsp-(40:64) = T[4:8] 
	mov qword [rsp + 24], rcx ; store c in spill location
	push rdi
	push rsi
	push r12
	push r13
	push r14
	push rbx

	mov rdi, rdx
	mov rsi, r8

	;mulbmi2
	mov rdx, [rdi +  0]
	mov r13, 0
	mulx r9,  r8,  [rsi +  0]
	mulx r10, rax, [rsi +  8]
	add  r9,  rax
	mulx r11, rax, [rsi + 16]
	adc  r10, rax
	mulx r12, rax, [rsi + 24]
	adc  r11, rax
	adc  r12, 0
	adc  r13, 0

	mov rdx, [rdi +  8]
	mov r14, 0
	mulx rbx, rax, [rsi +  0]
	add  r9,  rax
	adc  r10, rbx
	mulx rbx, rax, [rsi + 16]
	adc  r11, rax
	adc  r12, rbx
	adc  r13, 0
	mulx rbx, rax, [rsi +  8]
	add  r10, rax
	adc  r11, rbx
	mulx rbx, rax, [rsi + 24]
	adc  r12, rax
	adc  r13, rbx
	adc  r14, 0

	mov rdx, [rdi + 16]
	mov rcx, 0
	mulx rbx, rax, [rsi +  0]
	add  r10, rax
	adc  r11, rbx
	mulx rbx, rax, [rsi + 16]
	adc  r12, rax
	adc  r13, rbx
	adc  r14, 0
	mulx rbx, rax, [rsi +  8]
	add  r11, rax
	adc  r12, rbx
	mulx rbx, rax, [rsi + 24]
	adc  r13, rax
	adc  r14, rbx
	adc  rcx, 0

	mov rdx, [rdi + 24]
	mulx rbx, rax, [rsi +  0]
	add  r11, rax
	adc  r12, rbx
	mulx rbx, rax, [rsi + 16]
	adc  r13, rax
	adc  r14, rbx
	adc  rcx, 0
	mulx rbx, rax, [rsi +  8]
	add  r12, rax
	adc  r13, rbx
	mulx rbx, rax, [rsi + 24]
	adc  r14, rax
	adc  rcx, rbx

	;store
	mov qword [rsp -  8], r8
	mov qword [rsp - 16], r9
	mov qword [rsp - 24], r10
	mov qword [rsp - 32], r11
	mov qword [rsp - 40], r12
	mov qword [rsp - 48], r13
	mov qword [rsp - 56], r14
	mov qword [rsp - 64], rcx

	;reduce
	mov rdx, [rel np +  0]
	mulx r8,  r9,  [rsp -  8]
	mulx rax, r10, [rsp - 16]
	add  r9, rax
	mulx rax, r11, [rsp - 24]
	adc  r10, rax
	mulx rax, rbx, [rsp - 32]
	adc  r11, rax

	mov rdx, [rel np +  8]
	mulx rax, rbx, [rsp -  8]
	add  r9,  rax
	adc  r10, rbx
	mulx rax, rbx, [rsp - 24]
	adc  r11, rax
	mulx rax, rbx, [rsp - 16]
	adc  r10, rax
	adc  r11, rbx

	mov rdx, [rel np + 16]
	mulx rax, rbx, [rsp -  8]
	add  r10, rax
	adc  r11, rbx
	mulx rax, rbx, [rsp - 16]
	add  r11, rax

	mov rdx, [rel np + 24]
	mulx rax, rbx, [rsp - 8]
	add  r11, rax

	; store
	mov qword [rsp - 72], r8
	mov qword [rsp - 80], r9
	mov qword [rsp - 88], r10
	mov qword [rsp - 96], r11

	;mulbmi2 m*N
	mov rdx, [rel p2 +  0]
	mov r13, 0
	mulx r9,  r8,  [rsp - 72]
	mulx r10, rax, [rsp - 80]
	add  r9,  rax
	mulx r11, rax, [rsp - 88]
	adc  r10, rax
	mulx r12, rax, [rsp - 96]
	adc  r11, rax
	adc  r12, 0
	adc  r13, 0

	mov rdx, [rel p2 +  8]
	mov r14, 0
	mulx rbx, rax, [rsp - 72]
	add  r9,  rax
	adc  r10, rbx
	mulx rbx, rax, [rsp - 88]
	adc  r11, rax
	adc  r12, rbx
	adc  r13, 0
	mulx rbx, rax, [rsp - 80]
	add  r10, rax
	adc  r11, rbx
	mulx rbx, rax, [rsp - 96]
	adc  r12, rax
	adc  r13, rbx
	adc  r14, 0

	mov rdx, [rel p2 + 16]
	mov rcx, 0
	mulx rbx, rax, [rsp - 72]
	add  r10, rax
	adc  r11, rbx
	mulx rbx, rax, [rsp - 88]
	adc  r12, rax
	adc  r13, rbx
	adc  r14, 0
	mulx rbx, rax, [rsp - 80]
	add  r11, rax
	adc  r12, rbx
	mulx rbx, rax, [rsp - 96]
	adc  r13, rax
	adc  r14, rbx
	adc  rcx, 0

	mov rdx, [rel p2 + 24]
	mulx rbx, rax, [rsp - 72]
	add  r11, rax
	adc  r12, rbx
	mulx rbx, rax, [rsp - 88]
	adc  r13, rax
	adc  r14, rbx
	adc  rcx, 0
	mulx rbx, rax, [rsp - 80]
	add  r12, rax
	adc  r13, rbx
	mulx rbx, rax, [rsp - 96]
	adc  r14, rax
	adc  rcx, rbx

	;; add the intermediate to m*N
	mov rax, 0
	add r8,  [rsp -  8]
	adc r9,  [rsp - 16]
	adc r10, [rsp - 24]
	adc r11, [rsp - 32]
	adc r12, [rsp - 40]
	adc r13, [rsp - 48]
	adc r14, [rsp - 56]
	adc rcx, [rsp - 64]

	;; carry(r12, r13, r14, rcx, rax,   r8, r9, r10, r11, rbx)
	mov r8,  r12
	mov r9,  r13
	mov r10, r14
	mov r11, rcx
	mov rbx, rax

	sub r8,  [rel p2 +  0]
	sbb r9,  [rel p2 +  8]
	sbb r10, [rel p2 + 16]
	sbb r11, [rel p2 + 24]
	sbb rbx, 0

	cmovge r12, r8
	cmovge r13, r9
	cmovge r14, r10
	cmovge rcx, r11

	;; store result
	; restore rcx (c)
	mov rdi, [rsp + 72] ; 48 more because we haven't popped callee saved regs
	
	; storing res
	mov qword [rdi +  0], r12
	mov qword [rdi +  8], r13
	mov qword [rdi + 16], r14
	mov qword [rdi + 24], rcx

	; restore non volatile registers
	pop rbx
	pop r14
	pop r13
	pop r12
	pop rsi
	pop rdi
	ret


section .data

; we re-define constants here for safety reasons and locality
p2:
	dq 0x185cac6c5e089667, 0xee5b88d120b5b59e, 0xaa6fecb86184dc21, 0x8fb501e34aa387f9

np:
	dq 0x2387f9007f17daa9, 0x734b3343ab8513c8, 0x2524282f48054c12, 0x38997ae661c3ef3c