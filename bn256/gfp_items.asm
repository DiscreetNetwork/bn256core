section .text
bits 64

; windows passes pointers and integers in rcx, rdx, r8, and r9
; rax, rcx, rdx, r8, r9, r10, r11 are volatile. we must store r12, r13, and r14 before use. We also shadow-store parameters, so the first 32 bytes above the fp are reserved.
;

%macro storeBlock 5
	mov qword [%5 +  0], %1
	mov qword [%5 +  8], %2
	mov qword [%5 + 16], %3
	mov qword [%5 + 24], %4
%endmacro

%macro loadBlock 5
	mov %2, qword [%1 +  0]
	mov %3, qword [%1 +  8]
	mov %4, qword [%1 + 16]
	mov %5, qword [%1 + 24]
%endmacro

; b: 6-10, a: 1-5
%macro gfpCarry 10
	mov %6, %1
	mov %7, %2
	mov %8, %3
	mov %9, %4
	mov %10, %5
	sub %6, [rel p2 +  0]
	sbb %7, [rel p2 +  8]
	sbb %8, [rel p2 + 16]
	sbb %9, [rel p2 + 24]
	sbb %10, 0
	cmovae %1, %6
	cmovae %2, %7
	cmovae %3, %8
	cmovae %4, %9
%endmacro

%macro mulBMI2 5
	mov rdx, %1
	mov r13, 0
	mulx r9,  r8,  [%5 +  0]
	mulx r10, rax, [%5 +  8]
	add  r9,  rax
	mulx r11, rax, [%5 + 16]
	adc  r10, rax
	mulx r12, rax, [%5 + 24]
	adc  r11, rax
	adc  r12, 0
	adc  r13, 0

	mov rdx, %2
	mov r14, 0
	mulx rbx, rax, [%5 +  0]
	add  r9,  rax
	adc  r10, rbx
	mulx rbx, rax, [%5 + 16]
	adc  r11, rax
	adc  r12, rbx
	adc  r13, 0
	mulx rbx, rax, [%5 +  8]
	add  r10, rax
	adc  r11, rbx
	mulx rbx, rax, [%5 + 24]
	adc  r12, rax
	adc  r13, rbx
	adc  r14, 0

	mov rdx, %3
	mov rcx, 0
	mulx rbx, rax, [%5 +  0]
	add  r10, rax
	adc  r11, rbx
	mulx rbx, rax, [%5 + 16]
	adc  r12, rax
	adc  r13, rbx
	adc  r14, 0
	mulx rbx, rax, [%5 +  8]
	add  r11, rax
	adc  r12, rbx
	mulx rbx, rax, [%5 + 24]
	adc  r13, rax
	adc  r14, rbx
	adc  rcx, 0

	mov rdx, %4
	mulx rbx, rax, [%5 +  0]
	add  r11, rax
	adc  r12, rbx
	mulx rbx, rax, [%5 + 16]
	adc  r13, rax
	adc  r14, rbx
	adc  rcx, 0
	mulx rbx, rax, [%5 +  8]
	add  r12, rax
	adc  r13, rbx
	mulx rbx, rax, [%5 + 24]
	adc  r14, rax
	adc  rcx, rbx
%endmacro

%rmacro mulregl 6
    mov rax, %1
    mul qword [%5 + 0]
    mov r8, rax
    mov r9, rdx
    mov rax, %1
    mul qword [%5 + 8]
    add r9, rax
    adc rdx, 0
    mov r10, rdx
    mov rax, %1
    mul qword [%5 + 16]
    add r10, rax
    adc rdx, 0
    mov r11, rdx
    mov rax, %1
    mul qword [%5 + 24]
    add r11, rax
    adc rdx, 0
    mov r12, rdx
    storeBlock r8,r9,r10,r11, %6 + 0
    mov [%6 + 32], r12
    mov rax, %2
    mul qword [%5 + 0]
    mov r8, rax
    mov r9, rdx
    mov rax, %2
    mul qword [%5 + 8]
    add r9, rax
    adc rdx, 0
    mov r10, rdx
    mov rax, %2
    mul qword [%5 + 16]
    add r10, rax
    adc rdx, 0
    mov r11, rdx
    mov rax, %2
    mul qword [%5 + 24]
    add r11, rax
    adc rdx, 0
    mov r12, rdx
    add r8, [%6 + 8]
    adc r9, [%6 + 16]
    adc r10, [%6 + 24]
    adc r11, [%6 + 32]
    adc r12, 0
    storeBlock r8,r9,r10,r11, %6 + 8
    mov [%6 + 40], r12
    mov rax, %3
    mul qword [%5 + 0]
    mov r8, rax
    mov r9, rdx
    mov rax, %3
    mul qword [%5 + 8]
    add r9, rax
    adc rdx, 0
    mov r10, rdx
    mov rax, %3
    mul qword [%5 + 16]
    add r10, rax
    adc rdx, 0
    mov r11, rdx
    mov rax, %3
    mul qword [%5 + 24]
    add r11, rax
    adc rdx, 0
    mov r12, rdx
    add r8, [%6 + 16]
    adc r9, [%6 + 24]
    adc r10, [%6 + 32]
    adc r11, [%6 + 40]
    adc r12, 0
    storeBlock r8,r9,r10,r11, %6 + 16
    mov [%6 + 48], r12
    mov rax, %4
    mul qword [%5 + 0]
    mov r8, rax
    mov r9, rdx
    mov rax, %4
    mul qword [%5 + 8]
    add r9, rax
    adc rdx, 0
    mov r10, rdx
    mov rax, %4
    mul qword [%5 + 16]
    add r10, rax
    adc rdx, 0
    mov r11, rdx
    mov rax, %4
    mul qword [%5 + 24]
    add r11, rax
    adc rdx, 0
    mov r12, rdx
    add r8, [%6 + 24]
    adc r9, [%6 + 32]
    adc r10, [%6 + 40]
    adc r11, [%6 + 48]
    adc r12, 0
    storeBlock r8,r9,r10,r11, %6 + 24
    mov [%6 + 56], r12
