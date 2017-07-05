assume cs:code,ds:data,ss:stack


data segment
	sfood dw 0
	sdct dw 0
	sbody dw 400 dup(0)
data ends

stack segment
	dw 20 dup(0)
stack ends

code segment

start:
	mov ax, data
	mov ds, ax

	mov ax, stack
	mov ss, ax
	mov sp, 20

	mov ax, 0b800h
	mov es, ax

	mov si, 4 ;保存数据段偏移量

	mov cx, 4;初始蛇长度
	mov ax, 0A04h

	s:;初始化蛇
		mov ds:[si], ax
		add si, 2
		inc al
		loop s

	mov ax, 4d00h;向右
	mov ds:[2], ax;初始化方向

	call clearBg;清屏
	call outBg;输出地图边框
	call outBody;输出蛇
	call creatFood;输出食物

	mov cx, 30
	Game:
		push cx

		call updateBody

		mov cx, 0Fh
		aaaa1:
			push cx
			mov cx, 0FFFh
			bbbb:
				push cx
				call getInput
				pop cx
				loop bbbb
			pop cx
			loop aaaa1
		
		;jmp GameEnd

		jmp Game

		
	GameEnd:	;退出
		;call outBody
		mov ax, 4c00h
		int 21h


updateBody:

	mov ax, ds:[2]
	mov di, si
	sub di, 2
	cmp ax, 4800h
	je shang

	mov ax, ds:[2]
	cmp ax, 5000h
	je xia

	mov ax, ds:[2]
	cmp ax, 4b00h
	je zuo

	mov ax, ds:[2]
	cmp ax, 4d00h
	je you

	shang:
		mov ax, ds:[di]
		sub ah, 1
		jmp checkBody

	xia:
		mov ax, ds:[di]
		add ah, 1
		jmp checkBody
	zuo:
		mov ax, ds:[di]
		sub al, 1
		jmp checkBody

	you:
		mov ax, ds:[di]
		add al, 1
		;mov ds:[di], ax
		jmp checkBody

checkBody:
	push ax

	;判断蛇头是否碰到地图边界
	cmp ah, 0
	je GameEnd
	cmp ah, 20
	je GameEnd
	cmp al, 0
	je GameEnd
	cmp al, 20
	je GameEnd

	;判断蛇头是否碰到蛇身
	mov cx, si
	sub cx, 6
	mov di, 4

	s0: 
		mov bx, ds:[di]
		cmp bx, ax
		je GameEnd

		add di, 2
		sub cx, 1
		loop s0

	pop ax

	;判断蛇头是否吃到食物
	mov bx, ds:[0]
	cmp ax, bx
	je addBody

	jmp updateStart

updateStart:
	mov cx, si
	sub cx, 6
	mov di, 4

	push ax

	mov dl, ' ';字符
	mov dh, 0;颜色
	mov bx, ds:[di]
	call outStr

	s5: 
		mov dx, ds:[di+2]
		mov ds:[di], dx

		add di, 2
		sub cx, 1
		loop s5

	mov dl, ' ';字符
	mov dh, 71h;颜色
	mov bx, ds:[di]
	call outStr

	pop ax
	mov ds:[di], ax

	mov dl, ' ';字符
	mov dh, 44h;颜色
	mov bx, ds:[di]
	call outStr


updateEnd:
	ret

addBody:
	mov dl, ' ';字符
	mov dh, 71h;颜色
	mov bx, ds:[di]
	call outStr

	mov ax, ds:[0]
	mov ds:[si], ax

	mov dl, ' ';字符
	mov dh, 44h;颜色
	mov bx, ds:[si]
	call outStr

	add si, 2

	call creatFood

	jmp updateEnd

getInput:;获取键盘输入

	mov al, 0
	mov ah, 1
	int 16h;接收键盘
	cmp ah, 1
	je getInputEnd

	mov al, 0
	mov ah, 0
	int 16h;
	mov cx, ax;键盘值在ax
	;判断输入
	cmp cx, 4800h
	je gshang

	cmp cx, 5000h
	je gxia

	cmp cx, 4b00h
	je gzuo

	cmp cx, 4d00h
	je gyou

	jmp getInputEnd

	gshang:
		mov ax, ds:[2]
		cmp ax, 5000h
		je getInputEnd
		jmp fx

	gxia:
		mov ax, ds:[2]
		cmp ax, 4800h
		je getInputEnd
		jmp fx

	gzuo:
		mov ax, ds:[2]
		cmp ax, 4d00h
		je getInputEnd
		jmp fx

	gyou:
		mov ax, ds:[2]
		cmp ax, 4b00h
		je getInputEnd
		jmp fx

	fx:;更改方向标志
		
		mov ds:[2], cx
		
	getInputEnd:
		ret;结束



outBody:
	mov cx, si
	sub cx, 6
	mov di, 4
	s1: 
		mov ax, ds:[di]
		
		mov dl, ' ';字符
		mov dh, 71h;颜色

		mov bl, al;列
		mov bh, ah;行
		call outStr

		add di, 2
		sub cx, 1
		loop s1
	mov dl, ' '
	mov dh, 44h
	mov ax, ds:[di]
	mov bl, al
	mov bh, ah
	call outStr
	ret

outBg:
	mov dl, ' ';字符
	mov dh, 71h;颜色
	
	mov bl, 0;列
	mov bh, 0;行

	mov cx, 20
	row:
		push cx
		
		push bx
		call outStr;上边界
		pop bx

		push bx
		add bh, 20
		call outStr;下边界
		pop bx

		inc bl;列加1
		
		pop cx

		loop row

	mov bl, 0;
	mov bh, 0;
	mov cx, 21
	col:
		push cx
		
		push bx
		call outStr;左边界
		pop bx
			
		push bx
		add bl, 20
		call outStr;右边界
		pop bx
		
		inc bh;行加1
			
		pop cx

		loop col
	ret

outStr: ;在指定位置输出字符

	mov al, 80
	mul bh;行乘以80
	mov bh, 0

	add bl, bl;

	add ax, bx;加上列即为偏移量

	push si
	mov si, ax
	add si, si
	
	mov es:[si], dl
	mov es:[si+1], dh

	mov es:[si+2], dl
	mov es:[si+3], dh

	pop si
	ret

creatFood:;生成食物

	call getFoodPosition

	mov dl, ' '
	mov dh, 071h
	mov bx, ds:[0]

	call outStr

	ret


getFoodPosition:;获取食物位置
	f1:	
		call getRand
		mov ds:[0], al
		call getRand
		mov ds:[1], al

		mov cx, si
		sub cx, 4
		mov di, 4
		s11: 
			mov ax, ds:[di]
			
			cmp ax, ds:[0]
			je f1

			add di, 2
			sub cx, 1
			loop s11

	ret

getRand:;获取随机数 范围1~19

	mov ax, 0h;间隔定时器
	out 43h, al;通过端口43h
	in al, 40h;
	in al, 40h;
	in al, 40h;访问3次，保证随机性
	
	mov bl, 18
	div bl 
	
	mov al, ah
	mov ah, 0

	inc al

	ret

clearBg:	;清屏
	mov ax, 3h
	int 10h
	ret


code ends

end start
