CC = g++
CPPFLAGS = -std=c++11 -g -Wall
OBJTS = app.o group.o stack.o queue.o

app: $(OBJTS)

app.o: group.h stack.h queue.h

group.o: group.h

stack.o: stack.h group.h

queue.o: queue.h group.h

clean:
	rm app *.o