%endmacro

global __cpuidex
; We provide our own CPUID code. we only need the one function anyway.
__cpuidex:
	; rcx contains a pointer to the return value
	; rdx contains what rax needs to
	; r8 contains what rcx needs to
	mov qword [rsp - 8], rcx
	mov rax, rdx
	mov rcx, r8
	cpuid
	mov r8, qword [rsp - 8]
	mov dword [r8 +  0], eax
	mov dword [r8 +  4], ebx
	mov dword [r8 +  8], ecx
	mov dword [r8 + 16], edx
	ret


global gfpneg
gfpneg:
	push r12
	push r13
	push r14
	push rsi
	push rdi
	push rbx

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
	gfpCarry r8, r9, r10, r11, rax,  r12, r13, r14, rcx, rbx

	;store result (r8:r11)
	storeBlock r8, r9, r10, r11,  rdi
	
	pop rbx
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

	mov [rsp - 8], rcx
	mov rdi, rdx
	mov rsi, r8

	; load rdi (a) into r8:r11
	loadBlock rdi, r8, r9, r10, r11

	; perform add
	mov r12, 0
	add r8,  [rsi +  0]
	adc r9,  [rsi +  8]
	adc r10, [rsi + 16]
	adc r11, [rsi + 24]
	adc r12, 0

	; carry (R8,R9,R10,R11,R12, R13,R14,DX,AX,BX)
	gfpCarry r8, r9, r10, r11, r12,  r13, r14, rcx, rax, rbx

	; store result (r8:r11) in c
	mov rdi, [rsp - 8]
	storeBlock r8, r9, r10, r11, rdi

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

	mov [rsp - 8], rcx
	mov rdi, rdx
	mov rsi, r8

	; load di (a) into r8:r11
	loadBlock rdi, r8, r9, r10, r11

	mov r12, [rel p2 +  0]
	mov r13, [rel p2 +  8]
	mov r14, [rel p2 + 16]
	mov rcx, [rel p2 + 24]
	mov rax, 0

	sub r8,  [rsi +  0]
	sbb r9,  [rsi +  8]
	sbb r10, [rsi + 16]
	sbb r11, [rsi + 24]

	cmovae r12, rax
	cmovae r13, rax
	cmovae r14, rax
	cmovae rcx, rax

	add r8,  r12
	adc r9,  r13
	adc r10, r14
	adc r11, rcx

	mov rdi, [rsp - 8]
	storeBlock r8, r9, r10, r11, rdi

	pop rsi
	pop rdi
	pop r14
	pop r13
	pop r12
	ret

; MULXQ source2, dest1, dest2
; for us, it's:
; mulx destlo, desthi, source2

; hasBMI2: 32-bit integer
; This is a flag that gets set on dll entry indicating if
; the processor supports bmi2 instructions (we use mulx if so)
extern hasBMI2

global gfpfastmul ; c = rcx, a = rdx, b = r8
gfpfastmul:
	xor rax, rax
	mov eax, [rel hasBMI2]
	cmp eax, 1
	jne mulregular

