#!/bin/sh
rm diff_disassembler
for f in ./*.s
	do asm_s=$(basename $f)
	asm_cor="$(basename $f .s).cor"
	dis_s="$(basename $f .s)_dis.s"
	dis_cor="$(basename $f .s)_dis.cor"
	./asm $asm_s
	hexdump -vC $asm_cor > asm_dif
	mv $asm_cor $dis_cor
	./disassembler $dis_cor
	./asm $dis_s
	hexdump -vC $dis_cor > dis_dif
	echo "diff = \n"
	diff asm_dif dis_dif
	echo "\n\n diff $asm_s \n" >> "diff_disassembler"
	diff asm_dif dis_dif >> "diff_disassembler"
	rm $dis_cor $dis_s "asm_dif" "dis_dif"
	echo "\n\n"
done
