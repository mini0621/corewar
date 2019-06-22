.nae""
.comment""

entry:
fork	%-1
	st	-	r15, -5
live		%42
	fork	%1
	st		r1, 6
	live	%42
	fork	%1
ardeftgt:
