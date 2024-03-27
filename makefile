calculator: main.o calc.o stack.o queue.o
	gcc -o calculator main.o calc.o stack.o queue.o -lm

main.o: main.c
	gcc -c -o main.o main.c

calc.o: calc.c
	gcc -c -o calc.o calc.c

stack.o: stack.c
	gcc -c -o stack.o stack.c

queue.o: queue.c
	gcc -c -o queue.o queue.c

clean:
	rm *.o calculator