CC = gcc
CFLAGS = -Wall -g

all: reminder

reminder: main.o interact.o linked_list.o reminder.o
	$(CC) $(CFLAGS) -o reminder main.o interact.o linked_list.o reminder.o

main.o: main.c interact.h reminder.h linked_list.h
	$(CC) $(CFLAGS) -c main.c

interact.o: interact.c interact.h reminder.h
	$(CC) $(CFLAGS) -c interact.c

linked_list.o: linked_list.c linked_list.h
	$(CC) $(CFLAGS) -c linked_list.c

reminder.o: reminder.c reminder.h linked_list.h
	$(CC) $(CFLAGS) -c reminder.c

clean:
	rm -f *.o reminder
