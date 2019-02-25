src = ./src
obj = ./obj
inc = ./inc

clean:
	rm -rf obj
	mkdir obj
	clear
	

compile: clean
	gcc -c src/main.c -o obj/main.o -I inc
	gcc -c src/lexer.c -o obj/lexer.o -I inc
	gcc obj/main.o obj/lexer.o -o obj/final.o

run: compile
	obj/final.o
