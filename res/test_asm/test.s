_main::
NOP
LD A,#4
LD B,#0
LD C,#0
LD D,#0
LD E,#0
LD H,#0
LD L,#0
loop:
INC B
INC C
INC D
INC E
INC H
INC L
DEC L
DEC H
DEC E
DEC D
DEC C
DEC B
DEC A
JP NZ, loop