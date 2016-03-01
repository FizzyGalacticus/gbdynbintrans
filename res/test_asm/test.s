_main::
NOP
LD A,#0
LD B,#1
LD C,#2
LD D,#3
LD E,#4
LD H,#5
LD L,#6
LD BC,#257 ;Both B & C should be 1
LD DE,#257 ;Both D & E should be 1
LD HL,#257 ;Both H & L should be 1
LD A,#255
SUB A,H
SUB A,E
SUB A,D
SUB A,C
SUB A,B
SUB A,A
SUB A,L
LD A,#1
LD B,#0
LD C,#0
LD D,#0
LD E,#0
LD H,#0
LD L,#0
loop:
LD L,H
LD H,E
LD E,D
LD D,C
LD C,B
LD B,A
LD A,L
ADD A,H
ADD A,E
ADD A,D
ADD A,C
ADD A,B
ADD A,A
ADD A,L
ADD HL,BC
ADD HL,DE
ADD HL,HL
ADD HL,SP
JP loop