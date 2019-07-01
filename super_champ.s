.name	"Leeloo"
.comment "Multipass"


ld %4, r5
ld %300, r3 				#7bytes
st r1, 17 					#5
st r1, 38					#5

copy_values:
	ldi :copy_values, r2, r4 	#6
	live %17 					#5
	sti r4, r3, r2 				#5
	add r5, r2, r2 				#5
	and r2, %64, r16 			#8
	zjmp %:copy_values 			#4
	live %38					#5
	ld %0, r2					#7
	fork %250 					#4
	st r1, 6					#5
live_loop:
	live %6						#5
	zjmp %-5					#4
