	.file	"dungeons.c"
	.globl	_corridorTile
	.section .rdata,"dr"
_corridorTile:
	.byte	35
	.globl	_floorTile
_floorTile:
	.byte	46
	.globl	_rockTile
_rockTile:
	.byte	32
	.globl	_upstairTile
_upstairTile:
	.byte	60
	.globl	_downstairTile
_downstairTile:
	.byte	62
	.globl	_sizeX
	.align 4
_sizeX:
	.long	79
	.globl	_sizeY
	.align 4
_sizeY:
	.long	20
	.globl	_minRoomX
	.align 4
_minRoomX:
	.long	4
	.globl	_minRoomY
	.align 4
_minRoomY:
	.long	3
	.globl	_minRoomNum
	.align 4
_minRoomNum:
	.long	6
	.globl	_maxRoomX
	.align 4
_maxRoomX:
	.long	10
	.globl	_maxRoomY
	.align 4
_maxRoomY:
	.long	10
	.globl	_maxRoomNum
	.align 4
_maxRoomNum:
	.long	12
	.comm	_map, 4, 2
	.def	___main;	.scl	2;	.type	32;	.endef
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB19:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	andl	$-16, %esp
	subl	$32, %esp
	.cfi_offset 3, -12
	call	___main
	movl	$0, (%esp)
	call	_time
	movl	%eax, (%esp)
	call	_srand
	movl	$79, %edx
	movl	$20, %eax
	imull	%edx, %eax
	sall	$3, %eax
	movl	%eax, (%esp)
	call	_malloc
	movl	%eax, _map
	movl	$0, 28(%esp)
	jmp	L2
L3:
	movl	_map, %eax
	movl	28(%esp), %edx
	sall	$2, %edx
	leal	(%eax,%edx), %ebx
	movl	$79, %eax
	sall	$3, %eax
	movl	%eax, (%esp)
	call	_malloc
	movl	%eax, (%ebx)
	addl	$1, 28(%esp)
L2:
	movl	$20, %eax
	cmpl	%eax, 28(%esp)
	jl	L3
	movl	$0, 28(%esp)
	jmp	L4
L7:
	movl	$0, 24(%esp)
	jmp	L5
