build: editor

editor: main.o queue.o stack.o double_linked_list.o commands.o
	gcc main.o queue.o stack.o double_linked_list.o commands.o -o editor

main.o: main.c

queue.o: queue.h queue.c

stack.o: stack.h stack.c

double_linked_list.o: double_linked_list.h double_linked_list.c

commands.o: commands.h commands.c

run:
	./editor

memcheck:
	valgrind --leak-check=full ./editor

make clean:
	rm -f *.o editor
