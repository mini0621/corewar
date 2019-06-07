.name	"Leeloo"
.comment "Multipass"
	
tst:	ld %100, r2
		ld %0, r1
		ld %100, r3
		sub r2, r3, r4
		sub r1, r3, r5
		st r4, 45
		st r5, 52