L6:
	movl	_map, %eax
	movl	28(%esp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	24(%esp), %edx
	sall	$3, %edx
	addl	%edx, %eax
	movl	$32, %edx
	movb	%dl, (%eax)
	movl	_map, %eax
	movl	28(%esp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	24(%esp), %edx
	sall	$3, %edx
	leal	(%eax,%edx), %ebx
	movl	$100, 4(%esp)
	movl	$1, (%esp)
	call	_getRandInt
	movl	%eax, 4(%ebx)
	addl	$1, 24(%esp)
L5:
	movl	$79, %eax
	cmpl	%eax, 24(%esp)
	jl	L6
	addl	$1, 28(%esp)
L4:
	movl	$20, %eax
	cmpl	%eax, 28(%esp)
	jl	L7
	call	_generateRooms
	call	_printMap
	movl	_map, %eax
	movl	%eax, (%esp)
	call	_free
	movl	$0, %eax
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE19:
	.section .rdata,"dr"
LC0:
	.ascii "|\0"
	.text
	.globl	_printMap
	.def	_printMap;	.scl	2;	.type	32;	.endef
_printMap:
LFB20:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	$0, -12(%ebp)
	jmp	L10
L11:
	movl	$45, (%esp)
	call	_putchar
	addl	$1, -12(%ebp)
L10:
	movl	$79, %eax
	addl	$1, %eax
	cmpl	-12(%ebp), %eax
	jge	L11
	movl	$10, (%esp)
	call	_putchar
	movl	$0, -12(%ebp)
	jmp	L12
L15:
	movl	$124, (%esp)
	call	_putchar
	movl	$0, -16(%ebp)
	jmp	L13
L14:
	movl	_map, %eax
	movl	-12(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-16(%ebp), %edx
	sall	$3, %edx
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %eax
	movl	%eax, (%esp)
	call	_putchar
	addl	$1, -16(%ebp)
L13:
	movl	$79, %eax
	cmpl	%eax, -16(%ebp)
	jl	L14
	movl	$LC0, (%esp)
	call	_puts
	addl	$1, -12(%ebp)
L12:
	movl	$20, %eax
	cmpl	%eax, -12(%ebp)
	jl	L15
	movl	$0, -12(%ebp)
	jmp	L16
L17:
	movl	$45, (%esp)
	call	_putchar
	addl	$1, -12(%ebp)
L16:
	movl	$79, %eax
	addl	$1, %eax
	cmpl	-12(%ebp), %eax
	jge	L17
	movl	$10, (%esp)
	call	_putchar
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE20:
	.globl	_generateRooms
	.def	_generateRooms;	.scl	2;	.type	32;	.endef
_generateRooms:
LFB21:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%edi
	pushl	%esi
	pushl	%ebx
	subl	$124, %esp
	.cfi_offset 7, -12
	.cfi_offset 6, -16
	.cfi_offset 3, -20
	movl	%esp, %eax
	movl	%eax, %edi
	movl	$0, -32(%ebp)
	movl	$12, %edx
	movl	$6, %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_getRandInt
	movl	%eax, -48(%ebp)
	movl	-48(%ebp), %ecx
	leal	-1(%ecx), %eax
	movl	%eax, -52(%ebp)
	movl	%ecx, %eax
	movl	$0, %edx
	imull	$160, %edx, %esi
	imull	$0, %eax, %ebx
	addl	%esi, %ebx
	movl	$160, %esi
	mull	%esi
	addl	%edx, %ebx
	movl	%ebx, %edx
	movl	%ecx, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%ecx, %eax
	movl	$0, %edx
	imull	$160, %edx, %esi
	imull	$0, %eax, %ebx
	addl	%esi, %ebx
	movl	$160, %esi
	mull	%esi
	addl	%edx, %ebx
	movl	%ebx, %edx
	movl	%ecx, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	leal	3(%eax), %edx
	movl	$16, %eax
	subl	$1, %eax
	addl	%edx, %eax
	movl	$16, %esi
	movl	$0, %edx
	divl	%esi
	imull	$16, %eax, %eax
	call	___chkstk_ms
	subl	%eax, %esp
	leal	40(%esp), %eax
	addl	$3, %eax
	shrl	$2, %eax
	sall	$2, %eax
	movl	%eax, -56(%ebp)
	movl	$0, -32(%ebp)
	jmp	L19
L28:
	movb	$1, -33(%ebp)
	movl	$10, %edx
	movl	$4, %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_getRandInt
	movl	%eax, -68(%ebp)
	movl	$10, %edx
	movl	$3, %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	_getRandInt
	movl	%eax, -64(%ebp)
	movl	$79, %eax
	movl	%eax, %edx
	movl	-68(%ebp), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	subl	$1, %eax
	movl	%eax, 4(%esp)
	movl	$1, (%esp)
	call	_getRandInt
	movl	%eax, -76(%ebp)
	movl	$20, %eax
	movl	%eax, %edx
	movl	-64(%ebp), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	subl	$1, %eax
	movl	%eax, 4(%esp)
	movl	$1, (%esp)
	call	_getRandInt
	movl	%eax, -72(%ebp)
	movb	$0, -60(%ebp)
	movl	$0, -28(%ebp)
	jmp	L20
L22:
	movl	-56(%ebp), %ecx
	movl	-28(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	addl	%ecx, %eax
	movl	(%eax), %edx
	movl	%edx, 20(%esp)
	movl	4(%eax), %edx
	movl	%edx, 24(%esp)
	movl	8(%eax), %edx
	movl	%edx, 28(%esp)
	movl	12(%eax), %edx
	movl	%edx, 32(%esp)
	movl	16(%eax), %eax
	movl	%eax, 36(%esp)
	movl	-76(%ebp), %eax
	movl	%eax, (%esp)
	movl	-72(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-68(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-64(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-60(%ebp), %eax
	movl	%eax, 16(%esp)
	call	_roomIntersect
	testl	%eax, %eax
	je	L21
	movb	$0, -33(%ebp)
L21:
	addl	$1, -28(%ebp)
L20:
	movl	-28(%ebp), %eax
	cmpl	-32(%ebp), %eax
	jl	L22
	cmpb	$0, -33(%ebp)
	je	L19
	movl	-56(%ebp), %ecx
	movl	-32(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	addl	%ecx, %eax
	movl	-76(%ebp), %edx
	movl	%edx, (%eax)
	movl	-72(%ebp), %edx
	movl	%edx, 4(%eax)
	movl	-68(%ebp), %edx
	movl	%edx, 8(%eax)
	movl	-64(%ebp), %edx
	movl	%edx, 12(%eax)
	movl	-60(%ebp), %edx
	movl	%edx, 16(%eax)
	addl	$1, -32(%ebp)
	movl	-72(%ebp), %eax
	movl	%eax, -40(%ebp)
	jmp	L24
L27:
	movl	-76(%ebp), %eax
	movl	%eax, -44(%ebp)
	jmp	L25
L26:
	movl	_map, %eax
	movl	-40(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-44(%ebp), %edx
	sall	$3, %edx
	addl	%edx, %eax
	movl	$46, %edx
	movb	%dl, (%eax)
	addl	$1, -44(%ebp)
L25:
	movl	-76(%ebp), %edx
	movl	-68(%ebp), %eax
	addl	%eax, %edx
	movl	-44(%ebp), %eax
	cmpl	%eax, %edx
	ja	L26
	addl	$1, -40(%ebp)
L24:
	movl	-72(%ebp), %edx
	movl	-64(%ebp), %eax
	addl	%eax, %edx
	movl	-40(%ebp), %eax
	cmpl	%eax, %edx
	ja	L27
L19:
	movl	-32(%ebp), %eax
	cmpl	-48(%ebp), %eax
	jl	L28
	movl	-56(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-48(%ebp), %eax
	movl	%eax, (%esp)
	call	_generatePaths
	movl	-56(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-48(%ebp), %eax
	movl	%eax, (%esp)
	call	_generateRoomObj
	movl	%edi, %esp
	nop
	leal	-12(%ebp), %esp
	popl	%ebx
	.cfi_restore 3
	popl	%esi
	.cfi_restore 6
	popl	%edi
	.cfi_restore 7
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE21:
	.globl	_generatePaths
	.def	_generatePaths;	.scl	2;	.type	32;	.endef
_generatePaths:
LFB22:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$120, %esp
	movl	$0, -12(%ebp)
	jmp	L30
L34:
	movl	$1000, -24(%ebp)
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %ecx
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	8(%eax), %eax
	shrl	%eax
	addl	%ecx, %eax
	movl	%eax, -32(%ebp)
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	4(%eax), %ecx
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	12(%eax), %eax
	shrl	%eax
	addl	%ecx, %eax
	movl	%eax, -36(%ebp)
	movl	$0, -16(%ebp)
	jmp	L31
L33:
	movl	-16(%ebp), %eax
	cmpl	-12(%ebp), %eax
	je	L32
	movl	-16(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %ecx
	movl	-16(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	8(%eax), %eax
	shrl	%eax
	addl	%ecx, %eax
	movl	%eax, -40(%ebp)
	movl	-16(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	4(%eax), %ecx
	movl	-16(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	12(%eax), %eax
	shrl	%eax
	addl	%ecx, %eax
	movl	%eax, -44(%ebp)
	movl	-40(%ebp), %eax
	subl	-32(%ebp), %eax
	movl	%eax, %edx
	movl	-40(%ebp), %eax
	subl	-32(%ebp), %eax
	imull	%eax, %edx
	movl	-44(%ebp), %eax
	subl	-36(%ebp), %eax
	movl	%eax, %ecx
	movl	-44(%ebp), %eax
	subl	-36(%ebp), %eax
	imull	%ecx, %eax
	addl	%edx, %eax
	movl	%eax, -80(%ebp)
	fildl	-80(%ebp)
	fstpl	(%esp)
	call	_sqrt
	fnstcw	-74(%ebp)
	movzwl	-74(%ebp), %eax
	movb	$12, %ah
	movw	%ax, -76(%ebp)
	fldcw	-76(%ebp)
	fistpl	-48(%ebp)
	fldcw	-74(%ebp)
	movl	-48(%ebp), %eax
	cmpl	-24(%ebp), %eax
	jge	L32
	movl	-16(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movzbl	16(%eax), %eax
	xorl	$1, %eax
	testb	%al, %al
	je	L32
	movl	-48(%ebp), %eax
	movl	%eax, -24(%ebp)
	movl	-16(%ebp), %eax
	movl	%eax, -20(%ebp)
L32:
	addl	$1, -16(%ebp)
L31:
	movl	-16(%ebp), %eax
	cmpl	8(%ebp), %eax
	jl	L33
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movb	$1, 16(%eax)
	movl	-20(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %ecx
	movl	-20(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	8(%eax), %eax
	shrl	%eax
	addl	%ecx, %eax
	movl	%eax, -40(%ebp)
	movl	-20(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	4(%eax), %ecx
	movl	-20(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	12(%eax), %eax
	shrl	%eax
	addl	%ecx, %eax
	movl	%eax, -44(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, 24(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 20(%esp)
	movl	-20(%ebp), %eax
	movl	%eax, 16(%esp)
	movl	-44(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-40(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-36(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-32(%ebp), %eax
	movl	%eax, (%esp)
	call	_buildPath
	addl	$1, -12(%ebp)
L30:
	movl	-12(%ebp), %eax
	cmpl	8(%ebp), %eax
	jl	L34
	movl	$3, 4(%esp)
	movl	$1, (%esp)
	call	_getRandInt
	movl	%eax, -52(%ebp)
	movl	$0, -12(%ebp)
	jmp	L35
L38:
	movl	8(%ebp), %eax
	subl	$1, %eax
	movl	%eax, 4(%esp)
	movl	$0, (%esp)
	call	_getRandInt
	movl	%eax, -56(%ebp)
	movl	8(%ebp), %eax
	subl	$1, %eax
	movl	%eax, 4(%esp)
	movl	$0, (%esp)
	call	_getRandInt
	movl	%eax, -28(%ebp)
	jmp	L36
L37:
	movl	8(%ebp), %eax
	subl	$1, %eax
	movl	%eax, 4(%esp)
	movl	$0, (%esp)
	call	_getRandInt
	movl	%eax, -28(%ebp)
L36:
	movl	-56(%ebp), %eax
	cmpl	-28(%ebp), %eax
	je	L37
	movl	-56(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %ecx
	movl	-56(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	8(%eax), %eax
	shrl	%eax
	addl	%ecx, %eax
	movl	%eax, -60(%ebp)
	movl	-56(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	4(%eax), %ecx
	movl	-56(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	12(%eax), %eax
	shrl	%eax
	addl	%ecx, %eax
	movl	%eax, -64(%ebp)
	movl	-28(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %ecx
	movl	-28(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	8(%eax), %eax
	shrl	%eax
	addl	%ecx, %eax
	movl	%eax, -68(%ebp)
	movl	-28(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	4(%eax), %ecx
	movl	-28(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	12(%eax), %eax
	shrl	%eax
	addl	%ecx, %eax
	movl	%eax, -72(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, 24(%esp)
	movl	8(%ebp), %eax
	movl	%eax, 20(%esp)
	movl	-28(%ebp), %eax
	movl	%eax, 16(%esp)
	movl	-72(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	-68(%ebp), %eax
	movl	%eax, 8(%esp)
	movl	-64(%ebp), %eax
	movl	%eax, 4(%esp)
	movl	-60(%ebp), %eax
	movl	%eax, (%esp)
	call	_buildPath
	addl	$1, -12(%ebp)
L35:
	movl	-12(%ebp), %eax
	cmpl	-52(%ebp), %eax
	jl	L38
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE22:
	.globl	_generateRoomObj
	.def	_generateRoomObj;	.scl	2;	.type	32;	.endef
_generateRoomObj:
LFB23:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	8(%ebp), %eax
	subl	$1, %eax
	movl	%eax, 4(%esp)
	movl	$0, (%esp)
	call	_getRandInt
	movl	%eax, -16(%ebp)
	movl	8(%ebp), %eax
	subl	$1, %eax
	movl	%eax, 4(%esp)
	movl	$0, (%esp)
	call	_getRandInt
	movl	%eax, -12(%ebp)
	jmp	L40
L41:
	movl	8(%ebp), %eax
	subl	$1, %eax
	movl	%eax, 4(%esp)
	movl	$0, (%esp)
	call	_getRandInt
	movl	%eax, -12(%ebp)
L40:
	movl	-12(%ebp), %eax
	cmpl	-16(%ebp), %eax
	je	L41
	movl	-16(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	8(%eax), %eax
	subl	$2, %eax
	movl	%eax, 4(%esp)
	movl	$1, (%esp)
	call	_getRandInt
	movl	%eax, -20(%ebp)
	movl	-16(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	12(%eax), %eax
	subl	$2, %eax
	movl	%eax, 4(%esp)
	movl	$1, (%esp)
	call	_getRandInt
	movl	%eax, -24(%ebp)
	movl	_map, %ecx
	movl	-16(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	4(%eax), %edx
	movl	-24(%ebp), %eax
	addl	%edx, %eax
	sall	$2, %eax
	addl	%ecx, %eax
	movl	(%eax), %ecx
	movl	-16(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %edx
	movl	-20(%ebp), %eax
	addl	%edx, %eax
	sall	$3, %eax
	addl	%ecx, %eax
	movl	$62, %edx
	movb	%dl, (%eax)
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	8(%eax), %eax
	subl	$2, %eax
	movl	%eax, 4(%esp)
	movl	$1, (%esp)
	call	_getRandInt
	movl	%eax, -20(%ebp)
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	12(%eax), %eax
	subl	$2, %eax
	movl	%eax, 4(%esp)
	movl	$1, (%esp)
	call	_getRandInt
	movl	%eax, -24(%ebp)
	movl	_map, %ecx
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	4(%eax), %edx
	movl	-24(%ebp), %eax
	addl	%edx, %eax
	sall	$2, %eax
	addl	%ecx, %eax
	movl	(%eax), %ecx
	movl	-12(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	12(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %edx
	movl	-20(%ebp), %eax
	addl	%edx, %eax
	sall	$3, %eax
	addl	%ecx, %eax
	movl	$60, %edx
	movb	%dl, (%eax)
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE23:
	.globl	_buildPath
	.def	_buildPath;	.scl	2;	.type	32;	.endef
_buildPath:
LFB24:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$68, %esp
	.cfi_offset 3, -12
	movl	8(%ebp), %eax
	cmpl	16(%ebp), %eax
	jg	L43
	movl	$1, %eax
	jmp	L44
L43:
	movl	$-1, %eax
L44:
	movl	%eax, -24(%ebp)
	movl	12(%ebp), %eax
	cmpl	20(%ebp), %eax
	jg	L45
	movl	$1, %eax
	jmp	L46
L45:
	movl	$-1, %eax
L46:
	movl	%eax, -28(%ebp)
	movb	$0, -17(%ebp)
	movl	8(%ebp), %eax
	movl	%eax, -12(%ebp)
	movl	12(%ebp), %eax
	movl	%eax, -16(%ebp)
	jmp	L47
L67:
	movl	_map, %eax
	movl	-16(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$3, %edx
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %edx
	movl	$46, %eax
	movsbl	%al, %eax
	cmpl	%eax, %edx
	je	L48
	movl	_map, %eax
	movl	-16(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$3, %edx
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %edx
	movl	$35, %eax
	movsbl	%al, %eax
	cmpl	%eax, %edx
	je	L48
	movl	_map, %eax
	movl	-16(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$3, %edx
	addl	%edx, %eax
	movl	$35, %edx
	movb	%dl, (%eax)
	movl	-12(%ebp), %eax
	cmpl	16(%ebp), %eax
	jne	L49
	movl	-28(%ebp), %eax
	addl	%eax, -16(%ebp)
	jmp	L50
L49:
	movl	-16(%ebp), %eax
	cmpl	20(%ebp), %eax
	jne	L51
	movl	-24(%ebp), %eax
	addl	%eax, -12(%ebp)
	jmp	L50
L51:
	movl	16(%ebp), %eax
	subl	-12(%ebp), %eax
	movl	%eax, %edx
	movl	-24(%ebp), %eax
	leal	(%edx,%eax), %ecx
	movl	16(%ebp), %eax
	subl	-12(%ebp), %eax
	movl	%eax, %edx
	movl	-24(%ebp), %eax
	addl	%edx, %eax
	imull	%eax, %ecx
	movl	%ecx, %edx
	movl	20(%ebp), %eax
	subl	-16(%ebp), %eax
	movl	%eax, %ecx
	movl	20(%ebp), %eax
	subl	-16(%ebp), %eax
	imull	%ecx, %eax
	addl	%edx, %eax
	movl	%eax, -48(%ebp)
	fildl	-48(%ebp)
	fstpl	(%esp)
	call	_sqrt
	fstpl	-48(%ebp)
	movl	16(%ebp), %eax
	subl	-12(%ebp), %eax
	movl	%eax, %edx
	movl	16(%ebp), %eax
	subl	-12(%ebp), %eax
	imull	%eax, %edx
	movl	20(%ebp), %eax
	subl	-16(%ebp), %eax
	movl	%eax, %ecx
	movl	-28(%ebp), %eax
	leal	(%ecx,%eax), %ebx
	movl	20(%ebp), %eax
	subl	-16(%ebp), %eax
	movl	%eax, %ecx
	movl	-28(%ebp), %eax
	addl	%ecx, %eax
	imull	%ebx, %eax
	addl	%edx, %eax
	movl	%eax, -52(%ebp)
	fildl	-52(%ebp)
	fstpl	(%esp)
	call	_sqrt
	fldl	-48(%ebp)
	fxch	%st(1)
	fucompp
	fnstsw	%ax
	sahf
	jbe	L69
	movl	-28(%ebp), %eax
	addl	%eax, -16(%ebp)
	jmp	L50
L69:
	movl	_map, %eax
	movl	-16(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %ecx
	movl	-24(%ebp), %edx
	addl	%ecx, %edx
	sall	$3, %edx
	addl	%edx, %eax
	movl	4(%eax), %edx
	movl	_map, %eax
	movl	-16(%ebp), %ebx
	movl	-28(%ebp), %ecx
	addl	%ebx, %ecx
	sall	$2, %ecx
	addl	%ecx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %ecx
	sall	$3, %ecx
	addl	%ecx, %eax
	movl	4(%eax), %eax
	cmpl	%eax, %edx
	jnb	L54
	movl	-24(%ebp), %eax
	addl	%eax, -12(%ebp)
	jmp	L50
L54:
	movl	-28(%ebp), %eax
	addl	%eax, -16(%ebp)
L50:
	cmpl	$3, -16(%ebp)
	jle	L55
	movl	$20, %eax
	subl	$3, %eax
	cmpl	-16(%ebp), %eax
	jle	L55
	movl	_map, %eax
	movl	-16(%ebp), %edx
	addl	$2, %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$3, %edx
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %edx
	movl	$35, %eax
	movsbl	%al, %eax
	cmpl	%eax, %edx
	je	L56
	movl	_map, %eax
	movl	-16(%ebp), %edx
	addl	$2, %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$3, %edx
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %edx
	movl	$46, %eax
	movsbl	%al, %eax
	cmpl	%eax, %edx
	jne	L57
L56:
	movl	_map, %eax
	movl	-16(%ebp), %edx
	addl	$1, %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$3, %edx
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %edx
	movl	$46, %eax
	movsbl	%al, %eax
	cmpl	%eax, %edx
	je	L57
	movl	_map, %eax
	movl	-16(%ebp), %edx
	addl	$1, %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$3, %edx
	addl	%edx, %eax
	movl	4(%eax), %eax
	cmpl	$24, %eax
	ja	L57
	movl	_map, %eax
	movl	-16(%ebp), %edx
	addl	$1, %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$3, %edx
	addl	%edx, %eax
	movl	$35, %edx
	movb	%dl, (%eax)
L57:
	movl	_map, %eax
	movl	-16(%ebp), %edx
	addl	$1073741822, %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$3, %edx
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %edx
	movl	$35, %eax
	movsbl	%al, %eax
	cmpl	%eax, %edx
	je	L58
	movl	_map, %eax
	movl	-16(%ebp), %edx
	addl	$1073741822, %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$3, %edx
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %edx
	movl	$46, %eax
	movsbl	%al, %eax
	cmpl	%eax, %edx
	jne	L55
L58:
	movl	_map, %eax
	movl	-16(%ebp), %edx
	addl	$1073741823, %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$3, %edx
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %edx
	movl	$46, %eax
	movsbl	%al, %eax
	cmpl	%eax, %edx
	je	L55
	movl	_map, %eax
	movl	-16(%ebp), %edx
	addl	$1073741823, %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$3, %edx
	addl	%edx, %eax
	movl	4(%eax), %eax
	cmpl	$24, %eax
	ja	L55
	movl	_map, %eax
	movl	-16(%ebp), %edx
	addl	$1073741823, %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$3, %edx
	addl	%edx, %eax
	movl	$35, %edx
	movb	%dl, (%eax)
L55:
	cmpl	$3, -12(%ebp)
	jle	L47
	movl	$79, %eax
	subl	$3, %eax
	cmpl	-12(%ebp), %eax
	jle	L47
	movl	_map, %eax
	movl	-16(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	addl	$2, %edx
	sall	$3, %edx
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %edx
	movl	$35, %eax
	movsbl	%al, %eax
	cmpl	%eax, %edx
	jne	L60
	movl	_map, %eax
	movl	-16(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$3, %edx
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %edx
	movl	$35, %eax
	movsbl	%al, %eax
	cmpl	%eax, %edx
	jne	L60
	movl	_map, %eax
	movl	-16(%ebp), %edx
	addl	$2, %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	sall	$3, %edx
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %edx
	movl	$35, %eax
	movsbl	%al, %eax
	cmpl	%eax, %edx
	jne	L60
	movl	_map, %eax
	movl	-16(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	addl	$2, %edx
	sall	$3, %edx
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %edx
	movl	$35, %eax
	movsbl	%al, %eax
	cmpl	%eax, %edx
	je	L61
	movl	_map, %eax
	movl	-16(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	addl	$2, %edx
	sall	$3, %edx
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %edx
	movl	$46, %eax
	movsbl	%al, %eax
	cmpl	%eax, %edx
	jne	L60
L61:
	movl	_map, %eax
	movl	-16(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	addl	$1, %edx
	sall	$3, %edx
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %edx
	movl	$46, %eax
	movsbl	%al, %eax
	cmpl	%eax, %edx
	je	L60
	movl	_map, %eax
	movl	-16(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	addl	$1, %edx
	sall	$3, %edx
	addl	%edx, %eax
	movl	4(%eax), %eax
	cmpl	$24, %eax
	ja	L60
	movl	_map, %eax
	movl	-16(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	addl	$1, %edx
	sall	$3, %edx
	addl	%edx, %eax
	movl	$35, %edx
	movb	%dl, (%eax)
L60:
	movl	_map, %eax
	movl	-16(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	addl	$536870910, %edx
	sall	$3, %edx
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %edx
	movl	$35, %eax
	movsbl	%al, %eax
	cmpl	%eax, %edx
	je	L62
	movl	_map, %eax
	movl	-16(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	addl	$536870910, %edx
	sall	$3, %edx
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %edx
	movl	$46, %eax
	movsbl	%al, %eax
	cmpl	%eax, %edx
	jne	L47
L62:
	movl	_map, %eax
	movl	-16(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	addl	$536870911, %edx
	sall	$3, %edx
	addl	%edx, %eax
	movzbl	(%eax), %eax
	movzbl	%al, %edx
	movl	$46, %eax
	movsbl	%al, %eax
	cmpl	%eax, %edx
	je	L47
	movl	_map, %eax
	movl	-16(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	addl	$536870911, %edx
	sall	$3, %edx
	addl	%edx, %eax
	movl	4(%eax), %eax
	cmpl	$24, %eax
	ja	L47
	movl	_map, %eax
	movl	-16(%ebp), %edx
	sall	$2, %edx
	addl	%edx, %eax
	movl	(%eax), %eax
	movl	-12(%ebp), %edx
	addl	$536870911, %edx
	sall	$3, %edx
	addl	%edx, %eax
	movl	$35, %edx
	movb	%dl, (%eax)
	jmp	L47
L48:
	movl	24(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	32(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %edx
	movl	-12(%ebp), %eax
	cmpl	%eax, %edx
	jnb	L63
	movl	24(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	32(%ebp), %eax
	addl	%edx, %eax
	movl	(%eax), %ecx
	movl	24(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	32(%ebp), %eax
	addl	%edx, %eax
	movl	8(%eax), %eax
	leal	(%ecx,%eax), %edx
	movl	-12(%ebp), %eax
	cmpl	%eax, %edx
	jbe	L63
	movl	24(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	32(%ebp), %eax
	addl	%edx, %eax
	movl	4(%eax), %edx
	movl	-16(%ebp), %eax
	cmpl	%eax, %edx
	jnb	L63
	movl	24(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	32(%ebp), %eax
	addl	%edx, %eax
	movl	4(%eax), %ecx
	movl	24(%ebp), %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	sall	$2, %eax
	movl	%eax, %edx
	movl	32(%ebp), %eax
	addl	%edx, %eax
	movl	12(%eax), %eax
	leal	(%ecx,%eax), %edx
	movl	-16(%ebp), %eax
	cmpl	%eax, %edx
	jbe	L63
	movb	$1, -17(%ebp)
	jmp	L47
L63:
	movl	-12(%ebp), %eax
	cmpl	16(%ebp), %eax
	jne	L64
	movl	-28(%ebp), %eax
	addl	%eax, -16(%ebp)
	jmp	L47
L64:
	movl	-16(%ebp), %eax
	cmpl	20(%ebp), %eax
	jne	L65
	movl	-24(%ebp), %eax
	addl	%eax, -12(%ebp)
	jmp	L47
L65:
	movl	16(%ebp), %eax
	imull	-24(%ebp), %eax
	movl	%eax, %edx
	movl	-12(%ebp), %eax
	leal	(%edx,%eax), %ecx
	movl	20(%ebp), %eax
	imull	-28(%ebp), %eax
	movl	%eax, %edx
	movl	-16(%ebp), %eax
	addl	%edx, %eax
	cmpl	%eax, %ecx
	jg	L66
	movl	-28(%ebp), %eax
	addl	%eax, -16(%ebp)
	jmp	L47
L66:
	movl	-24(%ebp), %eax
	addl	%eax, -12(%ebp)
L47:
	movzbl	-17(%ebp), %eax
	xorl	$1, %eax
	testb	%al, %al
	jne	L67
	nop
	addl	$68, %esp
	popl	%ebx
	.cfi_restore 3
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE24:
	.globl	_getRandInt
	.def	_getRandInt;	.scl	2;	.type	32;	.endef
_getRandInt:
LFB25:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	call	_rand
	movl	%eax, %edx
	movl	12(%ebp), %eax
	subl	8(%ebp), %eax
	leal	1(%eax), %ecx
	movl	%edx, %eax
	cltd
	idivl	%ecx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE25:
	.globl	_roomIntersect
	.def	_roomIntersect;	.scl	2;	.type	32;	.endef
_roomIntersect:
LFB26:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	leal	-1(%eax), %edx
	movl	28(%ebp), %eax
	cmpl	%eax, %edx
	jnb	L73
	movl	8(%ebp), %edx
	movl	16(%ebp), %eax
	leal	(%edx,%eax), %ecx
	movl	28(%ebp), %edx
	movl	36(%ebp), %eax
	addl	%edx, %eax
	cmpl	%eax, %ecx
	ja	L74
L73:
	movl	12(%ebp), %eax
	leal	-1(%eax), %edx
	movl	32(%ebp), %eax
	cmpl	%eax, %edx
	jnb	L75
	movl	12(%ebp), %edx
	movl	20(%ebp), %eax
	leal	(%edx,%eax), %ecx
	movl	32(%ebp), %edx
	movl	40(%ebp), %eax
	addl	%edx, %eax
	cmpl	%eax, %ecx
	ja	L74
L75:
	movl	28(%ebp), %eax
	movl	8(%ebp), %edx
	subl	$1, %edx
	cmpl	%edx, %eax
	jnb	L76
	movl	28(%ebp), %edx
	movl	36(%ebp), %eax
	leal	(%edx,%eax), %ecx
	movl	8(%ebp), %edx
	movl	16(%ebp), %eax
	addl	%edx, %eax
	subl	$1, %eax
	cmpl	%eax, %ecx
	ja	L74
L76:
	movl	32(%ebp), %eax
	movl	12(%ebp), %edx
	subl	$1, %edx
	cmpl	%edx, %eax
	jnb	L77
	movl	32(%ebp), %edx
	movl	40(%ebp), %eax
	leal	(%edx,%eax), %ecx
	movl	12(%ebp), %edx
	movl	20(%ebp), %eax
	addl	%edx, %eax
	subl	$1, %eax
	cmpl	%eax, %ecx
	ja	L74
L77:
	movl	8(%ebp), %eax
	leal	-1(%eax), %edx
	movl	28(%ebp), %eax
	cmpl	%eax, %edx
	jb	L78
	movl	8(%ebp), %eax
	leal	-1(%eax), %ecx
	movl	28(%ebp), %edx
	movl	36(%ebp), %eax
	addl	%edx, %eax
	cmpl	%eax, %ecx
	ja	L78
	movl	12(%ebp), %eax
	leal	-1(%eax), %edx
	movl	32(%ebp), %eax
	cmpl	%eax, %edx
	jb	L78
	movl	12(%ebp), %eax
	leal	-1(%eax), %ecx
	movl	32(%ebp), %edx
	movl	40(%ebp), %eax
	addl	%edx, %eax
	cmpl	%eax, %ecx
	jbe	L74
L78:
	movl	8(%ebp), %edx
	movl	16(%ebp), %eax
	addl	%eax, %edx
	movl	28(%ebp), %eax
	cmpl	%eax, %edx
	jb	L79
	movl	8(%ebp), %edx
	movl	16(%ebp), %eax
	leal	(%edx,%eax), %ecx
	movl	28(%ebp), %edx
	movl	36(%ebp), %eax
	addl	%edx, %eax
	cmpl	%eax, %ecx
	ja	L79
	movl	12(%ebp), %eax
	leal	-1(%eax), %edx
	movl	32(%ebp), %eax
	cmpl	%eax, %edx
	jb	L79
	movl	12(%ebp), %eax
	leal	-1(%eax), %ecx
	movl	32(%ebp), %edx
	movl	40(%ebp), %eax
	addl	%edx, %eax
	cmpl	%eax, %ecx
	jbe	L74
L79:
	movl	8(%ebp), %eax
	leal	-1(%eax), %edx
	movl	28(%ebp), %eax
	cmpl	%eax, %edx
	jb	L80
	movl	8(%ebp), %eax
	leal	-1(%eax), %ecx
	movl	28(%ebp), %edx
	movl	36(%ebp), %eax
	addl	%edx, %eax
	cmpl	%eax, %ecx
	ja	L80
	movl	12(%ebp), %edx
	movl	20(%ebp), %eax
	addl	%eax, %edx
	movl	32(%ebp), %eax
	cmpl	%eax, %edx
	jb	L80
	movl	12(%ebp), %edx
	movl	20(%ebp), %eax
	leal	(%edx,%eax), %ecx
	movl	32(%ebp), %edx
	movl	40(%ebp), %eax
	addl	%edx, %eax
	cmpl	%eax, %ecx
	jbe	L74
L80:
	movl	8(%ebp), %edx
	movl	16(%ebp), %eax
	addl	%eax, %edx
	movl	28(%ebp), %eax
	cmpl	%eax, %edx
	jb	L81
	movl	8(%ebp), %edx
	movl	16(%ebp), %eax
	leal	(%edx,%eax), %ecx
	movl	28(%ebp), %edx
	movl	36(%ebp), %eax
	addl	%edx, %eax
	cmpl	%eax, %ecx
	ja	L81
	movl	12(%ebp), %edx
	movl	20(%ebp), %eax
	addl	%eax, %edx
	movl	32(%ebp), %eax
	cmpl	%eax, %edx
	jb	L81
	movl	12(%ebp), %edx
	movl	20(%ebp), %eax
	leal	(%edx,%eax), %ecx
	movl	32(%ebp), %edx
	movl	40(%ebp), %eax
	addl	%edx, %eax
	cmpl	%eax, %ecx
	jbe	L74
L81:
	movl	28(%ebp), %eax
	movl	8(%ebp), %edx
	subl	$1, %edx
	cmpl	%edx, %eax
	jb	L82
	movl	28(%ebp), %eax
	movl	8(%ebp), %ecx
	movl	16(%ebp), %edx
	addl	%ecx, %edx
	subl	$1, %edx
	cmpl	%edx, %eax
	ja	L82
	movl	32(%ebp), %eax
	movl	12(%ebp), %edx
	subl	$1, %edx
	cmpl	%edx, %eax
	jb	L82
	movl	32(%ebp), %eax
	movl	12(%ebp), %ecx
	movl	20(%ebp), %edx
	addl	%ecx, %edx
	subl	$1, %edx
	cmpl	%edx, %eax
	jbe	L74
L82:
	movl	28(%ebp), %edx
	movl	36(%ebp), %eax
	addl	%eax, %edx
	movl	8(%ebp), %eax
	subl	$1, %eax
	cmpl	%eax, %edx
	jb	L83
	movl	28(%ebp), %edx
	movl	36(%ebp), %eax
	leal	(%edx,%eax), %ecx
	movl	8(%ebp), %edx
	movl	16(%ebp), %eax
	addl	%edx, %eax
	subl	$1, %eax
	cmpl	%eax, %ecx
	ja	L83
	movl	32(%ebp), %eax
	movl	12(%ebp), %edx
	subl	$1, %edx
	cmpl	%edx, %eax
	jb	L83
	movl	32(%ebp), %eax
	movl	12(%ebp), %ecx
	movl	20(%ebp), %edx
	addl	%ecx, %edx
	subl	$1, %edx
	cmpl	%edx, %eax
	jbe	L74
L83:
	movl	28(%ebp), %eax
	movl	8(%ebp), %edx
	subl	$1, %edx
	cmpl	%edx, %eax
	jb	L84
	movl	28(%ebp), %eax
	movl	8(%ebp), %ecx
	movl	16(%ebp), %edx
	addl	%ecx, %edx
	subl	$1, %edx
	cmpl	%edx, %eax
	ja	L84
	movl	32(%ebp), %edx
	movl	40(%ebp), %eax
	addl	%eax, %edx
	movl	12(%ebp), %eax
	subl	$1, %eax
	cmpl	%eax, %edx
	jb	L84
	movl	32(%ebp), %edx
	movl	40(%ebp), %eax
	leal	(%edx,%eax), %ecx
	movl	12(%ebp), %edx
	movl	20(%ebp), %eax
	addl	%edx, %eax
	subl	$1, %eax
	cmpl	%eax, %ecx
	jbe	L74
L84:
	movl	28(%ebp), %edx
	movl	36(%ebp), %eax
	addl	%eax, %edx
	movl	8(%ebp), %eax
	subl	$1, %eax
	cmpl	%eax, %edx
	jb	L85
	movl	28(%ebp), %edx
	movl	36(%ebp), %eax
	leal	(%edx,%eax), %ecx
	movl	8(%ebp), %edx
	movl	16(%ebp), %eax
	addl	%edx, %eax
	subl	$1, %eax
	cmpl	%eax, %ecx
	ja	L85
	movl	32(%ebp), %edx
	movl	40(%ebp), %eax
	addl	%eax, %edx
	movl	12(%ebp), %eax
	subl	$1, %eax
	cmpl	%eax, %edx
	jb	L85
	movl	32(%ebp), %edx
	movl	40(%ebp), %eax
	leal	(%edx,%eax), %ecx
	movl	12(%ebp), %edx
	movl	20(%ebp), %eax
	addl	%edx, %eax
	subl	$1, %eax
	cmpl	%eax, %ecx
	ja	L85
L74:
	movl	$1, %eax
	jmp	L86
L85:
	movl	$0, %eax
L86:
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE26:
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_time;	.scl	2;	.type	32;	.endef
	.def	_srand;	.scl	2;	.type	32;	.endef
	.def	_malloc;	.scl	2;	.type	32;	.endef
	.def	_free;	.scl	2;	.type	32;	.endef
	.def	_putchar;	.scl	2;	.type	32;	.endef
	.def	_puts;	.scl	2;	.type	32;	.endef
	.def	_sqrt;	.scl	2;	.type	32;	.endef
	.def	_rand;	.scl	2;	.type	32;	.endef
