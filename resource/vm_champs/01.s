.name	"Leeloo"
.comment "Multipass"
	
tst:	live %-2
		ld :tst, r1
		lld %-4, r2
tst1:	st r1, r5
		st r2, r6
		st r5, 30
		st r6, 40

