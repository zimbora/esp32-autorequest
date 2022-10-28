

# additional flags
CXXFLAGS += -std=c++11

MACROS = -DDEBUG

all: autorequest

autorequest: init cp_autorequest make_autorequest run clean

init:
	mkdir ./tmp
	cp ./Arduino.h	 ./tmp/
	cp ./Arduino.cpp ./tmp/

cp_autorequest:
	cp ../src/autorequest.hpp ./tmp/
	cp ../src/autorequest.cpp ./tmp/

make_autorequest:
	@echo "Compiling.."
	clang++ $(CXXFLAGS) -DUNITTEST -DALARMTEST $(MACROS) ar_runner.cpp ./tmp/Arduino.cpp ./tmp/autorequest.cpp

run:
	@echo "Running test.."
	./a.out

clean:
	@echo "Cleaning up"
	rm -r ./tmp
	rm *.out