mulbmi2:			; rsp-(8:32) = T[0:4], rsp-(40:64) = T[4:8] 
	push rdi
	push rsi
	push r12
	push r13
	push r14
	push rbx

	mov qword [rsp - 104], rcx ; store c

	mov rdi, rdx
	mov rsi, r8

	;mulbmi2
	mulBMI2 [rdi +  0], [rdi +  8], [rdi + 16], [rdi + 24], rsi

	;store
	storeBlock r8, r9, r10, r11, rsp - 32
	storeBlock r12, r13, r14, rcx, rsp - 64

	;reduce
	mov rdx, [rel np +  0]
	mulx r9,  r8,  [rsp - 32 +  0]
	mulx r10, rax, [rsp - 32 +  8]
	add  r9,  rax
	mulx r11, rax, [rsp - 32 + 16]
	adc  r10, rax
	mulx rbx, rax, [rsp - 32 + 24]
	adc  r11, rax

	mov rdx, [rel np +  8]
	mulx rbx, rax, [rsp - 32 +  0]
	add  r9,  rax
	adc  r10, rbx
	mulx rbx, rax, [rsp - 32 + 16]
	adc  r11, rax
	mulx rbx, rax, [rsp - 32 +  8]
	add  r10, rax
	adc  r11, rbx

	mov rdx, [rel np + 16]
	mulx rbx, rax, [rsp - 32 +  0]
	add  r10, rax
	adc  r11, rbx
	mulx rbx, rax, [rsp - 32 +  8]
	add  r11, rax

	mov rdx, [rel np + 24]
	mulx rbx, rax, [rsp - 32 +  0]
	add  r11, rax

	; store
	storeBlock r8, r9, r10, r11, rsp - 96

	;mulbmi2 m*N
	mulBMI2 [rel p2 +  0], [rel p2 +  8], [rel p2 + 16], [rel p2 + 24], rsp - 96

	;; add the intermediate to m*N
	mov rax, 0
	add r8,  [rsp - 32 +  0]
	adc r9,  [rsp - 32 +  8]
	adc r10, [rsp - 32 + 16]
	adc r11, [rsp - 32 + 24]
	adc r12, [rsp - 64 +  0]
	adc r13, [rsp - 64 +  8]
	adc r14, [rsp - 64 + 16]
	adc rcx, [rsp - 64 + 24]
	adc rax, 0

	;; carry(r12, r13, r14, rcx, rax,   r8, r9, r10, r11, rbx)
	gfpCarry r12, r13, r14, rcx, rax,  r8, r9, r10, r11, rbx

	;; store result
	; restore rcx (c)
	mov rdi, [rsp - 104]
	
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

mulregular: ; non BMI2 mult, rcx = c, rdx = a, r8 = b
	push rdi
	push rsi
	push r12
	push r13
	push r14
	push rbx

	mov qword [rsp - 168], rcx
	mov rdi, rdx
	mov rsi, r8

	; multiply
	; args: a0:3 = rdi (off), rb = rsi, stack = rsp
	mulregl [rdi +  0], [rdi +  8], [rdi + 16], [rdi + 24], rsi, rsp - 64

	; reduce
	mov rax, [rel np +  0]
    mul qword [rsp - 64 + 0]
    mov r8, rax
    mov r9, rdx
    mov rax, [rel np +  0]
    mul qword [rsp - 64 + 8]
    add r9, rax
    adc rdx, 0
    mov r10, rdx
    mov rax, [rel np +  0]
    mul qword [rsp - 64 + 16]
    add r10, rax
    adc rdx, 0
    mov r11, rdx
    mov rax, [rel np +  0]
    mul qword [rsp - 64 + 24]
    add r11, rax
    mov rax, [rel np +  8]
    mul qword [rsp - 64 + 0]
    mov r12, rax
    mov r13, rdx
    mov rax, [rel np +  8]
    mul qword [rsp - 64 + 8]
    add r13, rax
    adc rdx, 0
    mov r14, rdx
    mov rax, [rel np +  8]
    mul qword [rsp - 64 + 16]
    add r14, rax
    add r9, r12
    adc r10, r13
    adc r11, r14
    mov rax, [rel np + 16]
    mul qword [rsp - 64 + 0]
    mov r12, rax
    mov r13, rdx
    mov rax, [rel np + 16]
    mul qword [rsp - 64 + 8]
    add r13, rax
    add r10, r12
    adc r11, r13
    mov rax, [rel np + 24]
    mul qword [rsp - 64 + 0]
    add r11, rax

	; store
	storeBlock r8, r9, r10, r11, rsp - 96

	;second mul
	mulregl [rel p2 +  0], [rel p2 +  8], [rel p2 + 16], [rel p2 + 24], rsp - 96, rsp - 160

	;loads
	loadBlock rsp - 160, r8, r9, r10, r11
	loadBlock rsp - 128, r12, r13, r14, rcx

	mov rax, 0
	add r8,  [rsp - 64 +  0]
	adc r9,  [rsp - 64 +  8]
	adc r10, [rsp - 64 + 16]
	adc r11, [rsp - 64 + 24]
	adc r12, [rsp - 64 + 32]
	adc r13, [rsp - 64 + 40]
	adc r14, [rsp - 64 + 48]
	adc rcx, [rsp - 64 + 56]
	adc rax, 0

	; carry
	gfpCarry r12, r13, r14, rcx, rax,  r8, r9, r10, r11, rbx

	;; store result
	; restore rcx (c)
	mov rdi, [rsp - 168]
	
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