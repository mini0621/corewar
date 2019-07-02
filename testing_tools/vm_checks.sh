#!/bin/sh
for f in ./*.s
	do b=$(basename $f)
	c="$(basename $f .s).cor"
	echo "$b"
	./asm $b
	./$1 $c
	rm $c
	echo "\n\n"
done
