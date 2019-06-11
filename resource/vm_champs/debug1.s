.name	"Leeloo"
.comment "Multipass"
	
store:	live %100

tst:	ld %1, r1
		st r1, 40
		ldi %-17, r1 , r2
		sti r2, %1, r4
		st	r4, 10

