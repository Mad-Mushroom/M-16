nop
hlt
aluStuff:
	add &a, 0xffff
	adr &a, &b
	dec &b, 0xffff
	der &c, &b

otherRegStuff:
	set &d, 0xffff

jumpStuff:
	jmp jumpStuff
	jmr &a
	jmz aluStuff
	jmo otherRegStuff

compareStuff:
	cmp &a, 0xffff
	cmr &a, &c
	je jumpStuff

ioStuff:
	inb &a
