CC=g++
CFLAGS=-Wall
CFLAGS= -std=c++11
EXECUTABLE=list

DOXYGEN =doxygen
SOURCES = main.cpp task/subtask.cpp task/task.cpp platform/processor.cpp platform/platform.cpp task/taskset.cpp common/list.cpp analysis/analysis.cpp

SOURCESGEN = main_gen.cpp task/subtask.cpp task/task.cpp task/taskset.cpp common/list.cpp code_gen/subtask_code.cpp code_gen/task_code.cpp code_gen/taskset_code.cpp

list: common/list.o task/subtask.o task/task.o platform/platform.o platform/processor.o main.cpp
	$(CC) $(CFLAGS) -g -Wall -o $(EXECUTABLE) $(SOURCES)

%.o : %.cpp
	$(CC) -std=c++11 -c -o $@ $^

#subtask.o: task/subtask.hpp
#list.o: common/list.hpp

clean:
	rm -rf *.o *.gch $(EXECUTABLE)
	rm -rf common/*.o
	rm -rf task/*.o

leaks:
	valgrind --leak-check=yes ./$(EXECUTABLE)

docs: Doxyfile
	$(DOXYGEN) $^
