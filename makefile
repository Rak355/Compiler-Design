src = ./src
obj = ./obj
inc = ./inc

clean:
	clear
	rm -f obj/*.o

compile: clean
	gcc -c src/main.c -o obj/main.o -I inc
	gcc -c src/tokenizer.c -o obj/tokenizer.o -I inc
	gcc obj/main.o obj/tokenizer.o -o obj/final.o

run: compile
	obj/final.o
