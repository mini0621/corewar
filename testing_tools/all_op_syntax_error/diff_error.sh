#!/bin/sh
for f in ./*.s
	do b=$(basename $f)
	./asm $b
	./asm_ref $b
	echo "\n\n"
done
