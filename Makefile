CC=g++
CFLAGS=-Wall
CFLAGS= -std=c++11
EXECUTABLE=list

DOXYGEN =doxygen
SOURCES = main.cpp task/subtask.cpp task/task.cpp platform/processor.cpp platform/platform.cpp task/taskset.cpp common/list.cpp analysis/analysis.cpp task/buffer.cpp
SOURCESGEN = main_gen.cpp task/subtask.cpp task/task.cpp task/taskset.cpp task/buffer.cpp task/comm.cpp  common/list.cpp code_gen/subtask_code.cpp code_gen/task_code.cpp code_gen/taskset_code.cpp

list: common/list.o task/subtask.o task/task.o task/buffer.o task/comm.o  platform/platform.o platform/processor.o main.cpp
	$(CC) $(CFLAGS) -g -Wall -o $(EXECUTABLE) $(SOURCES)

gen: common/list.o task/subtask.o task/task.o task/buffer.o platform/platform.o platform/processor.o main.cpp
	$(CC) $(CFLAGS) -g -Wall -o gen $(SOURCESGEN)

%.o : %.cpp
	$(CC) -std=c++11 -c -o $@ $^

clean:
	rm -rf *.o *.gch $(EXECUTABLE)
	rm -rf common/*.o
	rm -rf task/*.o
	rm -rf platform/*.o

leaks:
	valgrind --leak-check=yes ./$(EXECUTABLE)

docs: Doxyfile
	$(DOXYGEN) $^
