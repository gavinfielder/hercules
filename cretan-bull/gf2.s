.name "railgun"
.comment "This is bound to hit something eventually"

ld %8, r2 ;iterate by this much
ld %1, r5 ;live command

ld %787432, r9 ;fork %1000
ld %12583065, r8 ;fork saboteur

fork %:agent2

ld %150, r3 ;start here
ld %146, r4  ;start here

loop:
		sti r1, %:live, %1
		;add r2, r3, r3
		;add r2, r4, r4
		;sti r1, %:loop, r3
		;sti r5, %:loop, r4
live:	live %1
		ld %0, r7 ;carry is 1
		zjmp %:loop

agent2:

st r5, 256

loop2:
		sti r1, %:live2, %1
		add r2, r0, r0
live2:	live %1
		fork %:saboteur
		ld %0, r7 ;carry is 1
		zjmp %:loop2

saboteur:
	ld 35, r16
	ld 35, r15
	ld 35, r14
	ld 35, r13
	ld 35, r12
	ld 35, r11
	ld 35, r10
	st r10, 256
	st r16, 256
	st r15, 256
	st r14, 256
	st r13, 256
	st r12, 256
	st r11, 256
	st r5, 900


