.model small
.stack 100h
.data
	f_retVar dw ?
	u2 dw ?
	z2 dw ?
	t1 dw ?
	t2 dw ?
	g_retVar dw ?
	x3 dw ?
	main_retVar dw ?
	a4 dw ?
	b4 dw ?
	t3 dw ?
	t4 dw ?
	t5 dw ?
	t6 dw ?
	t7 dw ?
	t8 dw ?
	t9 dw ?
	t10 dw ?
	t11 dw ?
	t12 dw ?
	t13 dw ?
	x2 dw 17 dup (?)
	ara2 dw 89 dup (?)
	ara4 dw 58 dup (?)
.code

println proc
	pusha
	
	mov bx , 10d
	xor cx , cx
	xor dx , dx
	
	cmp ax , 0
	jge L3
	neg ax
	push ax
	push dx
	mov dx , '-'
	mov ah , 2
	int 21h
	pop dx
	pop ax
L3:
	idiv bx
	push dx
	xor dx , dx
	inc cx
	cmp ax , 0
	je L4
	jmp L3
L4:
	mov ah , 2
	pop dx
	add dx , 30h
	int 21h
	loop L4
	mov dl , 0ah
	int 21h
	mov dl , 0dh
	int 21h
	
	popa
	ret
println endp

proc f
	pusha

	push u2
	mov t1 , 89
	mov bx , t1
	add bx , bx
	push u2
	pop ara2[bx]
	mov t2 , 89
	mov bx , t2
	add bx , bx
	push ara2
	pop f_retVar
	jmp f_return

f_return:
	pop u2
	popa
	ret
f endp

proc g
	pusha

	push x3
	push x3
	pop u2
	call f
	push f_retVar
	pop g_retVar
	jmp g_return

g_return:
	pop x3
	popa
	ret
g endp

proc main
	mov ax , @data
	mov ds , ax

	mov t3 , 56
	push t3
	pop t4
	neg t4
	push t4
	pop b4
	push b4
	pop t5
	inc b4
	push b4
	pop t7
	neg t7
	push t7
	pop x3
	call g
	mov t6 , 8
	mov bx , t6
	add bx , bx
	push g_retVar
	pop ara4[bx]
	mov t9 , 8
	mov bx , t9
	add bx , bx
	mov t8 , 9
	mov bx , t8
	add bx , bx
	push ara4
	pop ara4[bx]
	mov t10 , 9
	mov bx , t10
	add bx , bx
	push ara4
	pop a4
	push ax
	mov ax , a4
	call println
	pop ax
	cmp a4 , 0
	je L1
	mov t11 , 0
	jmp L2
L1:
	mov t11 , 1
	jmp L2
L2:
	push t11
	pop b4
	push a4
	pop t12
	inc a4
	push ax
	mov ax , a4
	call println
	pop ax
	push ax
	mov ax , b4
	call println
	pop ax
	mov t13 , 0
	push t13
	pop main_retVar
	jmp main_return

main_return:

	mov ah, 4ch
	int 21h
main endp

	end main

