all: main.out
main.out: hdag_driver.o hdag_parser.o hdag_scanner.o ../task/buffer.o ../task/taskset.o ../task/comm.o ../common/list.o ../common/common.o ../task/subtask.o ../task/task.o  main.o
	g++ -o main.out hdag_driver.o hdag_parser.o ../task/buffer.o ../task/taskset.o ../task/comm.o hdag_scanner.o main.o ../task/subtask.o ../task/task.o ../common/list.o ../common/common.o
hdag_parser.o: hdag_parser.cc hdag_parser.hh hdag_driver.hh
	g++ -c hdag_parser.cc
hdag_parser.cc hdag_parser.hh: hdag_parser.yy
	bison --defines=hdag_parser.hh -o hdag_parser.cc hdag_parser.yy
hdag_scanner.o: hdag_scanner.cc hdag_parser.hh hdag_driver.hh
	g++ -c hdag_scanner.cc
list.o: ../common/list.hpp
	g++ -c ../common/list.hpp
common.o: ../common/common.cpp
	g++ -c ../common/common.cpp
comm.o: ../task/comm.cpp
	g++ -c ../task/comm.cpp
buffer.o: ../task/buffer.cpp
	g++ -c ../task/buffer.cpp
subtask.o: ../task/subtask.cpp
	g++ -c ../task/subtask.cpp
taskset.o: ../task/taskset.cpp
	g++ -c ../task/taskset.cpp
task.o: ../task/task.cpp
	g++ -c ../task/task.cpp
hdag_scanner.cc: hdag_scanner.ll
	flex -o hdag_scanner.cc hdag_scanner.ll
hdag_driver.o: hdag_driver.cc hdag_driver.hh hdag_parser.hh
	g++ -c hdag_driver.cc

main.o: main.cc
	g++ -c main.cc

.PHONY: clean
clean:
	rm *.o hdag_parser.hh hdag_parser.cc hdag_scanner.cc location.hh position.hh stack.hh main.out ../task/*.o ../common/*.o
