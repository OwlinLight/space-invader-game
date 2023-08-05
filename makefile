# author: kirby
# modified: Sitao Tong
all:
	make -r main
	all.sh

# test linkList with string 
linkListTest: linkListTest.o
	gcc -ansi -pedantic -g -o $@ $^ -L. -linvaders -llinkedlist -lncurses

# test allocate and copy with struct
memoryTest: memoryTest.o memory.o function.o motion.o
	gcc -ansi -pedantic -g -o $@ $^ -L. -linvaders -llinkedlist -lncurses

# test linkelist with alien
aliensTest: aliensTest.o code.o
	gcc -ansi -pedantic -g -o $@ $^ -L. -linvaders -llinkedlist -lncurses

# test sim struct
simTest: simTest.o code.o
	gcc -ansi -pedantic -g -o $@ $^ -L. -linvaders -llinkedlist -lncurses

# test attack on alien
attackTest: attackTest.o code.o
	gcc -ansi -pedantic -g -o $@ $^ -L. -linvaders -llinkedlist -lncurses


main: main.o code.o function.o memory.o motion.o output.o
	gcc -ansi -pedantic -g -o $@ $^ -L. -linvaders -llinkedlist -lncurses


main.zip: makefile *.c *.h *.a *.sh *.sa README_LAB3
# $^ inludes all the dependencies, you only need to change dependcies above
	zip $@ $^
	rm -rf install
	mkdir install
	unzip main.zip -d install
	make -C install main

p1: p1.o 
	gcc -ansi -pedantic -g -o $@ $^ 

# this is our master compiler rule to generate .o files.
# It needs all 4 warnings

%.o:%.c *.h
	gcc -ansi -pedantic -Wimplicit-function-declaration -Wreturn-type -g -c $< -o $@


