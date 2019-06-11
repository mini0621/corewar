.name	"Leeloo"
.comment "Multipass"
	
store:	live %100

tst:	ld %1, r1
		ld %2, r2
		add r1, r2, r3
		sub r1, r1, r4
		and r1, r2, r5
		and r1, r3, r5
		and r1, %2, r5
		or	r1, r2, r5
		or	r1, r4, r5
		xor r1, r2, r5
		xor r1, %0, r5
