# Space Invader Game Simulation

## Description
This is a game simulating the space invader, consists of the following part.
### enemy decoding
The enemy's color/type and start point/velocity is encoded in *.sa file.
### store in linked list
The enemy info is stored inside a self made linked list.
### bounce/hit simulation
The enemy will bounce when it hits the wall, and the laser from bolt will delete the enemy when it hits the enemy.

# result
You could change from graphic mode to text mode in `debug.h`

## Graphic Mode
### Video Link
![Demo](https://youtu.be/ioLIfdPtMwk)

## Text Mode
sample output
```bash
allocate_alien: 1 allocated
DIAGNOSTIC: 1 nodes allocated.
allocate_alien: 2 allocated
DIAGNOSTIC: 2 nodes allocated.
Input terminated: scanf returned -1

Code       T C Pts ( __X_____, __Y_____) ( __VX____,  __VY____) ET=  0.00000
0x032F3F1F 3 1  50 (-25.00000, 19.50000) (-32.00000, -16.00000)
0x096F3F3F 3 3 150 ( 30.00000, 16.00000) ( 32.00000, -16.00000)

Flying saucer worth 150 points escapes at ET = 0.28125!
free_alien: 1 freed
DIAGNOSTIC: 1 nodes freed.
Flying saucer worth 50 points escapes at ET = 0.43750!
free_alien: 2 freed
DIAGNOSTIC: 2 nodes freed.


Victory! No attackers remain at ET = 0.43750
Total score is 0 points
Clearing the attacking list... 
    ... 0 cleared
Total run time is 0.000171423 seconds.
```



## Installation
### Prerequisite
* gcc
* make
### Compile
```bash
make main
```
### Run
you could replace bounce.sa with any other *.sa file
```bash
./main < bounce.sa
```
### Troubleshooting
If you encounter the following error, please try to compile again adding `-no-pie` to makefile.
```bash
/usr/bin/ld: ./libinvaders.a(libinvaders.o): relocation R_X86_64_32S against `.bss' can not be used when making a PIE object; recompile with -fPIE
/usr/bin/ld: ./libinvaders.a(n2.o): relocation R_X86_64_32 against `.rodata' can not be used when making a PIE object; recompile with -fPIE
/usr/bin/ld: ./liblinkedlist.a(insert.o): relocation R_X86_64_32 against `.rodata' can not be used when making a PIE object; recompile with -fPIE
/usr/bin/ld: ./liblinkedlist.a(deleteSome.o): relocation R_X86_64_32 against `.rodata' can not be used when making a PIE object; recompile with -fPIE
collect2: error: ld returned 1 exit status
make: *** [Makefile:10: main] Error 1
```
EG.
`gcc -ansi -pedantic -g -o $@ $^ -L. -linvaders -llinkedlist -lncurses
`
