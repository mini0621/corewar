#!/bin/sh
for f in ./*.s
	do b=$(basename $f)
	c="$(basename $f .s).cor"
	echo "$b"
	./asm $b
	hexdump -vC $c > notre
	rm $c
	./asm_ref $b
	hexdump -vC $c > leur
	echo "diff = \n"
	diff leur notre
	echo "\n\n diff $c \n" >> "diff_cor"
	diff leur notre >> "diff_cor"
	rm $c "leur" "notre"
	echo "\n\n"
done
