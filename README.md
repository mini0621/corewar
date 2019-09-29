# corewar
42 project corewar

"Core War is a 1984 programming game created by D. G. Jones and A. K. Dewdney in which two or more battle programs (called "warriors") compete for control of a virtual computer. These battle programs are written in an abstract assembly language called Redcode."
[wikipedia](https://en.wikipedia.org/wiki/Core_War)


![corewar_infinite_zorkling_vs_car](https://github.com/mini0621/corewar/media/corewar.gif)

## description
the 42 corewar project includes assembly compiler, arena vm, and a champion.

#### asm
asm is an assembly compiler which compiles a champion from .s file to .cor file.


#### corewar
corewar is an arena vm, where .cor binary files fights against each other inside the memory of 4096 bytes.

#### champion
our champion, infinite_zorkling.


##### bornus
assembler error messages
vm debug mode
vm visualizer
disassembler 
disassembler visualizer

## requirements
ncurses for visualizer

## usage
```
make
usage: ./asm 'sourcefile.s

Usage:./corewar [-d N]  [-v] [-de N] [-n N] <champion1.cor> <...>
### CONTESTANT ######################################################
your_champion.cor: Champion compiled with the asm
-n (0 < N < INTMAX)    :  Set champion number for the next champion
### DUMP ############################################################
-dump (0 < N < ULLMAX) :  Dumps memory after N cycles then exits
### DEBUG OUTPUT MODE ###############################################
-de (0 < N < INTMAX)  1:  cycle number
                      2:  death logs
                      4:  live logs
                      8:  load logs
                     16:  store logs
                     32:  logical op logs
                     64:  jump, fork logs
### PRINT OFF MODE ##################################################
-p                   1 :  live comment off
                     2 :  aff comment off
                     3 :  all comment off
### VISUAL MODE #####################################################
-v                   Ncurses visualizer mode
#####################################################################
```



## author
[Alblfbv](https://github.com/Alblfbv)
[Mthandazo42](https://github.com/Mthandazo42)
[sunca7](https://github.com/sunca7)
[mini0621](https://github.com/mini0621)
