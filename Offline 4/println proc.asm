.model small
.stack 100h
.data


.code  

main proc	
	mov ax , 1234   
	
	xor cx , cx
	xor dx , dx
	    
    mov bx , 10d		
loop_:
    idiv bx
    
    
    push dx
    xor dx , dx
    
    inc cx
    
    cmp ax , 0
    je print_
    
    jmp loop_

print_:
    mov ah , 2
    pop dx  
    add dx , 30h
    int 21h
    loop print_      
    
    
    mov dl , 0ah
    int 21h
    mov dl , 0dh
    int 21h
    
    
    
    
    mov ah , 4ch
    int 21h
    	
main endp

    end main
		  
